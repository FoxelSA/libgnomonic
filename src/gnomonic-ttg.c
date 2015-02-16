/*
 * libgnomonic - Gnomonic projection algorithms library
 *
 * Copyright (c) 2013-2015 FOXEL SA - http://foxel.ch
 * Please read <http://foxel.ch/license> for more information.
 *
 *
 * Author(s):
 *
 *      Nils Hamel <n.hamel@foxel.ch>
 *
 * Contributor(s) :
 *
 *      Stephane Flotron <s.flotron@foxel.ch>
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
    Source - Equirectangular tile to rectilinear transform - Centered-specific
 */

    lg_Void_t lg_ttg_center(

        li_C8_t     const * const lgeBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        li_C8_t           * const lgrBitmap,
        lg_Size_t   const         lgrWidth,
        lg_Size_t   const         lgrHeight,
        lg_Size_t   const         lgrLayers,
        lg_Size_t   const         lgmWidth,
        lg_Size_t   const         lgmHeight,
        lg_Size_t   const         lgmCornerX,
        lg_Size_t   const         lgmCornerY,
        lg_Real_t   const         lgAzim,
        lg_Real_t   const         lgElev,
        lg_Real_t   const         lgRoll,
        lg_Real_t   const         lgFocal,
        lg_Real_t   const         lgPixel,
        li_Method_t const         lgInter

    ) { lg_ttg_centerp(

        lgeBitmap,
        lgeWidth,
        lgeHeight,
        lgeLayers,
        lgrBitmap,
        lgrWidth,
        lgrHeight,
        lgrLayers,
        lgmWidth,
        lgmHeight,
        lgmCornerX,
        lgmCornerY,
        lgAzim,
        lgElev,
        lgRoll,
        lgFocal,
        lgPixel,
        lgInter,
        lg_Size_s( 1 )

    ); }

    lg_Void_t lg_ttg_centerp(

        li_C8_t     const * const lgeBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        li_C8_t           * const lgrBitmap,
        lg_Size_t   const         lgrWidth,
        lg_Size_t   const         lgrHeight,
        lg_Size_t   const         lgrLayers,
        lg_Size_t   const         lgmWidth,
        lg_Size_t   const         lgmHeight,
        lg_Size_t   const         lgmCornerX,
        lg_Size_t   const         lgmCornerY,
        lg_Real_t   const         lgAzim,
        lg_Real_t   const         lgElev,
        lg_Real_t   const         lgRoll,
        lg_Real_t   const         lgFocal,
        lg_Real_t   const         lgPixel,
        li_Method_t const         lgInter,
        lg_Size_t   const         lgThread

    ) { lg_ttg_genericp(

        lgeBitmap,
        lgeWidth,
        lgeHeight,
        lgeLayers,
        lgrBitmap,
        lgrWidth,
        lgrHeight,
        lgrLayers,
        lg_Real_c( lgrWidth  ) / lg_Real_s( 2.0 ),
        lg_Real_c( lgrHeight ) / lg_Real_s( 2.0 ),
        lgmWidth,
        lgmHeight,
        lgmCornerX,
        lgmCornerY,
        lgAzim,
        lgElev,
        lgRoll,
        lgFocal,
        lgPixel,
        lgInter,
        lgThread

    ); }

    lg_Void_t lg_ttg_center_point(

        lg_Real_t const         lgePointX,
        lg_Real_t const         lgePointY,
        lg_Real_t       * const lgrPointX,
        lg_Real_t       * const lgrPointY,
        lg_Size_t const         lgrWidth,
        lg_Size_t const         lgrHeight,
        lg_Size_t const         lgmWidth,
        lg_Size_t const         lgmHeight,
        lg_Size_t const         lgmCornerX,
        lg_Size_t const         lgmCornerY,
        lg_Real_t const         lgAzim,
        lg_Real_t const         lgElev,
        lg_Real_t const         lgRoll,
        lg_Real_t const         lgFocal,
        lg_Real_t const         lgPixel

    ) { lg_ttg_generic_point(

        lgePointX,
        lgePointY,
        lgrPointX,
        lgrPointY,
        lg_Real_c( lgrWidth  ) / lg_Real_s( 2.0 ),
        lg_Real_c( lgrHeight ) / lg_Real_s( 2.0 ),
        lgmWidth,
        lgmHeight,
        lgmCornerX,
        lgmCornerY,
        lgAzim,
        lgElev,
        lgRoll,
        lgFocal,
        lgPixel

    ); }

/*
    Source - Equirectangular tile to rectilinear transform - Elphel-specific
 */

    lg_Void_t lg_ttg_elphel(

        li_C8_t     const * const lgeBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        li_C8_t           * const lgrBitmap,
        lg_Size_t   const         lgrWidth,
        lg_Size_t   const         lgrHeight,
        lg_Size_t   const         lgrLayers,
        lg_Real_t   const         lgrSightX,
        lg_Real_t   const         lgrSightY,
        lg_Size_t   const         lgmWidth,
        lg_Size_t   const         lgmHeight,
        lg_Size_t   const         lgmCornerX,
        lg_Size_t   const         lgmCornerY,
        lg_Real_t   const         lgRoll,
        lg_Real_t   const         lgAzim,
        lg_Real_t   const         lgElev,
        lg_Real_t   const         lgHead,
        lg_Real_t   const         lgPixel,
        lg_Real_t   const         lgFocal,
        li_Method_t const         lgInter

    ) { lg_ttg_elphelp(

        lgeBitmap,
        lgeWidth,
        lgeHeight,
        lgeLayers,
        lgrBitmap,
        lgrWidth,
        lgrHeight,
        lgrLayers,
        lgrSightX,
        lgrSightY,
        lgmWidth,
        lgmHeight,
        lgmCornerX,
        lgmCornerY,
        lgRoll,
        lgAzim,
        lgElev,
        lgHead,
        lgPixel,
        lgFocal,
        lgInter,
        lg_Size_s( 1 )

    ); }

    lg_Void_t lg_ttg_elphelp(

        li_C8_t     const * const lgeBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        li_C8_t           * const lgrBitmap,
        lg_Size_t   const         lgrWidth,
        lg_Size_t   const         lgrHeight,
        lg_Size_t   const         lgrLayers,
        lg_Real_t   const         lgrSightX,
        lg_Real_t   const         lgrSightY,
        lg_Size_t   const         lgmWidth,
        lg_Size_t   const         lgmHeight,
        lg_Size_t   const         lgmCornerX,
        lg_Size_t   const         lgmCornerY,
        lg_Real_t   const         lgRoll,
        lg_Real_t   const         lgAzim,
        lg_Real_t   const         lgElev,
        lg_Real_t   const         lgHead,
        lg_Real_t   const         lgPixel,
        lg_Real_t   const         lgFocal,
        li_Method_t const         lgInter,
        lg_Size_t   const         lgThread

    ) { lg_ttg_genericp(

        lgeBitmap,
        lgeWidth,
        lgeHeight,
        lgeLayers,
        lgrBitmap,
        lgrWidth,
        lgrHeight,
        lgrLayers,
        lgrSightX,
        lgrSightY,
        lgmWidth,
        lgmHeight,
        lgmCornerX,
        lgmCornerY,
        lgAzim + lgHead + LG_PI,
        lgElev,
        lgRoll,
        lgFocal,
        lgPixel,
        lgInter,
        lgThread

    ); }

    lg_Void_t lg_ttg_elphel_point(

        lg_Real_t const         lgePointX,
        lg_Real_t const         lgePointY,
        lg_Real_t       * const lgrPointX,
        lg_Real_t       * const lgrPointY,
        lg_Real_t const         lgrSightX,
        lg_Real_t const         lgrSightY,
        lg_Size_t const         lgmWidth,
        lg_Size_t const         lgmHeight,
        lg_Size_t const         lgmCornerX,
        lg_Size_t const         lgmCornerY,
        lg_Real_t const         lgRoll,
        lg_Real_t const         lgAzim,
        lg_Real_t const         lgElev,
        lg_Real_t const         lgHead,
        lg_Real_t const         lgPixel,
        lg_Real_t const         lgFocal

    ) { lg_ttg_generic_point(

        lgePointX,
        lgePointY,
        lgrPointX,
        lgrPointY,
        lgrSightX,
        lgrSightY,
        lgmWidth,
        lgmHeight,
        lgmCornerX,
        lgmCornerY,
        lgAzim + lgHead + LG_PI,
        lgElev,
        lgRoll,
        lgFocal,
        lgPixel

    ); }

/*
    Source - Equirectangular tile to rectilinear transform
 */

    lg_Void_t lg_ttg_generic(

        li_C8_t     const * const lgeBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        li_C8_t           * const lgrBitmap,
        lg_Size_t   const         lgrWidth,
        lg_Size_t   const         lgrHeight,
        lg_Size_t   const         lgrLayers,
        lg_Real_t   const         lgrSightX,
        lg_Real_t   const         lgrSightY,
        lg_Size_t   const         lgmWidth,
        lg_Size_t   const         lgmHeight,
        lg_Size_t   const         lgmCornerX,
        lg_Size_t   const         lgmCornerY,
        lg_Real_t   const         lgAzim,
        lg_Real_t   const         lgElev,
        lg_Real_t   const         lgRoll,
        lg_Real_t   const         lgFocal,
        lg_Real_t   const         lgPixel,
        li_Method_t const         lgInter

    ) { lg_ttg_genericp(

        lgeBitmap,
        lgeWidth,
        lgeHeight,
        lgeLayers,
        lgrBitmap,
        lgrWidth,
        lgrHeight,
        lgrLayers,
        lgrSightX,
        lgrSightY,
        lgmWidth,
        lgmHeight,
        lgmCornerX,
        lgmCornerY,
        lgAzim,
        lgElev,
        lgRoll,
        lgFocal,
        lgPixel,
        lgInter,
        lg_Size_s( 1 )

    ); }

    lg_Void_t lg_ttg_genericp(

        li_C8_t     const * const lgeBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        li_C8_t           * const lgrBitmap,
        lg_Size_t   const         lgrWidth,
        lg_Size_t   const         lgrHeight,
        lg_Size_t   const         lgrLayers,
        lg_Real_t   const         lgrSightX,
        lg_Real_t   const         lgrSightY,
        lg_Size_t   const         lgmWidth,
        lg_Size_t   const         lgmHeight,
        lg_Size_t   const         lgmCornerX,
        lg_Size_t   const         lgmCornerY,
        lg_Real_t   const         lgAzim,
        lg_Real_t   const         lgElev,
        lg_Real_t   const         lgRoll,
        lg_Real_t   const         lgFocal,
        lg_Real_t   const         lgPixel,
        li_Method_t const         lgInter,
        lg_Size_t   const         lgThread

    ) {

        /* Coordinates variables */
        lg_Size_t lgDX = lg_Size_s( 0   );
        lg_Size_t lgDY = lg_Size_s( 0   );
        lg_Real_t lgSX = lg_Real_s( 0.0 );
        lg_Real_t lgSY = lg_Real_s( 0.0 );

        /* Position vector variables */
        lg_Real_t lgPvi[3] = { lg_Real_s( 0.0 ) };
        lg_Real_t lgPvf[3] = { lg_Real_s( 0.0 ) };

        /* Rotation matrix variables */
        lg_Real_t lgMat[3][3] = { { lg_Real_s( 0.0 ) } };

        /* Optimization variables */
        lg_Size_t lgmEdgeX = lgmWidth  - lg_Size_s( 1 );
        lg_Size_t lgmEdgeY = lgmHeight - lg_Size_s( 1 );

        /* Transparency variables */
        lg_Real_t lgWeiA = lg_Real_s( 0.0 );
        lg_Real_t lgWeiB = lg_Real_s( 0.0 );

        /* Alpha channel variables */
        li_C8_t lgAlpha = li_C8_s( 0 );

        /* Bitmap padding variable */
        lg_Size_t lgrPad = LG_B4PAD( lgrWidth * lgrLayers );

        /* Compute rotation matrix */
        lg_algebra_r2erotation( lgMat, lgAzim, lgElev, lgRoll );

        /* Rectilinear pixels y-loop */
        # ifdef __OPENMP__
        # pragma omp parallel private(lgDX,lgDY,lgSX,lgSY,lgPvi,lgPvf,lgAlpha,lgWeiA,lgWeiB) firstprivate(lgmEdgeX,lgmEdgeY,lgrPad,lgMat) num_threads( lgThread )
        {
        # pragma omp for
        # endif
        for ( lgDY = lg_Size_s( 0 ); lgDY < lgrHeight; lgDY ++ ) {

            /* Rectilinear pixels x-loop */
            for ( lgDX = lg_Size_s( 0 ); lgDX < lgrWidth; lgDX ++ ) {

                /* Compute pixel position in 3d-frame */
                lgPvi[0] = lgFocal;
                lgPvi[1] = lgPixel * ( lg_Real_c( lgDX ) - lgrSightX );
                lgPvi[2] = lgPixel * ( lg_Real_c( lgDY ) - lgrSightY );

                /* Compute rotated pixel position in 3d-frame */
                lgPvf[0] = lgMat[0][0] * lgPvi[0] + lgMat[0][1] * lgPvi[1] + lgMat[0][2] * lgPvi[2];
                lgPvf[1] = lgMat[1][0] * lgPvi[0] + lgMat[1][1] * lgPvi[1] + lgMat[1][2] * lgPvi[2];
                lgPvf[2] = lgMat[2][0] * lgPvi[0] + lgMat[2][1] * lgPvi[1] + lgMat[2][2] * lgPvi[2];

                /* Retrieve mapping pixel (x,y)-coordinates */
                lgSX = - lgmCornerX + lgmEdgeX * ( LG_ATN( lgPvf[0], lgPvf[1] ) / LG_PI2 ) ;
                lgSY = - lgmCornerY + lgmEdgeY * ( LG_ASN( lgPvf[2] / LG_EUCLR3( lgPvf ) ) / LG_PI + lg_Real_s( 0.5 ) );

                /* Mapping boundary conditions management */
                lgSX = ( lgSX < lg_Size_s( 0 ) ) ? lgSX + lgmWidth : lgSX;

                /* Verify coordinates range */
                if ( ( lgSX >= lg_Real_s( 0.0 ) ) && ( lgSY >= lg_Real_s( 0.0 ) ) && ( lgSX < lgeWidth ) && ( lgSY < lgeHeight ) ) {

                    /* Transparency management */
                    if ( lgeLayers == lg_Size_s( 4 ) ) {

                        /* Obtain alpha value and compute direct transparency weight */
                        lgAlpha = lgInter( ( li_C8_t * ) lgeBitmap, lgeWidth, lgeHeight, lgeLayers, lg_Size_s( 3 ), lgSX, lgSY );

                        /* Compute transparency weights */
                        lgWeiA = lg_Real_c( lgAlpha ) / lg_Real_s( 255.0 );
                        lgWeiB = lg_Real_s( 1.0 ) - lgWeiA;

                        /* Assign interpolated pixel */
                        LG_B4( lgrBitmap, lgrPad, lgrLayers, lgDX, lgDY, lg_Size_s( 0 ) ) = lgInter( 

                            ( li_C8_t * ) lgeBitmap, 
                            lgeWidth, 
                            lgeHeight, 
                            lgeLayers, 
                            lg_Size_s( 0 ), 
                            lgSX,
                            lgSY

                        ) * lgWeiA + LG_B4( lgrBitmap, lgrPad, lgrLayers, lgDX, lgDY, lg_Size_s( 0 ) ) * lgWeiB;

                        /* Assign interpolated pixel */
                        LG_B4( lgrBitmap, lgrPad, lgrLayers, lgDX, lgDY, lg_Size_s( 1 ) ) = lgInter( 

                            ( li_C8_t * ) lgeBitmap,
                            lgeWidth, 
                            lgeHeight, 
                            lgeLayers, 
                            lg_Size_s( 1 ), 
                            lgSX, 
                            lgSY

                        ) * lgWeiA + LG_B4( lgrBitmap, lgrPad, lgrLayers, lgDX, lgDY, lg_Size_s( 1 ) ) * lgWeiB;;

                        /* Assign interpolated pixel */
                        LG_B4( lgrBitmap, lgrPad, lgrLayers, lgDX, lgDY, lg_Size_s( 2 ) ) = lgInter( 

                            ( li_C8_t * ) lgeBitmap, 
                            lgeWidth, 
                            lgeHeight, 
                            lgeLayers, 
                            lg_Size_s( 2 ), 
                            lgSX, 
                            lgSY

                        ) * lgWeiA + LG_B4( lgrBitmap, lgrPad, lgrLayers, lgDX, lgDY, lg_Size_s( 2 ) ) * lgWeiB;;

                        /* Assign transparency pixel */
                        if ( lgrLayers == 4 ) LG_B4( lgrBitmap, lgrPad, lgrLayers, lgDX, lgDY, lg_Size_s( 3 ) ) = lgAlpha;

                    } else {

                        /* Assign interpolated pixel */
                        LG_B4( lgrBitmap, lgrPad, lgrLayers, lgDX, lgDY, lg_Size_s( 0 ) ) = lgInter( 

                            ( li_C8_t * ) lgeBitmap, 
                            lgeWidth, 
                            lgeHeight, 
                            lgeLayers, 
                            lg_Size_s( 0 ), 
                            lgSX,
                            lgSY

                        );

                        /* Assign interpolated pixel */
                        LG_B4( lgrBitmap, lgrPad, lgrLayers, lgDX, lgDY, lg_Size_s( 1 ) ) = lgInter( 

                            ( li_C8_t * ) lgeBitmap,
                            lgeWidth, 
                            lgeHeight, 
                            lgeLayers, 
                            lg_Size_s( 1 ), 
                            lgSX, 
                            lgSY

                        );

                        /* Assign interpolated pixel */
                        LG_B4( lgrBitmap, lgrPad, lgrLayers, lgDX, lgDY, lg_Size_s( 2 ) ) = lgInter( 

                            ( li_C8_t * ) lgeBitmap, 
                            lgeWidth, 
                            lgeHeight, 
                            lgeLayers, 
                            lg_Size_s( 2 ), 
                            lgSX, 
                            lgSY

                        );

                    }

                }

            }

        }

        # ifdef __OPENMP__
        }
        # endif 

    }

    lg_Void_t lg_ttg_generic_point(

        lg_Real_t const         lgePointX,
        lg_Real_t const         lgePointY,
        lg_Real_t       * const lgrPointX,
        lg_Real_t       * const lgrPointY,
        lg_Real_t const         lgrSightX,
        lg_Real_t const         lgrSightY,
        lg_Size_t const         lgmWidth,
        lg_Size_t const         lgmHeight,
        lg_Size_t const         lgmCornerX,
        lg_Size_t const         lgmCornerY,
        lg_Real_t const         lgAzim,
        lg_Real_t const         lgElev,
        lg_Real_t const         lgRoll,
        lg_Real_t const         lgFocal,
        lg_Real_t const         lgPixel

    ) {

         /* Matrix array variables */
        lg_Real_t lgMat[3][3] = { { lg_Real_s( 0.0 ) } };

        /* Position arrays variables */
        lg_Real_t lgPvi[3] = { lg_Real_s( 0.0 ) };
        lg_Real_t lgPvf[3] = { lg_Real_s( 0.0 ) };

        /* Angular position variables */
        lg_Real_t lgAngleX = lg_Real_s( 0.0 );
        lg_Real_t lgAngleY = lg_Real_s( 0.0 );

        /* Compute rotation matrix */
        lg_algebra_e2rrotation( lgMat, lgAzim, lgElev, lgRoll );

        /* Compute mapping angular coordinates */
        lgAngleX = + ( ( ( lgePointX + lg_Real_c( lgmCornerX ) ) / lg_Real_c( lgmWidth  - lg_Size_s( 1 ) ) ) * LG_PI2 );
        lgAngleY = + ( ( ( lgePointY + lg_Real_c( lgmCornerY ) ) / lg_Real_c( lgmHeight - lg_Size_s( 1 ) ) ) - lg_Real_s( 0.5 ) ) * LG_PI;

        /* Compute pixel position in 3d-frame */
        lgPvi[0] = cos( lgAngleY );
        lgPvi[1] = sin( lgAngleX ) * lgPvi[0];
        lgPvi[0] = cos( lgAngleX ) * lgPvi[0];
        lgPvi[2] = sin( lgAngleY );

        /* Compute rotated pixel position in 3d-frame */
        lgPvf[0] = lgMat[0][0] * lgPvi[0] + lgMat[0][1] * lgPvi[1] + lgMat[0][2] * lgPvi[2];
        lgPvf[1] = lgMat[1][0] * lgPvi[0] + lgMat[1][1] * lgPvi[1] + lgMat[1][2] * lgPvi[2];
        lgPvf[2] = lgMat[2][0] * lgPvi[0] + lgMat[2][1] * lgPvi[1] + lgMat[2][2] * lgPvi[2];

        /* Retrieve rectilinear (x,y)-coordinates */
        ( * lgrPointX ) = + ( ( lgPvf[1] / lgPvf[0] ) * lgFocal ) / lgPixel + lgrSightX;
        ( * lgrPointY ) = + ( ( lgPvf[2] / lgPvf[0] ) * lgFocal ) / lgPixel + lgrSightY;

    }

