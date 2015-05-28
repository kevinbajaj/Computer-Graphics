// Bench.h

#ifndef Bench_H
#define Bench_H

#include "ModelViewWithLighting.h"
#include "Block.h"

class Bench : public ModelViewWithLighting
{
public:
	Bench(float cx, float cy, float cz, float lx, float ly, float lz);
	virtual ~Bench();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	void define_Bench();


	float xmin, xmax, ymin, ymax, zmin, zmax;

	float top_x, top_y, top_z;
	float top_length_x, top_length_y, top_length_z; 
	float leg_length_x, leg_length_y, leg_length_z;
	Block* Block_1;
	Block* Block_2;
	Block* Block_3;


};

#endif
