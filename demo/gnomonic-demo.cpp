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

    /* Standard includes */
    # include <stdio.h>
    # include <stdlib.h>
    # include <string.h>

    /* Gnomonic library - Adpat this line on your machine ! */
    # include "../src/gnomonic-all.h"

    /* OpenCV */
    # include <opencv2/core/core.hpp>
    # include <opencv2/highgui/highgui.hpp>

/*
    Source - Usage function
 */

    void usage( void ) {

        /* Display help */
        printf( "Usage : gnomonic-demo\n" );
        printf( "gnomonic-demo [path_to_equirectangular_panorama_image] [path_to_gnomonic_projection_image]\n" );

    }

/*
    Source - Demonstration function
 */

    int main ( int argc, char ** argv ) {

        /* Verify help */
        if ( ( strcmp( argv[1], "--help" ) == 0 ) || ( strcmp( argv[1], "-h" ) == 0 ) ) {

            /* Display help */
            usage();

        } else {

            /* Gnomonic image size */
            int gnm_width = 512;
            int gnm_height = 512;

            /* OpenCV read equirectangular panorama image */
            cv::Mat pan_img( cv::imread( argv[1], 1 ) );

            /* OpenCV allocate image for gnomonic projection */
            cv::Mat rct_img( gnm_height, gnm_width, CV_8UC3 );

            /* OpenCV panorama image size */
            cv::Size pan_siz( pan_img.size() );

            /* Gnomonic projection example */
            gnomonic_etg(

                pan_img.data,
                pan_siz.width,
                pan_siz.height,
                pan_img.channels(),
                rct_img.data,
                gnm_width,
                gnm_height,
                3,
                315.0 * ( M_PI / 180.0 ),
                45.0 * ( M_PI / 180.0 ),
                45.0 * ( M_PI / 180.0 ),
                45.0 * ( M_PI / 180.0 ),
                gnomonic_interp_bicubicf

            );

            /* OpenCV save image - Gnomonic projection */
            cv::imwrite( argv[2], rct_img );

        }

    }

