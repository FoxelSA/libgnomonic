/*
 * libgnomonic - Gnomonic projection algorithms library
 *
 * Copyright (c) 2013-2014 FOXEL SA - http://foxel.ch
 * Please read <http://foxel.ch/license> for more information.
 *
 *
 * Author(s):
 *
 *      Stéphane Flotron <s.flotron@foxel.ch>
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


    //! @file   gnomonic-coord.h
    //! @author Stéphane Flotron (stephane.flotron@foxel.ch)
    //!
    //! Coordinates transformation

/*
    Header - Include guard
 */

    # ifndef __LIBGNOMONIC_COORD__
    # define __LIBGNOMONIC_COORD__

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

    void gnomonic_ttg_coord(

        double   eqx,
        double   eqy,
        long int eqr_w,
        long int eqr_h,
        double * rcx,
        double * rcy,
        long int rct_w,
        long int rct_h,
        long int pan_w,
        long int pan_h,
        long int eqr_x,
        long int eqr_y,
        double sen_x,
        double sen_y

    );

 void gnomonic_gtt_coord(

        double * eqx,
        double * eqy,
        long int eqr_w,
        long int eqr_h,
        double   rcx,
        double   rcy,
        long int rct_w,
        long int rct_h,
        long int pan_w,
        long int pan_h,
        long int eqr_x,
        long int eqr_y,
        double sen_x,
        double sen_y

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

