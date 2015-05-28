// Disk.c++

#include <iostream>
#include <math.h>

#include "Disk.h"
#include "ShaderIF.h"


typedef float vec3[3];

Disk::Disk(float cx, float cy, float cz, float radius, float r, float g, float b)
{
	xmin = cx; xmax = cx + radius*2;
	ymin = cy; ymax = cy;
	zmin = cz; zmax = cz + radius*2;

	color[0] = r; color[1] = g; color[2] = b;
	defineDisk(radius);
}

Disk::~Disk()
{
	glDeleteBuffers(1, vbo);
	glDeleteVertexArrays(1, vao);
}

void Disk::defineDisk(double radius)
{

	numberOfpoints = 50;

	double xmid, ymid, zmid;
	
	xmid = 0.5 * (xmin + xmax);
	ymid = ymin;
	zmid = 0.5 * (zmin + zmax);


	double theta = 0.0;
	double dTheta = (2.0*3.14) / 49.0;

	vec3* vtx = new vec3[numberOfpoints + 1]; // +1 for center

	//add center point
	vtx[0][0] = xmid;
	vtx[0][1] = ymid;
	vtx[0][2] = zmid;

	for(int i=1; i<numberOfpoints ; i++)
	{
		vtx[i][0] = xmid + radius * cos(theta);
		vtx[i][1] = ymid;
		vtx[i][2] = zmid + radius * sin(theta);
		theta = theta + dTheta;
	}

	// last point has same coordinates as first non center point.
	for (int i=0; i<3; i++)
	{
		vtx[numberOfpoints][i] = vtx[1][i];
	}


	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);

	glGenBuffers(1, vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, (numberOfpoints+1)*sizeof(vec3), vtx, GL_STATIC_DRAW);
	glVertexAttribPointer(pvaLoc_mcPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(pvaLoc_mcPosition);

	glDisableVertexAttribArray(pvaLoc_mcNormal);
}


// xyzLimits: {mcXmin, mcXmax, mcYmin, mcYmax, mcZmin, mcZmax}
void Disk::getMCBoundingBox(double* xyzLimits) const
{
	xyzLimits[0] = xmin;
	xyzLimits[1] = xmax;
	xyzLimits[2] = ymin;
	xyzLimits[3] = ymax;
	xyzLimits[4] = zmin;
	xyzLimits[5] = zmax;
}

void Disk::render()
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

	glVertexAttrib3f(pvaLoc_mcNormal, 0.0, 1.0, 0.0);
	glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfpoints+1);


	glUseProgram(pgm);


}
