// Bleachers.c++

#include "Bleachers.h"
#include "Block.h"
#include "ShaderIF.h"
#include "Block.h"

Bleachers::Bleachers(float cx, float cy, float cz, float lx, float ly, float lz, bool flip)
{
	reverse = flip;

	xmin = cx; xmax = cx + lx;
	ymin = cy; ymax = cy + ly;
	zmin = cz; zmax = cz + lz;

	x_length = lx;
	y_length = ly;
	z_length = lz;

	//default seat depth for each bleacher
	seat_depth = 0.125;

}

Bleachers::~Bleachers()
{

}

// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Bleachers::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin; // xmin  Give real values!
	xyzLimits[1] = xmax;  // xmax         |
	xyzLimits[2] = ymin; // ymin         |
	xyzLimits[3] = ymax; // ymax         |
	xyzLimits[4] = zmin; // zmin         |
	xyzLimits[5] = zmax; // zmax        \_/
}

void Bleachers::render()
{

	if(reverse == false)
	{
		//render bottom Block
		//Block* Block_1 = new Block(xmin, ymin, zmin,
		//						 x_length, y_length, z_length,
		//						 0.54, 0.54, 0.54);
		//Block_1->render();

		Block* Block_1 = new Block(xmin, ymin, zmin,
								 x_length, y_length, z_length,
								 0.54, 0.54, 0.54);
		Block_1->render();
		//render first set of seats
		Block* Block_2 = new Block(xmin, ymin + y_length, zmin,
								 x_length, y_length, z_length - seat_depth,
								 0.54, 0.54, 0.54);
		Block_2->render();

		//render second set of seats
		Block* Block_3 = new Block(xmin, ymin + y_length*2, zmin,
								 x_length, y_length, z_length - seat_depth*2,
								 0.54, 0.54, 0.54);
		Block_3->render();

		//render third set of seats
		Block* Block_4 = new Block(xmin, ymin + y_length*3, zmin,
								 x_length, y_length, z_length - seat_depth*3,
								 0.54, 0.54, 0.54);
		Block_4->render();
	}
	if(reverse == true)
	{
		Block* Block_1 = new Block(xmin, ymin, zmin,
								 x_length, y_length, z_length,
								 0.54, 0.54, 0.54);
		Block_1->render();	
	
		//render first set of seats
		Block* Block_2 = new Block(xmin, ymin + y_length, zmin + seat_depth,
								 x_length, y_length, z_length - seat_depth,
								 0.54, 0.54, 0.54);
		Block_2->render();

		//render first set of seats
		Block* Block_3 = new Block(xmin, ymin + y_length*2, zmin + seat_depth*2,
								 x_length, y_length, z_length - seat_depth*2,
								 0.54, 0.54, 0.54);
		Block_3->render();

		//render first set of seats
		Block* Block_4 = new Block(xmin, ymin + y_length*3, zmin + seat_depth*3,
								 x_length, y_length, z_length - seat_depth*3,
								 0.54, 0.54, 0.54);
		Block_4->render();
		
	}

}
