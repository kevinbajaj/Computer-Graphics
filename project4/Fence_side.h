// Fence_side.h

#ifndef Fence_side_H
#define Fence_side_H

#include <GL/gl.h>

#include "ModelViewWithLighting.h"

typedef float vec2[2];

class Fence_side : public ModelViewWithLighting
{
public:
	Fence_side(float cx, float cy, float cz, // lower left corner
	      float lx, float ly, float lz,// lengths in 3 directions
		  float r, float g, float b, //rgb values
		  vec2* tex_Coords,
		  const char* texImageSource); // image input
	virtual ~Fence_side();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimits) const;
	void render();
	void defineFence_side(vec2* tex_Coords);
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