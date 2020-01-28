#pragma once
#ifndef _COMMONMETHODS_H_
#define _COMMONMETHODS_H_
#include <vector>;


class CommonMethods {
	private:
		struct frame { 
			unsigned short int r; unsigned short int g; unsigned short int b;
		};

	public:
		class zBuffer { 
		public:
			zBuffer(unsigned int width, unsigned int height, float Min, float Max);
			bool updateZBuffer(int& x, int& y, float& zValue);
			float getZvalue(int& x, int& y);
			float getZMin();
			void setZMin(float Min);
			float getZMax();
			void setZMax(float Max);
			
		private:
			std::vector<std::vector<float>> buf;
			float min;
			float max;
		};

		class frameBuffer { 
		public:
			frameBuffer(unsigned int width, unsigned int height);
			void updateFBuffer(int& x, int& y, unsigned short int& r, unsigned short int& g, unsigned short int& b);
			unsigned short int* getFvalue(int& x, int& y);

		private:
			std::vector<std::vector<frame>> buf;
		};
		CommonMethods() {};
		~CommonMethods() {};
		static double triangleArea(int& x0, int& x1, int& x2, int& y0, int& y1, int& y2); //calculates the area inbetween 3 verticies
		static void barycentricPoints(int& px, int& py, int& x0, int& x1, int& x2, int& y0, int& y1, int& y2, float& w, float& v, float& z, bool& isInside);
		static void getTriangleBoxDimensions(int& x0, int& x1, int& x2, int& y0, int& y1, int& y2, int& one, int& two, int& three, int& four);
		static void getColors(float& w, float& v, float& z, unsigned int& p1r, unsigned int& p1g, unsigned int& p1b,
								unsigned int& p2r, unsigned int& p2g, unsigned int& p2b,
								unsigned int& p3r, unsigned int& p3g, unsigned int& p3b,
								unsigned int& r, unsigned int& g, unsigned int& b);




		//thoughts on useful functions;
		//static double distance(pt2D A, pt2D B);
		//static void get_sides();
		//static void get_side_length();
		//static void rise_run();
		//static void draw_line()

	



};


#endif