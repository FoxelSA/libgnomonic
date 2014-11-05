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
    Source - Equirectangular mapping rotation
 */

    lg_Void_t lg_transform_rotate( 

        li_C8_t     const * const lgiBitmap,
        li_C8_t           * const lgoBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        lg_Real_t   const         lgAzim,
        lg_Real_t   const         lgElev,
        lg_Real_t   const         lgRoll,
        li_Method_t const         lgInter

    ) { lg_transform_rotatep(

        lgiBitmap,
        lgoBitmap,
        lgeWidth,
        lgeHeight,
        lgeLayers,
        lgAzim,
        lgElev,
        lgRoll,
        lgInter,
        lg_Size_s( 1 )

    ); }

    lg_Void_t lg_transform_rotatep( 

        li_C8_t     const * const lgiBitmap,
        li_C8_t           * const lgoBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        lg_Real_t   const         lgAzim,
        lg_Real_t   const         lgElev,
        lg_Real_t   const         lgRoll,
        li_Method_t const         lgInter,
        lg_Size_t   const         lgThread

    ) {

        /* Coordinates variables */
        lg_Size_t lgSX = lg_Size_s( 0   );
        lg_Size_t lgSY = lg_Size_s( 0   );
        lg_Real_t lgDX = lg_Real_s( 0.0 );
        lg_Real_t lgDY = lg_Real_s( 0.0 );

        /* Optimization variables */
        lg_Real_t lgeEdgeX = lgeWidth  - lg_Size_s( 1 );
        lg_Real_t lgeEdgeY = lgeHeight - lg_Size_s( 1 );

        /* Position vector variables */
        lg_Real_t lgPvi[3] = { lg_Real_s( 0.0 ) };
        lg_Real_t lgPvf[3] = { lg_Real_s( 0.0 ) };

        /* Rotation matrix variables */
        lg_Real_t lgMat[3][3] = { { lg_Real_s( 0.0 ) } };

        /* Bitmap padding variable */
        lg_Size_t lgePad = LG_B4PAD( lgeWidth * lgeLayers );

        /* Compute rotation matrix */
        lg_algebra_r2erotation( lgMat, lgAzim, lgElev, lgRoll );

        /* Processing loop on y */
        # ifdef __OPENMP__
        # pragma omp parallel private(lgSX,lgSY,lgDX,lgDY,lgPvi,lgPvf) firstprivate(lgeEdgeX,lgeEdgeY,lgePad,lgMat) num_threads( lgThread )
        {
        # pragma omp for
        # endif
        for ( lgSY = lg_Size_s( 0 ); lgSY < lgeHeight; lgSY ++ ) {

            /* Processing loop on x */
            for ( lgSX = lg_Size_s( 0 ); lgSX < lgeWidth; lgSX ++ ) {

                /* Compute mapping pixel angular coordinates */
                lgDX = ( ( lg_Real_c( lgSX ) / lgeEdgeX ) * lg_Real_s( 2.0 ) ) * LG_PI;
                lgDY = ( ( lg_Real_c( lgSY ) / lgeEdgeY ) - lg_Real_s( 0.5 ) ) * LG_PI;

                /* Compute pixel position in 3d-frame */
                lgPvi[0] = cos( lgDY ) * cos( lgDX );
                lgPvi[1] = cos( lgDY ) * sin( lgDX );
                lgPvi[2] = sin( lgDY );

                /* Compute rotated pixel position in 3d-frame */
                lgPvf[0] = lgMat[0][0] * lgPvi[0] + lgMat[0][1] * lgPvi[1] + lgMat[0][2] * lgPvi[2];
                lgPvf[1] = lgMat[1][0] * lgPvi[0] + lgMat[1][1] * lgPvi[1] + lgMat[1][2] * lgPvi[2];
                lgPvf[2] = lgMat[2][0] * lgPvi[0] + lgMat[2][1] * lgPvi[1] + lgMat[2][2] * lgPvi[2];

                /* Retrieve mapping pixel (x,y)-coordinates */
                lgDX = lgeEdgeX * ( LG_ATN( lgPvf[0] , lgPvf[1] ) / LG_PI2 );
                lgDY = lgeEdgeY * ( ( LG_ASN( lgPvf[2] ) / LG_PI ) + lg_Real_s( 0.5 ) );

                /* Assign interpolated pixel */
                LG_B4( lgoBitmap, lgePad, lgeLayers, lgSX, lgSY, lg_Size_s( 0 ) ) = lgInter( ( li_C8_t * ) lgiBitmap, lgeWidth, lgeHeight, lgeLayers, lg_Size_s( 0 ), lgDX, lgDY );
                LG_B4( lgoBitmap, lgePad, lgeLayers, lgSX, lgSY, lg_Size_s( 1 ) ) = lgInter( ( li_C8_t * ) lgiBitmap, lgeWidth, lgeHeight, lgeLayers, lg_Size_s( 1 ), lgDX, lgDY );
                LG_B4( lgoBitmap, lgePad, lgeLayers, lgSX, lgSY, lg_Size_s( 2 ) ) = lgInter( ( li_C8_t * ) lgiBitmap, lgeWidth, lgeHeight, lgeLayers, lg_Size_s( 2 ), lgDX, lgDY );

            }

        }

        # ifdef __OPENMP__
        }
        # endif 

    }

