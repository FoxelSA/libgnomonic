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


/*
    Source - Includes
 */

    # include "gnomonic-ttg.h"

/*
    Source - Gnomonic projection from tile of equirectangular panoramic image
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
                    LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 0 ) ) = lgInter( lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayer, 0, lgSX, lgSY );
                    LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 1 ) ) = lgInter( lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayer, 1, lgSX, lgSY );
                    LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 2 ) ) = lgInter( lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayer, 2, lgSX, lgSY );

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
    Source - Gnomonic projection from tile of equirectangular panoramic image using elphel's method
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
        lg_Real_t   lgEqrCenterX,
        lg_Real_t   lgEqrCenterY,
        lg_Real_t   lgRoll,
        lg_Real_t   lgAzi,
        lg_Real_t   lgEle,
        lg_Real_t   lgHea,
        lg_Real_t   lgPixSize,
        lg_Real_t   lgFocalLength,
        li_Method_t lgInter

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
        
        /* initialize rotation matrices */
        lg_Real_t Rx[3][3] = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0} };
        lg_Real_t Ry[3][3] = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0} };
        lg_Real_t Rz[3][3] = { {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0} };
        
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
                if(lgAH < 0.0)
                    lgAH += LG_PI2;
                    
                if( fabs(lgAH -lgPhi) > lg_Real_s( 1.5 ) * LG_PI ) {

                    /* Compute x-coordinates */
                    lgSX = lg_Real_c( lgPanWidth - 1 ) * ( ( lgAH - LG_PI2 - lgPhi) / LG_PI2 ) - lgEqrPosX + lgEqrCenterX ;

                } else {

                    /* Compute x-coordinates */
                    lgSX = lg_Real_c( lgPanWidth - 1 ) * ( ( lgAH - lgPhi ) / LG_PI2 ) - lgEqrPosX + lgEqrCenterX ;

                }
                
                /* Retrieve panoramic y-pixel coordinates */
                if( fabs(lgAV-lgTheta) > lg_Real_s( 1.5 ) * LG_PI ) {

                    /* Compute y-coordinates */
                    lgSY = lg_Real_c( lgPanWidth - 1 ) * ( ( -lgAV - LG_PI2 + lgTheta) / LG_PI2 ) - lgEqrPosY + lgEqrCenterY ;

                } else {

                    /* Compute y-coordinates */
                    lgSY = lg_Real_c( lgPanWidth - 1 ) * ( ( -lgAV + lgTheta ) / LG_PI2 ) - lgEqrPosY + lgEqrCenterY ;

                }
                
                /* Verify tile panoramic range */
                if ( 

                    ( lgSX > lg_Size_s( 0 ) ) && 
                    ( lgSY > lg_Size_s( 0 ) ) && 
                    ( lgSX < ( lgEqrWidth  - lg_Size_s( 1 ) ) ) && 
                    ( lgSY < ( lgEqrHeight - lg_Size_s( 1 ) ) )

                ) {

                    /* Interpolation process */
                    LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 0 ) ) = lgInter( lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayer, 0, lgSX, lgSY );
                    LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 1 ) ) = lgInter( lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayer, 1, lgSX, lgSY );
                    LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 2 ) ) = lgInter( lgEqrIn, lgEqrWidth, lgEqrHeight, lgEqrLayer, 2, lgSX, lgSY );

                } else {

                    /* Assign black pixel */
                    LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 0 ) ) = li_C8_s( 0 );
                    LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 1 ) ) = li_C8_s( 0 );
                    LG_B4( lgRectOut, lgRectPad, lgRectLayer, lgDX, lgDY, lg_Size_s( 2 ) ) = li_C8_s( 0 );

                }

            }

        }

    }
    
