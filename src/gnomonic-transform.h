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
    # include "inter-all.h"

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
     *  This function applies a rotation matrix to the sphere mapped by the 
     *  gEqrIn equirectangular image. The result is drawn in the gEqrOut bitmap 
     *  that has to be already allocated. The gEqrOut bitmap has to be the same
     *  size and to have the same number of chromatic layer count than gEqrIn
     *  bitmap.
     *  
     *  \param lgEqrIn      Input equirectangular bitmap
     *  \param lgEqrOut     Output equirectangular bitmap
     *  \param lgEqrWidth   Width, in pixel, of input/output bitmaps
     *  \param lgEqrHeight  Height, in pixel, of input/output bitmaps
     *  \param lgEqrLayers  Chromatic layer count of input/output bitmaps
     *  \param lgAngleX     Rotation angle, in radiant, along x-axis
     *  \param lgAngleY     Rotation angle, in radiant, along y-axis
     *  \param lgAngleZ     Rotation angle, in radiant, along z-axis
     *  \param lgInter      Pointer to interpolation method function
     */

    lg_Void_t lg_transform_rotate( 

        li_C8_t     const * const lgEqrIn,
        li_C8_t           * const lgEqrOut,
        lg_Size_t   const         lgEqrWidth,
        lg_Size_t   const         lgEqrHeight,
        lg_Size_t   const         lgEqrLayers,
        lg_Real_t   const         lgAngleX,
        lg_Real_t   const         lgAngleY,
        lg_Real_t   const         lgAngleZ,
        li_Method_t const         lgInter

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

