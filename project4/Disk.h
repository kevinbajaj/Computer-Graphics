// Disk.h

#ifndef Disk_H
#define Disk_H

#include <GL/gl.h>

#include "ModelViewWithLighting.h"

class Disk : public ModelViewWithLighting
{
public:
	Disk(float cy, float cx, float cz, float radius, float r, float g, float b);
	virtual ~Disk();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	GLuint vao[1];
	GLuint vbo[1];

	float xmin, xmax, ymin, ymax, zmin, zmax;
	float color[3];
	int numberOfpoints;


	void defineDisk(double radius);
};

#endif
