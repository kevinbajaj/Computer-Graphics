#version 410 core

in vec3 colorToFS;
in vec2 texCoordsToFS;

uniform sampler2D textureMap;
uniform int hasTex;
uniform int drawingTrans;

out vec4 fragmentColor;


void main()
{
	
	if(hasTex == 1)
	{
		vec4 tColor = texture(textureMap, texCoordsToFS);
		fragmentColor = vec4(colorToFS, 1.0) * tColor;	
	}
	else
		fragmentColor = vec4(colorToFS, 0.2);
}
