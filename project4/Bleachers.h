// Bleachers.h

#ifndef Bleachers_H
#define Bleachers_H

#include "ModelViewWithLighting.h"

class Bleachers : public ModelViewWithLighting
{
public:
	Bleachers(float cx, float cy, float cz, float lx, float ly, float lz, bool flip);
	virtual ~Bleachers();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	float xmin, xmax, ymin, ymax, zmin, zmax;
	float x_length, y_length, z_length;
	float seat_depth;
	bool reverse;
};

#endif
