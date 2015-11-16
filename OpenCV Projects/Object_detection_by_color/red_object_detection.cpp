/**
* Module : Red color object detection using OpenCV
*
* Author : Krishnaswamy Kannan
*
* Copyright (c) 2015, Krishnaswamy Kannan
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
*   * Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the
*     documentation and/or other materials provided with the distribution.
*   * Neither the name of Redis nor the names of its contributors may be used
*     to endorse or promote products derived from this software without
*     specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/

#include <iostream>
// -------- Include the OpenCV headers and cv namespace --------
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	string src_img_path = "C:/Users/Krishnaswamy Kannan/Pictures/img3.jpg";
	string dst_img_path = "C:/Users/Krishnaswamy Kannan/Pictures/Test3.jpg";
	//-------- Declare the Mat objects --------
	Mat src; // Source image
	Mat dst; // Destination image in BGR format
	Mat dstHSV; // Destination image in HSV format
	Mat dstThresholded; // Final Thresholded image

	cout << "\n ----------------- RED COLOR OBJECT DETECTION USING OPENCV -----------------n";
	// -------- Read the source image --------
	src = imread(src_img_path, 1);

	// -------- Print an error if failed to read the image --------
	if (!src.data)
	{
		cout << "Error loading the image" << endl;
		return -1;
	}

	// -------- Create the dst & dstHSV structure by cloning the src
	dst = src.clone();
	dstHSV = src.clone();
	
	while (true)
	{		
		// -------- Convert the destination image from BGR to HSV format to detect the object by color --------
		cvtColor(dst, dstHSV, COLOR_BGR2HSV); 
		// -------- Threshold the image by checking for HSV value of red color --------
		// -------- Red object will appear white while others being black --------
		inRange(dstHSV, Scalar(0, 105, 30), Scalar(255, 255, 255), dstThresholded); 

		// -------- To avoid small objects in the foreground to be detected do morphological opening --------
		erode(dstThresholded, dstThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(dstThresholded, dstThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		// -------- To remove small holes in the foreground do morphological closing --------
		dilate(dstThresholded, dstThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(dstThresholded, dstThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		
		// -------- Display the original and thresholded images --------
		imshow("Thresholded Image", dstThresholded); 
		imshow("Original Image", dst); 

		if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
		{
			cout << "esc key is pressed by user" << endl;
			break;
		}
	}

	imwrite(dst_img_path, dstThresholded);
	cout << "\n Thresholded image has been saved in " << dst_img_path << endl;
	return 0;

}