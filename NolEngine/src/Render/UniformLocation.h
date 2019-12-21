#pragma once

namespace Nol
{
	const size_t MaxNumberofLightSupported = 16;
	const size_t MaxNumberofTextureSupported = 8;

	const int CameraBufferIndex = 0;
	const int LightBufferIndex = 1;

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
		int Type;
		int Position;
		int Direction;
		int Color;

		int CutoffAngle;
		int OuterCutoffAngle;
		int Constant;
		int Linear;
		int Quadratic;
	} LightUniformLocation;

	typedef struct uniformLocation
	{
		int ModelMatrix;
		int ViewMatrix;
		int ProjectionMatrix;
		int ProjectionViewMatrix;

		int Color;
		int CameraPosition;

		int NumberofLights;
		int NumberofTextures;

		int Texture[MaxNumberofTextureSupported];

		MaterialUniformLocation Material;
		LightUniformLocation Light[MaxNumberofLightSupported];

	} UniformLocation;
}