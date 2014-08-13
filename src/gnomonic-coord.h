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

    /*! \file   gnomonic-coord.h
     *  \author Stéphane Flotron (stephane.flotron@foxel.ch)
     *
     *  Coordinates transformation
     */

/*
    Header - Include guard
 */

    # ifndef __LG_COORD__
    # define __LG_COORD__

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

    /* Ascending compatibility alias - Ensured until v1.0 */
    # define gnomonic_ttg_coord lg_ttg_coord
    # define gnomonic_gtt_coord lg_gtt_coord

/*
    Header - Typedefs
 */

/*
    Header - Structures
 */

/*
    Header - Function prototypes
 */

    /*! \brief Equirectangular tile to rectilinear coordinates transform
     *  
     *  Performs a conversion from the coordinates of a point in an
     *  equirectangular tile to the coordinates of the corresponding point 
     *  in the rectilinear projection of the tile.
     *
     * \param eqx Equirectangular point x-coordinate
     * \param eqy Equirectangular point y-coordinate
     * \param eqr_w Width, in pixels, of the equirectangular tile
     * \param eqr_h Height, in pixels, of the equirectangular tile
     * \param rcx Pointer to the rectilinear point x-coordinate (output)
     * \param rcy Pointer to the rectilinear point y-coordinate (output)
     * \param rct_w Width, in pixels, of the rectilinear image
     * \param rct_h Height, in pixels, of the rectilinear image
     * \param pan_w Width, in pixels, of the full equirectangular image
     * \param pan_h Height, in pixels, of the full equirectangular image
     * \param eqr_x X-Position, in pixels, of the top-left corner of the equirectangular tile in the full equirectangular image
     * \param eqr_y Y-Position, in pixels, of the top-left corner of the equirectangular tile in the full equirectangular image
     * \param sen_x X-Position, in pixels, of the rectilinear center in the full equirectangular image
     * \param sen_x Y-Position, in pixels, of the rectilinear center in the full equirectangular image
     */

    lg_Void_t lg_ttg_coord(

        lg_Real_t   eqx,
        lg_Real_t   eqy,
        lg_Size_t   eqr_w,
        lg_Size_t   eqr_h,
        lg_Real_t * rcx,
        lg_Real_t * rcy,
        lg_Size_t   rct_w,
        lg_Size_t   rct_h,
        lg_Size_t   pan_w,
        lg_Size_t   pan_h,
        lg_Size_t   eqr_x,
        lg_Size_t   eqr_y,
        lg_Real_t   sen_x,
        lg_Real_t   sen_y

    );

    /*! \brief Rectilinear to equirectangular tile coordinates transform
     *  
     * Performs the conversion from the coordinates of a point in a rectilinear
     * image to the corresponding point in a equirectangular tile image.
     *
     * \param eqx Pointer to quirectangular point x-coordinate (output)
     * \param eqy Pointer to equirectangular point y-coordinate (output)
     * \param eqr_w Width, in pixels, of the equirectangular tile
     * \param eqr_h Height, in pixels, of the equirectangular tile
     * \param rcx Rectilinear point x-coordinate
     * \param rcy Rectilinear point y-coordinate
     * \param rct_w Width, in pixels, of the rectilinear image
     * \param rct_h Height, in pixels, of the rectilinear image
     * \param pan_w Width, in pixels, of the full equirectangular image
     * \param pan_h Height, in pixels, of the full equirectangular image
     * \param eqr_x X-Position, in pixels, of the top-left corner of the equirectangular tile in the full equirectangular image
     * \param eqr_y Y-Position, in pixels, of the top-left corner of the equirectangular tile in the full equirectangular image
     * \param sen_x X-Position, in pixels, of the rectilinear center in the full equirectangular image
     * \param sen_x Y-Position, in pixels, of the rectilinear center in the full equirectangular image
     */

    lg_Void_t lg_gtt_coord(

        lg_Real_t * eqx,
        lg_Real_t * eqy,
        lg_Size_t   eqr_w,
        lg_Size_t   eqr_h,
        lg_Real_t   rcx,
        lg_Real_t   rcy,
        lg_Size_t   rct_w,
        lg_Size_t   rct_h,
        lg_Size_t   pan_w,
        lg_Size_t   pan_h,
        lg_Size_t   eqr_x,
        lg_Size_t   eqr_y,
        lg_Real_t   sen_x,
        lg_Real_t   sen_y

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

