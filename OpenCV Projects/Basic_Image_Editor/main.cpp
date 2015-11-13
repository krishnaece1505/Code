/**
* Module : Basic Image Editor v1.0 using OpenCV
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
#include <vector>
#include <tuple>
#include <string.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "display_image.h"
#include "blur.h"
#include "brightness.h"
#include "contrast.h"
#include "grayscale.h"

using namespace std;
using namespace cv;

// Global Variables
int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;

// Mat objects for source, destination, entry and exit images in the editor
Mat src; Mat dst; Mat intro_exit;
char window_name[] = "Basic Image Editor";

// Function headers
int display_caption(const char* caption);
int display_dst(int delay, Mat dst);

int main(void)
{	
	string image_path = "";
	int choice;
	int program_exit_flag = 0;
	// -------- Create a window with Normal layout --------
	namedWindow(window_name, WINDOW_NORMAL);

	intro_exit = imread("C:/Kannan/OpenCV/Image_Editor/Intro.jpg", 1);
	// -------- Display the Entry screen image for the editor --------
	display_dst(DELAY_BLUR+200, intro_exit, window_name);
	
	cout << "\n ------------------- IMAGE EDITOR -------------------\n";
	cout << "\n Enter the file path of the image : ";
	getline(cin, image_path); // used instead of cin in order to get input string with spaces
	// -------- Load the source image --------
	src = imread(image_path, 1); // anything > 0 indicates color image
	dst = src.clone();
	// -------- Display the loaded image --------
	display_dst(DELAY_BLUR + 200, src, window_name);
	while (1)
	{
		cout << "\n ------------------- Image Editing Options -------------------";
		cout << "\n 1. Blur \n 2. Brightness \n 3. Contrast \n 4. Black & White \n 5. Exit";
		cout << "\n Enter your choice : ";
		cin >> choice;
		switch (choice)
		{
		// -------------------------------------- Blur Control --------------------------------------
		case 1:
			tie(src,dst) = blur_image(src, dst, window_name, MAX_KERNEL_LENGTH, DELAY_BLUR);
			// -------- Display the edited image --------
			display_dst(DELAY_BLUR + 200, src, window_name);
			break;
		// -------------------------------------- Brightness Control --------------------------------------
		case 2: 
			tie(src, dst) = brightness(src, dst, window_name, MAX_KERNEL_LENGTH, DELAY_BLUR);
			// -------- Display the edited image --------
			display_dst(DELAY_BLUR + 200, src, window_name);
			break;
			// -------------------------------------- Contrast Control --------------------------------------
		case 3:
			tie(src, dst) = contrast(src, dst, window_name, MAX_KERNEL_LENGTH, DELAY_BLUR);
			// -------- Display the edited image --------
			display_dst(DELAY_BLUR + 200, src, window_name);
			break;
		// -------------------------------------- Black & White Image --------------------------------------
		case 4:
			tie(src, dst) = gray(src, dst, window_name, MAX_KERNEL_LENGTH, DELAY_BLUR);
			// -------- Display the edited image --------
			display_dst(DELAY_BLUR + 200, src, window_name);
			break;
			
		// -------------------------------------- Default Case --------------------------------------
		default: 
			// -------- Display the exit screen image for the editor --------
			intro_exit = imread("C:/Kannan/OpenCV/Image_Editor/Exit.jpg", 1);
			display_dst(DELAY_BLUR+6000, intro_exit, window_name);
			program_exit_flag = 1;
			break;
		}
		if (program_exit_flag == 1)
			break;
	}
	
	// -------- Change the destination path and name of the edited image here --------
	imwrite("C:/Kannan/OpenCV/Image_Editor/Edited_Image.jpg", dst);
	cout << "\n Image Saved in \"C:/Kannan/OpenCV/Image_Editor/Edited_Image.jpg\" \n";
	waitKey(0);

	return 0;
}

