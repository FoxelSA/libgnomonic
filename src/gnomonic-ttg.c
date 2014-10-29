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
 *    Stephane Flotron <s.flotron@foxel.ch>
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

    # include "gnomonic-ttg.h"

/*
    Source - Equirectangular tile to rectilinear gnomonic projection
 */

    lg_Void_t lg_ttg(

        li_C8_t     const * const lgEqrIn,
        lg_Size_t   const         lgEqrWidth,
        lg_Size_t   const         lgEqrHeight,
        lg_Size_t   const         lgEqrLayer,
        li_C8_t           * const lgRectOut,
        lg_Size_t   const         lgRectWidth,
        lg_Size_t   const         lgRectHeight,
        lg_Size_t   const         lgRectLayer,
        lg_Size_t   const         lgPanWidth,
        lg_Size_t   const         lgPanHeight,
        lg_Size_t   const         lgEqrPosX,
        lg_Size_t   const         lgEqrPosY,
        lg_Real_t   const         lgEqrCenterX,
        lg_Real_t   const         lgEqrCenterY,
        li_Method_t const         lgInter

    ) {

        /* Parsing variables */
        lg_Size_t lgDX = lg_Size_s( 0 );
        lg_Size_t lgDY = lg_Size_s( 0 );

        /* Projection variables */
        lg_Real_t lgSX   = lg_Real_s( 0.0 );
        lg_Real_t lgSY   = lg_Real_s( 0.0 );
        lg_Real_t lgPX   = lg_Real_s( 0.0 );
        lg_Real_t lgPY   = lg_Real_s( 0.0 );
        lg_Real_t lgAH   = lg_Real_s( 0.0 );
        lg_Real_t lgAV   = lg_Real_s( 0.0 );

        /* Compute gnomonic projection center */
        lg_Real_t lgNadH = ( lg_Real_c( lgEqrCenterX ) / lg_Real_c( lgPanWidth ) ) * LG_PI2;
        lg_Real_t lgNadV = ( lg_Real_s( 0.5 ) - ( lg_Real_c( lgEqrCenterY ) / lg_Real_c( lgPanHeight ) ) ) * LG_PI;

        /* Compute gnomonic apperture tangants */
        lg_Real_t lgTanAppH = tan( ( lg_Real_c( lgEqrWidth  ) / lg_Real_c( lgPanWidth  ) ) * LG_PI );
        lg_Real_t lgTanAppV = tan( ( lg_Real_c( lgEqrHeight ) / lg_Real_c( lgPanHeight ) ) * LG_PI * lg_Real_s( 0.5 ) );

        /* Rotation matrix coefficients */
        lg_Real_t lgCosY = cos( + lgNadV );
        lg_Real_t lgSinY = sin( + lgNadV );
        lg_Real_t lgCosZ = cos( + lgNadH );
        lg_Real_t lgSinZ = sin( + lgNadH );

        /* Position vector */
        lg_Real_t lgVectori[3] = { lg_Real_s( 0.0 ) };
        lg_Real_t lgVectorf[3] = { lg_Real_s( 0.0 ) };

        /* Padding variable */
        lg_Size_t lgRectPad = lgRectWidth * lgRectLayer; if ( lgRectPad % lg_Size_s( 4 ) ) lgRectPad += lg_Size_s( 4 ) - lgRectPad % lg_Size_s( 4 );

        /* Planar projection referential y-loop */
        for ( lgDY = lg_Size_s( 0 ); lgDY < lgRectHeight; lgDY++ ) {

            /* Planar projection referential x-loop */
            for ( lgDX = lg_Size_s( 0 ); lgDX < lgRectWidth; lgDX++ ) {

                /* Normalized planar coordinates */
                lgPX = ( ( lg_Real_s( 2.0 ) * ( lg_Real_t ) lgDX / ( lg_Real_t ) ( lgRectWidth  - lg_Size_s( 1 ) ) ) - lg_Real_s( 1.0 ) ) * lgTanAppH;
                lgPY = ( ( lg_Real_s( 2.0 ) * ( lg_Real_t ) lgDY / ( lg_Real_t ) ( lgRectHeight - lg_Size_s( 1 ) ) ) - lg_Real_s( 1.0 ) ) * lgTanAppV;

                /* Rebuild position vector - x y z */
                lgVectori[0] = cos( atan( sqrt( lgPX * lgPX + lgPY * lgPY ) ) );
                lgVectori[1] = lgPX * lgVectori[0];
                lgVectori[2] = lgPY * lgVectori[0];

                /* Invert rotation due to t-nadir and p-nadir */
                lgVectorf[0] = + lgCosZ * lgCosY * lgVectori[0] - lgSinZ * lgVectori[1] + lgCosZ * lgSinY * lgVectori[2];
                lgVectorf[1] = + lgSinZ * lgCosY * lgVectori[0] + lgCosZ * lgVectori[1] + lgSinZ * lgSinY * lgVectori[2];
                lgVectorf[2] = - lgSinY          * lgVectori[0] + lg_Real_s( 0.0 )      + lgCosY          * lgVectori[2];

                /* Retreive angular position */
                lgAH = LG_ATN( lgVectorf[0] , lgVectorf[1] );
                lgAV = LG_ASN( lgVectorf[2] );

                /* Retrieve panoramic pixel coordinates */
                lgSX = ( lgPanWidth  - lg_Size_s( 1 ) ) * ( lgAH / LG_PI2 ) - lgEqrPosX;
                lgSY = ( lgPanHeight - lg_Size_s( 1 ) ) * ( ( lgAV / LG_PI ) + lg_Real_s( 0.5 ) ) - lgEqrPosY;

                /* Verify tile panoramic range */
                if ( 

                    ( lgSX > lg_Size_s( 0 ) ) && 
                    ( lgSY > lg_Size_s( 0 ) ) && 
                    ( lgSX < ( lgEqrWidth  - lg_Size_s( 1 ) ) ) && 
                    ( lgSY < ( lgEqrHeight - lg_Size_s( 1 ) ) )

                ) {

                    /* Interpolation process */
                    LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 0 ) ) = lgInter( ( li_C8_t * ) lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayer, 0, lgSX, lgSY );
                    LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 1 ) ) = lgInter( ( li_C8_t * ) lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayer, 1, lgSX, lgSY );
                    LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 2 ) ) = lgInter( ( li_C8_t * ) lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayer, 2, lgSX, lgSY );

                } else {

                    /* Assign black pixel */
                    LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 0 ) ) = li_C8_s( 0 );
                    LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 1 ) ) = li_C8_s( 0 );
                    LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 2 ) ) = li_C8_s( 0 );

                }

            }

        }

    }

/*
    Source - Equirectangular tile to rectilinear fixed focal gnomonic projection
 */

    lg_Void_t lg_ttg_focal(

        li_C8_t     const * const lgEQRBitmap,
        lg_Size_t   const         lgEQRWidth,
        lg_Size_t   const         lgEQRHeight,
        lg_Size_t   const         lgEQRLayer,
        li_C8_t           * const lgRECBitmap,
        lg_Size_t   const         lgRECWidth,
        lg_Size_t   const         lgRECHeight,
        lg_Size_t   const         lgRECLayer,
        lg_Size_t   const         lgEQRMapWidth,
        lg_Size_t   const         lgEQRMapHeight,
        lg_Size_t   const         lgEQRTopLeftX,
        lg_Size_t   const         lgEQRTopLeftY,
        lg_Real_t   const         lgAzimut,
        lg_Real_t   const         lgElevat,
        lg_Real_t   const         lgRoll,
        lg_Real_t   const         lgFocalLength,
        lg_Real_t   const         lgPixelLength,
        li_Method_t const         lgInter

    ) {

        /* Coordinates variables */
        lg_Size_t lgDX = lg_Size_s( 0   );
        lg_Size_t lgDY = lg_Size_s( 0   );
        lg_Real_t lgSX = lg_Real_s( 0.0 );
        lg_Real_t lgSY = lg_Real_s( 0.0 );

        /* Angles trigonometric value variables */
        lg_Real_t lgCosAz = cos( + lgAzimut );
        lg_Real_t lgSinAz = sin( + lgAzimut );
        lg_Real_t lgCosEl = cos( + lgElevat );
        lg_Real_t lgSinEl = sin( + lgElevat );
        lg_Real_t lgCosRl = cos( + lgRoll   );
        lg_Real_t lgSinRl = sin( + lgRoll   );

        /* Position vector variables */
        lg_Real_t lgVectori[3] = { lg_Real_s( 0.0 ) };
        lg_Real_t lgVectorf[3] = { lg_Real_s( 0.0 ) };

        /* Rotation matrix variables */
        lg_Real_t lgMatrix[3][3] = {

            { + lgCosAz * lgCosEl, + lgCosAz * lgSinEl * lgSinRl - lgSinAz * lgCosRl, + lgCosAz * lgSinEl * lgCosRl + lgSinAz * lgSinRl },
            { + lgSinAz * lgCosEl, + lgSinAz * lgSinEl * lgSinRl + lgCosAz * lgCosRl, + lgSinAz * lgSinEl * lgCosRl - lgCosAz * lgSinRl },
            { - lgSinEl          , + lgCosEl * lgSinRl                              , + lgCosEl * lgCosRl                               },

        };

        /* Bitmap padding variable */
        lg_Size_t lgRECPad = LG_B4PAD( lgRECWidth * lgRECLayer );

        /* Optimization variables */
        lg_Size_t lgEQRWidthEdge  = lgEQRWidth  - lg_Size_s( 1 );
        lg_Size_t lgEQRHeightEdge = lgEQRHeight - lg_Size_s( 1 );

        /* Optimization variables */
        lg_Real_t lgRCTWidthHalf  = lg_Real_c( lgRECWidth  ) / lg_Real_s( 2.0 );
        lg_Real_t lgRCTHeightHalf = lg_Real_c( lgRECHeight ) / lg_Real_s( 2.0 );

        /* Planar projection referential y-loop */
        for ( lgDY = lg_Size_s( 0 ); lgDY < lgRECHeight; lgDY++ ) {

            /* Planar projection referential x-loop */
            for ( lgDX = lg_Size_s( 0 ); lgDX < lgRECWidth; lgDX++ ) {

                /* Compute virtual sensor pixel position in 3D-frame */
                lgVectori[0] = lgFocalLength;
                lgVectori[1] = lgPixelLength * ( lg_Real_c( lgDX ) - lgRCTWidthHalf  );
                lgVectori[2] = lgPixelLength * ( lg_Real_c( lgDY ) - lgRCTHeightHalf );

                /* Compute rotated vector based on rotation matrix */
                lgVectorf[0] = lgMatrix[0][0] * lgVectori[0] + lgMatrix[0][1] * lgVectori[1] + lgMatrix[0][2] * lgVectori[2];
                lgVectorf[1] = lgMatrix[1][0] * lgVectori[0] + lgMatrix[1][1] * lgVectori[1] + lgMatrix[1][2] * lgVectori[2];
                lgVectorf[2] = lgMatrix[2][0] * lgVectori[0] + lgMatrix[2][1] * lgVectori[1] + lgMatrix[2][2] * lgVectori[2];

                /* Retrieve panoramic pixel x,y-coordinates */
                lgSX = - lgEQRTopLeftX + ( lgEQRMapWidth  - lg_Size_s( 1 ) ) * ( LG_ATN( lgVectorf[0], lgVectorf[1] ) / LG_PI2 ) ;
                lgSY = - lgEQRTopLeftY + ( lgEQRMapHeight - lg_Size_s( 1 ) ) * ( LG_ASN( lgVectorf[2] / LG_EUCLR3( lgVectorf ) ) / LG_PI + lg_Real_s( 0.5 ) );

                /* Correction of boundary tiles */
                lgSX = ( lgSX < lg_Size_s( 0 ) ) ? lgSX + lgEQRMapWidth : lgSX;

                /* Verify panoramic x,y-coordinates range */
                if ( ( lgSX > lg_Size_s( 0 ) ) && ( lgSY > lg_Size_s( 0 ) ) && ( lgSX < lgEQRWidthEdge ) && ( lgSY < lgEQRHeightEdge ) ) {

                    /* Interpolation process */
                    LG_B4( lgRECBitmap, lgRECPad, lgRECLayer, lgDX, lgDY, lg_Size_s( 0 ) ) = lgInter( ( li_C8_t * ) lgEQRBitmap, lgEQRWidth, lgEQRHeight, lgEQRLayer, lg_Size_s( 0 ), lgSX, lgSY );
                    LG_B4( lgRECBitmap, lgRECPad, lgRECLayer, lgDX, lgDY, lg_Size_s( 1 ) ) = lgInter( ( li_C8_t * ) lgEQRBitmap, lgEQRWidth, lgEQRHeight, lgEQRLayer, lg_Size_s( 1 ), lgSX, lgSY );
                    LG_B4( lgRECBitmap, lgRECPad, lgRECLayer, lgDX, lgDY, lg_Size_s( 2 ) ) = lgInter( ( li_C8_t * ) lgEQRBitmap, lgEQRWidth, lgEQRHeight, lgEQRLayer, lg_Size_s( 2 ), lgSX, lgSY );

                } else {

                    /* Assign black pixel */
                    LG_B4( lgRECBitmap, lgRECPad, lgRECLayer, lgDX, lgDY, lg_Size_s( 0 ) ) = li_C8_s( 0 );
                    LG_B4( lgRECBitmap, lgRECPad, lgRECLayer, lgDX, lgDY, lg_Size_s( 1 ) ) = li_C8_s( 0 );
                    LG_B4( lgRECBitmap, lgRECPad, lgRECLayer, lgDX, lgDY, lg_Size_s( 2 ) ) = li_C8_s( 0 );

                }

            }

        }

    }

 /*
    Source - Equirectangular tile to uncentered rectilinear gnomonic projection
 */

    lg_Void_t lg_ttg_uc(

        li_C8_t     const * const lgEqrIn,
        lg_Size_t   const         lgEqrWidth,
        lg_Size_t   const         lgEqrHeight,
        lg_Size_t   const         lgEqrLayer,
        li_C8_t           * const lgRectOut,
        lg_Size_t   const         lgRectWidth,
        lg_Size_t   const         lgRectHeight,
        lg_Size_t   const         lgRectLayer,
        lg_Real_t   const         lgPx0,
        lg_Real_t   const         lgPy0,
        lg_Size_t   const         lgPanWidth,
        lg_Size_t   const         lgPanHeight,
        lg_Size_t   const         lgEqrPosX,
        lg_Size_t   const         lgEqrPosY,
        lg_Real_t   const         lgRoll,
        lg_Real_t   const         lgAzi,
        lg_Real_t   const         lgEle,
        lg_Real_t   const         lgHea,
        lg_Real_t   const         lgPixSize,
        lg_Real_t   const         lgFocalLength,
        li_Method_t const         lgInter

    ) {

        /* Parsing variables */
        lg_Size_t lgDX = lg_Size_s( 0 );
        lg_Size_t lgDY = lg_Size_s( 0 );

        /* Projection variables */
        lg_Real_t lgSX   = lg_Real_s( 0.0 );
        lg_Real_t lgSY   = lg_Real_s( 0.0 );
        lg_Real_t lgPX   = lg_Real_s( 0.0 );
        lg_Real_t lgPY   = lg_Real_s( 0.0 );
        lg_Real_t lgAH   = lg_Real_s( 0.0 );
        lg_Real_t lgAV   = lg_Real_s( 0.0 );
        lg_Real_t lgNorm = lg_Real_s( 0.0 );
        
        /* compute rotations */
        lg_Real_t lgTheta = lgEle ; 
        lg_Real_t lgPsi   = lgRoll ; 
        lg_Real_t lgPhi   = lgAzi + lgHea ;
        
        /* initialize rotation matrices x-axis */
        lg_Real_t Rx[3][3] = { 

            { lg_Real_s( 1.0 ), lg_Real_s( 0.0 ), lg_Real_s( 0.0 ) }, 
            { lg_Real_s( 0.0 ), lg_Real_s( 1.0 ), lg_Real_s( 0.0 ) }, 
            { lg_Real_s( 0.0 ), lg_Real_s( 0.0 ), lg_Real_s( 1.0 ) } 

        };

        /* initialize rotation matrices y-axis */
        lg_Real_t Ry[3][3] = { 

            { lg_Real_s( 1.0 ), lg_Real_s( 0.0 ), lg_Real_s( 0.0 ) }, 
            { lg_Real_s( 0.0 ), lg_Real_s( 1.0 ), lg_Real_s( 0.0 ) }, 
            { lg_Real_s( 0.0 ), lg_Real_s( 0.0 ), lg_Real_s( 1.0 ) } 

        };

        /* initialize rotation matrices z-axis */
        lg_Real_t Rz[3][3] = { 

            { lg_Real_s( 1.0 ), lg_Real_s( 0.0 ), lg_Real_s( 0.0 ) }, 
            { lg_Real_s( 0.0 ), lg_Real_s( 1.0 ), lg_Real_s( 0.0 ) }, 
            { lg_Real_s( 0.0 ), lg_Real_s( 0.0 ), lg_Real_s( 1.0 ) } 

        };
        
        /* Rx rotation matrix */
        Rx[1][1] = + cos( lgTheta ); 
        Rx[1][2] = + sin( lgTheta );
        Rx[2][1] = - Rx[1][2];
        Rx[2][2] = + Rx[1][1];
        
        /* Ry rotation matrix */
        Ry[0][0] = + cos( lgPhi );
        Ry[0][2] = + sin( lgPhi ); 
        Ry[2][0] = - Ry[0][2];
        Ry[2][2] = + Ry[0][0];
        
        /* Rz rotation matrix */
        Rz[0][0] = + cos( lgPsi );
        Rz[0][1] = + sin( lgPsi );
        Rz[1][0] = - Rz[0][1]; 
        Rz[1][1] = + Rz[0][0];

        /* Position vector */
        lg_Real_t lgVectori[3] = { lg_Real_s( 0.0 ) };
        lg_Real_t lgVectorf[3] = { lg_Real_s( 0.0 ) };
        
        /* Padding variable */
        lg_Size_t lgRectPad = lgRectWidth * lgRectLayer; if ( lgRectPad % lg_Size_s( 4 ) ) lgRectPad += lg_Size_s( 4 ) - lgRectPad % lg_Size_s( 4 );
        
        /* Planar projection referential y-loop */
        for ( lgDY = lg_Size_s( 0 ); lgDY < lgRectHeight; lgDY++ ) {

            /* Planar projection referential x-loop */
            for ( lgDX = lg_Size_s( 0 ); lgDX < lgRectWidth; lgDX++ ) {

                /* Normalized planar coordinates */
                lgPX = ( lgPixSize * ( lg_Real_c( lgDX ) - lgPx0 ) ) ;
                lgPY = ( lgPixSize * ( lg_Real_c( lgDY ) - lgPy0 ) ) ;
              
                /* Rebuild position vector - x y z */
                lgVectori[0] =  lgPX ;
                lgVectori[1] = -lgPY ;
                lgVectori[2] =  lgFocalLength;
                
                /* apply z rotation */
                lgVectorf[0] = Rz[0][0] * lgVectori[0] + Rz[0][1] * lgVectori[1] + Rz[0][2] * lgVectori[2] ;
                lgVectorf[1] = Rz[1][0] * lgVectori[0] + Rz[1][1] * lgVectori[1] + Rz[1][2] * lgVectori[2] ;
                lgVectorf[2] = Rz[2][0] * lgVectori[0] + Rz[2][1] * lgVectori[1] + Rz[2][2] * lgVectori[2] ;
                
                /* apply x rotation */
                lgVectori[0] = Rx[0][0] * lgVectorf[0] + Rx[0][1] * lgVectorf[1] + Rx[0][2] * lgVectorf[2] ;
                lgVectori[1] = Rx[1][0] * lgVectorf[0] + Rx[1][1] * lgVectorf[1] + Rx[1][2] * lgVectorf[2] ;
                lgVectori[2] = Rx[2][0] * lgVectorf[0] + Rx[2][1] * lgVectorf[1] + Rx[2][2] * lgVectorf[2] ;
                
                /* Apply y rotation */
                lgVectorf[0] = Ry[0][0] * lgVectori[0] + Ry[0][1] * lgVectori[1] + Ry[0][2] * lgVectori[2];
                lgVectorf[1] = Ry[1][0] * lgVectori[0] + Ry[1][1] * lgVectori[1] + Ry[1][2] * lgVectori[2];
                lgVectorf[2] = Ry[2][0] * lgVectori[0] + Ry[2][1] * lgVectori[1] + Ry[2][2] * lgVectori[2];
                
                /* Compute final vector norm */
                lgNorm = sqrt( lgVectorf[0] * lgVectorf[0] + lgVectorf[1] * lgVectorf[1] + lgVectorf[2] * lgVectorf[2]) ;
                
                /* Normalize final vector */
                lgVectorf[0] /= lgNorm; 
                lgVectorf[1] /= lgNorm; 
                lgVectorf[2] /= lgNorm; 
                
                /* Compute azimuth-elevation */
                if( sqrt( lgVectorf[0] * lgVectorf[0] + lgVectorf[2] * lgVectorf[2]  ) > lg_Real_s( 0.0 ) ) {

                    /* Retrieve azimuth and elevation angles */
                    lgAH = atan2 ( lgVectorf[0] , lgVectorf[2]  ) ;
                    lgAV = atan2 ( lgVectorf[1] , sqrt( lgVectorf[0] * lgVectorf[0] + lgVectorf[2] * lgVectorf[2] ) );

                } else {

                    /* Retrieve azimuth and elevation angles */
                    lgAH = lg_Real_s( 0.0 );
                    lgAV = ( lgVectorf[1] > lg_Real_s( 0.0 ) ) ? LG_PI / lg_Real_s( 2.0 ): - LG_PI / lg_Real_s( 2.0 );

                }

                /* Retrieve panoramic x-pixel coordinates */
                lgSX = lg_Real_c( lgPanWidth - 1 ) * ( ( lgAH + LG_PI ) / LG_PI2 ) - lgEqrPosX ;

                /* Retrieve panoramic y-pixel coordinates */
                lgSY = lg_Real_c( lgPanWidth - 1 ) * ( ( -lgAV + LG_PI / lg_Real_s( 2.0 ) ) / LG_PI2 ) - lgEqrPosY ;

                /* Correction of boundary tiles */
                lgSX = ( lgSX < lg_Size_s( 0 ) ) ? lgSX + lgPanWidth : lgSX;

                /* Verify tile panoramic range */
                if ( 

                    ( lgSX > lg_Size_s( 0 ) ) && 
                    ( lgSY > lg_Size_s( 0 ) ) && 
                    ( lgSX < ( lgEqrWidth  - lg_Size_s( 1 ) ) ) && 
                    ( lgSY < ( lgEqrHeight - lg_Size_s( 1 ) ) )

                ) {

                    /* Interpolation process */
                    LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 0 ) ) = lgInter( ( li_C8_t * ) lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayer, lg_Size_s( 0 ), lgSX, lgSY );
                    LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 1 ) ) = lgInter( ( li_C8_t * ) lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayer, lg_Size_s( 1 ), lgSX, lgSY );
                    LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 2 ) ) = lgInter( ( li_C8_t * ) lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayer, lg_Size_s( 2 ), lgSX, lgSY );

                } else {

                    /* Assign black pixel */
                    LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 0 ) ) = li_C8_s( 0 );
                    LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 1 ) ) = li_C8_s( 0 );
                    LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 2 ) ) = li_C8_s( 0 );

                }

            }

        }

    }

/*
    Source - Equirectangular tile to rectilinear - Centered sight methods
 */

/*
    Source - Equirectangular tile to rectilinear - Elphel methods
 */

/*
    Source - Equirectangular tile to rectilinear image gnomonic projection
 */

    lg_Void_t lg_ttg_generic(

        li_C8_t     const * const lgeBitmap,
        lg_Size_t   const         lgeWidth,
        lg_Size_t   const         lgeHeight,
        lg_Size_t   const         lgeLayers,
        li_C8_t           * const lgrBitmap,
        lg_Size_t   const         lgrWidth,
        lg_Size_t   const         lgrHeight,
        lg_Size_t   const         lgrLayers,
        lg_Real_t   const         lgrSightX,
        lg_Real_t   const         lgrSightY,
        lg_Size_t   const         lgmWidth,
        lg_Size_t   const         lgmHeight,
        lg_Size_t   const         lgmCornerX,
        lg_Size_t   const         lgmCornerY,
        lg_Real_t   const         lgAzim,
        lg_Real_t   const         lgElev,
        lg_Real_t   const         lgRoll,
        lg_Real_t   const         lgFocal,
        lg_Real_t   const         lgPixel,
        li_Method_t const         lgInter

    ) {

        /* Coordinates variables */
        lg_Size_t lgDX = lg_Size_s( 0   );
        lg_Size_t lgDY = lg_Size_s( 0   );
        lg_Real_t lgSX = lg_Real_s( 0.0 );
        lg_Real_t lgSY = lg_Real_s( 0.0 );

        /* Position vector variables */
        lg_Real_t lgPvi[3] = { lg_Real_s( 0.0 ) };
        lg_Real_t lgPvf[3] = { lg_Real_s( 0.0 ) };

        /* Rotation matrix variables */
        lg_Real_t lgMat[3][3] = { { lg_Real_s( 0.0 ) } };

        /* Optimization variables */
        lg_Size_t lgeEdgeX = lgeWidth  - lg_Size_s( 1 );
        lg_Size_t lgeEdgeY = lgeHeight - lg_Size_s( 1 );
        lg_Size_t lgmEdgeX = lgmWidth  - lg_Size_s( 1 );
        lg_Size_t lgmEdgeY = lgmHeight - lg_Size_s( 1 );

        /* Bitmap padding variable */
        lg_Size_t lgrPad = LG_B4PAD( lgrWidth * lgrLayers );

        /* Compute rotation matrix */
        lg_algebra_r2erotation( lgMat, lgAzim, lgElev, lgRoll );

        /* Rectilinear pixels y-loop */
        for ( lgDY = lg_Size_s( 0 ); lgDY < lgrHeight; lgDY ++ ) {

            /* Rectilinear pixels x-loop */
            for ( lgDX = lg_Size_s( 0 ); lgDX < lgrWidth; lgDX ++ ) {

                /* Compute pixel position in 3d-frame */
                lgPvi[0] = lgFocal;
                lgPvi[1] = lgPixel * ( lg_Real_c( lgDX ) - lgrSightX );
                lgPvi[2] = lgPixel * ( lg_Real_c( lgDY ) - lgrSightY );

                /* Compute rotated pixel position in 3d-frame */
                lgPvf[0] = lgMat[0][0] * lgPvi[0] + lgMat[0][1] * lgPvi[1] + lgMat[0][2] * lgPvi[2];
                lgPvf[1] = lgMat[1][0] * lgPvi[0] + lgMat[1][1] * lgPvi[1] + lgMat[1][2] * lgPvi[2];
                lgPvf[2] = lgMat[2][0] * lgPvi[0] + lgMat[2][1] * lgPvi[1] + lgMat[2][2] * lgPvi[2];

                /* Retrieve mapping pixel (x,y)-coordinates */
                lgSX = - lgmCornerX + lgmEdgeX * ( LG_ATN( lgPvf[0], lgPvf[1] ) / LG_PI2 ) ;
                lgSY = - lgmCornerY + lgmEdgeY * ( LG_ASN( lgPvf[2] / LG_EUCLR3( lgPvf ) ) / LG_PI + lg_Real_s( 0.5 ) );

                /* Mapping boundary conditions management */
                lgSX = ( lgSX < lg_Size_s( 0 ) ) ? lgSX + lgmWidth : lgSX;

                /* Verify mapping pixel (x,y)-coordinates */
                if ( ( lgSX >= lg_Size_s( 0 ) ) && ( lgSY >= lg_Size_s( 0 ) ) && ( lgSX <= lgeEdgeX ) && ( lgSY <= lgeEdgeY ) ) {

                    /* Assign interpolated pixel */
                    LG_B4( lgrBitmap, lgrPad, lgrLayers, lgDX, lgDY, lg_Size_s( 0 ) ) = lgInter( ( li_C8_t * ) lgeBitmap, lgeWidth, lgeHeight, lgeLayers, lg_Size_s( 0 ), lgSX, lgSY );
                    LG_B4( lgrBitmap, lgrPad, lgrLayers, lgDX, lgDY, lg_Size_s( 1 ) ) = lgInter( ( li_C8_t * ) lgeBitmap, lgeWidth, lgeHeight, lgeLayers, lg_Size_s( 1 ), lgSX, lgSY );
                    LG_B4( lgrBitmap, lgrPad, lgrLayers, lgDX, lgDY, lg_Size_s( 2 ) ) = lgInter( ( li_C8_t * ) lgeBitmap, lgeWidth, lgeHeight, lgeLayers, lg_Size_s( 2 ), lgSX, lgSY );

                } else {

                    /* Assign black pixel */
                    LG_B4( lgrBitmap, lgrPad, lgrLayers, lgDX, lgDY, lg_Size_s( 0 ) ) = li_C8_s( 0 );
                    LG_B4( lgrBitmap, lgrPad, lgrLayers, lgDX, lgDY, lg_Size_s( 1 ) ) = li_C8_s( 0 );
                    LG_B4( lgrBitmap, lgrPad, lgrLayers, lgDX, lgDY, lg_Size_s( 2 ) ) = li_C8_s( 0 );

                }

            }

        }

    }

