#include <iostream>
#include <string>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "Image.h"
#include "Triangle.h"
using namespace std;

//methods for steps in rasterization
float get_scale(vector<float>& posBuf, float& tx, float& ty, float width, float height);
int st(float& point, float& scale, float& translation);

//main function//
int main(int argc, char **argv)
{
	if(argc < 2) {
		cout << "Usage: A1 meshfile" << endl;
		return 0;
	}
	string meshName(argv[1]);

	// Load geometry
	vector<float> posBuf; // list of vertex positions
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	string errStr;
	bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
	if(!rc) {
		cerr << errStr << endl;
	} else {
		// Some OBJ files have different indices for vertex positions, normals,
		// and texture coordinates. For example, a cube corner vertex may have
		// three different normals. Here, we are going to duplicate all such
		// vertices.
		// Loop over shapes
		for(size_t s = 0; s < shapes.size(); s++) {
			// Loop over faces (polygons)
			size_t index_offset = 0;
			for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
				size_t fv = shapes[s].mesh.num_face_vertices[f];
				// Loop over vertices in the face.
				for(size_t v = 0; v < fv; v++) {
					// access to vertex
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+0]);
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+1]);
					posBuf.push_back(attrib.vertices[3*idx.vertex_index+2]);
				}
				index_offset += fv;
				// per-face material (IGNORE)
				shapes[s].mesh.material_ids[f];
			}
		}
	}

	/* Trent's implemented code. Reads input into triangles based on format below & prints each triangle out.
	-----------------------------------------------------------------------------------------------
| x0 | y0 | z0 | x1 | y1 | z1 | x2 | y2 | z2 | x3 | y3 | z3 | x4 | y4 | z4 | x5 | y5 | z5 | ... <- posBuf array
-----------------------------------------------------------------------------------------------

|   vertex 0   |   vertex 1   |   vertex 2   |   vertex 3   |   vertex 4   |   vertex 5   |
|                 triangle 1                 |                 triangle 2                 |
	*/

	//before I do anything, I must find the correct scale for the obj and translation for each side
	float ty; //translation x and y
	float tx;
	float scale = get_scale(posBuf, tx, ty, atoi(argv[3]), atoi(argv[4]) ); //returns both the scale and the translation
	
	//instantiate an image to print out with the correct size
	auto image = make_shared<Image>(atoi(argv[3]), atoi(argv[4]));

	//now I will itterate through the list of verticies and create a list of triangles.
	vector<Triangle> object;
	vector<float>::iterator index = posBuf.begin();
	while(index != posBuf.end() )
	{
		Triangle::vertex A;
		Triangle::vertex B;
		Triangle::vertex C;
		//create 3 verticies and set there positions in image. st is function to scale and translate corrdinates
		A.x = st(*index, scale, tx); index++; A.y = st(*index, scale, ty); index++; A.z = *index; index++;

		B.x = st(*index, scale, tx); index++; B.y = st(*index, scale, ty); index++; B.z = *index; index++;

		C.x = st(*index, scale, tx); index++; C.y = st(*index, scale, ty); index++; C.z = *index; index++;

		//set verticies random color (for now)
		A.R = rand() % 255; A.G = rand() % 255; A.B = rand() % 255;
		B.R = rand() % 255; B.G = rand() % 255; B.B = rand() % 255;
		C.R = rand() % 255; C.G = rand() % 255; C.B = rand() % 255;

		//create triangle and add to list
		Triangle currentTriangle = Triangle(A, B, C);
		object.push_back(currentTriangle);

	}

	//now I read each triangle and print to the image
	vector<Triangle>::iterator triangleindex = object.begin();
	vector<int> currentTriangleDimensions;
	while (triangleindex != object.end()) {

		//this prints out the bounding box. 
		//triangleindex->printBoundingBox(*image);
		//this prints out a triangle
		triangleindex->printTriangle(*image, false);
		triangleindex++;
	}

	cout << meshName << " has Number of vertices: " << posBuf.size()/3 << endl;
	string filename = argv[2];
	image->writeToFile(filename);
	
	return 0;
}

//****************Helper functions************************//

float get_scale(vector<float>& posBuf, float& tx, float& ty, float width, float height) {
	vector<float>::iterator index = posBuf.begin();
	float minX = 0.0f, maxX = 0.0f, minY = 0.0f, maxY = 0.0f;

	while (index != posBuf.end()) //find the minimum and maximum values of the x & ycoordinates
	{
		if (*index > maxX) maxX = *index;
		if (*index < minX) minX = *index;
		index++;
		if (*index > maxY) maxY = *index;
		if (*index < minY) minY = *index;
		index = index + 2;
	}

	float midx = maxX - ((maxX - minX) * 0.5f); //then get the middle value between these two respective values
	float midy = maxY - ((maxY - minY) * 0.5f);

	float xSize = width / (abs(minX) + abs(maxX)); //find the scale for the x and y axsis
	float ySize = height / (abs(minY) + abs(maxY));

	float theScale = xSize < ySize ? xSize : ySize; //set the scale, and determine the translation values based on mid points & scale
	tx = (width * 0.5f) - (theScale * midx);
	ty = (height * 0.5f) - (theScale * midy);
	return theScale;
}

int st(float& point, float& scale, float& translation) {
	return (int)((scale * point) + translation);
}

