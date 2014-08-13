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

    gnomonic_Void_t gnomonic_gte(

        inter_C8_t *     lgEqrIO,
        gnomonic_Index_t lgEqrWidth,
        gnomonic_Index_t lgEqrHeight,
        gnomonic_Index_t lgEqrLayer,
        inter_C8_t *     lgRectIn,
        gnomonic_Index_t lgRectWidth,
        gnomonic_Index_t lgRectHeight,
        gnomonic_Index_t lgRectLayer,
        gnomonic_Real_t  lgNadH,
        gnomonic_Real_t  lgNadV,
        gnomonic_Real_t  lgAppH,
        gnomonic_Real_t  lgAppV,
        inter_Method_t   lgInter

    ) {

        /* Parsing variables */
        gnomonic_Index_t lgDX = 0;
        gnomonic_Index_t lgDY = 0;

        /* Projection variables */
        gnomonic_Real_t lgPX = 0.0;
        gnomonic_Real_t lgPY = 0.0;
        gnomonic_Real_t lgAH = 0.0;
        gnomonic_Real_t lgAV = 0.0;

        /* Mathematical Variables */
        gnomonic_Real_t lgTanAppH = 0.0;
        gnomonic_Real_t lgTanAppV = 0.0;

        /* Position vector */
        gnomonic_Real_t lgVectori[3] = { 0.0, 0.0, 0.0 };
        gnomonic_Real_t lgVectorf[3] = { 0.0, 0.0, 0.0 };

        /* Rotation matrix */
        gnomonic_Real_t lgMatrixY[3][3] = { { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0 } };
        gnomonic_Real_t lgMatrixZ[3][3] = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } };

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
        for ( lgDY = 0; lgDY < lgEqrHeight; lgDY++ ) {

            /* Planar projection referential x-loop */
            for ( lgDX = 0; lgDX < lgEqrWidth; lgDX++ ) {

                /* Build angular position */
                lgAH = ( ( ( gnomonic_Real_t ) lgDX / ( gnomonic_Real_t ) ( lgEqrWidth  - 1 ) ) * 2.0 ) * LG_PI;
                lgAV = ( ( ( gnomonic_Real_t ) lgDY / ( gnomonic_Real_t ) ( lgEqrHeight - 1 ) ) - 0.5 ) * LG_PI;

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
                if ( lgVectori[0] > 0 ) {

                    /* Apply projection and scaling */
                    lgPX = ( ( ( lgVectori[1] / lgVectori[0] / lgTanAppH ) + 1.0 ) / 2.0 ) * ( lgRectWidth  - 1 );
                    lgPY = ( ( ( lgVectori[2] / lgVectori[0] / lgTanAppV ) + 1.0 ) / 2.0 ) * ( lgRectHeight - 1 );

                    /* Verify gnomonic domain */
                    if ( ( lgPX >= 0 ) && ( lgPX < lgRectWidth ) && ( lgPY >= 0 ) && ( lgPY < lgRectHeight ) ) {

                        /* Interpolation process */
                        * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX )     ) = lgInter( lgRectIn, lgRectWidth, lgRectHeight, lgRectLayer, 0, lgPX, lgPY );
                        * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX ) + 1 ) = lgInter( lgRectIn, lgRectWidth, lgRectHeight, lgRectLayer, 1, lgPX, lgPY );
                        * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX ) + 2 ) = lgInter( lgRectIn, lgRectWidth, lgRectHeight, lgRectLayer, 2, lgPX, lgPY );

                    }

                }

            }

        }

    }

/*
    Source - Blended reprojection of gnomonic image back into equirectangluar image
 */

    gnomonic_Void_t gnomonic_gte_blend(

        inter_C8_t *     lgEqrIO,
        gnomonic_Index_t lgEqrWidth,
        gnomonic_Index_t lgEqrHeight,
        gnomonic_Index_t lgEqrLayer,
        inter_C8_t *     lgRectIn,
        inter_C8_t *     lgMaskIn,
        gnomonic_Index_t lgRectWidth,
        gnomonic_Index_t lgRectHeight,
        gnomonic_Index_t lgRectLayer,
        gnomonic_Real_t  lgNadH,
        gnomonic_Real_t  lgNadV,
        gnomonic_Real_t  lgAppH,
        gnomonic_Real_t  lgAppV,
        inter_Method_t   lgInter

    ) {

        /* Parsing variables */
        gnomonic_Index_t lgDX = 0;
        gnomonic_Index_t lgDY = 0;

        /* Projection variables */
        gnomonic_Real_t lgPX = 0.0;
        gnomonic_Real_t lgPY = 0.0;
        gnomonic_Real_t lgAH = 0.0;
        gnomonic_Real_t lgAV = 0.0;
        gnomonic_Real_t lgBF = 0.0;

        /* Mathematical Variables */
        gnomonic_Real_t lgTanAppH = 0.0;
        gnomonic_Real_t lgTanAppV = 0.0;

        /* Position vector */
        gnomonic_Real_t lgVectori[3] = { 0.0, 0.0, 0.0 };
        gnomonic_Real_t lgVectorf[3] = { 0.0, 0.0, 0.0 };

        /* Rotation matrix */
        gnomonic_Real_t lgMatrixY[3][3] = { { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0 } };
        gnomonic_Real_t lgMatrixZ[3][3] = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } };

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
        for ( lgDY = 0; lgDY < lgEqrHeight; lgDY++ ) {

            /* Planar projection referential x-loop */
            for ( lgDX = 0; lgDX < lgEqrWidth; lgDX++ ) {

                /* Build angular position */
                lgAH = ( ( ( gnomonic_Real_t ) lgDX / ( gnomonic_Real_t ) ( lgEqrWidth  - 1 ) ) * 2.0 ) * LG_PI;
                lgAV = ( ( ( gnomonic_Real_t ) lgDY / ( gnomonic_Real_t ) ( lgEqrHeight - 1 ) ) - 0.5 ) * LG_PI;

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
                if ( lgVectori[0] > 0 ) {

                    /* Apply projection and scaling */
                    lgPX = ( ( ( lgVectori[1] / lgVectori[0] / lgTanAppH ) + 1.0 ) / 2.0 ) * ( lgRectWidth  - 1 );
                    lgPY = ( ( ( lgVectori[2] / lgVectori[0] / lgTanAppV ) + 1.0 ) / 2.0 ) * ( lgRectHeight - 1 );

                    /* Verify gnomonic domain */
                    if ( ( lgPX >= 0 ) && ( lgPX < lgRectWidth ) && ( lgPY >= 0 ) && ( lgPY < lgRectHeight ) ) {

                        /* Compute the blending factor */
                        lgBF = ( gnomonic_Real_t ) * ( lgMaskIn + lgRectWidth * ( gnomonic_Index_t ) trunc( lgPY ) + ( gnomonic_Index_t ) trunc( lgPX ) ) / 255.0;

                        /* Interpolation and blending process */
                        * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX )     ) = * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX )     ) * ( 1.0 - lgBF ) + lgInter( lgRectIn, lgRectWidth, lgRectHeight, lgRectLayer, 0, lgPX, lgPY ) * lgBF;
                        * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX ) + 1 ) = * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX ) + 1 ) * ( 1.0 - lgBF ) + lgInter( lgRectIn, lgRectWidth, lgRectHeight, lgRectLayer, 1, lgPX, lgPY ) * lgBF;
                        * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX ) + 2 ) = * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX ) + 2 ) * ( 1.0 - lgBF ) + lgInter( lgRectIn, lgRectWidth, lgRectHeight, lgRectLayer, 2, lgPX, lgPY ) * lgBF;

                    }

                }

            }

        }

    }

