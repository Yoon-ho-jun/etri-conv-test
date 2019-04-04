#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

int your_conv( cv::Mat src,  //matrix
               cv::Mat dst,  //output
               cv::Mat kernel, //filter
               int stride,
               int padding
               )
{
    int src_height = src.rows;
    int src_width = src.cols;
   

    int x,y,i,j,k;

    int kernel_hieght = kernel.rows;
    int kernel_width = kernel.cols;
    

    int dst_height;
    int dst_width;
    
    dst_height = (src_height + 2 * padding - kernel_hieght)/stride +1;
    dst_width = (src_width + 2 * padding - kernel_width)/stride +1;
    // src.ptr<unsigned char>(i)[ calculate INDEX]

    // MAKE YOUR OWN CONVOLUTION PROCESS

    for(x=0; x<dst_height; x++){
	for(y=0; y<dst_width; y++){

		for(i=0; i<dst_height; i++){
			for(j=0; j<dst_width; j++){
				for(k=0; k<3; k++)
					dst.at<float>(x,y) += (src.at<float>(i,j,k) * kernel.at<float>(i,j,k));		
			}
		}
	}
    }
				
	
	
    // if success
    return 0;

    // if fail - in the case of wrong parameters...
    // return -1
}

int main ( int argc, char** argv )
{
    if (argc < 2) {
        std::cout << "no filename given." << std::endl;
        std::cout << "usage: " << argv[0] << " image" << std::endl;
        return -1;
    }

    cv::Mat src, kernel, dst; 

    // Load an image
    src = cv::imread( argv[1] );
    if( !src.data )  { return -1; }

    // Make filter
    kernel = (cv::Mat_<float>(3, 3) << -1, -1, -1, -1, 8, -1, -1, -1, -1);


    // Run 2D filter
    //cv::filter2D(src, dst, -1 , kernel, cv::Point( -1, -1 ), 0, cv::BORDER_DEFAULT );

    // ---------------------------
    your_conv(src,dst,kernel,1,0);
    // ---------------------------

    cv::namedWindow( "filter2D Demo", cv::WINDOW_AUTOSIZE );
    cv::imshow( "filter2D Demo", dst );

    cv::waitKey(0);
    return 0;
}
