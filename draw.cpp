#include "draw.h"

void Draw::drawCircle(int x, int y) {
	lastImages.push(image.clone());
	circle(image, Point(x, y), 1, Scalar(0, 0, 255), 2, 8);

	informations.top().headUp_x = x;
	informations.top().headUp_y = y;

	imshow("Upperbody Generator", image);
}

void Draw::drawLeftBar(int x, int y) {
	lastImages.push(image.clone());
	line(image, Point(x, 0), Point(x, image.rows),  Scalar(0, 0, 255), 2, 8);
	line(image, Point(x, image.rows / 2), Point(x + 50, image.rows / 2),  Scalar(0, 0, 255), 2, 8);

	informations.top().left = x;

	imshow("Upperbody Generator", image);
}

void Draw::drawRightBar(int x, int y) {
	lastImages.push(image.clone());
	line(image, Point(x, 0), Point(x, image.rows),  Scalar(0, 0, 255), 2, 8);
	line(image, Point(x, image.rows / 2), Point(x - 50, image.rows / 2),  Scalar(0, 0, 255), 2, 8);

	informations.top().right = x;

	imshow("Upperbody Generator", image);
}

void Draw::drawCross(int x, int y) {
	lastImages.push(image.clone());
	line(image, Point(x - 50, y), Point(x + 50, y),  Scalar(0, 0, 255), 2, 8);
	line(image, Point(x, y - 50), Point(x, y + 50),  Scalar(0, 0, 255), 2, 8);

	informations.top().headMiddle_x = x;
	informations.top().headMiddle_y = y;

	imshow("Upperbody Generator", image);
}

void Draw::prepareCircle(int x, int y) {
	Mat toDraw = image.clone();
	circle(toDraw, Point(x, y), 1, Scalar(0, 0, 255), 2, 8);

	imshow("Upperbody Generator", toDraw);
}

void Draw::prepareLeftBar(int x, int y) {
	Mat toDraw = image.clone();
	line(toDraw, Point(x, 0), Point(x, image.rows),  Scalar(0, 0, 255), 2, 8);
	line(toDraw, Point(x, image.rows / 2), Point(x + 50, image.rows / 2),  Scalar(0, 0, 255), 2, 8);

	imshow("Upperbody Generator", toDraw);
}

void Draw::prepareRightBar(int x, int y) {
	Mat toDraw = image.clone();
	line(toDraw, Point(x, 0), Point(x, image.rows),  Scalar(0, 0, 255), 2, 8);
	line(toDraw, Point(x, image.rows / 2), Point(x - 50, image.rows / 2),  Scalar(0, 0, 255), 2, 8);

	imshow("Upperbody Generator", toDraw);
}

void Draw::prepareCross(int x, int y) {
	Mat toDraw = image.clone();
	line(toDraw, Point(x - 50, y), Point(x + 50, y),  Scalar(0, 0, 255), 2, 8);
	line(toDraw, Point(x, y - 50), Point(x, y + 50),  Scalar(0, 0, 255), 2, 8);

	imshow("Upperbody Generator", toDraw);
}