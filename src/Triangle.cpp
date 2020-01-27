#include <iostream>
#include "CommonMethods.h"
#include <cmath>
#include "Triangle.h"

using namespace std;

Triangle::Triangle() {}
Triangle::Triangle(int& x1, int& y1, int& z1, int& x2, int& y2, int& z2, int& x3, int& y3, int& z3, 
					unsigned int& r1, unsigned int& g1, unsigned int& b1, unsigned int& r2, unsigned int& g2, unsigned int& b2,
					unsigned int& r3, unsigned int& g3, unsigned int& b3 )
{
	Triangle::setVertex0(x1, y1, z1, r1, g1, b1);
	Triangle::setVertex1(x2, y2, z2, r1, r2, r3);
	Triangle::setVertex2(x3, y3, z3, r1, r2, r3);

	Triangle::setTriangleDimensions();
}
Triangle::Triangle(Triangle::vertex one, Triangle::vertex two, Triangle::vertex three)
{
	v0 = one;
	v1 = two;
	v2 = three;
	Triangle::setTriangleDimensions();
}
Triangle::~Triangle() {}

void Triangle::printTriangle(Image& im, bool solidcolor) {
	for (int i = triangleDimensions[0]; i < triangleDimensions[1]; i++) {
		unsigned int r = 0;
		unsigned int g = 0;
		unsigned int b = 0;

		for (int j = triangleDimensions[2]; j < triangleDimensions[3]; j++) {
			float w = 0.0f;
			float v = 0.0f;
			float z = 0.0f;
			bool isInside = false;
			//if (i == 230 && j == 260) {
			//	cout << "" << endl;
			//}
			CommonMethods::barycentricPoints(i, j,
				v0.x, v1.x, v2.x,
				v0.y, v1.y, v2.y,
				w, v, z, isInside);

			if (isInside) {
				if (solidcolor) {
					r = v0.R; g = v0.G; b = v0.B;
				}
				else {
					CommonMethods::getColors(w, v, z, v0.R, v0.G, v0.B, v1.R, v1.G, v1.B, v2.R, v2.G, v2.B, r, g, b);
				}
					im.setPixel(i, j, r, g, b);
			}
		}
	}
}

void Triangle::printBoundingBox(Image& im) {

	for (int i = triangleDimensions[0]; i < triangleDimensions[1]; i++) {
		unsigned int r = 0;
		unsigned int g = 0;
		unsigned int b = 0;
		for (int j = triangleDimensions[2]; j < triangleDimensions[3]; j++) {
				r = v0.R; g = v0.G; b = v0.B;
				im.setPixel(i, j, r, g, b);
		}
	}
}


void Triangle::getBarycentricpoints(int& px, int& py, float& w, float& u, float& v, bool& isInside) {
	CommonMethods::barycentricPoints(px, py, v0.x, v1.x, v2.x, v0.y, v1.y, v2.y, w, u, v, isInside);
}

void Triangle::setTriangleDimensions() {
	CommonMethods::getTriangleBoxDimensions(v0.x, v1.x, v2.x, v0.y, v1.y, v2.y,
											triangleDimensions[0], triangleDimensions[1], 
											triangleDimensions[2], triangleDimensions[3]);
}

vector<int> Triangle::getTriangleDimensions() {
	Triangle::setTriangleDimensions();
	vector<int> temp;
	temp.push_back(triangleDimensions[0]); temp.push_back(triangleDimensions[1]);
	temp.push_back(triangleDimensions[2]); temp.push_back(triangleDimensions[3]);
	return temp;
}


//***********Getters & Setters******************//
//vertex0
Triangle::vertex Triangle::getVertex0() {
	return v0;
}		
void Triangle::setVertex0(vertex& vert){
	v0 = vert;
}
void Triangle::setVertex0(int& x, int& y, int& z, unsigned int& r, unsigned int& g, unsigned int& b) {
	v0.x = x;
	v0.y = y;
	v0.z = z;
	v0.R = r;
	v0.G = g;
	v0.B = b;
}
//vertex1
Triangle::vertex Triangle::getVertex1(){
	return v1;
}
void Triangle::setVertex1(vertex& vert) {
	v1 = vert;
}
void Triangle::setVertex1(int& x, int& y, int& z, unsigned int& r, unsigned int& g, unsigned int& b) {
	v1.x = x;
	v1.y = y;
	v1.z = z;
	v1.R = r;
	v1.G = g;
	v1.B = b;
}
//vertex2
Triangle::vertex Triangle::getVertex2(){
	return v2;
}
void Triangle::setVertex2(vertex& vert){
	v2 = vert;
}
void Triangle::setVertex2(int& x, int& y, int& z, unsigned int& r, unsigned int& g, unsigned int& b) {
	v2.x = x;
	v2.y = y;
	v2.z = z;
	v2.R = r;
	v2.G = g;
	v2.B = b;
}
