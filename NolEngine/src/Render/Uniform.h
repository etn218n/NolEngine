#pragma once

const unsigned int MaxLights  = 20;
const unsigned int MaxTexures = 10;

typedef struct uniform
{
	int Model;
	int View;
	int Projection;
	int ProjectionView;

	int Color;

	struct _Material
	{
		int Ambient;
		int Diffuse;
		int Specular;
		int Shininess;
	};

	struct _Light
	{
		int Type;
		int Position;
		int Direction;
		int Color;

		int Cutoff;
		int OuterCutoff;
		int Constant;
		int Linear;
		int Quadratic;
	};

	_Light Lights[MaxLights];
	_Material Material;

	int NumberofLights;
	int Textures[MaxTexures];
	int CameraPosition;

} Uniform;
