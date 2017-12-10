#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <vector>
#include <vector>
#include <thread>
#include <atomic>
#include "RayTracer.h"

using std::ofstream;
using std::ifstream;
using namespace std;

// store width and height of the render
int width = 512;
int height = 512;
int maxDepth = 4;
double fov = 55.0;

// Our ray tracer
RayTracer * rt;
string filename;

vector<thread> threads;
int threadCount = 8;
atomic_int progress(0);

void getPixelColors(int id, float *** pixels) {
	int range = height / threadCount;
	int start = range * id;
	int end = id == threadCount - 1 ? height : start + range;

    for(int i = start; i < end; i++){
		for (int j = 0; j < width; j++) {
			// int i = ctr % width;
			// int j = ctr / width;
			Color rad = rt->calculate(i,j);
			pixels[i][j][0] = rad.r; //Red
			pixels[i][j][1] = rad.g; //Green
			pixels[i][j][2] = rad.b; //Blue
			pixels[i][j][3] = 1.0; //Alpha
		}
		progress++;
    }
}

// Prints how much of the scene has been calculated
void printProgress() {
	
	int p = progress.load();
	int percent = (p / float(height)) * 100;
	int digits = 1;
	int tmp = percent / 10;
	
	while (tmp > 0) {
		tmp /= 10;
		digits++;
	}
	int prevDigits = digits;
	cout << "Progress " << progress << "%";

	while (progress < height) {
		p = progress.load() + 1;		// add 1 so that it will print 100% too
		percent = (p / float(height)) * 100;
		
		digits = 1;
		tmp = percent / 10;
		
		while (tmp > 0) {
			tmp /= 10;
			digits++;
		}
		
		cout << string(prevDigits + 1, '\b') << percent << "%";
		prevDigits = digits;
	}
	cout << endl;	
	
}

int main(int argc, char *argv[]){
   
	if ( argc < 2)
	{
		cerr << " Error. Usage: ./rayTracer <--default / --yours> <width> <height> <max depth> <fov> <threads>" << endl;
		return -1;
	}
	
	switch(argc)	// leave at default values if args not specified
	{
		case 7 : threadCount = atoi(argv[6]);
		case 6 : fov = atoi(argv[5]);
		case 5 : maxDepth = atoi(argv[4]);
		case 4 : height = atoi(argv[3]);
		case 3 : width = atoi(argv[2]);
		default : break;
	}

	if (strcmp(argv[1], "--default") == 0)
	{
		// Test scene with max depth of 4 and sampling of 
		rt = new RayTracer(Scene::initTestScene(width, fov), maxDepth,4);
		filename = "default.ppm";
	}
	else if (strcmp(argv[1], "--yours") == 0)
	{
		// Test scene with max depth of 4 and sampling of 1
		if (argc < 6) fov = 75;		
		rt = new RayTracer(Scene::customScene(width, fov), maxDepth,4);
		filename = "yours.ppm";
	}
	else 
	{
		cerr << "Error. Usage: ./rayTracer <--default / --yours> <width> <height> <max depth> <fov> <threads>" << endl;
		return -1;
	}

	// allocate memory for array	
	float ***pixels = new float**[height];
	for (int i = 0; i < height; i++) {
		pixels[i] = new float*[width];
		for (int j = 0; j < width; j++)
			pixels[i][j] = new float[4];		// r g b a
	}

	for (int i = 0; i < threadCount; i++)
		threads.push_back(thread(getPixelColors, i, pixels));
	
	cout << "Calculating scene" << endl;
	printProgress();
	
	for (auto &th : threads)	
		th.join();				// wait for all threads to complete
	
	cout << "Done!"<< endl
		<< "Writing to file: " << filename << endl;

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
	cout << "Done!" << endl;
	
	// clean up
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			delete [] pixels[i][j];
		}
		delete [] pixels[i];
	}
	delete [] pixels;

    return 0;   
}
