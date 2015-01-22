/*
 * libgnomonic - Gnomonic projection algorithms library
 *
 * Copyright (c) 2013-2015 FOXEL SA - http://foxel.ch
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

    /*! \file   gnomonic-algebra.h
     *  \author Nils Hamel <n.hamel@foxel.ch>
     *
     *  Algebra related algorithms
     */

/*
    Header - Include guard
 */

    # ifndef __LG_ALGEBRA__
    # define __LG_ALGEBRA__

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

    /*! \brief Three angles rectilinear to equirectangular rotation matrix
     *
     *  This function compute three angles defined rotation matrix. The matrix
     *  considers the three angles as follows :
     *
     *      M = Ry(Elevation) Rz(Azimuth) Rx(Roll)
     *
     *  to compute the matrix entries.
     *
     *  \param lgMatrix Computed rotation matrix
     *  \param lgAzim   Azimuth angle, in radians
     *  \param lgElev   Elevation angle, in radians
     *  \param lgRoll   Roll angle, in radians
     * 
     */

    lg_Void_t lg_algebra_r2erotation(

        lg_Real_t       lgMatrix[3][3],
        lg_Real_t const lgAzim,
        lg_Real_t const lgElev,
        lg_Real_t const lgRoll

    );

    /*! \brief Three angles equirectangular to rectilinear rotation matrix
     *
     *  This function computes the three angles defined rotation matrix that
     *  corresponds to the invert, using the same angles, of the matrix provided
     *  by the lg_algebra_r2erotation function.
     *
     *  \param lgMatrix Matrix to compute
     *  \param lgAzim   Azimuth angle
     *  \param lgElev   Elevation angle
     *  \param lgRoll   Roll angle
     */

    lg_Void_t lg_algebra_e2rrotation(

        lg_Real_t       lgMatrix[3][3],
        lg_Real_t const lgAzim,
        lg_Real_t const lgElev,
        lg_Real_t const lgRoll

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

