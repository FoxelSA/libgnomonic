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

    /*! \file   gnomonic-all.h
     *  \author Nils Hamel (n.hamel@foxel.ch)
     *
     *  Library general includer
     */

/*
    Header - Include guard
 */

    # ifndef __LG_ALL__
    # define __LG_ALL__

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
    # include "gnomonic-etg.h"
    # include "gnomonic-gte.h"
    # include "gnomonic-ttg.h"
    # include "gnomonic-transform.h"
    # include "gnomonic-coord.h"

/*
    Header - Preprocessor definitions
 */

    /* Ascending compatibility - Macros */
    # define GNOMONIC_PI                LG_PI

    /* Ascending compatibility - Functions */
    # define gnomonic_ttg_coord         lg_ttg_coord        /* Beta 0.2 */
    # define gnomonic_gtt_coord         lg_gtt_coord        /* Beta 0.2 */
    # define gnomonic_etg               lg_etg              /* Beta 0.2 */
    # define gnomonic_gte               lg_gte              /* Beta 0.2 */
    # define gnomonic_gte_blend         lg_gte_blend        /* Beta 0.2 */
    # define gnomonic_transform_rotate  lg_transform_rotate /* Beta 0.2 */
    # define gnomonic_ttg               lg_ttg              /* Beta 0.2 */

    /* Ascending compatibility - Types */
    # define gnomonic_Void_t            lg_Void_t           /* Beta 0.2 */
    # define gnomonic_Index_t           lg_Size_t           /* Beta 0.2 */
    # define gnomonic_Real_t            lg_Real_t           /* Beta 0.2 */

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

