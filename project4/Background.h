// Background.h

#ifndef Background_H
#define Background_H

#include <GL/gl.h>

#include "ModelViewWithLighting.h"

typedef float vec2[2];

class Background : public ModelViewWithLighting
{
public:
	Background(float cx, float cy, float cz, // lower left corner
	      float lx, float ly, float lz,// lengths in 3 directions
		  float r, float g, float b, //rgb values
		  vec2* tex_Coords,
		  const char* texImageSource); // image input
	virtual ~Background();

	// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
	void getMCBoundingBox(double* xyzLimits) const;
	void render();
	void defineBackground(vec2* tex_Coords);
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
