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

    # include "gnomonic-etg.h"

/*
    Source - Gnomonic projection from equirectangular panoramic image
 */

    lg_Void_t lg_etg(

        li_C8_t *   lgEqrIn,
        lg_Size_t   lgEqrWidth,
        lg_Size_t   lgEqrHeight,
        lg_Size_t   lgEqrLayer,
        li_C8_t *   lgRectOut,
        lg_Size_t   lgRectWidth,
        lg_Size_t   lgRectHeight,
        lg_Size_t   lgRectLayer,
        lg_Real_t   lgNadH,
        lg_Real_t   lgNadV,
        lg_Real_t   lgAppH,
        lg_Real_t   lgAppV,
        li_Method_t lgInter

    ) {

        /* Parsing Variables */
        lg_Size_t lgDX = lg_Size_s( 0 );
        lg_Size_t lgDY = lg_Size_s( 0 );

        /* Projection Variables */
        lg_Real_t lgSX = lg_Real_s( 0.0 );
        lg_Real_t lgSY = lg_Real_s( 0.0 );
        lg_Real_t lgPX = lg_Real_s( 0.0 );
        lg_Real_t lgPY = lg_Real_s( 0.0 );
        lg_Real_t lgAH = lg_Real_s( 0.0 );
        lg_Real_t lgAV = lg_Real_s( 0.0 );

        /* Compute gnomonic apperture tangants */
        lg_Real_t lgTanAppH = tan( lgAppH );
        lg_Real_t lgTanAppV = tan( lgAppV );

        /* Rotation matrix coefficients */
        lg_Real_t lgCosY = cos( + lgNadV );
        lg_Real_t lgSinY = sin( + lgNadV );
        lg_Real_t lgCosZ = cos( + lgNadH );
        lg_Real_t lgSinZ = sin( + lgNadH );

        /* Position vector */
        lg_Real_t lgVectori[3] = { lg_Real_s( 0.0 ) };
        lg_Real_t lgVectorf[3] = { lg_Real_s( 0.0 ) };

        /* Padding variable */
        lg_Size_t lgRectPad = lgRectWidth * lgRectLayer; if ( lgRectPad % lg_Size_s( 4 ) ) lgRectPad += lg_Size_s( 4 ) - lgRectPad % lg_Size_s( 4 );

        /* Planar projection referential y-loop */
        for ( lgDY = lg_Size_s( 0 ); lgDY < lgRectHeight; lgDY++ ) {

            /* Planar projection referential x-loop */
            for ( lgDX = lg_Size_s( 0 ); lgDX < lgRectWidth; lgDX++ ) {

                /* Normalized planar coordinates */
                lgPX = ( ( lg_Real_s( 2.0 ) * lg_Real_c( lgDX ) / lg_Real_c( lgRectWidth  - lg_Size_s( 1 ) ) ) - lg_Real_s( 1.0 ) ) * lgTanAppH;
                lgPY = ( ( lg_Real_s( 2.0 ) * lg_Real_c( lgDY ) / lg_Real_c( lgRectHeight - lg_Size_s( 1 ) ) ) - lg_Real_s( 1.0 ) ) * lgTanAppV;

                /* Rebuild position vector - x y z */
                lgVectori[0] = cos( atan( sqrt( lgPX * lgPX + lgPY * lgPY ) ) );
                lgVectori[1] = lgPX * lgVectori[0];
                lgVectori[2] = lgPY * lgVectori[0];

                /* Invert rotation due to t-nadir and p-nadir */
                lgVectorf[0] = + lgCosZ * lgCosY * lgVectori[0] - lgSinZ * lgVectori[1] + lgCosZ * lgSinY * lgVectori[2];
                lgVectorf[1] = + lgSinZ * lgCosY * lgVectori[0] + lgCosZ * lgVectori[1] + lgSinZ * lgSinY * lgVectori[2];
                lgVectorf[2] = - lgSinY          * lgVectori[0] + lg_Real_s( 0.0 )      + lgCosY          * lgVectori[2];

                /* Retreive angular position */
                lgAH = LG_ATN( lgVectorf[0] , lgVectorf[1] );
                lgAV = LG_ASN( lgVectorf[2] );

                /* Retrieve panoramic pixel coordinates */
                lgSX = ( lgEqrWidth  - lg_Size_s( 1 ) ) * ( lgAH / LG_PI2 );
                lgSY = ( lgEqrHeight - lg_Size_s( 1 ) ) * ( ( lgAV / LG_PI ) + lg_Real_s( 0.5 ) );

                /* Interpolation process */
                LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 0 ) ) = lgInter( lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayer, lg_Size_s( 0 ), lgSX, lgSY );
                LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 1 ) ) = lgInter( lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayer, lg_Size_s( 1 ), lgSX, lgSY );
                LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 2 ) ) = lgInter( lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayer, lg_Size_s( 2 ), lgSX, lgSY );

            }

        }

    }

