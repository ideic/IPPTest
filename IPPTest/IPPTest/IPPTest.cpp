// IPPTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <ippcc.h>

int main()
{
	Ipp8u* src = new Ipp8u[32]{
	   101, 102, 103 ,104,   111,112,113,114,    121,122,123,124,   131,132,133,134,
	   201, 202, 203 ,204,   211,212,213,214,    221,222,223,224,   231,232,233,234
	};
	int step = 4;
	int width = 4;
	int height = 2;
	int outputChannel = 3;
	int screenSize = width * height;
	Ipp8u ** dst = new Ipp8u*[outputChannel];
	dst[0] = new Ipp8u[screenSize+ screenSize / 4 + screenSize /4];
	dst[1] = dst[0] + screenSize;
	dst[2] = dst[1] + screenSize /4;

	int dstStep[3]{ width, width, width};
	IppiSize roiSize{ width, height };

	ippiBGRToYUV420_8u_AC4P3R(src, step, dst, dstStep, roiSize);
	ippiBGRToYCbCr420_8u_AC4P3R (src, step, dst, dstStep, roiSize);

	Ipp8u ** dst2 = new Ipp8u*[2];
	dst2[0] = new Ipp8u[screenSize + screenSize / 2];
	dst2[1] = dst2[0] + screenSize;

	ippiBGRToYCbCr420_8u_AC4P2R(src, step, dst2[0], width, dst2[1], width , roiSize);

	delete[] src;
    std::cout << "Hello World!\n"; 
}

