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


/*
    Source - Includes
 */

    # include "gnomonic-gte.h"

/*
    Source - Rectilinear to equirectangular transform
 */

    lg_Void_t lg_gte_apperture( 

        li_C8_t           * const lgeBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        li_C8_t     const * const lgrBitmap,
        lg_Size_t   const         lgrWidth,
        lg_Size_t   const         lgrHeight,
        lg_Size_t   const         lgrLayers, 
        lg_Real_t   const         lgAzim,
        lg_Real_t   const         lgElev,
        lg_Real_t   const         lgRoll,
        lg_Real_t   const         lgApper,
        li_Method_t const         lgInter

    ) { lg_gte_apperturep(

        lgeBitmap,
        lgeWidth,
        lgeHeight,
        lgeLayers,
        lgrBitmap,
        lgrWidth,
        lgrHeight,
        lgrLayers, 
        lgAzim,
        lgElev,
        lgRoll,
        lgApper,
        lgInter,
        lg_Size_s( 1 )

    ); }

    lg_Void_t lg_gte_apperturep( 

        li_C8_t           * const lgeBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        li_C8_t     const * const lgrBitmap,
        lg_Size_t   const         lgrWidth,
        lg_Size_t   const         lgrHeight,
        lg_Size_t   const         lgrLayers, 
        lg_Real_t   const         lgAzim,
        lg_Real_t   const         lgElev,
        lg_Real_t   const         lgRoll,
        lg_Real_t   const         lgApper,
        li_Method_t const         lgInter,
        lg_Size_t   const         lgThread

    ) { lg_gtt_genericp(

        lgeBitmap,
        lgeWidth,
        lgeHeight,
        lgeLayers,
        lgrBitmap,
        lgrWidth,
        lgrHeight,
        lgrLayers,
        lg_Real_c( lgrWidth  ) / lg_Real_s( 2.0 ),
        lg_Real_c( lgrHeight ) / lg_Real_s( 2.0 ),
        lgeWidth,
        lgeHeight,
        lg_Real_s( 0.0 ),
        lg_Real_s( 0.0 ),
        lgAzim,
        lgElev,
        lgRoll,
        lg_Real_s( 1.0 ),
        lg_Real_s( 2.0 ) * tan( lgApper / lg_Real_s( 2.0 ) ) / lgrWidth,
        lgInter,
        lgThread

    ); }

