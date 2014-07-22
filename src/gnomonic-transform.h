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


    //! @file   gnomonic-transform.h
    //! @author Nils Hamel (n.hamel@foxel.ch)
    //!
    //! Equirectangular transformation

/*
    Header - Include guard
 */

    # ifndef __LIBGNOMONIC_TRANSFORM__
    # define __LIBGNOMONIC_TRANSFORM__

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

    //! Equirectangular mapping rotation

    //! This function apply a rotation matrix to the sphere mapped by the gEqrIn equirectangular
    //! mapping. The result is drawn in the gEqrOut bitmap that has to be already allocated.
    //! The gEqrOut bitmap has to have the same size and chromatic layer count than gEqrIn
    //! bitmap.
    //!
    //! @param gEqrIn Input equirectangular bitmap
    //! @param gEqrOut Output equirectangular bitmap
    //! @param gEqrWidth Width, in pixel, of input/output bitmaps
    //! @param gEqrHeight Height, in pixel, of input/output bitmaps
    //! @param gEqrLayer Chromatic layer count of input/output bitmaps
    //! @param gAngleX Rotation angle, in radiant, along x-axis
    //! @param gAngleY Rotation angle, in radiant, along y-axis
    //! @param gAngleZ Rotation angle, in radiant, along z-axis
    //! @param gInter Pointer to interpolation method function

    gnomonic_Void_t gnomonic_transform_rotate( 

        inter_C8_t *     lgEqrIn,
        inter_C8_t *     lgEqrOut,
        gnomonic_Index_t lgEqrWidth,
        gnomonic_Index_t lgEqrHeight,
        gnomonic_Index_t lgEqrLayers,
        gnomonic_Real_t  lgAngleX,
        gnomonic_Real_t  lgAngleY,
        gnomonic_Real_t  lgAngleZ,
        inter_Method_t   lgInter

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

