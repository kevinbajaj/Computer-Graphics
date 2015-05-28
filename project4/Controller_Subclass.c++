// Controller_Subclass.c++: An Abstract base Class for a Controller_Subclass (in Model-View-Controller_Subclass sense)

#ifdef __APPLE_CC__
#define GLFW_INCLUDE_GLCOREARB
#define GLFW_INCLUDE_GLU
#include "GLFW/glfw3.h"
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "Controller.h"
#include "GLFWController.h"
#include "Controller_Subclass.h"
#include "ModelView.h"
#include "ModelViewWithLighting.h"
#include "ShaderIF.h"
#include <iostream>
#include <string>

using namespace std;

int glob_x, glob_y;
bool clicked;

Controller_Subclass::Controller_Subclass(const std::string& windowTitle, int rcFlag)
										 : GLFWController(windowTitle, rcFlag)
{
}

Controller_Subclass::~Controller_Subclass()
{
	
}


void Controller_Subclass::handleScroll(bool up)
{
	if(up)
	{
		ModelView::addToGlobalZoom(0.1);
	}
	else
	{
		ModelView::addToGlobalZoom(-0.1);
	}

 	redraw();

 }

void Controller_Subclass::handleMouseMotion(int x, int y)
{

	float delta_x = glob_x - x;
	float delta_y = glob_y - y;

	delta_x = glob_x - x;
	delta_y = glob_y - y;



	if(clicked == true)
	{
		ModelView::addToGlobalRotationDegrees(0.0, 0.0, delta_x/250.0);

	}

}

void Controller_Subclass::handleMouseButton(MouseButton button, bool pressed, int x, int y, int mods)
{
	

	clicked = false;
	if (button == LEFT_BUTTON && pressed)
	{
		//Controller::handleMouseMotion(x, y);
		clicked = true;
	}
	
	glob_x = x;
	glob_y = y;

}

void Controller_Subclass::handleDisplay()
{


	glfwMakeContextCurrent(theWindow);
	int width, height;
	glfwGetFramebufferSize(theWindow, &width, &height);
	glViewport(0, 0, width, height);

	// clear the frame buffer
//	glDepthMask(GL_TRUE);
	glClear(glClearFlags);


	// draw the collection of models
	int which = 0;

	for (std::vector<ModelView*>::iterator it=models.begin() ; it<models.end() ; it++)
	{
		(*it)->render();
	}

	glfwSwapBuffers(theWindow);
}

bool Controller_Subclass::trans_object()
{
	int holder;
//	holder = ModelViewWithLighting.ppuLoc_drawingTrans;

	if(holder == 1)
		return true;
	else
		return false;
}

