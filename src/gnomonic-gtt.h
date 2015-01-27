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

    /*! \file   gnomonic-gtt.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  Rectilinear tile to equirectangular tile transforms
     */

/*
    Header - Include guard
 */

    # ifndef __LG_GTT__
    # define __LG_GTT__

/*
    Header - C/C++ compatibility
 */

    # ifdef __cplusplus
    extern "C" {
    # endif

/*
    Header - Includes
 */

    # include "gnomonic.h"
    # include "gnomonic-algebra.h"

/*
    Header - Preprocessor definitions
 */

/*
    Header - Preprocessor macros
 */

/*
    Header - Typedefs
 */

/*
    Header - Structures
 */

/*
    Header - Function prototypes
 */

    /*! \brief Rectilinear to equirectangular tile transform - Centered-specific
     *
     *  This function is the mono-threaded front-end to the definition of the
     *  lg_gtt_center.
     *
     *  \param lgeBitmap      Pointer to equirectangular tile bitmap
     *  \param lgeWidth       Width, in pixels, of the equirectangular tile
     *                        bitmap
     *  \param lgeHeight      Height, in pixels, of the equirectangular tile
     *                        bitmap
     *  \param lgeLayers      Depth, in chromatic layer count, of equirectangular 
     *                        tile bitmap
     *  \param lgrBitmap      Pointer to rectilinear bitmap that recieve the 
     *                        gnomonic projection
     *  \param lgrWidth       Width, in pixels, of the rectilinear bitmap
     *  \param lgrHeight      Height, in pixels, of the rectilinear bitmap
     *  \param lgrLayers      Depth, in chromatic layer count, of rectilinear 
     *                        bitmap
     *  \param lgmWidth       Width, in pixels, of the entire equirectangular 
     *                        mapping from which the tile is extracted
     *  \param lgmHeight      Height, in pixels, of the entire equirectangular 
     *                        mapping from which the tile is extracted
     *  \param lgmCornerX     Position X, in pixels, of the equirectangular tile
     *                        top-left corner in the entire mapping
     *  \param lgmCornerY     Position Y, in pixels, of the equirectangular tile
     *                        top-left corner in the entire mapping
     *  \param lgAzim         Azimuth angle, in radians, of gnomonic center
     *  \param lgElev         Elevation angle, in radians, of gnomonic center
     *  \param lgRoll         Roll angle, in radians, around gnomonic axis
     *  \param lgFocal        Focal length, in mm, of the rectilinear image
     *  \param lgPixel        Length, in mm, of the pixels of the rectilinear
     *                        image virtual camera
     *  \param lgInter        Pointer to interpolation method function
     */

    lg_Void_t lg_gtt_center(

        li_C8_t           * const lgeBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        li_C8_t     const * const lgrBitmap,
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

    );

    /*! \brief Rectilinear to equirectangular tile transform - Centered-specific
     *
     *  This function offers the inverted gnomonic projection provided by the
     *  centered specific lg_ttg_centerp function. Their parameters are the same
     *  and have to be understood in the exact same way, swapping input and 
     *  output role of the provided bitmaps.
     *
     *  This function is then a front-end to the lg_gtt_genericp function in the
     *  same way lg_ttg_centerp is a front-end to the lg_ttg_genericp function.
     *
     *  \param lgeBitmap      Pointer to equirectangular tile bitmap
     *  \param lgeWidth       Width, in pixels, of the equirectangular tile
     *                        bitmap
     *  \param lgeHeight      Height, in pixels, of the equirectangular tile
     *                        bitmap
     *  \param lgeLayers      Depth, in chromatic layer count, of equirectangular 
     *                        tile bitmap
     *  \param lgrBitmap      Pointer to rectilinear bitmap that recieve the 
     *                        gnomonic projection
     *  \param lgrWidth       Width, in pixels, of the rectilinear bitmap
     *  \param lgrHeight      Height, in pixels, of the rectilinear bitmap
     *  \param lgrLayers      Depth, in chromatic layer count, of rectilinear 
     *                        bitmap
     *  \param lgmWidth       Width, in pixels, of the entire equirectangular 
     *                        mapping from which the tile is extracted
     *  \param lgmHeight      Height, in pixels, of the entire equirectangular 
     *                        mapping from which the tile is extracted
     *  \param lgmCornerX     Position X, in pixels, of the equirectangular tile
     *                        top-left corner in the entire mapping
     *  \param lgmCornerY     Position Y, in pixels, of the equirectangular tile
     *                        top-left corner in the entire mapping
     *  \param lgAzim         Azimuth angle, in radians, of gnomonic center
     *  \param lgElev         Elevation angle, in radians, of gnomonic center
     *  \param lgRoll         Roll angle, in radians, around gnomonic axis
     *  \param lgFocal        Focal length, in mm, of the rectilinear image
     *  \param lgPixel        Length, in mm, of the pixels of the rectilinear
     *                        image virtual camera
     *  \param lgInter        Pointer to interpolation method function
     *  \param lgThread       Thread number (OpenMP)
     */

    lg_Void_t lg_gtt_centerp(

        li_C8_t           * const lgeBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        li_C8_t     const * const lgrBitmap,
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

    );

    /*! \brief Rectilinear to equirectangular tile transform - Elphel-specific
     *
     *  This function is the mono-threaded front-end to the definition of the
     *  lg_gtt_elphelp.
     *
     *  \param lgeBitmap      Pointer to equirectangular tile bitmap
     *  \param lgeWidth       Width, in pixels, of the equirectangular tile
     *                        bitmap
     *  \param lgeHeight      Height, in pixels, of the equirectangular tile
     *                        bitmap
     *  \param lgeLayers      Depth, in chromatic layer count, of equirectangular 
     *                        tile bitmap
     *  \param lgrBitmap      Pointer to rectilinear bitmap that recieve the 
     *                        gnomonic projection
     *  \param lgrWidth       Width, in pixels, of the rectilinear bitmap
     *  \param lgrHeight      Height, in pixels, of the rectilinear bitmap
     *  \param lgrLayers      Depth, in chromatic layer count, of rectilinear 
     *                        bitmap
     *  \param lgrSightX      Position X, in pixels on rectilinear image,of the
     *                        gnomonic projection center
     *  \param lgrSightY      Position Y, in pixels on rectilinear image,of the
     *                        gnomonic projection center
     *  \param lgmWidth       Width, in pixels, of the entire equirectangular 
     *                        mapping from which the tile is extracted
     *  \param lgmHeight      Height, in pixels, of the entire equirectangular 
     *                        mapping from which the tile is extracted
     *  \param lgmCornerX     Position X, in pixels, of the equirectangular tile
     *                        top-left corner in the entire mapping
     *  \param lgmCornerY     Position Y, in pixels, of the equirectangular tile
     *                        top-left corner in the entire mapping
     *  \param lgRoll         Elphel calirbation roll angle, in radians
     *  \param lgAzim         Elphel calirbation azimuth angle, in radians
     *  \param lgElev         Elphel calirbation elevation angle, in radians
     *  \param lgHead         Elphel calirbation heading angle, in radians
     *  \param lgFocal        Focal length, in mm, of the rectilinear image
     *  \param lgPixel        Length, in mm, of the pixels of the rectilinear
     *                        image virtual camera
     *  \param lgInter        Pointer to interpolation method function
     */

    lg_Void_t lg_gtt_elphel(

        li_C8_t           * const lgeBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        li_C8_t     const * const lgrBitmap,
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

    );

    /*! \brief Rectilinear to equirectangular tile transform - Elphel-specific
     *
     *  This function offers the inverted gnomonic projection provided by the
     *  Elphel calibrated cameras specific lg_ttg_elphelp function. Their
     *  parameters are the same and have to be understood in the exact same way,
     *  swapping input and output role of the provided bitmaps.
     *
     *  This function is then a front-end to the lg_gtt_genericp function in the
     *  same way lg_ttg_elphelp is a front-end to the lg_ttg_genericp function.
     *
     *  \param lgeBitmap      Pointer to equirectangular tile bitmap
     *  \param lgeWidth       Width, in pixels, of the equirectangular tile
     *                        bitmap
     *  \param lgeHeight      Height, in pixels, of the equirectangular tile
     *                        bitmap
     *  \param lgeLayers      Depth, in chromatic layer count, of equirectangular 
     *                        tile bitmap
     *  \param lgrBitmap      Pointer to rectilinear bitmap that recieve the 
     *                        gnomonic projection
     *  \param lgrWidth       Width, in pixels, of the rectilinear bitmap
     *  \param lgrHeight      Height, in pixels, of the rectilinear bitmap
     *  \param lgrLayers      Depth, in chromatic layer count, of rectilinear 
     *                        bitmap
     *  \param lgrSightX      Position X, in pixels on rectilinear image,of the
     *                        gnomonic projection center
     *  \param lgrSightY      Position Y, in pixels on rectilinear image,of the
     *                        gnomonic projection center
     *  \param lgmWidth       Width, in pixels, of the entire equirectangular 
     *                        mapping from which the tile is extracted
     *  \param lgmHeight      Height, in pixels, of the entire equirectangular 
     *                        mapping from which the tile is extracted
     *  \param lgmCornerX     Position X, in pixels, of the equirectangular tile
     *                        top-left corner in the entire mapping
     *  \param lgmCornerY     Position Y, in pixels, of the equirectangular tile
     *                        top-left corner in the entire mapping
     *  \param lgRoll         Elphel calirbation roll angle, in radians
     *  \param lgAzim         Elphel calirbation azimuth angle, in radians
     *  \param lgElev         Elphel calirbation elevation angle, in radians
     *  \param lgHead         Elphel calirbation heading angle, in radians
     *  \param lgFocal        Focal length, in mm, of the rectilinear image
     *  \param lgPixel        Length, in mm, of the pixels of the rectilinear
     *                        image virtual camera
     *  \param lgInter        Pointer to interpolation method function
     *  \param lgThread       Thread number (OpenMP)
     */

    lg_Void_t lg_gtt_elphelp(

        li_C8_t           * const lgeBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        li_C8_t     const * const lgrBitmap,
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

    );

    /*! \brief Rectilinear to equirectangular tile transform
     *
     *  This function is the mono-threaded front-end to the definition of the
     *  lg_gtt_genericp.
     *
     *  \param lgeBitmap      Pointer to equirectangular tile bitmap
     *  \param lgeWidth       Width, in pixels, of the equirectangular tile
     *                        bitmap
     *  \param lgeHeight      Height, in pixels, of the equirectangular tile
     *                        bitmap
     *  \param lgeLayers      Depth, in chromatic layer count, of equirectangular 
     *                        tile bitmap
     *  \param lgrBitmap      Pointer to rectilinear bitmap that recieve the 
     *                        gnomonic projection
     *  \param lgrWidth       Width, in pixels, of the rectilinear bitmap
     *  \param lgrHeight      Height, in pixels, of the rectilinear bitmap
     *  \param lgrLayers      Depth, in chromatic layer count, of rectilinear 
     *                        bitmap
     *  \param lgrSightX      Position X, in pixels on rectilinear image,of the
     *                        gnomonic projection center
     *  \param lgrSightY      Position Y, in pixels on rectilinear image,of the
     *                        gnomonic projection center
     *  \param lgmWidth       Width, in pixels, of the entire equirectangular 
     *                        mapping from which the tile is extracted
     *  \param lgmHeight      Height, in pixels, of the entire equirectangular 
     *                        mapping from which the tile is extracted
     *  \param lgmCornerX     Position X, in pixels, of the equirectangular tile
     *                        top-left corner in the entire mapping
     *  \param lgmCornerY     Position Y, in pixels, of the equirectangular tile
     *                        top-left corner in the entire mapping
     *  \param lgAzim         Azimuth angle, in radians, of gnomonic center
     *  \param lgElev         Elevation angle, in radians, of gnomonic center
     *  \param lgRoll         Roll angle, in radians, around gnomonic axis
     *  \param lgFocal        Focal length, in mm, of the rectilinear image
     *  \param lgPixel        Length, in mm, of the pixels of the rectilinear
     *                        image virtual camera
     *  \param lgInter        Pointer to interpolation method function
     */

    lg_Void_t lg_gtt_generic(

        li_C8_t           * const lgeBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        li_C8_t     const * const lgrBitmap,
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

    );

    /*! \brief Rectilinear to equirectangular tile transform
     *
     *  This function offers the inverted gnomonic projection provided by the
     *  generic function lg_ttg_genericp. Their parameters are the same and have
     *  to be understood in the exact same way, swapping input and output role
     *  of the provided bitmaps.
     *
     *  The input rectilinear bitmap has to be a three or four chromatic layers 
     *  bitmap and the output equirectangular bitmap has to be already allocated
     *  according to its parameters and has to come with three or four chromatic
     *  layers. The bitmaps are standard bitmaps that considers byte padding in
     *  memory.
     *
     *  When input rectilinear bitmap comes with an alpha channel, it is used
     *  do define rectilinear pixels transparency. If the output equirectangular
     *  bitmap is allocated with an alpha channel, the de-projected alpha channel
     *  of the rectilinear bitmap is written in the equirectangular alpha channel.
     *
     *  \param lgeBitmap      Pointer to equirectangular tile bitmap
     *  \param lgeWidth       Width, in pixels, of the equirectangular tile
     *                        bitmap
     *  \param lgeHeight      Height, in pixels, of the equirectangular tile
     *                        bitmap
     *  \param lgeLayers      Depth, in chromatic layer count, of equirectangular 
     *                        tile bitmap
     *  \param lgrBitmap      Pointer to rectilinear bitmap that recieve the 
     *                        gnomonic projection
     *  \param lgrWidth       Width, in pixels, of the rectilinear bitmap
     *  \param lgrHeight      Height, in pixels, of the rectilinear bitmap
     *  \param lgrLayers      Depth, in chromatic layer count, of rectilinear 
     *                        bitmap
     *  \param lgrSightX      Position X, in pixels on rectilinear image,of the
     *                        gnomonic projection center
     *  \param lgrSightY      Position Y, in pixels on rectilinear image,of the
     *                        gnomonic projection center
     *  \param lgmWidth       Width, in pixels, of the entire equirectangular 
     *                        mapping from which the tile is extracted
     *  \param lgmHeight      Height, in pixels, of the entire equirectangular 
     *                        mapping from which the tile is extracted
     *  \param lgmCornerX     Position X, in pixels, of the equirectangular tile
     *                        top-left corner in the entire mapping
     *  \param lgmCornerY     Position Y, in pixels, of the equirectangular tile
     *                        top-left corner in the entire mapping
     *  \param lgAzim         Azimuth angle, in radians, of gnomonic center
     *  \param lgElev         Elevation angle, in radians, of gnomonic center
     *  \param lgRoll         Roll angle, in radians, around gnomonic axis
     *  \param lgFocal        Focal length, in mm, of the rectilinear image
     *  \param lgPixel        Length, in mm, of the pixels of the rectilinear
     *                        image virtual camera
     *  \param lgInter        Pointer to interpolation method function
     *  \param lgThread       Thread number (OpenMP)
     */

    lg_Void_t lg_gtt_genericp(

        li_C8_t           * const lgeBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        li_C8_t     const * const lgrBitmap,
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

    );

    /*! \brief Rectilinear to equirectangular tile transform
     * 
     *  This function offers the inverted coordinates convertion provided by the
     *  generic function lg_ttg_generic_point. Their parameters are the same and
     *  have to be understood in the exact same way, swapping input and output
     *  role of the provided points coordinates.
     *
     *  \param lgePointX      X-coordinate of point in equirectangular mapping
     *  \param lgePointY      Y-coordinate of point in equirectangular mapping
     *  \param lgrPointX      X-coordinate of point in rectilinear mapping
     *  \param lgrPointY      Y-coordinate of point in rectilinear mapping
     *  \param lgrSightX      Position X, in pixels on rectilinear image,of the
     *                        gnomonic projection center
     *  \param lgrSightY      Position Y, in pixels on rectilinear image,of the
     *                        gnomonic projection center
     *  \param lgmWidth       Width, in pixels, of the entire equirectangular 
     *                        mapping from which the tile is extracted
     *  \param lgmHeight      Height, in pixels, of the entire equirectangular 
     *                        mapping from which the tile is extracted
     *  \param lgmCornerX     Position X, in pixels, of the equirectangular tile
     *                        top-left corner in the entire mapping
     *  \param lgmCornerY     Position Y, in pixels, of the equirectangular tile
     *                        top-left corner in the entire mapping
     *  \param lgAzim         Azimuth angle, in radians, of gnomonic center
     *  \param lgElev         Elevation angle, in radians, of gnomonic center
     *  \param lgRoll         Roll angle, in radians, around gnomonic axis
     *  \param lgFocal        Focal length, in mm, of the rectilinear image
     *  \param lgPixel        Length, in mm, of the pixels of the rectilinear
     *                        image virtual camera
     */

    lg_Void_t lg_gtt_generic_point(

        lg_Real_t       * const lgePointX,
        lg_Real_t       * const lgePointY,
        lg_Real_t const         lgrPointX,
        lg_Real_t const         lgrPointY,
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

    );

/*
    Header - C/C++ compatibility
 */

    # ifdef __cplusplus
    }
    # endif

/*
    Header - Include guard
 */

    # endif
