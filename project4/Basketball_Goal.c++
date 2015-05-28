// Basketball_Goal.c++

#include "Basketball_Goal.h"
#include "Block.h"
#include "Disk.h"
#include "Tex_backboard.h"
#include "Tex_backboard_flip.h"
#include "ShaderIF.h"

 				//bottom left corner of basketball goal post
Basketball_Goal::Basketball_Goal(float x, float y, float z, bool flip)
{
	post_x = x;
	post_y = y;
	post_z = z;

	reverse = flip;

	define_Basketball_Goal();
}

Basketball_Goal::~Basketball_Goal()
{
}


void Basketball_Goal::define_Basketball_Goal()
{



	//default dimensions of our basketball goal
	post_length_x = 0.025;
	post_length_y = 0.35;
	post_length_z = 0.025;

	backboard_length_x = 0.025;
	backboard_length_y = 0.075;
	backboard_length_z = 0.3;

	rim_radius = 0.05;

	if(reverse)
	{
		backboard_x = post_x - backboard_length_x;
		backboard_y = post_y + post_length_y - backboard_length_y;
		backboard_z = post_z - backboard_length_z / 2.0;


		rim_x =  backboard_x - rim_radius*2;
		rim_y = backboard_y + backboard_length_y / 3;  //place rim 1/3 way up backboard
		rim_z = post_z - rim_radius + post_length_z;

		xmin = rim_x;
		xmax = post_x + post_length_x;
		ymin = post_y;
		ymax = post_y + post_length_y;
		zmin = backboard_z;
		zmax = post_z + backboard_length_z;
	}
	else
	{
		backboard_x = post_x + post_length_x;
		backboard_y = post_y + post_length_y - backboard_length_y;
		backboard_z = post_z - backboard_length_z / 2.0;

		rim_x =  backboard_x + backboard_length_x;
		rim_y = backboard_y + backboard_length_y / 3; //place rim 1/3 way up backboard
		rim_z = post_z - rim_radius + post_length_z;

		xmin = post_x;
		xmax = rim_x + rim_radius*2;
		ymin = post_y;
		ymax = post_y + post_length_y;
		zmin = backboard_z;
		zmax = post_z + backboard_length_z;
	}

	//define goalpost
//	Block_1 = new Block(post_x, post_y, post_z,
	//					post_length_x, post_length_y, post_length_z,
		//				1.0, 0.2, 0.2);
	//define backboard
	//Block_2 = new Block(backboard_x, backboard_y, backboard_z,
	//					backboard_length_x, backboard_length_y, backboard_length_z,
	//					0.25, 0.25, 0.25);
	//define rim
//	Disk_1 = new Disk(rim_x, rim_y, rim_z, rim_radius, 1.0, 0.5, 0.0);
}


// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Basketball_Goal::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin; // xmin  Give real values!
	xyzLimits[1] = xmax;  // xmax         |
	xyzLimits[2] = ymin; // ymin         |
	xyzLimits[3] = ymax; // ymax         |
	xyzLimits[4] = zmin; // zmin         |
	xyzLimits[5] = zmax; // zmax        \_/
}



void Basketball_Goal::render()
{

	//render goalpost
	Block* Block_1 = new Block(post_x, post_y, post_z,
							post_length_x, post_length_y, post_length_z,
							 1.0, 0.2, 0.2);
	Block_1->render();


	Disk* Disk_1 = new Disk(rim_x, rim_y, rim_z, rim_radius, 1.0, 0.5, 0.0);
	Disk_1->render();


	//render backboard
	/*
	Backboard* Backboard_1 = new Backboard(backboard_x, backboard_y, backboard_z,
							backboard_length_x, backboard_length_y, backboard_length_z,
							 0.9, 0.9, 0.9);

	Backboard_1->render();
	*/

	if(reverse)
	{
		Tex_backboard_flip* Tex_backboard_flip_1 = new Tex_backboard_flip(backboard_x, backboard_y, backboard_z,
						backboard_length_x, backboard_length_y, backboard_length_z,
						 0.9, 0.9, 0.9, "backboard.jpg");
		Tex_backboard_flip_1->render();

	}
	else
	{
		Tex_backboard* Tex_backboard_1 = new Tex_backboard(backboard_x, backboard_y, backboard_z,
						backboard_length_x, backboard_length_y, backboard_length_z,
						 0.9, 0.9, 0.9, "backboard.jpg");
		Tex_backboard_1->render();
	}

}
