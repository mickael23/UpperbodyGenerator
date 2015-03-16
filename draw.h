#ifndef DRAW_H
#define DRAW_H

#include "info.h"

#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>

#include<stack>
#include<vector>
#include<iostream>

using namespace cv;
using namespace std;

class Draw {
	public:
		Mat image;
		stack<Mat> lastImages;
		stack<Info> informations;

		void drawCircle(int x, int y);
		void drawLeftBar(int x, int y);
		void drawRightBar(int x, int y);
		void drawCross(int x, int y);

		void prepareCircle(int x, int y);
		void prepareLeftBar(int x, int y);
		void prepareRightBar(int x, int y);
		void prepareCross(int x, int y);
};

#endif
