#version 410 core

// simple3d.vsh - A simplistic vertex shader that illustrates ONE WAY
//                to handle transformations along with a simple 3D
//                lighting model.

// Naming convention for variables holding coordinates:
// mc - model coordinates
// ec - eye coordinates
// lds - logical device space
// "p_" prefix on any of the preceding indicates the coordinates have been
//      embedded in projective space
// (gl_Position would have label p_lds)

// Transformation Matrices
uniform mat4 mc_ec =   // (dynamic rotations) * (ViewOrientation(E,C,up))
	mat4(1.0, 0.0, 0.0, 0.0, // initialize to identity matrix
	     0.0, 1.0, 0.0, 0.0, // ==> no dynamic rotations -AND- MC = EC
	     0.0, 0.0, 1.0, 0.0,
	     0.0, 0.0, 0.0, 1.0);
uniform mat4 ec_lds = // (W-V map) * (projection matrix)
	mat4(1.0, 0.0, 0.0, 0.0, // initialize to (almost) identity matrix
	     0.0, 1.0, 0.0, 0.0, // ==> ORTHOGONAL projection -AND- EC = LDS
	     0.0, 0.0, -1.0, 0.0,
	     0.0, 0.0, 0.0, 1.0);
             
// There are MANY ways to deal with the basic object color.
// For now we will  simply assume:
uniform vec3 kd = // "kd" - diffuse reflectivity; basic object color
	vec3(0.8, 0.8, 0.8);

// There are also MANY ways to deal with light sources (number, type,
// strength, etc.).  For now we simply assume one directional source.
// In future projects, you will generalize this.

struct lightSource
{
	vec4 position;
	vec3 diffuse;
	vec3 specular;
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;

	float spotCutoff;
	float spotExponent;

	vec3 spotDirection;
};

const int numberOfLights = 1;
lightSource lights[numberOfLights];

lightSource light0 = lightSource(
	vec4(-1.0, 50.0, -1.0, 1.0),
	vec3(0.8, 0.8, 0.8),
	vec3(0.5, 0.5, 0.5),
	0.0, 0.8, 0.0,
	180.0, 20.0,
	vec3(0.0, -1.0, 0.0));

lightSource light1 = lightSource(
	vec4(10.0, 20.0, -10.0, 0.0),
	vec3(0.8, 0.8, 0.8),
	vec3(0.5, 0.5, 0.5),
	0.0, 1.0, 0.0,
	180.0, 20.0,
	vec3(0.0, -1.0, 0.0));

lightSource light2 = lightSource(
	vec4(0.0, 0.0, -20.0, 1.0),
	vec3(0.8, 0.8, 0.8),
	vec3(0.2, 0.2, 0.2),
	0.0, 1.0, 0.0,
	80.0, 20.0,
	vec3(-0.2, -1.0, -0.1));


struct material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

material mymaterial = material(
	vec3(0.2, 0.2, 0.2),
	vec3(1.0, 0.8, 0.8),
	vec3(0.2, 0.2, 0.2),
	5.0);
//vec3 kd = vec3(light0.diffuse);

// Per-vertex attributes
// 1. incoming vertex position in model coordinates
layout (location = 0) in vec3 mcPosition;
// 2. incoming vertex normal vector in model coordinates
in vec3 mcNormal; // incoming normal vector in model coordinates

out vec3 colorToFS;

layout (location = 1) in vec2 texCoords;
out vec2 texCoordsToFS;




vec3 phongModel(vec4 position, vec3 norm)
{
	lights[0] = light0;
//	lights[1] = light1;
//	lights[2] = light2;

	float attenuation;
	vec3 scene_ambient = vec3(0.2, 0.2, 0.2);
	vec3 ambient = scene_ambient * mymaterial.ambient;

	vec3 total_lighting = ambient;

	for(int index = 0; index < numberOfLights; index++)
	{
		vec3 s = normalize(vec3(lights[index].position - position));
		vec3 v = normalize(-position.xyz);
		vec3 r = reflect(-s, norm);

		if(lights[index].position.w == 0.0) //directional light source
		{
			attenuation = 1.0;
		}
		else // point light source (or spotlight)
		{
			float distance = length(s);
			attenuation = 1.0 / (lights[index].constantAttenuation 
								+ lights[index].linearAttenuation * distance
								+ lights[index].quadraticAttenuation * distance * distance);

			if(lights[index].spotCutoff <= 90) //light is a spotlight
			{
				float clampedCosine = max(0.0, dot(-s, normalize(lights[index].spotDirection)));
				if(clampedCosine < cos(lights[0].spotCutoff * 3.14159 / 180.0))
				{	//outside of spotlight
					attenuation = 0.0; 
				}
				else
				{
					attenuation = attenuation + pow(clampedCosine, lights[index].spotExponent);
				}
			}
		}

		float sDotN = max(dot(s,norm), 0.0);

		vec3 diffuse = attenuation * lights[index].diffuse * kd * sDotN;

		vec3 spec = vec3(0.0);

		if(sDotN > 0.0)
		{
			spec = attenuation * lights[index].specular * mymaterial.specular *
				   pow( max( dot(r,v), 0.0), mymaterial.shininess);
		}

		total_lighting = total_lighting + diffuse + spec;
	}


	return total_lighting;
}

void main ()
{
	// convert current vertex and its associated normal to eye coordinates
	vec4 p_ecPosition = mc_ec * vec4(mcPosition, 1.0);
	mat3 normalMatrix = transpose( inverse( mat3x3(mc_ec) ) );
	vec3 ec_nHat = normalize(normalMatrix * mcNormal);

	//send texcoords to fragment shader
	texCoordsToFS = texCoords;


	//colorToFS = evaluateLightingModel(p_ecPosition.xyz, ec_nHat);
	colorToFS = phongModel(p_ecPosition, ec_nHat);

	// apply the projection matrix to compute the projective space representation
	// of the 3D logical device space coordinates of the input vertex:
	gl_Position = ec_lds * p_ecPosition;
}
