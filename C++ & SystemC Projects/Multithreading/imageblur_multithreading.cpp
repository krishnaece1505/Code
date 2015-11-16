/**
* Module : Image Blur using OpenCV and Multithreading in C++
*
* Single thread execution time : 116 seconds to blur the image  
*
* Two threads execution time : 101 seconds to blur the image 
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


#define _CRT_SECURE_NO_DEPRECATE // used for localtime deprecated feature in getSysTime()
#include <iostream>
#include <vector>
#include <string.h>

#include <thread>
// -------- Headers for system time --------
#include <iomanip>  
#include <chrono> 
#include <ctime>

// -------- OpenCV headers --------
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"

using namespace std;
using namespace cv; // OpenCV 
//using namespace this_thread;
using std::chrono::system_clock; // system time

// -------- Global Variables --------
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 50;

// -------- Mat objects for the image --------
Mat src; Mat dst;
char window_name[] = "Imageblur_multithreading";

// ------------------------------------- Function definitions -------------------------------------

// -------- Function to display the image --------
int display_dst(int delay, Mat dst)
{
	imshow(window_name, dst);
	int c = waitKey(delay);
	if (c >= 0) { return -1; }
	return 0;
}
// -------- Prints the system time in 24 hr format --------
void getSysTime()
{
	time_t timet = chrono::system_clock::to_time_t(chrono::system_clock::now());
	//convert it to tm struct
	struct tm * time = localtime(&timet);
	cout << "\n Current time: " << put_time(time, "%X") << '\n';
}

void thread1()
{
	for (int i = 1; i < 25; i = i + 2)
	{
		// -------- Gaussian Blur is used here --------
		GaussianBlur(src, dst, Size(i, i), 0, 0); // size is the kernel size
		display_dst(DELAY_BLUR, dst);
	}	
}

void thread2()
{
	for (int i = 25; i < 50; i = i + 2)
	{
		// -------- Gaussian Blur is used here --------
		GaussianBlur(src, dst, Size(i, i), 0, 0); // size is the kernel size
		display_dst(DELAY_BLUR, dst);
	}
}

// ------------------------------------- Main function -------------------------------------
int main()
{	
	// -------- Create a window with Normal layout --------
	namedWindow(window_name, WINDOW_NORMAL);
	// -------- Read the image -------- 
	src = imread("C:/Users/Krishnaswamy Kannan/Pictures/Waterfall.jpg", 1); // change the src image path here
	// -------- Create the destination image structure --------
	dst = src.clone();
	display_dst(DELAY_BLUR, src);
	// ---------- Get system time before creating the threads ----------
	cout << "\n ---------- Before thread execution ---------- ";
	getSysTime();
	// ---------- Create t1 by passing a function to the thread ----------
	thread t1(thread1);
	// ---------- Create t2 by passing a function to the thread ----------
	thread t2(thread2);

	// ---------- Join the threads ----------
	t1.join();
	t2.join();
	// ---------- Get system time after the thread execution is complete ----------
	cout << "\n ---------- After thread execution ----------";
	getSysTime();
	display_dst(DELAY_BLUR, dst);
	imwrite("C:/Users/Krishnaswamy Kannan/Pictures/Waterfall_Blurred1.jpg", dst); // change the destination image path here
	
}
