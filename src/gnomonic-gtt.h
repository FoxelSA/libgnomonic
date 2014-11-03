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

    /*! \file   gnomonic-gtt.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  Rectilinear tile to equirectangular tile transform
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
