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
 * (lgAppH your option) any later version.
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

    gnomonic_Void_t gnomonic_etg(

        inter_C8_t *     lgEqrIn,
        gnomonic_Index_t lgEqrWidth,
        gnomonic_Index_t lgEqrHeight,
        gnomonic_Index_t lgEqrLayer,
        inter_C8_t *     lgRectOut,
        gnomonic_Index_t lgRectWidth,
        gnomonic_Index_t lgRectHeight,
        gnomonic_Index_t lgRectLayer,
        gnomonic_Real_t  lgNadH,
        gnomonic_Real_t  lgNadV,
        gnomonic_Real_t  lgAppH,
        gnomonic_Real_t  lgAppV,
        inter_Method_t   lgInter

    ) {

        /* Parsing Variables */
        gnomonic_Index_t lgDX = 0;
        gnomonic_Index_t lgDY = 0;

        /* Projection Variables */
        gnomonic_Real_t lgSX = 0.0;
        gnomonic_Real_t lgSY = 0.0;
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
        lgMatrixY[0][0] = + cos( + lgNadV );
        lgMatrixY[0][2] = + sin( + lgNadV );
        lgMatrixY[2][0] = - lgMatrixY[0][2];
        lgMatrixY[2][2] = + lgMatrixY[0][0];

        /* Rotation matrix - z */
        lgMatrixZ[0][0] = + cos( + lgNadH );
        lgMatrixZ[0][1] = - sin( + lgNadH );
        lgMatrixZ[1][0] = - lgMatrixZ[0][1];
        lgMatrixZ[1][1] = + lgMatrixZ[0][0];

        /* Angular apperture tangent computation */
        lgTanAppH = tan( lgAppH );
        lgTanAppV = tan( lgAppV );

        /* Planar projection referential y-loop */
        for ( lgDY = 0; lgDY < lgRectHeight; lgDY++ ) {

            /* Planar projection referential x-loop */
            for ( lgDX = 0; lgDX < lgRectWidth; lgDX++ ) {

                /* Normalized planar coordinates */
                lgPX = ( ( 2.0 * ( gnomonic_Real_t ) lgDX / ( gnomonic_Real_t ) ( lgRectWidth  - 1 ) ) - 1.0 ) * lgTanAppH;
                lgPY = ( ( 2.0 * ( gnomonic_Real_t ) lgDY / ( gnomonic_Real_t ) ( lgRectHeight - 1 ) ) - 1.0 ) * lgTanAppV;

                /* Rebuild position vector - x y z */
                lgVectori[0] = cos( atan( sqrt( lgPX * lgPX + lgPY * lgPY ) ) );
                lgVectori[1] = lgPX * lgVectori[0];
                lgVectori[2] = lgPY * lgVectori[0];

                /* Invert rotation due to t-nadir and p-nadir */
                lgVectorf[0] = lgMatrixY[0][0] * lgVectori[0] + lgMatrixY[0][2] * lgVectori[2];
                lgVectorf[1] = lgVectori[1];
                lgVectorf[2] = lgMatrixY[2][0] * lgVectori[0] + lgMatrixY[2][2] * lgVectori[2];
                lgVectori[0] = lgMatrixZ[0][0] * lgVectorf[0] + lgMatrixZ[0][1] * lgVectorf[1];
                lgVectori[1] = lgMatrixZ[1][0] * lgVectorf[0] + lgMatrixZ[1][1] * lgVectorf[1];
                lgVectori[2] = lgVectorf[2];

                /* Retrieve rotated position angles - horizontal */
                lgAH = lgVectori[0] / sqrt( lgVectori[0] * lgVectori[0] + lgVectori[1] * lgVectori[1] );

                /* Case study */
                if ( lgAH >= 1.0 ) {

                    /* Assign horizontal angle */
                    lgAH = 0.0;

                } else if ( lgAH <= - 1.0 ) {

                    /* Assign horizontal angle */
                    lgAH = M_PI;

                } else {

                    /* Case study */
                    if ( lgVectori[1] < 0.0 ) {

                        /* Assign horizontal angle */
                        lgAH = 2.0 * GNOMONIC_PI - acos( lgAH );

                    } else {

                        /* Assign horizontal angle */
                        lgAH = acos( lgAH );

                    }

                }

                /* Retreive angular position - Vertical */
                lgAV = asin( lgVectori[2] );

                /* Retrieve panoramic pixel coordinates */
                lgSX = ( lgAH / ( 2.0 * GNOMONIC_PI ) ) * ( lgEqrWidth  - 1 );
                lgSY = ( ( lgAV / GNOMONIC_PI ) + 0.5 ) * ( lgEqrHeight - 1 );

                /* Interpolation process */
                * ( lgRectOut + lgRectLayer * ( lgRectWidth * lgDY + lgDX )     ) = lgInter( lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayer, 0, lgSX, lgSY );
                * ( lgRectOut + lgRectLayer * ( lgRectWidth * lgDY + lgDX ) + 1 ) = lgInter( lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayer, 1, lgSX, lgSY );
                * ( lgRectOut + lgRectLayer * ( lgRectWidth * lgDY + lgDX ) + 2 ) = lgInter( lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayer, 2, lgSX, lgSY );

            }

        }

    }

