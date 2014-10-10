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
 * Contributor(s) :
 *
 *     Stephane Flotron <s.flotron@foxel.ch>
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

    /*! \file   gnomonic-ttg.h
     *  \author Nils Hamel (n.hamel@foxel.ch)
     *
     *  Equirectangular tile to rectilinear transformation
     */

/*
    Header - Include guard
 */

    # ifndef __LG_TTG__
    # define __LG_TTG__

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

    /*! \brief Equirectangular tile to rectilinear gnomonic projection
     *
     *  This function performs an gnomonic projection considering a tile of an entire
     *  equirectangular panorama using the desired interpolation method. The results
     *  are drawn in the lgRectOut bitmap. The lgRectOut has to be already allocated
     *  according to its parameters.
     *
     *  \param lgEqrIn Pointer to equirectangular tile bitmap
     *  \param lgEqrWidth Width, in pixels, of the equirectangular tile bitmap eqr_img
     *  \param lgEqrHeight Height, in pixels, of the equirectangular tile bitmap eqr_img
     *  \param lgEqrLayer Depth, in chromatic layer count, of the equirectangular tile bitmap eqr_img
     *  \param lgRectOut Pointer to gnomonic bitmap
     *  \param lgRectWidth Width, in pixels, of the gnomonic bitmap rct_img
     *  \param lgRectHeight Height, in pixels, of the gnomonic bitmap rct_img
     *  \param lgRectLayer Depth, in chromatic layer count, of the gnomonic bitmap rct_img
     *  \param lgPanWidth Width, in pixel, of the entire equirectangular mapping
     *  \param lgPanHeight Height, in pixel, of the entire equirectangular mapping
     *  \param lgEqrPosX Position x, in pixel, of the tile in the entire equirectangular mapping
     *  \param lgEqrPosY Position y, in pixel, of the tile in the entire equirectangular mapping
     *  \param lgEqrCenterX Position x, in pixel, of the tile center in the entire equirectangular mapping
     *  \param lgEqrCenterY Position y, in pixel, of the tile center in the entire equirectangular mapping
     *  \param lgInter Pointer to interpolation method function
     */

    lg_Void_t lg_ttg(

        li_C8_t *   lgEqrIn,
        lg_Size_t   lgEqrWidth,
        lg_Size_t   lgEqrHeight,
        lg_Size_t   lgEqrLayer,
        li_C8_t *   lgRectOut,
        lg_Size_t   lgRectWidth,
        lg_Size_t   lgRectHeight,
        lg_Size_t   lgRectLayer,
        lg_Size_t   lgPanWidth,
        lg_Size_t   lgPanHeight,
        lg_Size_t   lgEqrPosX,
        lg_Size_t   lgEqrPosY,
        lg_Real_t   lgEqrCenterX,
        lg_Real_t   lgEqrCenterY,
        li_Method_t lgInter

    );

    /*! \brief Equirectangular tile to rectilinear fixed focal gnomonic projection
     * 
     *  This function performs a gnomonic reprojection of an equirectangular tile extracted
     *  from an entire equirectangular mapping. The obtained rectilinear image can have an
     *  arbitrary size taking into account that scaling of pixels is set through focal length
     *  and pixel length, assumed to be identical in both direction.
     *  
     *  The input equirectangular tile has to be at least a three chromatic layers image and
     *  the output rectilinear image has to be already allocated according to its parameters
     *  and has to come with at least three chromatic layers. The bitmaps are standard bitmaps
     *  that consider byte padding in memory.
     *
     *  In order to perform the desired projection, the following 3d-frame is attached to the
     *  entire equirectangular mapping from which the tile is extracted : the x-axis points
     *  the left edge of the mapping at half height. The y-axis points at third fourth of the
     *  mapping width and at half of its height. The z-axis is obtained using a cross-product,
     *  inducing a direct frame.
     *
     *  The rectilinear image has its center attached to the x-axis and the image plane is
     *  orthogonal to this same x-axis. The rotation matrix is built as follows : 
     * 
     *      M = Rz(Azimut)Ry(Elevation)Rx(Roll)
     *
     *  and corresponds to the rotation that brings the rectilinear image pixels on the
     *  equirectangular mapping.
     *
     *  \param lgEQRBitmap Pointer to equirectangular tile bitmap
     *  \param lgEQRWidth Width, in pixels, of the equirectangular tile bitmap
     *  \param lgEQRHeight Height, in pixels, of the equirectangular tile bitmap
     *  \param lgEQRLayer Depth, in chromatic layer count, of the equirectangular tile bitmap
     *  \param lgRECBitmap Pointer to rectilinear bitmap that recieve the gnomonic projection
     *  \param lgRECWidth Width, in pixels, of the rectilinear bitmap
     *  \param lgRECHeight Height, in pixels, of the rectilinear bitmap
     *  \param lgRECLayer Depth, in chromatic layer count, of the rectilinear bitmap
     *  \param lgEQRMapWidth Width, in pixels, of the entire equirectangular mapping
     *  \param lgEQRMapHeight Height, in pixels, of the entire equirectangular mapping
     *  \param lgEQRTopLeftX Position x, in pixels, of the equirectangular tile top-left corner in the entire mapping
     *  \param lgEQRTopLeftY Position y, in pixels, of the equirectangular tile top-left corner in the entire mapping
     *  \param lgAzimut Azimut angle, in radians
     *  \param lgElevat Elevation angle, in radians
     *  \param lgRoll Roll angle, in radians
     *  \param lgFocalLength Focal length, in mm, of the rectilinear image
     *  \param lgPixelLength Length, in mm, of the pixels on the rectilinear image virtual camera
     *  \param lgInter Pointer to interpolation method function
     */

    lg_Void_t lg_ttg_focal(

        li_C8_t *   lgEQRBitmap,
        lg_Size_t   lgEQRWidth,
        lg_Size_t   lgEQRHeight,
        lg_Size_t   lgEQRLayer,
        li_C8_t *   lgRECBitmap,
        lg_Size_t   lgRECWidth,
        lg_Size_t   lgRECHeight,
        lg_Size_t   lgRECLayer,
        lg_Size_t   lgEQRMapWidth,
        lg_Size_t   lgEQRMapHeight,
        lg_Size_t   lgEQRTopLeftX,
        lg_Size_t   lgEQRTopLeftY,
        lg_Real_t   lgAzimut,
        lg_Real_t   lgElevat,
        lg_Real_t   lgRoll,
        lg_Real_t   lgFocalLength,
        lg_Real_t   lgPixelLength,
        li_Method_t lgInter

    );

    /*! \brief Equirectangular tile to uncentered rectilinear using elphel data
     *
     *  This function performs an gnomonic projection considering a tile of an entire
     *  equirectangular panorama using the desired interpolation method. The results
     *  are drawn in the lgRectOut bitmap. The lgRectOut has to be already allocated
     *  according to its parameters.
     *
     *  \param lgEqrIn Pointer to equirectangular tile bitmap
     *  \param lgEqrWidth Width, in pixels, of the equirectangular tile bitmap eqr_img
     *  \param lgEqrHeight Height, in pixels, of the equirectangular tile bitmap eqr_img
     *  \param lgEqrLayer Depth, in chromatic layer count, of the equirectangular tile bitmap eqr_img
     *  \param lgRectOut Pointer to gnomonic bitmap
     *  \param lgRectWidth Width, in pixels, of the gnomonic bitmap rct_img
     *  \param lgRectHeight Height, in pixels, of the gnomonic bitmap rct_img
     *  \param lgRectLayer Depth, in chromatic layer count, of the gnomonic bitmap rct_img
     *  \param lgPx0 X coordinate of principal point of the gnomonic bitmap rct_img
     *  \param lgPy0 Y coordinate of principal point of the gnomonic bitmap rct_img
     *  \param lgPanWidth Width, in pixel, of the entire equirectangular mapping
     *  \param lgPanHeight Height, in pixel, of the entire equirectangular mapping
     *  \param lgEqrPosX Position x, in pixel, of the tile in the entire equirectangular mapping
     *  \param lgEqrPosY Position y, in pixel, of the tile in the entire equirectangular mapping
     *  \param lgEqrCenterX Position x, in pixel, of the tile center in the entire equirectangular mapping
     *  \param lgEqrCenterY Position y, in pixel, of the tile center in the entire equirectangular mapping
     *  \param lgRoll Angle roll of elphel's camera
     *  \param lgAzi Azimuth angle of elphel's camera
     *  \param lgEle Elevation angle of elphel's camera
     *  \param lgHea Heading angle of elphel's camera
     *  \param lgPixSize Pixel size in mm
     *  \param lgFocalLength Focal length in mm
     *  \param lgInter Pointer to interpolation method function
     */

    lg_Void_t lg_ttg_uc(

        li_C8_t *   lgEqrIn,
        lg_Size_t   lgEqrWidth,
        lg_Size_t   lgEqrHeight,
        lg_Size_t   lgEqrLayer,
        li_C8_t *   lgRectOut,
        lg_Size_t   lgRectWidth,
        lg_Size_t   lgRectHeight,
        lg_Size_t   lgRectLayer,
        lg_Real_t   lgPx0,
        lg_Real_t   lgPy0,
        lg_Size_t   lgPanWidth,
        lg_Size_t   lgPanHeight,
        lg_Size_t   lgEqrPosX,
        lg_Size_t   lgEqrPosY,
        lg_Real_t   lgRoll,
        lg_Real_t   lgAzi,
        lg_Real_t   lgEle,
        lg_Real_t   lgHea,
        lg_Real_t   lgPixSize,
        lg_Real_t   lgFocalLength,
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
