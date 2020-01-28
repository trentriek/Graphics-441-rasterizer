#include <iostream>
#include "CommonMethods.h"
#include <cmath>

using namespace std;
/*double CommonMethods::distance(pt2D A, pt2D B) {
	double x = sqrt(A.x + B.x);
	double y = sqrt(A.y + B.y);
	return sqrt(x + y);
}*/

double CommonMethods::triangleArea(int& x0, int& x1, int& x2, int& y0, int& y1, int& y2) {
	return abs(0.5 * ( (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0) ) );
}
void CommonMethods::barycentricPoints(int& px, int& py, int& x0, int& x1, int& x2, int& y0, int& y1, int& y2, float& w, float& v, float& z, bool& isInside) {
	float totaltriangle = triangleArea(x0, x1, x2, y0, y1, y2);
	float trianglew = triangleArea(px, x0, x1, py, y0, y1);
	float trianglev = triangleArea(px, x1, x2, py, y1, y2);
	float trianglez = triangleArea(px, x0, x2, py, y0, y2);
	w = trianglew / totaltriangle;
	v = trianglev / totaltriangle;
	z = trianglez / totaltriangle;
	isInside = totaltriangle == trianglew + trianglev + trianglez;

}

void CommonMethods::getColors(float& w, float& v, float& z, unsigned int& p1r, unsigned int& p1g, unsigned int& p1b,
								unsigned int& p2r, unsigned int& p2g, unsigned int& p2b,
								unsigned int& p3r, unsigned int& p3g, unsigned int& p3b,
								unsigned int& r, unsigned int& g, unsigned int& b) {
	r = (unsigned int)(w * p1r + v * p2r + z * p3r);
	g = (unsigned int)(int)(w * p1g + v * p2g + z * p3g);
	b = (unsigned int)(int)(w * p1b + v * p2b + z * p3b);

}

void CommonMethods::getTriangleBoxDimensions(int& x0, int& x1, int& x2, int& y0, int& y1, int& y2, 
											 int& one, int& two, int& three, int& four) {

	int x[] = { x0, x1, x2 };
	int y[] = { y0, y1, y2 };
	int i, j, temp;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 2; j++) {
			if (x[i] < x[j]) {
				temp = x[j];
				x[j] = x[i];
				x[i] = temp;
			}
		}
	}
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 2; j++) {
			if (y[i] < y[j]) {
				temp = y[j];
				y[j] = y[i];
				y[i] = temp;
			}
		}
	}
	one = x[0];
	two = x[2];
	three = y[0];
	four = y[2];

}

CommonMethods::zBuffer::zBuffer(unsigned int width, unsigned int height, float Min, float Max) {
	buf.resize(width);
	for (int i = 0; i < buf.size(); i++) {
		buf.at(i).resize(height);
		for (int j = 0; j < buf.at(i).size(); j++) {
			buf.at(i).at(j) = - std::numeric_limits<float>::infinity();
		}
	}
	min = Min;
	max = Max;
}

bool CommonMethods::zBuffer::updateZBuffer(int& x, int& y, float& zValue) {

	if (zValue > buf.at(x).at(y) ) {
		buf.at(x).at(y) = zValue;
		return true;
	}
	return false;

}

float CommonMethods::zBuffer::getZvalue(int& x, int& y) {
	return buf.at(x).at(y);
}

float CommonMethods::zBuffer::getZMin() {
	return min;
}
void CommonMethods::zBuffer::setZMin(float Min) {
	min = Min;
}
float CommonMethods::zBuffer::getZMax() {
	return max;
}
void CommonMethods::zBuffer::setZMax(float Max) {
	max = Max;
}


CommonMethods::frameBuffer::frameBuffer(unsigned int width, unsigned int height) {
	buf.resize(width);
	for (int i = 0; i < buf.size(); i++) {
		buf.at(i).resize(height);
		for (int j = 0; j < buf.at(i).size(); j++) {
			buf.at(i).at(j).r = 0; buf.at(i).at(j).g = 0; buf.at(i).at(j).b = 0;
		}
	}
}

void CommonMethods::frameBuffer::updateFBuffer(int& x, int& y, unsigned short int& r, unsigned short int& g, unsigned short int& b) {
	buf.at(x).at(y).r = r; buf.at(x).at(y).g = g; buf.at(x).at(y).b = b;
	return;
}

unsigned short int * CommonMethods::frameBuffer::getFvalue(int& x, int& y) {
	unsigned short int temp[] = { buf.at(x).at(y).r , buf.at(x).at(y).g , buf.at(x).at(y).b };
	return temp;
}
