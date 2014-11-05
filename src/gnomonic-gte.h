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

    /*! \file   gnomonic-gte.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  Rectilinear to equirectangular transformation
     */

/*
    Header - Include guard
 */

    # ifndef __LG_GTE__
    # define __LG_GTE__

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
    # include "gnomonic-gtt.h"

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

    /*! \brief Rectilinear to equirectangular transform
     *
     *  This function is the mono-threaded front-end to the definition of the
     *  lg_gte_apperturep.
     *
     *  See lg_gte_apperturep documentation for more information.
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
     *  \param lgAzim         Azimuth angle, in radians, of gnomonic center
     *  \param lgElev         Elevation angle, in radians, of gnomonic center
     *  \param lgRoll         Roll angle, in radians, around gnomonic center
     *  \param lgApper        Horizontal apparture, in radians, of the gnomonic
     *                        projection.
     *  \param lgInter        Pointer to interpolation method function
     */

    lg_Void_t lg_gte_apperture( 

        li_C8_t           * const lgeBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        li_C8_t     const * const lgrBitmap,
        lg_Size_t   const         lgrWidth,
        lg_Size_t   const         lgrHeight,
        lg_Size_t   const         lgrLayers, 
        lg_Real_t   const         lgAzim,
        lg_Real_t   const         lgElev,
        lg_Real_t   const         lgRoll,
        lg_Real_t   const         lgApper,
        li_Method_t const         lgInter

    );

    /*! \brief Rectilinear to equirectangular transform
     *
     *  This function offers the inverted gnomonic projection provided by the
     *  lg_etg_apperture function. Their parameters are the same and have to be
     *  understood in the exact same way.
     *
     *  See lg_etg_apperture documentation for more information.
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
     *  \param lgAzim         Azimuth angle, in radians, of gnomonic center
     *  \param lgElev         Elevation angle, in radians, of gnomonic center
     *  \param lgRoll         Roll angle, in radians, around gnomonic center
     *  \param lgApper        Horizontal apparture, in radians, of the gnomonic
     *                        projection.
     *  \param lgInter        Pointer to interpolation method function
     *  \param lgThread       Thread number (OpenMP)
     */

    lg_Void_t lg_gte_apperturep( 

        li_C8_t           * const lgeBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        li_C8_t     const * const lgrBitmap,
        lg_Size_t   const         lgrWidth,
        lg_Size_t   const         lgrHeight,
        lg_Size_t   const         lgrLayers, 
        lg_Real_t   const         lgAzim,
        lg_Real_t   const         lgElev,
        lg_Real_t   const         lgRoll,
        lg_Real_t   const         lgApper,
        li_Method_t const         lgInter,
        lg_Size_t   const         lgThread

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

