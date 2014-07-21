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

        inter_C8_t *     gEqrIn,
        inter_C8_t *     gEqrOut,
        gnomonic_Index_t gEqrWidth,
        gnomonic_Index_t gEqrHeight,
        gnomonic_Index_t gEqrLayers,
        gnomonic_Real_t  gAngleX,
        gnomonic_Real_t  gAngleY,
        gnomonic_Real_t  gAngleZ,
        inter_Method_t   gInter

    ) {

        /* Position angles */
        gnomonic_Real_t gAngleHor = 0.0;
        gnomonic_Real_t gAngleVer = 0.0;

        /* Positionning variables */
        gnomonic_Real_t gDX = 0;
        gnomonic_Real_t gDY = 0;

        /* Parsing variable */
        gnomonic_Index_t gSX = 0;
        gnomonic_Index_t gSY = 0;

        /* Rotation matrix */
        gnomonic_Real_t gMatrix[3][3] = {

            { 
                + cos( gAngleZ ) * cos( gAngleY ), 
                + sin( gAngleZ ) * cos( gAngleX ) + cos( gAngleZ ) * sin( gAngleY ) * sin( gAngleX ), 
                + sin( gAngleZ ) * sin( gAngleX ) - cos( gAngleZ ) * sin( gAngleY ) * cos( gAngleX ) 
            },
            { 
                - sin( gAngleZ ) * cos( gAngleY ), 
                + cos( gAngleZ ) * cos( gAngleX ) - sin( gAngleZ ) * sin( gAngleY ) * sin( gAngleX ), 
                + cos( gAngleZ ) * sin( gAngleX ) + sin( gAngleZ ) * sin( gAngleY ) * cos( gAngleX ) 
            },
            { 
                + sin( gAngleY ), 
                - cos( gAngleY ) * sin( gAngleX ), 
                + cos( gAngleY ) * cos( gAngleX ) 
            }

        };

        /* Sphere point vectors */
        gnomonic_Real_t gVectori[3] = { 0.0, 0.0, 0.0 };
        gnomonic_Real_t gVectorf[3] = { 0.0, 0.0, 0.0 };

        /* Processing loop on y */
        for ( gSY = 0; gSY < gEqrHeight; gSY ++ ) {

            /* Processing loop on x */
            for ( gSX = 0; gSX < gEqrWidth; gSX ++ ) {

                /* Retrive position angles from pixels */
                gAngleHor = ( ( ( gnomonic_Real_t ) gSX / ( gEqrWidth  - 1 ) ) * 2.0 ) * GNOMONIC_PI;
                gAngleVer = ( ( ( gnomonic_Real_t ) gSY / ( gEqrHeight - 1 ) ) - 0.5 ) * GNOMONIC_PI;

                /* Retrieve initial vector on sphere */
                gVectori[0] = cos( gAngleHor ) * cos( gAngleVer );
                gVectori[1] = sin( gAngleHor ) * cos( gAngleVer );
                gVectori[2] = sin( gAngleVer );

                /* Apply rotation transform */
                gVectorf[0] = gMatrix[0][0] * gVectori[0] + gMatrix[0][1] * gVectori[1] + gMatrix[0][2] * gVectori[2];
                gVectorf[1] = gMatrix[1][0] * gVectori[0] + gMatrix[1][1] * gVectori[1] + gMatrix[1][2] * gVectori[2];
                gVectorf[2] = gMatrix[2][0] * gVectori[0] + gMatrix[2][1] * gVectori[1] + gMatrix[2][2] * gVectori[2];

                /* Retrieve rotated position angles - horizontal */
                gAngleHor = gVectorf[0] / sqrt( gVectorf[0] * gVectorf[0] + gVectorf[1] * gVectorf[1] );

                /* Case study */
                if ( gAngleHor >= 1.0 ) {

                    /* Assign horizontal angle */
                    gAngleHor = 0.0;

                } else if ( gAngleHor <= - 1.0 ) {

                    /* Assign horizontal angle */
                    gAngleHor = M_PI;

                } else {

                    /* Case study */
                    if ( gVectorf[1] < 0.0 ) {

                        /* Assign horizontal angle */
                        gAngleHor = 2.0 * GNOMONIC_PI - acos( gAngleHor );

                    } else {

                        /* Assign horizontal angle */
                        gAngleHor = acos( gAngleHor );

                    }

                }

                /* Retrieve rotated position angles - vertical */
                gAngleVer = asin( gVectorf[2] );

                /* Retrieve pixel components */
                gDX = ( gAngleHor / ( 2.0 * M_PI ) ) * ( gEqrWidth  - 1 );
                gDY = ( ( gAngleVer / M_PI ) + 0.5 ) * ( gEqrHeight - 1 );

                /* Assign pixel value */
                * ( gEqrOut + gEqrLayers * ( gEqrWidth * gSY + gSX )     ) = gInter( gEqrIn, gEqrWidth, gEqrHeight, gEqrLayers, 0, gDX, gDY );
                * ( gEqrOut + gEqrLayers * ( gEqrWidth * gSY + gSX ) + 1 ) = gInter( gEqrIn, gEqrWidth, gEqrHeight, gEqrLayers, 1, gDX, gDY );
                * ( gEqrOut + gEqrLayers * ( gEqrWidth * gSY + gSX ) + 2 ) = gInter( gEqrIn, gEqrWidth, gEqrHeight, gEqrLayers, 2, gDX, gDY );

            }

        }

    }

