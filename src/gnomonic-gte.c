/*
 * libgnomonic - Gnomonic projection algorithms library
 *
 * Copyright (c) 2013-2014 FOXEL SA - http://foxel.ch
 * Please read <http://foxel.ch/license> for more information.
 *
 *
 * Author(s):
 *
 *      Nils Hamel <n.hamel@foxel.ch>
 *
 *
 * This file is part of the FOXEL project <http://foxel.ch>.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Additional Terms:
 *
 *      You are required to preserve legal notices and author attributions in
 *      that material or in the Appropriate Legal Notices displayed by works
 *      containing it.
 *
 *      You are required to attribute the work as explained in the "Usage and
 *      Attribution" section of <http://foxel.ch/license>.
 */


/*
    Source - Includes
 */

    # include "gnomonic-gte.h"

/*
    Source - Reprojection of gnomonic image back into equirectangluar image
 */

    lg_Void_t lg_gte(

        li_C8_t *   lgEqrIO,
        lg_Size_t   lgEqrWidth,
        lg_Size_t   lgEqrHeight,
        lg_Size_t   lgEqrLayer,
        li_C8_t *   lgRectIn,
        lg_Size_t   lgRectWidth,
        lg_Size_t   lgRectHeight,
        lg_Size_t   lgRectLayer,
        lg_Real_t   lgNadH,
        lg_Real_t   lgNadV,
        lg_Real_t   lgAppH,
        lg_Real_t   lgAppV,
        li_Method_t lgInter

    ) {

        /* Parsing variables */
        lg_Size_t lgDX = lg_Size_s( 0 );
        lg_Size_t lgDY = lg_Size_s( 0 );

        /* Projection variables */
        lg_Real_t lgPX = lg_Real_s( 0.0 );
        lg_Real_t lgPY = lg_Real_s( 0.0 );
        lg_Real_t lgAH = lg_Real_s( 0.0 );
        lg_Real_t lgAV = lg_Real_s( 0.0 );

        /* Mathematical Variables */
        lg_Real_t lgTanAppH = lg_Real_s( 0.0 );
        lg_Real_t lgTanAppV = lg_Real_s( 0.0 );

        /* Position vector */
        lg_Real_t lgVectori[3] = { 0.0, 0.0, 0.0 };
        lg_Real_t lgVectorf[3] = { 0.0, 0.0, 0.0 };

        /* Rotation matrix */
        lg_Real_t lgMatrixY[3][3] = { { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0 } };
        lg_Real_t lgMatrixZ[3][3] = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } };

        /* Rotation matrix - y */
        lgMatrixY[0][0] = + cos( - lgNadV );
        lgMatrixY[0][2] = + sin( - lgNadV );
        lgMatrixY[2][0] = - lgMatrixY[0][2];
        lgMatrixY[2][2] = + lgMatrixY[0][0];

        /* Rotation matrix - z */
        lgMatrixZ[0][0] = + cos( - lgNadH );
        lgMatrixZ[0][1] = - sin( - lgNadH );
        lgMatrixZ[1][0] = - lgMatrixZ[0][1];
        lgMatrixZ[1][1] = + lgMatrixZ[0][0];

        /* Angular apperture tangent computation */
        lgTanAppH = tan( lgAppH );
        lgTanAppV = tan( lgAppV );

        /* Planar projection referential y-loop */
        for ( lgDY = lg_Size_s( 0 ); lgDY < lgEqrHeight; lgDY++ ) {

            /* Planar projection referential x-loop */
            for ( lgDX = lg_Size_s( 0 ); lgDX < lgEqrWidth; lgDX++ ) {

                /* Build angular position */
                lgAH = ( ( ( lg_Real_t ) lgDX / ( lg_Real_t ) ( lgEqrWidth  - lg_Size_s( 1 ) ) ) * lg_Real_s( 2.0 ) ) * LG_PI;
                lgAV = ( ( ( lg_Real_t ) lgDY / ( lg_Real_t ) ( lgEqrHeight - lg_Size_s( 1 ) ) ) - lg_Real_s( 0.5 ) ) * LG_PI;

                /* Build position vector */
                lgVectori[0] = cos( lgAH ) * cos( lgAV );
                lgVectori[1] = sin( lgAH ) * cos( lgAV );
                lgVectori[2] = sin( lgAV );

                /* Apply rotation due to t-nadir and p-nadir */
                lgVectorf[0] = lgMatrixZ[0][0] * lgVectori[0] + lgMatrixZ[0][1] * lgVectori[1];
                lgVectorf[1] = lgMatrixZ[1][0] * lgVectori[0] + lgMatrixZ[1][1] * lgVectori[1];
                lgVectorf[2] = lgVectori[2];
                lgVectori[0] = lgMatrixY[0][0] * lgVectorf[0] + lgMatrixY[0][2] * lgVectorf[2];
                lgVectori[1] = lgVectorf[1];
                lgVectori[2] = lgMatrixY[2][0] * lgVectorf[0] + lgMatrixY[2][2] * lgVectorf[2];

                /* Verify projection domain */
                if ( lgVectori[0] > lg_Real_s( 0.0 ) ) {

                    /* Apply projection and scaling */
                    lgPX = ( ( ( lgVectori[1] / lgVectori[0] / lgTanAppH ) + lg_Real_s( 1.0 ) ) / lg_Real_s( 2.0 ) ) * ( lgRectWidth  - 1 );
                    lgPY = ( ( ( lgVectori[2] / lgVectori[0] / lgTanAppV ) + lg_Real_s( 1.0 ) ) / lg_Real_s( 2.0 ) ) * ( lgRectHeight - 1 );

                    /* Verify gnomonic domain */
                    if ( ( lgPX >= lg_Real_s( 0.0 ) ) && ( lgPX < lgRectWidth ) && ( lgPY >= lg_Real_s( 0.0 ) ) && ( lgPY < lgRectHeight ) ) {

                        /* Interpolation process */
                        * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX )                  ) = lgInter( lgRectIn, lgRectWidth, lgRectHeight, lgRectLayer, lg_Size_s( 0 ), lgPX, lgPY );
                        * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX ) + lg_Size_s( 1 ) ) = lgInter( lgRectIn, lgRectWidth, lgRectHeight, lgRectLayer, lg_Size_s( 1 ), lgPX, lgPY );
                        * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX ) + lg_Size_s( 2 ) ) = lgInter( lgRectIn, lgRectWidth, lgRectHeight, lgRectLayer, lg_Size_s( 2 ), lgPX, lgPY );

                    }

                }

            }

        }

    }

/*
    Source - Blended reprojection of gnomonic image back into equirectangluar image
 */

    lg_Void_t lg_gte_blend(

        li_C8_t *   lgEqrIO,
        lg_Size_t   lgEqrWidth,
        lg_Size_t   lgEqrHeight,
        lg_Size_t   lgEqrLayer,
        li_C8_t *   lgRectIn,
        li_C8_t *   lgMaskIn,
        lg_Size_t   lgRectWidth,
        lg_Size_t   lgRectHeight,
        lg_Size_t   lgRectLayer,
        lg_Real_t   lgNadH,
        lg_Real_t   lgNadV,
        lg_Real_t   lgAppH,
        lg_Real_t   lgAppV,
        li_Method_t lgInter

    ) {

        /* Parsing variables */
        lg_Size_t lgDX = lg_Size_s( 0 );
        lg_Size_t lgDY = lg_Size_s( 0 );

        /* Projection variables */
        lg_Real_t lgPX = lg_Real_s( 0.0 );
        lg_Real_t lgPY = lg_Real_s( 0.0 );
        lg_Real_t lgAH = lg_Real_s( 0.0 );
        lg_Real_t lgAV = lg_Real_s( 0.0 );
        lg_Real_t lgBF = lg_Real_s( 0.0 );

        /* Mathematical Variables */
        lg_Real_t lgTanAppH = lg_Real_s( 0.0 );
        lg_Real_t lgTanAppV = lg_Real_s( 0.0 );

        /* Position vector */
        lg_Real_t lgVectori[3] = { 0.0, 0.0, 0.0 };
        lg_Real_t lgVectorf[3] = { 0.0, 0.0, 0.0 };

        /* Rotation matrix */
        lg_Real_t lgMatrixY[3][3] = { { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0 } };
        lg_Real_t lgMatrixZ[3][3] = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } };

        /* Rotation matrix - y */
        lgMatrixY[0][0] = + cos( - lgNadV );
        lgMatrixY[0][2] = + sin( - lgNadV );
        lgMatrixY[2][0] = - lgMatrixY[0][2];
        lgMatrixY[2][2] = + lgMatrixY[0][0];

        /* Rotation matrix - z */
        lgMatrixZ[0][0] = + cos( - lgNadH );
        lgMatrixZ[0][1] = - sin( - lgNadH );
        lgMatrixZ[1][0] = - lgMatrixZ[0][1];
        lgMatrixZ[1][1] = + lgMatrixZ[0][0];

        /* Angular apperture tangent computation */
        lgTanAppH = tan( lgAppH );
        lgTanAppV = tan( lgAppV );

        /* Planar projection referential y-loop */
        for ( lgDY = lg_Size_s( 0 ); lgDY < lgEqrHeight; lgDY++ ) {

            /* Planar projection referential x-loop */
            for ( lgDX = lg_Size_s( 0 ); lgDX < lgEqrWidth; lgDX++ ) {

                /* Build angular position */
                lgAH = ( ( ( lg_Real_t ) lgDX / ( lg_Real_t ) ( lgEqrWidth  - lg_Size_s( 1 ) ) ) * lg_Real_s( 2.0 ) ) * LG_PI;
                lgAV = ( ( ( lg_Real_t ) lgDY / ( lg_Real_t ) ( lgEqrHeight - lg_Size_s( 1 ) ) ) - lg_Real_s( 0.5 ) ) * LG_PI;

                /* Build position vector */
                lgVectori[0] = cos( lgAH ) * cos( lgAV );
                lgVectori[1] = sin( lgAH ) * cos( lgAV );
                lgVectori[2] = sin( lgAV );

                /* Apply rotation due to t-nadir and p-nadir */
                lgVectorf[0] = lgMatrixZ[0][0] * lgVectori[0] + lgMatrixZ[0][1] * lgVectori[1];
                lgVectorf[1] = lgMatrixZ[1][0] * lgVectori[0] + lgMatrixZ[1][1] * lgVectori[1];
                lgVectorf[2] = lgVectori[2];
                lgVectori[0] = lgMatrixY[0][0] * lgVectorf[0] + lgMatrixY[0][2] * lgVectorf[2];
                lgVectori[1] = lgVectorf[1];
                lgVectori[2] = lgMatrixY[2][0] * lgVectorf[0] + lgMatrixY[2][2] * lgVectorf[2];

                /* Verify projection domain */
                if ( lgVectori[0] > lg_Real_s( 0.0 ) ) {

                    /* Apply projection and scaling */
                    lgPX = ( ( ( lgVectori[1] / lgVectori[0] / lgTanAppH ) + lg_Real_s( 1.0 ) ) / lg_Real_s( 2.0 ) ) * ( lgRectWidth  - lg_Size_s( 1 ) );
                    lgPY = ( ( ( lgVectori[2] / lgVectori[0] / lgTanAppV ) + lg_Real_s( 1.0 ) ) / lg_Real_s( 2.0 ) ) * ( lgRectHeight - lg_Size_s( 1 ) );

                    /* Verify gnomonic domain */
                    if ( ( lgPX >= lg_Real_s( 0.0 ) ) && ( lgPX < lgRectWidth ) && ( lgPY >= lg_Real_s( 0.0 ) ) && ( lgPY < lgRectHeight ) ) {

                        /* Compute the blending factor */
                        lgBF = ( lg_Real_t ) * ( lgMaskIn + lgRectWidth * ( lg_Size_t ) trunc( lgPY ) + ( lg_Size_t ) trunc( lgPX ) ) / lg_Real_s( 255.0 );

                        /* Interpolation and blending process */
                        * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX )                  ) = * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX )                  ) * ( lg_Real_s( 1.0 ) - lgBF ) + lgInter( lgRectIn, lgRectWidth, lgRectHeight, lgRectLayer, lg_Size_s( 0 ), lgPX, lgPY ) * lgBF;
                        * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX ) + lg_Size_s( 1 ) ) = * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX ) + lg_Size_s( 1 ) ) * ( lg_Real_s( 1.0 ) - lgBF ) + lgInter( lgRectIn, lgRectWidth, lgRectHeight, lgRectLayer, lg_Size_s( 1 ), lgPX, lgPY ) * lgBF;
                        * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX ) + lg_Size_s( 2 ) ) = * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX ) + lg_Size_s( 2 ) ) * ( lg_Real_s( 1.0 ) - lgBF ) + lgInter( lgRectIn, lgRectWidth, lgRectHeight, lgRectLayer, lg_Size_s( 2 ), lgPX, lgPY ) * lgBF;

                    }

                }

            }

        }

    }

