// Court.c++

#include <iostream>
#include <math.h>

#include "AffPoint.h"
#include "AffVector.h"
#include "ImageReader.h"

#include "Court.h"
#include "ShaderIF.h"

typedef float vec3[3];
typedef float vec2[2];


// index lists for the three faces that can't be drawn with glDrawArrays
GLuint Court::indexList_xmin[4] = { 6, 7, 0, 1 };
GLuint Court::indexList_ymin[4] = { 6, 0, 4, 2 };
GLuint Court::indexList_ymax[4] = { 1, 7, 3, 5 };

Court::Court(float cx, float cy, float cz, 
			float lx, float ly, float lz, 
			float r, float g, float b,
			const char* texImageSource) :
			wrapS(GL_MIRRORED_REPEAT), wrapT(GL_MIRRORED_REPEAT)
{
	xmin = cx; xmax = cx + lx;
	ymin = cy; ymax = cy + ly;
	zmin = cz; zmax = cz + lz;

	color[0] = r;
	color[1] = g;
	color[2] = b;
	defineCourt();
	texID = defineTexture(texImageSource);
}

Court::~Court()
{
	glDeleteBuffers(2, vbo);
	glDeleteVertexArrays(1, vao);
}

void Court::defineCourt()
{
	vec3 vtx[] = { // The 8 unique vertices (Note the order)
		{xmin ,ymin, zmax}, {xmin, ymax, zmax},
		{xmax, ymin, zmax}, {xmax, ymax, zmax},
		{xmax, ymin, zmin}, {xmax, ymax, zmin},
		{xmin, ymin, zmin}, {xmin, ymax, zmin}
	};

	vec2 tex_Coords[] = { // The 8 unique vertices (Note the order)
		{9 ,9}, {0, 0},
		{9, 9}, {1.0, 0},
		{9, 9}, {1.0, 1.0},
		{9, 9}, {0, 1.0}
	};



	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);

	glGenBuffers(2, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(vec3), vtx, GL_STATIC_DRAW);
	glVertexAttribPointer(pvaLoc_mcPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(pvaLoc_mcPosition);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, 8*sizeof(vec2), tex_Coords, GL_STATIC_DRAW);
	glVertexAttribPointer(pvaLoc_texCoords, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(pvaLoc_texCoords);

	glDisableVertexAttribArray(pvaLoc_mcNormal);
}

GLuint Court::defineTexture(const char* texImageSource)
{
	if (texImageSource == NULL)
		return 0;
	ImageReader* texImage = ImageReader::create(texImageSource);
	if (texImage == NULL)
		return 0;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	GLuint locID[1];
	glGenTextures(1, locID);
	glBindTexture(GL_TEXTURE_2D, locID[0]);
	float borderColor[] = { 0.0, 0.0, 0.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	GLint level = 0; // mipmap level 0
	int pw = texImage->getWidth();
	int ph = texImage->getHeight();
	GLint iFormat = texImage->getInternalFormat();
	GLenum format = texImage->getFormat();
	GLenum type = texImage->getType();
	const GLint border = 0; // must be zero (only present for backwards compatibility)
	const void* pixelData = texImage->getTexture();
	glTexImage2D(GL_TEXTURE_2D, level, iFormat, pw, ph, border, format, type, pixelData);

	delete texImage; // all relevant information has been copied to OpenGL

	return locID[0];


}

void Court::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}



void Court::render()
{
	GLint pgm;
	glGetIntegerv(GL_CURRENT_PROGRAM, &pgm);
	glUseProgram(shaderProgram);

	cryph::Matrix4x4 mc_ec, ec_lds;
	getMatrices(mc_ec, ec_lds);
	float mat[16];
	glUniformMatrix4fv(ppuLoc_mc_ec, 1, false, mc_ec.extractColMajor(mat));
	glUniformMatrix4fv(ppuLoc_ec_lds, 1, false, ec_lds.extractColMajor(mat));


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	glBindVertexArray(vao[0]);
	
	glUniform3fv(ppuLoc_kd, 1, color);

	//enable texure mapping
	glEnable(GL_TEXTURE_2D);

// Establish current texture and any modified properties
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);

	// Set the textureMap variable in fragment shader to use "texture unit 0".
	glUniform1i(ppuLoc_textureMap, 0);

	// tell fragment shader we are rendering the court
	glUniform1i(ppuLoc_hasTex, 1);

	// face we want to texture
	glVertexAttrib3f(pvaLoc_mcNormal, 0.0, 1.0, 0.0);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, indexList_ymax);

	//disable texture mapping
	glDisable(GL_TEXTURE_2D);

	//done rendering texture
	glUniform1i(ppuLoc_hasTex, -2);


	// The three faces that can be drawn with glDrawArrays
	glVertexAttrib3f(pvaLoc_mcNormal, 0.0, 0.0, 1.0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glVertexAttrib3f(pvaLoc_mcNormal, 1.0, 0.0, 0.0);
	glDrawArrays(GL_TRIANGLE_STRIP, 2, 4);
	glVertexAttrib3f(pvaLoc_mcNormal, 0.0, 0.0, -1.0);
	glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);

	// The three faces that are drawn with glDrawElements
	glVertexAttrib3f(pvaLoc_mcNormal, -1.0, 0.0, 0.0);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, indexList_xmin);
	glVertexAttrib3f(pvaLoc_mcNormal, 0.0, -1.0, 0.0);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, indexList_ymin);






	glUseProgram(pgm);
}
