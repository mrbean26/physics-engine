#pragma once

#include <Engine/Object/Component.h>
#include <Engine/Engine.h>

class PointLight : public Component {
public:
	void Mainloop();
	void Initialise();

	// Shadows
	float near = 1.0f;
	float far = 50.0f;

	inline static GLuint cubemapShader = -1;
	GLuint depthCubemap;
	GLuint cubeMapFBO;

	void InitialiseCubemapShader();
	void InitialiseCubeMap();

	vector<mat4> ShadowTransforms();
	void RenderCubeMap();

	// Light Attributes
	float intensity = 1.0f;

	float attenuationConstant = 1.0f;
	float attenuationLinear = 0.09f;
	float attenuationQuadratic = 0.032f;

	float ambient = 0.05f;
	float diffuse = 0.8f;
	float specular = 1.0f;

	static void ApplyPointLights(int shaderValue);
};