// Extracted from: ModelView.c++ - an Abstract Base Class for a combined Model and View for OpenGL

#include "ModelView.h"
#include "Controller.h"
#include "Matrix4x4.h"
#include "Inline.h"
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

void ModelView::addToGlobalRotationDegrees(double rx, double ry, double rz)
{
	// TODO: 1. UPDATE dynamic_view
	// TODO: 2. Use dynamic_view in ModelView::getMatrices
	dynamic_view = dynamic_view * cryph::Matrix4x4::zRotationDegrees(rz);
	dynamic_view = dynamic_view * cryph::Matrix4x4::xRotationDegrees(rx);
	dynamic_view = dynamic_view * cryph::Matrix4x4::yRotationDegrees(ry);

/*
	dynamic_view = dynamic_view * cryph::Matrix4x4(
									1.0, 0.0, 0.0, 0.0,
									0.0,   c,  -s, 0.0,
									0.0,   s,   c, 0.0,
									0.0, 0.0, 0.0, 1.0
									);
*/


}

void ModelView::getMatrices(cryph::Matrix4x4& mc_ec, cryph::Matrix4x4& ec_lds)
{
	// TODO:
	// 1. Create the mc_ec matrix:
	//    Matrix M_ECu is created from the eye, center, and up. You can use the
	//    following utility from Matrix4x4:
	//
	//    cryph::Matrix4x4 cryph::Matrix4x4::lookAt(
	//          const cryph::AffPoint& eye, const cryph::AffPoint& center,
	//          const cryph::AffVector& up);
	//
	//    NOTE: eye, center, and up are specified in MODEL COORDINATES (MC)
	//
	//    So, for example:

       cryph::Matrix4x4 M_ECu = cryph::Matrix4x4::lookAt(eye, center, up);
       mc_ec = dynamic_view * M_ECu;

	//
	//    a) For project 2:        mc_ec = M_ECu
	//    b) For projects 3 and 4: mc_ec = dynamic_view * M_ECu
	//
	// 2. Create the ec_lds matrix:
	//    Using the three WIDTHS of the established mcRegionOfInterest:
	//      i) Compute appropriate ecX and ecY widths;
	//     ii) Adjust in the x OR y direction to match the viewport aspect ratio;
	//    iii) For projects 3 and 4: Scale the resulting widths by dynamic_zoom;
	//     iv) create the matrix using the method for the desired type of projection.
	//         (Note ecXmin = -ecXmax = (ecX width) / 2; analogous in the EC y
	//         direction; ecZmin, ecZmax, zpp, and obliqueProjectionDir are class
	//         variables whose values you just use.)
	//
	//    Any of the three Matrix4x4 methods shown below (declared in Matrix4x4.h)
	//    can be used to create ec_lds. On a given call to this "getMatrices" routine,
	//    you will use EXACTLY ONE of them, depending on what type of projection you
	//    currently want.

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!!!!   All coordinate data in the parameter lists below are specified      !!!!!!
	// !!!!!   in EYE COORDINATES (EC)! Be VERY sure you understand what that      !!!!!!
	// !!!!!   means!  (This is why I emphasized "WIDTHS" above.)                  !!!!!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	/* The three choices:

	cryph::Matrix4x4 cryph::Matrix4x4::orthogonal(double ecXmin, double ecXmax,
		double ecYmin, double ecYmax, double ecZmin, double ecZmax);

	cryph::Matrix4x4 cryph::Matrix4x4::perspective(double zpp, double ecXmin, double ecXmax,
		double ecYmin, double ecYmax, double ecZmin, double ecZmax);

	cryph::Matrix4x4 cryph::Matrix4x4::oblique(double zpp, double ecXmin, double ecXmax,
		double ecYmin, double ecYmax, double ecZmin, double ecZmax, const cryph::AffVector& projDir);

	*/
	double xwidth, ywidth, ecXmax, ecXmin, ecYmax, ecYmin, max_width;
	
	xwidth = mcRegionOfInterest[1] - mcRegionOfInterest[0];
	ywidth = mcRegionOfInterest[3] - mcRegionOfInterest[2];

	if(xwidth > ywidth)
		max_width = xwidth;
	else
		max_width = ywidth;



	ecXmin = dynamic_zoomScale * -(max_width/2) - .3;
	ecXmax = dynamic_zoomScale * (max_width/2) + .3;	
	ecYmin = dynamic_zoomScale * -(max_width/2) - .3;
	ecYmax = dynamic_zoomScale * (max_width/2) + .3;	

	// For example:
	 ec_lds = cryph::Matrix4x4::orthogonal(ecXmin, ecXmax, ecYmin, ecYmax, ecZmin, ecZmax);
	//
	// RECALL: Use the class variables ecZmin, ecZmax, and zpp in these calls.

	// THEN IN THE CALLER OF THIS METHOD:
	//
	// float mat[16];
	// glUniformMatrix4fv(ppuLoc_mc_ec, 1, false, mc_ec.extractColMajor(mat));
	// glUniformMatrix4fv(ppuLoc_ec_lds, 1, false, ec_lds.extractColMajor(mat));
	//
	// (The extractColMajor method copies the elements of the matrix into the given
	// array which is assumed to be of length 16. It then returns the array pointer
	// so it can be used as indicated in the two calls. Since the array is immediately
	// copied by glUniformMatrix to the GPU, "mat" can be reused as indicated.)
}
