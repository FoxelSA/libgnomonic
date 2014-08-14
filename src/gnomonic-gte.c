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

        /* Compute gnomonic apperture tangants */
        lg_Real_t lgTanAppH = tan( lgAppH );
        lg_Real_t lgTanAppV = tan( lgAppV );

        /* Rotation matrix coefficients */
        lg_Real_t lgCosY = cos( - lgNadV );
        lg_Real_t lgSinY = sin( - lgNadV );
        lg_Real_t lgCosZ = cos( - lgNadH );
        lg_Real_t lgSinZ = sin( - lgNadH );

        /* Position vector */
        lg_Real_t lgVectori[3] = { lg_Real_s( 0.0 ) };
        lg_Real_t lgVectorf[3] = { lg_Real_s( 0.0 ) };

        /* Planar projection referential y-loop */
        for ( lgDY = lg_Size_s( 0 ); lgDY < lgEqrHeight; lgDY++ ) {

            /* Planar projection referential x-loop */
            for ( lgDX = lg_Size_s( 0 ); lgDX < lgEqrWidth; lgDX++ ) {

                /* Build angular position */
                lgAH = ( ( lg_Real_c( lgDX ) / lg_Real_c( lgEqrWidth  - lg_Size_s( 1 ) ) ) * lg_Real_s( 2.0 ) ) * LG_PI;
                lgAV = ( ( lg_Real_c( lgDY ) / lg_Real_c( lgEqrHeight - lg_Size_s( 1 ) ) ) - lg_Real_s( 0.5 ) ) * LG_PI;

                /* Build position vector */
                lgVectori[0] = cos( lgAH ) * cos( lgAV );
                lgVectori[1] = sin( lgAH ) * cos( lgAV );
                lgVectori[2] = sin( lgAV );

                /* Apply rotation due to t-nadir and p-nadir */
                lgVectorf[0] = + lgCosY * lgCosZ * lgVectori[0] - lgCosY * lgSinZ * lgVectori[1] + lgSinY * lgVectori[2];
                lgVectorf[1] = + lgSinZ          * lgVectori[0] + lgCosZ          * lgVectori[1];
                lgVectorf[2] = - lgSinY * lgCosZ * lgVectori[0] + lgSinY * lgSinZ * lgVectori[1] + lgCosY * lgVectori[2];

                /* Verify projection domain */
                if ( lgVectorf[0] > lg_Real_s( 0.0 ) ) {

                    /* Apply projection and scaling */
                    lgPX = ( ( ( lgVectorf[1] / lgVectorf[0] / lgTanAppH ) + lg_Real_s( 1.0 ) ) / lg_Real_s( 2.0 ) ) * ( lgRectWidth  - lg_Size_s( 1 ) );
                    lgPY = ( ( ( lgVectorf[2] / lgVectorf[0] / lgTanAppV ) + lg_Real_s( 1.0 ) ) / lg_Real_s( 2.0 ) ) * ( lgRectHeight - lg_Size_s( 1 ) );

                    /* Verify gnomonic domain */
                    if ( ( lgPX >= lg_Real_s( 0.0 ) ) && ( lgPX < lg_Real_c( lgRectWidth - lg_Size_s( 1 ) ) ) && ( lgPY >= lg_Real_s( 0.0 ) ) && ( lgPY < lg_Real_c( lgRectHeight - lg_Size_s( 1 ) ) ) ) {

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

        /* Compute gnomonic apperture tangants */
        lg_Real_t lgTanAppH = tan( lgAppH );
        lg_Real_t lgTanAppV = tan( lgAppV );

        /* Rotation matrix coefficients */
        lg_Real_t lgCosY = cos( - lgNadV );
        lg_Real_t lgSinY = sin( - lgNadV );
        lg_Real_t lgCosZ = cos( - lgNadH );
        lg_Real_t lgSinZ = sin( - lgNadH );

        /* Position vector */
        lg_Real_t lgVectori[3] = { lg_Real_s( 0.0 ) };
        lg_Real_t lgVectorf[3] = { lg_Real_s( 0.0 ) };

        /* Planar projection referential y-loop */
        for ( lgDY = lg_Size_s( 0 ); lgDY < lgEqrHeight; lgDY++ ) {

            /* Planar projection referential x-loop */
            for ( lgDX = lg_Size_s( 0 ); lgDX < lgEqrWidth; lgDX++ ) {

                /* Build angular position */
                lgAH = ( ( lg_Real_c( lgDX ) / lg_Real_c( lgEqrWidth  - lg_Size_s( 1 ) ) ) * lg_Real_s( 2.0 ) ) * LG_PI;
                lgAV = ( ( lg_Real_c( lgDY ) / lg_Real_c( lgEqrHeight - lg_Size_s( 1 ) ) ) - lg_Real_s( 0.5 ) ) * LG_PI;

                /* Build position vector */
                lgVectori[0] = cos( lgAH ) * cos( lgAV );
                lgVectori[1] = sin( lgAH ) * cos( lgAV );
                lgVectori[2] = sin( lgAV );

                /* Apply rotation due to t-nadir and p-nadir */
                lgVectorf[0] = + lgCosY * lgCosZ * lgVectori[0] - lgCosY * lgSinZ * lgVectori[1] + lgSinY * lgVectori[2];
                lgVectorf[1] = + lgSinZ          * lgVectori[0] + lgCosZ          * lgVectori[1];
                lgVectorf[2] = - lgSinY * lgCosZ * lgVectori[0] + lgSinY * lgSinZ * lgVectori[1] + lgCosY * lgVectori[2];

                /* Verify projection domain */
                if ( lgVectorf[0] > lg_Real_s( 0.0 ) ) {

                    /* Apply projection and scaling */
                    lgPX = ( ( ( lgVectorf[1] / lgVectorf[0] / lgTanAppH ) + lg_Real_s( 1.0 ) ) / lg_Real_s( 2.0 ) ) * ( lgRectWidth  - lg_Size_s( 1 ) );
                    lgPY = ( ( ( lgVectorf[2] / lgVectorf[0] / lgTanAppV ) + lg_Real_s( 1.0 ) ) / lg_Real_s( 2.0 ) ) * ( lgRectHeight - lg_Size_s( 1 ) );

                    /* Verify gnomonic domain */
                    if ( ( lgPX >= lg_Real_s( 0.0 ) ) && ( lgPX < lg_Real_c( lgRectWidth - lg_Size_s( 1 ) ) ) && ( lgPY >= lg_Real_s( 0.0 ) ) && ( lgPY < lg_Real_c( lgRectHeight - lg_Size_s( 1 ) ) ) ) {

                        /* Compute the blending factor */
                        lgBF = lg_Real_c( * ( lgMaskIn + lgRectWidth * lg_Size_c( lgPY ) + lg_Size_c( lgPX ) ) ) / lg_Real_s( 255.0 );

                        /* Interpolation process */
                        * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX )                  ) = * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX )                  ) * ( lg_Real_s( 1.0 ) - lgBF ) + lgInter( lgRectIn, lgRectWidth, lgRectHeight, lgRectLayer, lg_Size_s( 0 ), lgPX, lgPY ) * lgBF;
                        * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX ) + lg_Size_s( 1 ) ) = * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX ) + lg_Size_s( 1 ) ) * ( lg_Real_s( 1.0 ) - lgBF ) + lgInter( lgRectIn, lgRectWidth, lgRectHeight, lgRectLayer, lg_Size_s( 1 ), lgPX, lgPY ) * lgBF;
                        * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX ) + lg_Size_s( 2 ) ) = * ( lgEqrIO + lgEqrLayer * ( lgEqrWidth * lgDY + lgDX ) + lg_Size_s( 2 ) ) * ( lg_Real_s( 1.0 ) - lgBF ) + lgInter( lgRectIn, lgRectWidth, lgRectHeight, lgRectLayer, lg_Size_s( 2 ), lgPX, lgPY ) * lgBF;

                    }

                }

            }

        }

    }

