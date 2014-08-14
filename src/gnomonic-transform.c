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

    # include "gnomonic-transform.h"

/*
    Source - 
 */

    lg_Void_t lg_transform_rotate( 

        li_C8_t *   lgEqrIn,
        li_C8_t *   lgEqrOut,
        lg_Size_t   lgEqrWidth,
        lg_Size_t   lgEqrHeight,
        lg_Size_t   lgEqrLayers,
        lg_Real_t   lgAngleX,
        lg_Real_t   lgAngleY,
        lg_Real_t   lgAngleZ,
        li_Method_t lgInter

    ) {

        /* Position angles */
        lg_Real_t lgAH = lg_Real_s( 0.0 );
        lg_Real_t lgAV = lg_Real_s( 0.0 );

        /* Positionning variables */
        lg_Real_t lgDX = lg_Real_s( 0.0 );
        lg_Real_t lgDY = lg_Real_s( 0.0 );

        /* Parsing variable */
        lg_Size_t lgSX = lg_Real_s( 0.0 );
        lg_Size_t lgSY = lg_Real_s( 0.0 );

        /* Sphere point vectors */
        lg_Real_t lgVectori[3] = { lg_Real_s( 0.0 ) };
        lg_Real_t lgVectorf[3] = { lg_Real_s( 0.0 ) };

        /* Rotation matrix */
        lg_Real_t lgMatrix[3][3] = {
            { 
                + cos( lgAngleZ ) * cos( lgAngleY ), 
                + sin( lgAngleZ ) * cos( lgAngleX ) + cos( lgAngleZ ) * sin( lgAngleY ) * sin( lgAngleX ), 
                + sin( lgAngleZ ) * sin( lgAngleX ) - cos( lgAngleZ ) * sin( lgAngleY ) * cos( lgAngleX ) 
            }, { 
                - sin( lgAngleZ ) * cos( lgAngleY ), 
                + cos( lgAngleZ ) * cos( lgAngleX ) - sin( lgAngleZ ) * sin( lgAngleY ) * sin( lgAngleX ), 
                + cos( lgAngleZ ) * sin( lgAngleX ) + sin( lgAngleZ ) * sin( lgAngleY ) * cos( lgAngleX ) 
            }, { 
                + sin( lgAngleY ), 
                - cos( lgAngleY ) * sin( lgAngleX ), 
                + cos( lgAngleY ) * cos( lgAngleX ) 
            }
        };

        /* Processing loop on y */
        for ( lgSY = lg_Size_s( 0 ); lgSY < lgEqrHeight; lgSY ++ ) {

            /* Processing loop on x */
            for ( lgSX = lg_Size_s( 0 ); lgSX < lgEqrWidth; lgSX ++ ) {

                /* Retrive position angles from pixels */
                lgAH = ( ( lg_Real_c( lgSX ) / lg_Real_c( lgEqrWidth  - lg_Size_s( 1 ) ) ) * lg_Real_s( 2.0 ) ) * LG_PI;
                lgAV = ( ( lg_Real_c( lgSY ) / lg_Real_c( lgEqrHeight - lg_Size_s( 1 ) ) ) - lg_Real_s( 0.5 ) ) * LG_PI;

                /* Retrieve initial vector on sphere */
                lgVectori[0] = cos( lgAH ) * cos( lgAV );
                lgVectori[1] = sin( lgAH ) * cos( lgAV );
                lgVectori[2] = sin( lgAV );

                /* Apply rotation transform */
                lgVectorf[0] = lgMatrix[0][0] * lgVectori[0] + lgMatrix[0][1] * lgVectori[1] + lgMatrix[0][2] * lgVectori[2];
                lgVectorf[1] = lgMatrix[1][0] * lgVectori[0] + lgMatrix[1][1] * lgVectori[1] + lgMatrix[1][2] * lgVectori[2];
                lgVectorf[2] = lgMatrix[2][0] * lgVectori[0] + lgMatrix[2][1] * lgVectori[1] + lgMatrix[2][2] * lgVectori[2];

                /* Retreive angular position */
                lgAH = LG_ATN( lgVectorf[0] , lgVectorf[1] );
                lgAV = LG_ASN( lgVectorf[2] );

                /* Retrieve panoramic pixel coordinates */
                lgDX = ( lgEqrWidth  - lg_Size_s( 1 ) ) * ( lgAH / LG_PI2 );
                lgDY = ( lgEqrHeight - lg_Size_s( 1 ) ) * ( ( lgAV / LG_PI ) + lg_Real_s( 0.5 ) );

                /* Assign pixel value */
                * ( lgEqrOut + lgEqrLayers * ( lgEqrWidth * lgSY + lgSX )                  ) = lgInter( lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayers, lg_Size_s( 0 ), lgDX, lgDY );
                * ( lgEqrOut + lgEqrLayers * ( lgEqrWidth * lgSY + lgSX ) + lg_Size_s( 1 ) ) = lgInter( lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayers, lg_Size_s( 1 ), lgDX, lgDY );
                * ( lgEqrOut + lgEqrLayers * ( lgEqrWidth * lgSY + lgSX ) + lg_Size_s( 2 ) ) = lgInter( lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayers, lg_Size_s( 2 ), lgDX, lgDY );

            }

        }

    }

