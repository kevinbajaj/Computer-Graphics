// Basketball_Goal.h

#ifndef Basketball_Goal_H
#define Basketball_Goal_H

#include "ModelViewWithLighting.h"
#include "Block.h"
#include "Disk.h"
#include "Tex_backboard.h"
#include "Tex_backboard_flip.h"

class Basketball_Goal : public ModelViewWithLighting
{
public:
	Basketball_Goal(float x, float y, float z, bool flip);
	virtual ~Basketball_Goal();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimitsF) const;
	void render();
private:
	void define_Basketball_Goal();

	float xmin, xmax, ymin, ymax, zmin, zmax;
	float x_length, y_length, z_length;
	float post_length_x, post_length_y, post_length_z;
	float post_x, post_y, post_z;
	float backboard_x, backboard_y, backboard_z;
	float backboard_length_x, backboard_length_y, backboard_length_z;
	float rim_radius;
	float rim_x, rim_y, rim_z;

	bool reverse;

	Block* Block_1;
	Block* Block_2;
	Disk* Disk_1;

};

#endif
