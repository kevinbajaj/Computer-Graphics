// Controller_Subclass.h: An Abstract base Class for a Controller (in Model-View-Controller sense)

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
#include "ModelView.h"
#include "ModelViewWithLighting.h"
#include <iostream>
#include <string>

using namespace std;

class Controller_Subclass : public GLFWController
{
public:
	Controller_Subclass(const std::string& windowTitle, int rcFlags = 0);
	virtual ~Controller_Subclass();
	bool trans_object();

private:
		// --> Mouse-related event handling
	virtual void handleMouseButton(MouseButton button, bool pressed, int x, int y, int mods);
	virtual void handleMouseMotion(int x, int y);
	virtual void handleScroll(bool up);
	virtual void handleDisplay();

};