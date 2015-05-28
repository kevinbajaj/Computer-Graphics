// project4.c++: Starter for EECS 672 Project 4

#include "GLFWController.h"
#include "Controller_Subclass.h"
#include "ModelViewWithLighting.h"
#include "Court.h"
#include "Background.h"
#include "Block.h"
#include "Basketball_Goal.h"
#include "Disk.h"
#include "Bench.h"
#include "Bleachers.h"
#include "Bench_Top.h"
#include "Fence_top.h"
#include "Fence_side.h"
#include "Tex_backboard.h"
#include "Tex_backboard_flip.h"

typedef float vec2[2];

void set3DViewingInformation(double xyz[6])
{
	ModelView::setMCRegionOfInterest(xyz);

	// Set values for eye-center-up to produce a reasonable off-axis
	// view of your scene, then:
	cryph::AffPoint eye(20.0, 12.0, 30.0);
	cryph::AffPoint center(0.15, 0.0, 0.0);
	double distEyeCenter = eye.distanceTo(center);
	cryph::AffVector up(0.0, 1.0, 0.0);

	// Notify the ModelView of our MC->EC viewing requests:
	ModelView::setEyeCenterUp(eye, center, up);


	// Set values for zpp, zmin, zmax that make sense in the context of
	// the EC system established above, then:
	
	double zmin = -distEyeCenter - 5.0;
	double zmax = -distEyeCenter + 5.0;
	double zpp = zmax;

	ModelView::setECZminZmax(zmin, zmax);
	ModelView::setProjectionPlaneZ(zpp);
	ModelView::setProjection(ORTHOGONAL);


}

int main(int argc, char* argv[])
{
	Controller_Subclass c("Basketball Court", MVC_USE_DEPTH_BIT);
	c.reportVersions(std::cout);

	ModelViewWithLighting::setShaderSources("simple3d.vsh", "simple3d.fsh");


	vec2 concrete_tex_Coords[] = { 
		{9, 9}, {0, 0},
		{9, 9}, {5.0, 0},
		{9, 9}, {5.0, 5.0},
		{9, 9}, {0, 5.0}
	};

	vec2 fence_tex_Coords[] = { 
		{0.0, 0.0}, {0.0, 5.0},
		{5.0, 0.0}, {5.0, 5.0},
		{0.0, 0.0}, {0.0, 5.0},
		{5.0, 0.0}, {5.0, 5.0}
	};

	vec2 fence_side_tex_Coords[] = { 
		{5.0, 0.0}, {5.0, 5.0},
		{0.0, 0.0}, {0.0, 5.0},
		{5.0, 0.0}, {5.0, 5.0},
		{0.0, 0.0}, {0.0, 5.0}
	};

	vec2 small_fence_tex_Coords[] = {
		{2.0, 0.0}, {2.0, 2.0},
		{0.0, 0.0}, {0.0, 2.0},
		{2.0, 0.0}, {2.0, 2.0},
		{0.0, 0.0}, {0.0, 2.0}
	};


// create your scene, adding things to the Controller....


	c.addModel(new Court(-0.50, -0.2, -0.5, 1.25, 0.025, 0.95,
							0.80, 0.66, 0.49, "court.jpg"));

	c.addModel(new Background(-0.75, -0.201, -1.2, 1.75, 0.025, 2.35,
							 0.5, 0.5, 0.5, concrete_tex_Coords, "concrete.jpg"));
	//south fence
	c.addModel(new Fence_top(-0.75, -0.201, 1.15, 1.75, 0.20, 0.005,
							 0.64, 0.16, 0.0, fence_tex_Coords, "fence.jpg"));
	//west fence
	c.addModel(new Fence_side(-0.75, -0.201, -1.2, 0.005, 0.20, 2.35,
							 0.64, 0.16, 0.0, fence_side_tex_Coords, "fence.jpg"));
	//north fence
	c.addModel(new Fence_top(-0.75, -0.201, -1.2, 1.75, 0.20, 0.005,
							 0.64, 0.16, 0.0, fence_tex_Coords, "fence.jpg"));
	//east fence parts
	c.addModel(new Fence_side(1.0, -0.201, -1.195, 0.005, 0.20, 0.9,
							 0.64, 0.16, 0.0, small_fence_tex_Coords, "fence.jpg"));
	c.addModel(new Fence_side(1.0, -0.201, 0.185, 0.005, 0.20, 0.970,
							 0.64, 0.16, 0.0, small_fence_tex_Coords, "fence.jpg"));

	//add the bleachers to our scene.  One on either side of the court.
	c.addModel(new Bleachers(-0.50, -0.2, -1.0, 1.25, .045, 0.50, false));
	c.addModel(new Bleachers(-0.50, -0.2, 0.45, 1.25, .045, 0.50, true));

	//add the benches to our scene
	c.addModel(new Bench(-0.60, -0.1, 0.14, 0.07, 0.010, 0.3));
	c.addModel(new Bench(-0.60, -0.1, -0.46, 0.07, 0.010, 0.3));


	//add the basketball goals to our scene.  One on either side of the court.
	c.addModel(new Basketball_Goal(-0.50, -0.175, -0.025, false));	
	c.addModel(new Basketball_Goal(0.725, -0.175, -0.025, true));


	glClearColor(0.0, 0.0, 0.0, 1.0);

	double xyz[6];
	c.getOverallMCBoundingBox(xyz);
	set3DViewingInformation(xyz);

	c.run();

	return 0;
}
