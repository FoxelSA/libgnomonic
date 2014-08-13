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
     *  \author Nils Hamel (n.hamel@foxel.ch)
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
    # include "inter-all.h"

/*
    Header - Preprocessor definitions
 */

/*
    Header - Preprocessor macros
 */

    /* Ascending compatibility alias - Ensured until v1.0 */
    # define gnomonic_gte       lg_gte
    # define gnomonic_gte_blend lg_gte_blend

/*
    Header - Typedefs
 */

/*
    Header - Structures
 */

/*
    Header - Function prototypes
 */

    /*! \brief Rectilinear to equirectangular inverted gnomonic projection
     *  
     *  This function performs an inverted gnomonic projection back in the original equirectangular
     *  image of an entire panorama. The results is drawn in the lgEqrIO bitmap that has to be
     *  already allocated according to its paramters.
     *  
     *  \param lgEqrIO Pointer to equirectangular bitmap
     *  \param lgEqrWidth Width, in pixels, of the equirectangular bitmap pan_img
     *  \param lgEqrHeight Height, in pixels, of the equirectangular bitmap pan_img
     *  \param lgEqrLayer Depth, in chromatic layer count, of the equirectangular bitmap pan_img
     *  \param lgRectIn Pointer to gnomonic bitmap
     *  \param lgRectWidth Width, in pixels, of the gnomonic bitmap rct_img
     *  \param lgRectHeight Height, in pixels, of the gnomonic bitmap rct_img
     *  \param lgRectLayer Depth, in chromatic layer count, of the gnomonic bitmap rct_img
     *  \param lgNadH Horizontal angle, in radian, of the center of view of the gnomonic projection, in [0,2PI[
     *  \param lgNadV Vertical angle, in radian, of the center of view of the gnomonic projection, in [-PI/2,+PI/2[
     *  \param lgAppH Half horizontal apperture, from center of view, of the gnomonic projection in radian
     *  \param lgAppV Half vertical apperture, from center of view, of the gnomonic projection in radian
     *  \param lgInter Pointer to interpolation method function
     */

    lg_Void_t lg_gte(

        li_C8_t *   lgEqrIO,
        lg_Size_t   lgEqrWidth,
        lg_Size_t   lgEqrHeight,
        lg_Size_t   lgEqrLayer,
        li_C8_t *   lgRectIn,
        lg_Size_t   lgRectWidth,
        lg_Size_t   lgRectHeight,
        lg_Size_t   lgRectLayer,
        lg_Real_t   lgNadH,
        lg_Real_t   lgNadV,
        lg_Real_t   lgAppH,
        lg_Real_t   lgAppV,
        li_Method_t lgInter

    );

    /*! \brief Blended rectilinear to equirectangular inverted gnomonic projection
     *  
     *  This function performs an inverted gnomonic projection back in the original equirectangular
     *  image of an entire panorama image using the alpha layer stored by lgMaskIn. The results is
     *  drawn in the lgEqrIO bitmap that has to be already allocated according to its parameters.
     *  
     *  The mask lgMaskIn has to be a monochromatic bitmap identical in size to the lgRectIn. The
     *  values in the mask are interpreted has the alpha channel of the lgRectIn.
     *  
     *  \param lgEqrIO Pointer to equirectangular bitmap
     *  \param lgEqrWidth Width, in pixels, of the equirectangular bitmap pan_img
     *  \param lgEqrHeight Height, in pixels, of the equirectangular bitmap pan_img
     *  \param lgEqrLayer Depth, in chromatic layer count, of the equirectangular bitmap pan_img
     *  \param lgRectIn Pointer to gnomonic bitmap
     *  \param lgMaskIn Pointer to monochromatic gnomonic mask bitmap
     *  \param lgRectWidth Width, in pixels, of the gnomonic bitmap rct_img
     *  \param lgRectHeight Height, in pixels, of the gnomonic bitmap rct_img
     *  \param lgRectLayer Depth, in chromatic layer count, of the gnomonic bitmap rct_img
     *  \param lgNadH Horizontal angle, in radian, of the center of view of the gnomonic projection, in [0,2PI[
     *  \param lgNadV Vertical angle, in radian, of the center of view of the gnomonic projection, in [-PI/2,+PI/2[
     *  \param lgAppH Half horizontal apperture, from center of view, of the gnomonic projection in radian
     *  \param lgAppV Half vertical apperture, from center of view, of the gnomonic projection in radian
     *  \param lgInter Pointer to interpolation method function
     */

    lg_Void_t lg_gte_blend(

        li_C8_t *   lgEqrIO,
        lg_Size_t   lgEqrWidth,
        lg_Size_t   lgEqrHeight,
        lg_Size_t   lgEqrLayer,
        li_C8_t *   lgRectIn,
        li_C8_t *   lgMaskIn,
        lg_Size_t   lgRectWidth,
        lg_Size_t   lgRectHeight,
        lg_Size_t   lgRectLayer,
        lg_Real_t   lgNadH,
        lg_Real_t   lgNadV,
        lg_Real_t   lgAppH,
        lg_Real_t   lgAppV,
        li_Method_t lgInter

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

