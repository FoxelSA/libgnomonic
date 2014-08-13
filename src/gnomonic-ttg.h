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

    /*! \file   gnomonic-ttg.h
     *  \author Nils Hamel (n.hamel@foxel.ch)
     *
     *  Equirectangular tile to rectilinear transformation
     */

/*
    Header - Include guard
 */

    # ifndef __LG_TTG__
    # define __LG_TTG__

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

    /*! \brief Equirectangular tile to rectilinear gnomonic projection
     *  
     *  This function performs an gnomonic projection considering a tile of an entire
     *  equirectangular panorama using the desired interpolation method. The results
     *  are drawn in the lgRectOut bitmap. The lgRectOut has to be already allocated
     *  according to its parameters.
     *  
     *  \param lgEqrIn Pointer to equirectangular tile bitmap
     *  \param lgEqrWidth Width, in pixels, of the equirectangular tile bitmap eqr_img
     *  \param lgEqrHeight Height, in pixels, of the equirectangular tile bitmap eqr_img
     *  \param lgEqrLayer Depth, in chromatic layer count, of the equirectangular tile bitmap eqr_img
     *  \param lgRectOut Pointer to gnomonic bitmap
     *  \param lgRectWidth Width, in pixels, of the gnomonic bitmap rct_img
     *  \param lgRectHeight Height, in pixels, of the gnomonic bitmap rct_img
     *  \param lgRectLayer Depth, in chromatic layer count, of the gnomonic bitmap rct_img
     *  \param lgPanWidth Width, in pixel, of the entire equirectangular mapping
     *  \param lgPanHeight Height, in pixel, of the entire equirectangular mapping
     *  \param lgEqrPosX Position x, in pixel, of the tile in the entire equirectangular mapping
     *  \param lgEqrPosY Position y, in pixel, of the tile in the entire equirectangular mapping
     *  \param lgEqrCenterX Position x, in pixel, of the tile center in the entire equirectangular mapping
     *  \param lgEqrCenterY Position y, in pixel, of the tile center in the entire equirectangular mapping
     *  \param lgInter Pointer to interpolation method function
     */

    gnomonic_Void_t gnomonic_ttg(

        inter_C8_t *     lgEqrIn,
        gnomonic_Index_t lgEqrWidth,
        gnomonic_Index_t lgEqrHeight,
        gnomonic_Index_t lgEqrLayer,
        inter_C8_t *     lgRectOut,
        gnomonic_Index_t lgRectWidth,
        gnomonic_Index_t lgRectHeight,
        gnomonic_Index_t lgRectLayer,
        gnomonic_Index_t lgPanWidth,
        gnomonic_Index_t lgPanHeight,
        gnomonic_Index_t lgEqrPosX,
        gnomonic_Index_t lgEqrPosY,
        gnomonic_Real_t  lgEqrCenterX,
        gnomonic_Real_t  lgEqrCenterY,
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

