/*
 * libgnomonic - Gnomonic projection algorithms library
 *
 * Copyright (c) 2013-2014 FOXEL SA - http://foxel.ch
 * Please read <http://foxel.ch/license> for more information.
 *
 *
 * Author(s):
 *
 *      Stéphane Flotron <s.flotron@foxel.ch>
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

    # include "gnomonic-coord.h"

/*
    Source - Coordinates conversion from equirectangular tile to gnomonic
 */

    lg_Void_t lg_ttg_coord(

        lg_Real_t   eqx,
        lg_Real_t   eqy,
        lg_Size_t   eqr_w,
        lg_Size_t   eqr_h,
        lg_Real_t * rcx,
        lg_Real_t * rcy,
        lg_Size_t   rct_w,
        lg_Size_t   rct_h,
        lg_Size_t   pan_w,
        lg_Size_t   pan_h,
        lg_Size_t   eqr_x,
        lg_Size_t   eqr_y,
        lg_Real_t   sen_x,
        lg_Real_t   sen_y

    ) {

        /* Projection Variables */
        lg_Real_t rx = 0.0;
        lg_Real_t ry = 0.0;
        lg_Real_t ux = 0.0;
        lg_Real_t uy = 0.0;
        lg_Real_t pt = 0.0;
        lg_Real_t pp = 0.0;
        lg_Real_t at = 0.0;
        lg_Real_t ap = 0.0;
        lg_Real_t nad_t = 0.0;
        lg_Real_t nad_p = 0.0;
        lg_Real_t app_t = 0.0;
        lg_Real_t app_p = 0.0;

        /* Position vector */
        lg_Real_t pv[3] = { 0.0, 0.0, 0.0 };
        lg_Real_t kv[3] = { 0.0, 0.0, 0.0 };

        /* Rotation matrix */
        lg_Real_t Ry[3][3] = { { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0 } };
        lg_Real_t Rz[3][3] = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } };

        /* Compute orientation variables */
        nad_t = ( sen_x / ( lg_Real_t ) pan_w ) * 2.0 * LG_PI;
        nad_p = ( 0.5 - ( sen_y / ( lg_Real_t ) pan_h ) ) * LG_PI;

        /* Rotation matrix - y */
        Ry[0][0] = + cos( - nad_p );
        Ry[0][2] = + sin( - nad_p );
        Ry[2][0] = - Ry[0][2];
        Ry[2][2] = + Ry[0][0];

        /* Rotation matrix - z */
        Rz[0][0] = + cos( - nad_t );
        Rz[0][1] = - sin( - nad_t );
        Rz[1][0] = - Rz[0][1];
        Rz[1][1] = + Rz[0][0];

        /* Compute angular appertures */
        app_t = ( ( lg_Real_t ) eqr_w / ( lg_Real_t ) pan_w ) * LG_PI;
        app_p = ( ( lg_Real_t ) eqr_h / ( lg_Real_t ) pan_h ) * LG_PI * 0.5;

        /* Compute angular apperture tangent */
        at = tan( app_t );
        ap = tan( app_p );

        /* Retreive angular position */
        pt =  2.0 * LG_PI * ( eqx + eqr_x ) /  ( lg_Real_t ) (pan_w -1) ;
        pp =  LG_PI * ( ( eqy + eqr_y ) / ( lg_Real_t ) ( pan_h - 1 ) - 0.5 );

        /* Rebuild position vector - x y z */
        pv[0] = cos( pp ) * cos ( pt );
        pv[1] = cos( pp ) * sin ( pt );
        pv[2] = sin( pp );

        /* Apply rotation due to t-nadir and p-nadir */
        kv[0] = Rz[0][0] * pv[0] + Rz[0][1] * pv[1];
        kv[1] = Rz[1][0] * pv[0] + Rz[1][1] * pv[1];
        kv[2] = pv[2];

        pv[0] = Ry[0][0] * kv[0] + Ry[0][2] * kv[2];
        pv[1] = kv[1];
        pv[2] = Ry[2][0] * kv[0] + Ry[2][2] * kv[2];

        /* Normalized planar coordinates */
        ux = pv[1] / pv[0];
        uy = pv[2] / pv[0];

        /* Retreive gnomonic pixels coordinates */
        rx = ( 1.0 + ux / at ) * ( rct_w - 1.0 ) * 0.5;
        ry = ( 1.0 + uy / ap ) * ( rct_h - 1.0 ) * 0.5;

        /* export coordinates */
        *rcx = rx;
        *rcy = ry;

    }

/*
    Source - Coordinates conversion from gnomonic to equirectangular tile
 */

   lg_Void_t lg_gtt_coord(

        lg_Real_t * eqx,
        lg_Real_t * eqy,
        lg_Size_t   eqr_w,
        lg_Size_t   eqr_h,
        lg_Real_t   rcx,
        lg_Real_t   rcy,
        lg_Size_t   rct_w,
        lg_Size_t   rct_h,
        lg_Size_t   pan_w,
        lg_Size_t   pan_h,
        lg_Size_t   eqr_x,
        lg_Size_t   eqr_y,
        lg_Real_t   sen_x,
        lg_Real_t   sen_y

    ) {

        /* Projection Variables */
        lg_Real_t dx = 0.0;
        lg_Real_t dy = 0.0;
        lg_Real_t ux = 0.0;
        lg_Real_t uy = 0.0;
        lg_Real_t pt = 0.0;
        lg_Real_t pp = 0.0;
        lg_Real_t at = 0.0;
        lg_Real_t ap = 0.0;
        lg_Real_t nad_t = 0.0;
        lg_Real_t nad_p = 0.0;
        lg_Real_t app_t = 0.0;
        lg_Real_t app_p = 0.0;

        /* Position vector */
        lg_Real_t pv[3] = { 0.0, 0.0, 0.0 };
        lg_Real_t kv[3] = { 0.0, 0.0, 0.0 };

        /* Rotation matrix */
        lg_Real_t Ry[3][3] = { { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 0.0 } };
        lg_Real_t Rz[3][3] = { { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 0.0, 1.0 } };

        /* Compute orientation variables */
        nad_t = ( sen_x / ( lg_Real_t ) pan_w ) * 2.0 * LG_PI;
        nad_p = ( 0.5 - ( sen_y / ( lg_Real_t ) pan_h ) ) * LG_PI;

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

        /* Compute angular appertures */
        app_t = ( ( lg_Real_t ) eqr_w / ( lg_Real_t ) pan_w ) * LG_PI;
        app_p = ( ( lg_Real_t ) eqr_h / ( lg_Real_t ) pan_h ) * LG_PI * 0.5;

        /* Compute angular apperture tangent */
        at = tan( app_t );
        ap = tan( app_p );

        /* Normalized planar coordinates */
        ux = ( ( 2.0 * ( lg_Real_t ) rcx / ( lg_Real_t ) ( rct_w - 1 ) ) - 1.0 ) * at;
        uy = ( ( 2.0 * ( lg_Real_t ) rcy / ( lg_Real_t ) ( rct_h - 1 ) ) - 1.0 ) * ap;

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

        /* Retreive angular position */
        pt = acos( pv[0] / sqrt( pv[0] * pv[0] + pv[1] * pv[1] ) ); pt = ( pv[1] < 0 ) ? ( 2.0 * LG_PI - pt ) : pt;
        pp = asin( pv[2] );

        /* Retrieve panoramic pixel coordinates */
        dx = ( pt / ( 2.0 * LG_PI ) ) * ( pan_w - 1 ) - eqr_x;
        dy = ( ( pp / LG_PI ) + 0.5 ) * ( pan_h - 1 ) - eqr_y;

        /* export coordinates */
        *eqx = dx;
        *eqy = dy;

    }

