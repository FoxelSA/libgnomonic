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

    //! This function performs a gnomonic reprojection on the base of an equirectangular
    //! projection of a entire panorama using disired interpolation method. The results is
    //! drawn in the rct_img bitmap. The rct_img has to be already allocated accroding to
    //! its parameters.
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

    void gnomonic_etg(

        unsigned char * pan_img,
        long int pan_w,
        long int pan_h,
        long int pan_d,
        unsigned char * rct_img,
        long int rct_w,
        long int rct_h,
        long int rct_d,
        double nad_t,
        double nad_p,
        double app_t,
        double app_p,
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

