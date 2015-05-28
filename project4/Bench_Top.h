// Bench_Top.h

#ifndef Bench_Top_H
#define Bench_Top_H

#include <GL/gl.h>

#include "ModelViewWithLighting.h"

class Bench_Top : public ModelViewWithLighting
{
public:
	Bench_Top(float cx, float cy, float cz, // lower left corner
	      float lx, float ly, float lz,// lengths in 3 directions
		  float r, float g, float b, //rgb values
		  const char* texImageSource); // image input
	virtual ~Bench_Top();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimits) const;
	void render();
	void defineBench_Top();
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
