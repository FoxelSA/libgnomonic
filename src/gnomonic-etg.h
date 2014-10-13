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

    /*! \file   gnomonic-etg.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  Equirectangular to rectilinear transformation
     */

/*
    Header - Include guard
 */

    # ifndef __LG_ETG__
    # define __LG_ETG__

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

    /*! \brief Equirectangular to rectilinear gnomonic projection
     *  
     *  This function performs a gnomonic reprojection on the base of an
     *  equirectangular mapping of an entire panorama using desired 
     *  interpolation method. The result is drawn in the lgRectOut bitmap. 
     *  The lgRectOut has to be already allocated accroding to its provided
     *  parameters.
     *  
     *  \param lgEqrIn      Pointer to equirectangular bitmap
     *  \param lgEqrWidth   Width, in pixels, of the equirectangular bitmap 
     *  \param lgEqrHeight  Height, in pixels, of the equirectangular bitmap 
     *  \param lgEqrLayer   Depth, in chromatic layer count, of equirectangular 
     *                      bitmap
     *  \param lgRectOut    Pointer to gnomonic bitmap
     *  \param lgRectWidth  Width, in pixels, of the rectilinear bitmap
     *  \param lgRectHeight Height, in pixels, of the rectilinear bitmap
     *  \param lgRectLayer  Depth, in chromatic layer count, of the rectilinear 
     *                      bitmap
     *  \param lgNadH       Horizontal angle, in radian, of the center of view 
     *                      of the gnomonic projection, in [0,2PI[
     *  \param lgNadV       Vertical angle, in radian, of the center of view of 
     *                      the gnomonic projection, in [-PI/2,+PI/2[
     *  \param lgAppH       Half horizontal apperture, from center of view, of 
     *                      the gnomonic projection in radian
     *  \param lgAppV       Half vertical apperture, from center of view, of the
     *                      gnomonic projection in radian
     *  \param lgInter      Pointer to interpolation method function
     */

    lg_Void_t lg_etg(

        li_C8_t     const * const lgEqrIn,
        lg_Size_t   const         lgEqrWidth,
        lg_Size_t   const         lgEqrHeight,
        lg_Size_t   const         lgEqrLayer,
        li_C8_t           * const lgRectOut,
        lg_Size_t   const         lgRectWidth,
        lg_Size_t   const         lgRectHeight,
        lg_Size_t   const         lgRectLayer,
        lg_Real_t   const         lgNadH,
        lg_Real_t   const         lgNadV,
        lg_Real_t   const         lgAppH,
        lg_Real_t   const         lgAppV,
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

