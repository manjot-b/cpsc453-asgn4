#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include "RayTracer.h"

using std::ofstream;
using std::ifstream;

// store width and height of the render
int width = 512;
int height = 512;

// Our ray tracer
RayTracer * rt;
string filename;

int main(int argc, char *argv[]){
   
	if ( argc < 2)
	{
		cerr << "Usage: ./rayTracer <--default / --yours>" << endl;
		return -1;
	}
	else if (strcmp(argv[1], "--default") == 0)
	{
		// Test scene with max depth of 4 and sampling of 1
		// rt = new RayTracer(Scene::initTestScene(width),12,4);
		rt = new RayTracer(Scene::initTestScene(width),4,4);
		filename = "default.ppm";
	}
	else if (strcmp(argv[1], "--yours") == 0)
	{
		// Test scene with max depth of 4 and sampling of 1
		rt = new RayTracer(Scene::customScene(width),12,4);
		filename = "yours.ppm";
	}
	else 
	{
		cerr << "Usage: ./rayTracer <--default / --yours>" << endl;
		return -1;
	}

	float pixels[width][height][4];
    for(int ctr = 0; ctr < height*width; ctr++){
    	int i = ctr % width;
    	int j = ctr / width;
    	Color rad = rt->calculate(i,j);
    	pixels[i][j][0] = rad.r; //Red
    	pixels[i][j][1] = rad.g; //Green
    	pixels[i][j][2] = rad.b; //Blue
    	pixels[i][j][3] = 1.0; //Alpha
    }
    // once we are done calculating, we will write to file.
    ofstream testimage;
	testimage.open(filename ,ios::binary | ios::out);
	testimage << "P3\n" << width << " " << height << "\n255\n";
	for(int j = height-1; j >=0 ; j-- ) {
	    for(int i = 0; i< width; i++){
	        for(int k = 0; k < 3; k++){
	             // normalize color value to 0-255.
	        	 // This assumes that the color values are in the
	        	 // range [0,1].
	        	testimage << int(pixels[i][j][k]*255) << " ";
	        }
			testimage << "\t";
	    }
		testimage << "\n";
	}
	testimage.close();
	

    return 0;   
}
