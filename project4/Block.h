// Block.h

#ifndef BLOCK_H
#define BLOCK_H

#include <GL/gl.h>

#include "ModelViewWithLighting.h"

class Block : public ModelViewWithLighting
{
public:
	Block(float cx, float cy, float cz, // lower left corner
	      float lx, float ly, float lz,// lengths in 3 directions
		  float r, float g, float b); //rgb values
	virtual ~Block();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimits) const;
	void render();
	void defineBlock();
private:
	GLuint vao[1];
	GLuint vbo[1];

	float xmin, xmax, ymin, ymax, zmin, zmax;
	float color[3];
	float diffuse[3];
	static GLuint indexList_xmin[4], indexList_ymin[4], indexList_ymax[4];

	
};

#endif
