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


    //! @file   gnomonic-etg.h
    //! @author Nils Hamel (n.hamel@foxel.ch)
    //!
    //! Equirectangular to rectilinear transformation

/*
    Header - Include guard
 */

    # ifndef __LIBGNOMONIC_ETG__
    # define __LIBGNOMONIC_ETG__

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

    //! Equirectangular to rectilinear gnomonic projection

    //! This function performs a gnomonic reprojection on the base of an equirectangular
    //! projection of a entire panorama using desired interpolation method. The results is
    //! drawn in the lgRectOut bitmap. The lgRectOut has to be already allocated accroding to
    //! its parameters.
    //!
    //! @param lgEqrIn Pointer to equirectangular bitmap
    //! @param lgEqrWidth Width, in pixels, of the equirectangular bitmap pan_img
    //! @param lgEqrHeight Height, in pixels, of the equirectangular bitmap pan_img
    //! @param lgEqrLayer Depth, in chromatic layer count, of the equirectangular bitmap pan_img
    //! @param lgRectOut Pointer to gnomonic bitmap
    //! @param lgRectWidth Width, in pixels, of the gnomonic bitmap rct_img
    //! @param lgRectHeight Height, in pixels, of the gnomonic bitmap rct_img
    //! @param lgRectLayer Depth, in chromatic layer count, of the gnomonic bitmap rct_img
    //! @param lgNadH Horizontal angle, in radian, of the center of view of the gnomonic projection, in [0,2PI[
    //! @param lgNadV Vertical angle, in radian, of the center of view of the gnomonic projection, in [-PI/2,+PI/2[
    //! @param lgAppH Half horizontal apperture, from center of view, of the gnomonic projection in radian
    //! @param lgAppV Half vertical apperture, from center of view, of the gnomonic projection in radian
    //! @param lgInter Pointer to interpolation method function

    gnomonic_Void_t gnomonic_etg(

        inter_C8_t *     lgEqrIn,
        gnomonic_Index_t lgEqrWidth,
        gnomonic_Index_t lgEqrHeight,
        gnomonic_Index_t lgEqrLayer,
        inter_C8_t *     lgRectOut,
        gnomonic_Index_t lgRectWidth,
        gnomonic_Index_t lgRectHeight,
        gnomonic_Index_t lgRectLayer,
        gnomonic_Real_t  lgNadH,
        gnomonic_Real_t  lgNadV,
        gnomonic_Real_t  lgAppH,
        gnomonic_Real_t  lgAppV,
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

