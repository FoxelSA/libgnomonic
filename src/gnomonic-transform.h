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

    /*! \file   gnomonic-transform.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  Equirectangular general transformation
     */

/*
    Header - Include guard
 */

    # ifndef __LG_TRANSFORM__
    # define __LG_TRANSFORM__

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

    /*! \brief Equirectangular mapping rotation
     *
     *  This function is the mono-threaded front-end to the definition of the
     *  lg_transform_rotatep.
     *
     *  \param lgiBitmap    Pointer to input equirectangular bitmap
     *  \param lgoBitmap    Pointer to output equirectangular bitmap
     *  \param lgeWidth     Width, in pixels, of input/output bitmaps
     *  \param lgeHeight    Height, in pixels, of input/output bitmaps
     *  \param lgeLayers    Depth, in chromatic layer count, of equirectangular 
     *                      bitmaps
     *  \param lgAzim       Azimuth angle, in radians
     *  \param lgElev       Elevation angle, in radians
     *  \param lgRoll       Roll angle, in radians
     *  \param lgInter      Pointer to interpolation method function
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

    );

    /*! \brief Equirectangular mapping rotation
     *  
     *  This function allows to rotate the sphere mapped by the provided
     *  equirectangular mapping. The result is drawn in the output bitmap that
     *  has to be already allocated according to its parameters.
     *
     *  The rotation is performed considering the following frame : the x-axis
     *  points the left edge of the mapping at half height. The y-axis points at
     *  third fourth of the mapping width and at half of its height. The z-axis
     *  is obtained using a cross-product, inducing a direct frame in which the 
     *  mapped sphere is considered.
     *
     *  The three angles defined rotation matrix is built as follows :
     *
     *      M = Rz(Azimuth)Ry(Elevation)Rx(Roll)
     *
     *  and is then used to rotate the mapped sphere.
     *  
     *  \param lgiBitmap    Pointer to input equirectangular bitmap
     *  \param lgoBitmap    Pointer to output equirectangular bitmap
     *  \param lgeWidth     Width, in pixels, of input/output bitmaps
     *  \param lgeHeight    Height, in pixels, of input/output bitmaps
     *  \param lgeLayers    Depth, in chromatic layer count, of equirectangular 
     *                      bitmaps
     *  \param lgAzim       Azimuth angle, in radians
     *  \param lgElev       Elevation angle, in radians
     *  \param lgRoll       Roll angle, in radians
     *  \param lgInter      Pointer to interpolation method function
     *  \param lgThread     Thread number (OpenMP)
     */

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

