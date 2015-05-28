// Bench.c++

#include "Bench.h"
#include "Block.h"
#include "Bench_Top.h"
#include "ShaderIF.h"
#include <iostream>
#include <string>

#define COUT if (true) std::cout

using namespace std;


Bench::Bench(float cx, float cy, float cz, float lx, float ly, float lz)
{
	top_x = cx;
	top_y = cy;
	top_z = cz;

	top_length_x = lx;
	top_length_y = ly;
	top_length_z = lz;

	define_Bench();
}

Bench::~Bench()
{

}

void Bench::define_Bench()
{
	//default dimensions of the legs of our bench
	leg_length_x = top_length_x;
	leg_length_y = 0.05;
	leg_length_z = 0.01;

	xmin = top_x;
	xmax = top_x + top_length_x;
	ymin = top_y - leg_length_y;
	ymax = top_y + top_length_y;
	zmin = top_z;
	zmax = top_z + top_length_z;


}



// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Bench::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin; // xmin  
	xyzLimits[1] = xmax;  // xmax    
	xyzLimits[2] = ymin; // ymin     
	xyzLimits[3] = ymax; // ymax 
	xyzLimits[4] = zmin; // zmin   
	xyzLimits[5] = zmax; // zmax    
}

void Bench::render()
{

//	Block* Block_1 = new Block(top_x, top_y, top_z,
//						 top_length_x, top_length_y, top_length_z,
//						 0.2, 0.6, 1.0);
//		Block_1->render();


	Bench_Top* Bench_Top_1 = new Bench_Top(top_x, top_y, top_z,
						 top_length_x, top_length_y, top_length_z,
						 0.5, 0.5, 0.5, "bench_2.jpg");
	Bench_Top_1->render();

	Block* Block_2 = new Block(top_x, top_y-leg_length_y, top_z,
					 leg_length_x, leg_length_y, leg_length_z,
					 0.0, 0.0, 0.0);

	Block_2->render();

	Block* Block_3 = new Block(xmax - leg_length_x, top_y-leg_length_y, top_z + top_length_z - leg_length_z,
					 leg_length_x, leg_length_y, leg_length_z,
					 0.0, 0.0, 0.0);
	Block_3->render();



}
