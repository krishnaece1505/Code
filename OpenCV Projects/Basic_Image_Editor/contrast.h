/**
* Module : contrast.h
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

#pragma once
#include <iostream>
#include <vector>
#include <tuple>
#include "display_image.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"


using namespace std;
using namespace cv;


tuple<Mat, Mat> contrast(Mat src, Mat dst, char window_name[], int MAX_KERNEL_LENGTH, int DELAY_BLUR)
{
	char save_changes = 'Y'; char exit_choice = 'N';
	int contrast_choice, contrast_range;
	int edit_flag = 0;
	// -------- Save a copy of the source image to revert back the changes made --------
	Mat src_copy = src.clone();


	while (1)
	{
		if (toupper(exit_choice) == 'Y')
		{
			cout << "\n Do you want to save changes to the image? \n Y to save or N to load the original image: ";
			cin >> save_changes;
			if (toupper(save_changes) == 'Y')
			{
				// -------- Make the edited image as the source for next stage --------
				src = dst; break;
			}
			else
			{
				// -------- Make the original image as the source for next stage --------
				src = src_copy.clone();	break;
			}
		}
		else if (edit_flag == 1)
		{
			src = dst; // the new src is the last edited version of the src
		}
		cout << "\n -------------------- Contrast OPTIONS --------------------";
		cout << "\n 1. Increase Contrast \n 2. Decrease Contrast";
		cout << "\n Enter the choice : ";
		cin >> contrast_choice;
		cout << "\n Select the percentage of Contrast to be increased/decreased in the image.....";
		cout << "\n 1. Low \n 2. Medium \n 3. High ";
		cout << "\n Enter the choice : ";
		cin >> contrast_range;
		switch (contrast_range)
		{
		case 1:
			if (contrast_choice == 1)
				// -------- Values 1.2, 0.8, etc implies the contrast --------
				// Value > 1 increases contrast while Value < 1 decreases contrast --------
				src.convertTo(dst, -1,1.2,0); // increase contrast 
			else
				src.convertTo(dst, -1, 0.8, 0); // decrease contrast 
			break;

		case 2:
			if (contrast_choice == 1)
				src.convertTo(dst, -1, 1.6, 0); // increase contrast 
			else
				src.convertTo(dst, -1, 0.6, 0); // decrease contrast 
			break;

		case 3:
			if (contrast_choice == 1)
				src.convertTo(dst, -1, 2, 0); // increase contrast 
			else
				src.convertTo(dst, -1, 0.5, 0); // decrease contrast 
			break;
		default: cout << "\n Enter a valid option......";
			break;
		}
		display_dst(DELAY_BLUR, dst, window_name);
		cout << "\n Enter Y to exit & N to go back to the options menu : ";
		cin >> exit_choice;
		edit_flag = 1;

	}
	// -------- Return the edited images to the main program --------
	return make_tuple(src, dst);
}