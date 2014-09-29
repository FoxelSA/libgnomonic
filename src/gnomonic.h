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

    /*! \file   gnomonic.h
     *  \author Nils Hamel (n.hamel@foxel.ch)
     *
     *  Library common header file
     */

    /*! \mainpage libgnomonic
     *
     *  \section libgnomonic
     *  \section _ Gnomonic projection algorithms library
     *  
     *  This library is made to perform gnomonic projections from a entire equirectangular
     *  panorama mapping to extract rectlinear mappings and the inverted operation. It
     *  also ensure gnomonic reprojection of specific tiles of the equirectangular mapping 
     *  to retrieve rectilinear mapping of the desired tile.
     *
     *  \section Documentation
     *
     *  A detailed documentation can be generated through doxygen. A more general documentation 
     *  can be consulted at https://github.com/FoxelSA/libgnomonic/wiki.
     *
     *  \section Copyright
     * 
     *  Copyright (c) 2013-2014 FOXEL SA - http://foxel.ch \n
     *  This program is part of the FOXEL project <http://foxel.ch>.
     *  
     *  Please read the COPYRIGHT.md file for more information.
     *
     *  \section License
     *
     *  This program is licensed under the terms of the GNU Affero General Public License
     *  v3 (GNU AGPL), with two additional terms. The content is licensed under the terms 
     *  of the Creative Commons Attribution-ShareAlike 4.0 International (CC BY-SA) license.
     *
     *  You must read <http://foxel.ch/license> for more information about our Licensing
     *  terms and our Usage and Attribution guidelines.
     */

/*
    Header - Include guard
 */

    # ifndef __LG_GNOMONIC__
    # define __LG_GNOMONIC__

/*
    Header - C/C++ compatibility
 */

    # ifdef __cplusplus
    extern "C" {
    # endif

/*
    Header - Includes
 */

    # include <stdio.h>
    # include <math.h>
    # include <stdint.h>

/*
    Header - Preprocessor definitions
 */

    /* Define mathematical constants */
    # define LG_PI              lg_Real_s( 3.14159265358979323846264338327950 )
    # define LG_PI2             lg_Real_s( 6.28318530717958647692528676655901 )

/*
    Header - Preprocessor macros
 */

    /* Define casting macro */
    # define lg_Size_c( x )     ( ( lg_Size_t ) x )
    # define lg_Real_c( x )     ( ( lg_Real_t ) x )

    /* Define litteral suffix */
    # define lg_Size_s( x )     INT64_C( x )
    # define lg_Real_s( x )     ( x ## f )

    /* Define formated output specifiers */
    # define lg_Size_p          PRId64
    # define lg_Real_p          "lf"

    /* Define formated input specifiers */
    # define lg_Size_i          SCNu64
    # define lg_Real_i          "lf"

    /* Define mathematical function */
    # define LG_ATN(x,y)        ( ( x >= 0 ) ? ( ( y >= 0 ) ? atan( y / x ) : LG_PI2 + atan( y / x ) ) : LG_PI + atan( y / x ) )
    # define LG_ASN(x)          ( asin( x ) )

    /* Define bitmap element accessing macro */
    # define LG_B4(b,p,l,x,y,c) ( * ( b + p * y + l * x + c ) )

/*
    Header - Typedefs
 */

    /* Define general void */
    typedef void    lg_Void_t;

    /* Define index type */
    typedef int64_t lg_Size_t;

    /* Define floating type */
    typedef double  lg_Real_t;

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

