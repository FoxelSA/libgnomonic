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


    //! @file   gnomonic-gte.h
    //! @author Nils Hamel (n.hamel@foxel.ch)
    //!
    //! Rectilinear to equirectangular transformation

/*
    Header - Include guard
 */

    # ifndef __LIBGNOMONIC_GTE__
    # define __LIBGNOMONIC_GTE__

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

    //! This function performs an inverted gnomonic projection back in the original equirectangular
    //! image of an entire panorama. The results is drawn in the pan_img bitmap that has to be
    //! already allocated according to its paramters.
    //!
    //! @param pan_img Pointer to equirectangular bitmap
    //! @param pan_w Width, in pixels, of the equirectangular bitmap pan_img
    //! @param pan_h Height, in pixels, of the equirectangular bitmap pan_img
    //! @param pan_d Depth, in chromatic layer count, of the equirectangular bitmap pan_img
    //! @param rct_img Pointer to gnomonic bitmap
    //! @param rct_w Width, in pixels, of the gnomonic bitmap rct_img
    //! @param rct_h Height, in pixels, of the gnomonic bitmap rct_img
    //! @param rct_d Depth, in chromatic layer count, of the gnomonic bitmap rct_img
    //! @param nad_t Horizontal angle, in radian, of the center of view of the gnomonic projection, in [0,2PI[
    //! @param nad_p Vertical angle, in radian, of the center of view of the gnomonic projection, in [-PI/2,+PI/2[
    //! @param app_t Half horizontal apperture, from center of view, of the gnomonic projection in radian
    //! @param app_p Half vertical apperture, from center of view, of the gnomonic projection in radian
    //! @param int_m Pointer to interpolation method function

    gnomonic_Void_t gnomonic_gte(

        inter_C8_t *     pan_img,
        gnomonic_Index_t pan_w,
        gnomonic_Index_t pan_h,
        gnomonic_Index_t pan_d,
        inter_C8_t *     rct_img,
        gnomonic_Index_t rct_w,
        gnomonic_Index_t rct_h,
        gnomonic_Index_t rct_d,
        gnomonic_Real_t  nad_t,
        gnomonic_Real_t  nad_p,
        gnomonic_Real_t  app_t,
        gnomonic_Real_t  app_p,
        inter_Method_t   int_m

    );

    //!  This function performs an inverted gnomonic projection back in the original equirectangular
    //!  image of an entire panorama image using the alpha mask mas_img. The results is drawn in
    //!  the pan_img bitmap that has to be already allocated according to its parameters.
    //!
    //!  The mask mas_img has to be a monochromatic bitmap identical in size to the rct_img. The
    //!  values in the mask are interpreted has the alpha channel of the rct_img.
    //!
    //! @param pan_img Pointer to equirectangular bitmap
    //! @param pan_w Width, in pixels, of the equirectangular bitmap pan_img
    //! @param pan_h Height, in pixels, of the equirectangular bitmap pan_img
    //! @param pan_d Depth, in chromatic layer count, of the equirectangular bitmap pan_img
    //! @param rct_img Pointer to gnomonic bitmap
    //! @param mas_img Pointer to monochromatic gnomonic mask bitmap
    //! @param rct_w Width, in pixels, of the gnomonic bitmap rct_img
    //! @param rct_h Height, in pixels, of the gnomonic bitmap rct_img
    //! @param rct_d Depth, in chromatic layer count, of the gnomonic bitmap rct_img
    //! @param nad_t Horizontal angle, in radian, of the center of view of the gnomonic projection, in [0,2PI[
    //! @param nad_p Vertical angle, in radian, of the center of view of the gnomonic projection, in [-PI/2,+PI/2[
    //! @param app_t Half horizontal apperture, from center of view, of the gnomonic projection in radian
    //! @param app_p Half vertical apperture, from center of view, of the gnomonic projection in radian
    //! @param int_m Pointer to interpolation method function

    gnomonic_Void_t gnomonic_gte_blend(

        inter_C8_t *     pan_img,
        gnomonic_Index_t pan_w,
        gnomonic_Index_t pan_h,
        gnomonic_Index_t pan_d,
        inter_C8_t *     rct_img,
        inter_C8_t *     mas_img,
        gnomonic_Index_t rct_w,
        gnomonic_Index_t rct_h,
        gnomonic_Index_t rct_d,
        gnomonic_Real_t  nad_t,
        gnomonic_Real_t  nad_p,
        gnomonic_Real_t  app_t,
        gnomonic_Real_t  app_p,
        inter_Method_t   int_m

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

