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

    gnomonic_Void_t gnomonic_etg(

        inter_C8_t *     pan_img,
        gnomonic_Index_t pan_w,
        gnomonic_Index_t pan_h,
        gnomonic_Index_t pan_d,
        inter_C8_t *     rct_img,
        gnomonic_Index_t rct_w,
        gnomonic_Index_t rct_h,
        gnomonic_Index_t rct_d,
        gnomonic_Real_t  nad_t,
        gnomonic_Real_t  nad_p,
        gnomonic_Real_t  app_t,
        gnomonic_Real_t  app_p,
        inter_Method_t   int_m

    ) {

        /* Projection Variables */
        gnomonic_Index_t rx = 0;
        gnomonic_Index_t ry = 0;
        gnomonic_Real_t  dx = 0.0;
        gnomonic_Real_t  dy = 0.0;
        gnomonic_Real_t  ux = 0.0;
        gnomonic_Real_t  uy = 0.0;
        gnomonic_Real_t  pt = 0.0;
        gnomonic_Real_t  pp = 0.0;
        gnomonic_Real_t  at = 0.0;
        gnomonic_Real_t  ap = 0.0;

        /* Position vector */
        gnomonic_Real_t pv[3] = { 0.0, 0.0, 0.0 };
        gnomonic_Real_t kv[3] = { 0.0, 0.0, 0.0 };

        /* Rotation matrix */
        gnomonic_Real_t Ry[3][3] = { { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0 } };
        gnomonic_Real_t Rz[3][3] = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } };

        /* Rotation matrix - y */
        Ry[0][0] = + cos( + nad_p );
        Ry[0][2] = + sin( + nad_p );
        Ry[2][0] = - Ry[0][2];
        Ry[2][2] = + Ry[0][0];

        /* Rotation matrix - z */
        Rz[0][0] = + cos( + nad_t );
        Rz[0][1] = - sin( + nad_t );
        Rz[1][0] = - Rz[0][1];
        Rz[1][1] = + Rz[0][0];

        /* Angular apperture tangent computation */
        at = tan( app_t );
        ap = tan( app_p );

        /* Planar projection referential y-loop */
        for ( ry = 0; ry < rct_h; ry++ ) {

            /* Planar projection referential x-loop */
            for ( rx = 0; rx < rct_w; rx++ ) {

                /* Normalized planar coordinates */
                ux = ( ( 2.0 * ( gnomonic_Real_t ) rx / ( gnomonic_Real_t ) ( rct_w - 1 ) ) - 1.0 ) * at;
                uy = ( ( 2.0 * ( gnomonic_Real_t ) ry / ( gnomonic_Real_t ) ( rct_h - 1 ) ) - 1.0 ) * ap;

                /* Rebuild position vector - x y z */
                pv[0] = cos( atan( sqrt( ux * ux + uy * uy ) ) );
                pv[1] = ux * pv[0];
                pv[2] = uy * pv[0];

                /* Invert rotation due to t-nadir and p-nadir */
                kv[0] = Ry[0][0] * pv[0] + Ry[0][2] * pv[2];
                kv[1] = pv[1];
                kv[2] = Ry[2][0] * pv[0] + Ry[2][2] * pv[2];
                pv[0] = Rz[0][0] * kv[0] + Rz[0][1] * kv[1];
                pv[1] = Rz[1][0] * kv[0] + Rz[1][1] * kv[1];
                pv[2] = kv[2];

                /* Retrieve rotated position angles - horizontal */
                pt = pv[0] / sqrt( pv[0] * pv[0] + pv[1] * pv[1] );

                /* Case study */
                if ( pt >= 1.0 ) {

                    /* Assign horizontal angle */
                    pt = 0.0;

                } else if ( pt <= - 1.0 ) {

                    /* Assign horizontal angle */
                    pt = M_PI;

                } else {

                    /* Case study */
                    if ( pv[1] < 0.0 ) {

                        /* Assign horizontal angle */
                        pt = 2.0 * GNOMONIC_PI - acos( pt );

                    } else {

                        /* Assign horizontal angle */
                        pt = acos( pt );

                    }

                }

                /* Retreive angular position - Vertical */
                pp = asin( pv[2] );

                /* Retrieve panoramic pixel coordinates */
                dx = ( pt / ( 2.0 * GNOMONIC_PI ) ) * ( pan_w - 1 );
                dy = ( ( pp / GNOMONIC_PI ) + 0.5 ) * ( pan_h - 1 );

                /* Interpolation process */
                * ( rct_img + rct_d * ( rct_w * ry + rx )     ) = int_m( pan_img, pan_w, pan_h, pan_d, 0, dx, dy );
                * ( rct_img + rct_d * ( rct_w * ry + rx ) + 1 ) = int_m( pan_img, pan_w, pan_h, pan_d, 1, dx, dy );
                * ( rct_img + rct_d * ( rct_w * ry + rx ) + 2 ) = int_m( pan_img, pan_w, pan_h, pan_d, 2, dx, dy );

            }

        }

    }

