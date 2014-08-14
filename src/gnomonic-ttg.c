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

    # include "gnomonic-ttg.h"

/*
    Source - Gnomonic projection from tile of equirectangular panoramic image
 */

    lg_Void_t lg_ttg(

        li_C8_t *   lgEqrIn,
        lg_Size_t   lgEqrWidth,
        lg_Size_t   lgEqrHeight,
        lg_Size_t   lgEqrLayer,
        li_C8_t *   lgRectOut,
        lg_Size_t   lgRectWidth,
        lg_Size_t   lgRectHeight,
        lg_Size_t   lgRectLayer,
        lg_Size_t   lgPanWidth,
        lg_Size_t   lgPanHeight,
        lg_Size_t   lgEqrPosX,
        lg_Size_t   lgEqrPosY,
        lg_Real_t   lgEqrCenterX,
        lg_Real_t   lgEqrCenterY,
        li_Method_t lgInter

    ) {

        /* Parsing variables */
        lg_Size_t lgDX = lg_Size_s( 0 );
        lg_Size_t lgDY = lg_Size_s( 0 );

        /* Projection variables */
        lg_Real_t lgSX   = lg_Real_s( 0.0 );
        lg_Real_t lgSY   = lg_Real_s( 0.0 );
        lg_Real_t lgPX   = lg_Real_s( 0.0 );
        lg_Real_t lgPY   = lg_Real_s( 0.0 );
        lg_Real_t lgAH   = lg_Real_s( 0.0 );
        lg_Real_t lgAV   = lg_Real_s( 0.0 );

        /* Compute gnomonic projection center */
        lg_Real_t lgNadH = ( lg_Real_c( lgEqrCenterX ) / lg_Real_c( lgPanWidth ) ) * LG_PI2;
        lg_Real_t lgNadV = ( lg_Real_s( 0.5 ) - ( lg_Real_c( lgEqrCenterY ) / lg_Real_c( lgPanHeight ) ) ) * LG_PI;

        /* Compute gnomonic apperture tangants */
        lg_Real_t lgTanAppH = tan( ( lg_Real_c( lgEqrWidth  ) / lg_Real_c( lgPanWidth  ) ) * LG_PI );
        lg_Real_t lgTanAppV = tan( ( lg_Real_c( lgEqrHeight ) / lg_Real_c( lgPanHeight ) ) * LG_PI * lg_Real_s( 0.5 ) );

        /* Rotation matrix coefficients */
        lg_Real_t lgCosY = cos( + lgNadV );
        lg_Real_t lgSinY = sin( + lgNadV );
        lg_Real_t lgCosZ = cos( + lgNadH );
        lg_Real_t lgSinZ = sin( + lgNadH );

        /* Position vector */
        lg_Real_t lgVectori[3] = { lg_Real_s( 0.0 ) };
        lg_Real_t lgVectorf[3] = { lg_Real_s( 0.0 ) };

        /* Planar projection referential y-loop */
        for ( lgDY = lg_Size_s( 0 ); lgDY < lgRectHeight; lgDY++ ) {

            /* Planar projection referential x-loop */
            for ( lgDX = lg_Size_s( 0 ); lgDX < lgRectWidth; lgDX++ ) {

                /* Normalized planar coordinates */
                lgPX = ( ( lg_Real_s( 2.0 ) * ( lg_Real_t ) lgDX / ( lg_Real_t ) ( lgRectWidth  - lg_Size_s( 1 ) ) ) - lg_Real_s( 1.0 ) ) * lgTanAppH;
                lgPY = ( ( lg_Real_s( 2.0 ) * ( lg_Real_t ) lgDY / ( lg_Real_t ) ( lgRectHeight - lg_Size_s( 1 ) ) ) - lg_Real_s( 1.0 ) ) * lgTanAppV;

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
                lgSX = ( lgPanWidth  - lg_Size_s( 1 ) ) * ( lgAH / LG_PI2 ) - lgEqrPosX;
                lgSY = ( lgPanHeight - lg_Size_s( 1 ) ) * ( ( lgAV / LG_PI ) + lg_Real_s( 0.5 ) ) - lgEqrPosY;

                /* Verify tile panoramic range */
                if ( ( lgSX > lg_Size_s( 0 ) ) && ( lgSX < ( lgEqrWidth - lg_Size_s( 1 ) ) ) && ( lgSY > lg_Size_s( 0 ) ) && ( lgSY < ( lgEqrHeight - lg_Size_s( 1 ) ) ) ) {

                    /* Interpolation process */
                    * ( lgRectOut + lgRectLayer * ( lgRectWidth * lgDY + lgDX )                  ) = lgInter( lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayer, 0, lgSX, lgSY );
                    * ( lgRectOut + lgRectLayer * ( lgRectWidth * lgDY + lgDX ) + lg_Size_s( 1 ) ) = lgInter( lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayer, 1, lgSX, lgSY );
                    * ( lgRectOut + lgRectLayer * ( lgRectWidth * lgDY + lgDX ) + lg_Size_s( 2 ) ) = lgInter( lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayer, 2, lgSX, lgSY );

                } else {

                    /* Assign black pixel */
                    * ( lgRectOut + lgRectLayer * ( lgRectWidth * lgDY + lgDX )                  ) = li_C8_s( 0 );
                    * ( lgRectOut + lgRectLayer * ( lgRectWidth * lgDY + lgDX ) + lg_Size_s( 1 ) ) = li_C8_s( 0 );
                    * ( lgRectOut + lgRectLayer * ( lgRectWidth * lgDY + lgDX ) + lg_Size_s( 2 ) ) = li_C8_s( 0 );
                }

            }

        }

    }

