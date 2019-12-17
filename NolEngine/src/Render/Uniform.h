#pragma once

const unsigned int MaxLights  = 20;
const unsigned int MaxTexures = 32;

typedef struct matrixUniformLocation {
	int Model;
	int View;
	int Projection;
	int ProjectionView;
} MatrixUniformLocation;

typedef struct materialUniformLocation {
	int Color;
	int Ambient;
	int Diffuse;
	int Specular;
	int Shininess;
} MaterialUniformLocation;

typedef struct lightUniformLocation {
	struct _Light
	{
		int Type;
		int Position;
		int Direction;
		int Color;

		int CutoffAngle;
		int OuterCutoffAngle;
		int Constant;
		int Linear;
		int Quadratic;
	};

	_Light Lights[MaxLights];
	int NumberofLights;
} LightUniformLocation;

typedef struct textureUniformLocation {
	int Textures[MaxTexures];
} TextureUniformLocation;

typedef struct generalUniformLocation {
	int Color;
	int CameraPosition;
} GeneralUniformLocation;