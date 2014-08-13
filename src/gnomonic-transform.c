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

    gnomonic_Void_t gnomonic_transform_rotate( 

        inter_C8_t *     lgEqrIn,
        inter_C8_t *     lgEqrOut,
        gnomonic_Index_t lgEqrWidth,
        gnomonic_Index_t lgEqrHeight,
        gnomonic_Index_t lgEqrLayers,
        gnomonic_Real_t  lgAngleX,
        gnomonic_Real_t  lgAngleY,
        gnomonic_Real_t  lgAngleZ,
        inter_Method_t   lgInter

    ) {

        /* Position angles */
        gnomonic_Real_t lgAngleHor = 0.0;
        gnomonic_Real_t lgAngleVer = 0.0;

        /* Positionning variables */
        gnomonic_Real_t lgDX = 0;
        gnomonic_Real_t lgDY = 0;

        /* Parsing variable */
        gnomonic_Index_t lgSX = 0;
        gnomonic_Index_t lgSY = 0;

        /* Rotation matrix */
        gnomonic_Real_t lgMatrix[3][3] = {

            { 
                + cos( lgAngleZ ) * cos( lgAngleY ), 
                + sin( lgAngleZ ) * cos( lgAngleX ) + cos( lgAngleZ ) * sin( lgAngleY ) * sin( lgAngleX ), 
                + sin( lgAngleZ ) * sin( lgAngleX ) - cos( lgAngleZ ) * sin( lgAngleY ) * cos( lgAngleX ) 
            },
            { 
                - sin( lgAngleZ ) * cos( lgAngleY ), 
                + cos( lgAngleZ ) * cos( lgAngleX ) - sin( lgAngleZ ) * sin( lgAngleY ) * sin( lgAngleX ), 
                + cos( lgAngleZ ) * sin( lgAngleX ) + sin( lgAngleZ ) * sin( lgAngleY ) * cos( lgAngleX ) 
            },
            { 
                + sin( lgAngleY ), 
                - cos( lgAngleY ) * sin( lgAngleX ), 
                + cos( lgAngleY ) * cos( lgAngleX ) 
            }

        };

        /* Sphere point vectors */
        gnomonic_Real_t lgVectori[3] = { 0.0, 0.0, 0.0 };
        gnomonic_Real_t lgVectorf[3] = { 0.0, 0.0, 0.0 };

        /* Processing loop on y */
        for ( lgSY = 0; lgSY < lgEqrHeight; lgSY ++ ) {

            /* Processing loop on x */
            for ( lgSX = 0; lgSX < lgEqrWidth; lgSX ++ ) {

                /* Retrive position angles from pixels */
                lgAngleHor = ( ( ( gnomonic_Real_t ) lgSX / ( lgEqrWidth  - 1 ) ) * 2.0 ) * LG_PI;
                lgAngleVer = ( ( ( gnomonic_Real_t ) lgSY / ( lgEqrHeight - 1 ) ) - 0.5 ) * LG_PI;

                /* Retrieve initial vector on sphere */
                lgVectori[0] = cos( lgAngleHor ) * cos( lgAngleVer );
                lgVectori[1] = sin( lgAngleHor ) * cos( lgAngleVer );
                lgVectori[2] = sin( lgAngleVer );

                /* Apply rotation transform */
                lgVectorf[0] = lgMatrix[0][0] * lgVectori[0] + lgMatrix[0][1] * lgVectori[1] + lgMatrix[0][2] * lgVectori[2];
                lgVectorf[1] = lgMatrix[1][0] * lgVectori[0] + lgMatrix[1][1] * lgVectori[1] + lgMatrix[1][2] * lgVectori[2];
                lgVectorf[2] = lgMatrix[2][0] * lgVectori[0] + lgMatrix[2][1] * lgVectori[1] + lgMatrix[2][2] * lgVectori[2];

                /* Retrieve rotated position angles - horizontal */
                lgAngleHor = lgVectorf[0] / sqrt( lgVectorf[0] * lgVectorf[0] + lgVectorf[1] * lgVectorf[1] );

                /* Case study */
                if ( lgAngleHor >= 1.0 ) {

                    /* Assign horizontal angle */
                    lgAngleHor = 0.0;

                } else if ( lgAngleHor <= - 1.0 ) {

                    /* Assign horizontal angle */
                    lgAngleHor = M_PI;

                } else {

                    /* Case study */
                    if ( lgVectorf[1] < 0.0 ) {

                        /* Assign horizontal angle */
                        lgAngleHor = 2.0 * LG_PI - acos( lgAngleHor );

                    } else {

                        /* Assign horizontal angle */
                        lgAngleHor = acos( lgAngleHor );

                    }

                }

                /* Retrieve rotated position angles - vertical */
                lgAngleVer = asin( lgVectorf[2] );

                /* Retrieve pixel components */
                lgDX = ( lgAngleHor / ( 2.0 * M_PI ) ) * ( lgEqrWidth  - 1 );
                lgDY = ( ( lgAngleVer / M_PI ) + 0.5 ) * ( lgEqrHeight - 1 );

                /* Assign pixel value */
                * ( lgEqrOut + lgEqrLayers * ( lgEqrWidth * lgSY + lgSX )     ) = lgInter( lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayers, 0, lgDX, lgDY );
                * ( lgEqrOut + lgEqrLayers * ( lgEqrWidth * lgSY + lgSX ) + 1 ) = lgInter( lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayers, 1, lgDX, lgDY );
                * ( lgEqrOut + lgEqrLayers * ( lgEqrWidth * lgSY + lgSX ) + 2 ) = lgInter( lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayers, 2, lgDX, lgDY );

            }

        }

    }

