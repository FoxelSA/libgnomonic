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


/*
    Source - Includes
 */

    # include "gnomonic-algebra.h"

/*
    Source - Three angles rectilinear to equirectangular rotation matrix
 */

    lg_Void_t lg_algebra_r2erotation(

        lg_Real_t       lgMatrix[3][3],
        lg_Real_t const lgAzim,
        lg_Real_t const lgElev,
        lg_Real_t const lgRoll

    ) {

        /* Trigonometric variables */
        lg_Real_t const lgCosA = cos( lgAzim );
        lg_Real_t const lgSinA = sin( lgAzim );
        lg_Real_t const lgCosE = cos( lgElev );
        lg_Real_t const lgSinE = sin( lgElev );
        lg_Real_t const lgCosR = cos( lgRoll );
        lg_Real_t const lgSinR = sin( lgRoll );

        /* Compute matrix entries */
        lgMatrix[0][0] = + lgCosA * lgCosE;
        lgMatrix[0][1] = + lgCosA * lgSinE * lgSinR - lgSinA * lgCosR;
        lgMatrix[0][2] = + lgCosA * lgSinE * lgCosR + lgSinA * lgSinR;
        lgMatrix[1][0] = + lgSinA * lgCosE; 
        lgMatrix[1][1] = + lgSinA * lgSinE * lgSinR + lgCosA * lgCosR;
        lgMatrix[1][2] = + lgSinA * lgSinE * lgCosR - lgCosA * lgSinR;
        lgMatrix[2][0] = - lgSinE;
        lgMatrix[2][1] = + lgCosE * lgSinR;
        lgMatrix[2][2] = + lgCosE * lgCosR;


    }

/*
    Source - Three angles equirectangular to rectilinear rotation matrix
 */

    lg_Void_t lg_algebra_e2rrotation(

        lg_Real_t       lgMatrix[3][3],
        lg_Real_t const lgAzim,
        lg_Real_t const lgElev,
        lg_Real_t const lgRoll

    ) {

        /* Trigonometric variables */
        //lg_Real_t const lgCosA = cos( lgAzim );
        //lg_Real_t const lgSinA = sin( lgAzim );
        //lg_Real_t const lgCosE = cos( lgElev );
        //lg_Real_t const lgSinE = sin( lgElev );
        //lg_Real_t const lgCosR = cos( lgRoll );
        //lg_Real_t const lgSinR = sin( lgRoll );

    }
