#pragma once
#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_
#include <vector>
#include "Image.h"


class Triangle {


public:

	struct vertex {
		int x;
		int y;
		int z;
		unsigned int R;
		unsigned int G;
		unsigned int B;
	};

	Triangle();
	Triangle(int& x1, int& y1, int& z1, int& x2, int& y2, int& z2, int& x3, int& y3, int& z3,
		unsigned int& r1, unsigned int& g1, unsigned int& b1, unsigned int& r2, unsigned int& g2, unsigned int& b2,
		unsigned int& r3, unsigned int& g3, unsigned int& b3);
	Triangle(vertex one, vertex two, vertex three);
	~Triangle();

	void getBarycentricpoints(int& px, int& py, float& w, float& u, float& v, bool& isInside);
	void printTriangle(Image& im, bool solidcolor);
	void printBoundingBox(Image& im);
	void setTriangleDimensions();
	std::vector<int> getTriangleDimensions();

	vertex getVertex0();			//getters & setters
	void setVertex0(vertex& vert);
	void setVertex0(int& x, int& y, int& z, unsigned int& r, unsigned int &g, unsigned int&b);
	vertex getVertex1();
	void setVertex1(vertex& vert);
	void setVertex1(int& x, int& y, int& z, unsigned int& r, unsigned int& g, unsigned int& b);
	vertex getVertex2();
	void setVertex2(vertex& vert);
	void setVertex2(int& x, int& y, int& z, unsigned int& r, unsigned int& g, unsigned int& b);
	

private:
	vertex v0, v1, v2; //create spots to hold current vertex
	int triangleDimensions[4]; //hold current triangle dimensions


};
#endif