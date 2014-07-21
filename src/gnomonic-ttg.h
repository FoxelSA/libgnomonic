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


    //! @file   gnomonic-ttg.h
    //! @author Nils Hamel (n.hamel@foxel.ch)
    //!
    //! Equirectangular tile to rectilinear transformation

/*
    Header - Include guard
 */

    # ifndef __LIBGNOMONIC_TTG__
    # define __LIBGNOMONIC_TTG__

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

    //! This function performs an gnomonic projection considering a tile of an entire
    //! equirectangular panorama using the desired interpolation method. The results
    //! are drawn in the rct_img bitmap. The rct_img has to be already allocated
    //! according to its parameters.
    //!
    //! @param eqr_img Pointer to equirectangular tile bitmap
    //! @param eqr_w Width, in pixels, of the equirectangular tile bitmap eqr_img
    //! @param eqr_h Height, in pixels, of the equirectangular tile bitmap eqr_img
    //! @param eqr_d Depth, in chromatic layer count, of the equirectangular tile bitmap eqr_img
    //! @param rct_img Pointer to gnomonic bitmap
    //! @param rct_w Width, in pixels, of the gnomonic bitmap rct_img
    //! @param rct_h Height, in pixels, of the gnomonic bitmap rct_img
    //! @param rct_d Depth, in chromatic layer count, of the gnomonic bitmap rct_img
    //! @param pan_w Width, in pixel, of the entire equirectangular mapping
    //! @param pan_h Height, in pixel, of the entire equirectangular mapping
    //! @param eqr_x Position x, in pixel, of the tile in the entire equirectangular mapping
    //! @param eqr_y Position y, in pixel, of the tile in the entire equirectangular mapping
    //! @param sen_x Position x, in pixel, of the tile center in the entire equirectangular mapping
    //! @param sen_y Position y, in pixel, of the tile center in the entire equirectangular mapping
    //! @param int_m Pointer to interpolation method function

    void gnomonic_ttg(

        unsigned char * eqr_img,
        long int eqr_w,
        long int eqr_h,
        long int eqr_d,
        unsigned char * rct_img,
        long int rct_w,
        long int rct_h,
        long int rct_d,
        long int pan_w,
        long int pan_h,
        long int eqr_x,
        long int eqr_y,
        double sen_x,
        double sen_y,
        inter_Method_t int_m

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

