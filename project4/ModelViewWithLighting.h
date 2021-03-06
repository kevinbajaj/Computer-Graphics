// ModelViewWithLighting.h

#ifndef MODELVIEWWITHLIGHTING_H
#define MODELVIEWWITHLIGHTING_H

#ifdef __APPLE_CC__
#define GLFW_INCLUDE_GLCOREARB
#include "GLFW/glfw3.h"
#else
#include <GL/gl.h>
#endif

#include "ModelView.h"
#include "ShaderIF.h"
#include "Matrix4x4.h"

class ModelViewWithLighting : public ModelView
{
public:
	ModelViewWithLighting();
	virtual ~ModelViewWithLighting();

	static GLint ppuLoc_hasTex, ppuLoc_drawingTrans;
	static void setShaderSources(const std::string& vShader, const std::string& fShader);

protected:

	static ShaderIF* shaderIF;
	static int numInstances;
	static GLuint shaderProgram;
	static GLint pvaLoc_mcPosition, pvaLoc_mcNormal, pvaLoc_texCoords;
	static GLint ppuLoc_kd, ppuLoc_textureMap, ppuLoc_court;
	static GLint ppuLoc_mc_ec, ppuLoc_ec_lds;

	static void fetchGLSLVariableLocations();

private:
	static std::string vShaderSource, fShaderSource;
};

#endif
