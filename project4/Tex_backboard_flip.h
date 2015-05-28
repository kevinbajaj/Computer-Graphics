// Tex_backboard_flip.h

#ifndef Tex_backboard_flip_H
#define Tex_backboard_flip_H

#include <GL/gl.h>

#include "ModelViewWithLighting.h"

class Tex_backboard_flip : public ModelViewWithLighting
{
public:
	Tex_backboard_flip(float cx, float cy, float cz, // lower left corner
	      float lx, float ly, float lz,// lengths in 3 directions
		  float r, float g, float b, //rgb values
		  const char* texImageSource); // image input
	virtual ~Tex_backboard_flip();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimits) const;
	void render();
	void defineTex_backboard_flip();
	GLuint defineTexture(const char* texImageSource);
private:
	GLuint vao[1];
	GLuint vbo[2];
	GLuint texID;
	GLenum wrapS, wrapT;

	float xmin, xmax, ymin, ymax, zmin, zmax;
	float color[3];
	static GLuint indexList_xmin[4], indexList_ymin[4], indexList_ymax[4];

	
};

#endif
