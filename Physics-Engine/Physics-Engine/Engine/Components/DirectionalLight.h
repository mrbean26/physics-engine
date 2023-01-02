#pragma once

#include <Engine/Object/Component.h>
#include <Engine/Engine.h>

class DirectionalLight : public Component {
public:
	void Mainloop();
	void Initialise();
	
	// Light Attributes
	float intensity = 1.0f;

	float attenuationConstant = 1.0f;
	float attenuationLinear = 0.09f;
	float attenuationQuadratic = 0.032f;

	float ambient = 0.05f;
	float diffuse = 0.8f;
	float specular = 1.0f;

	float lowerAngleLight = 12.5f;
	float upperAngleLight = 15.0f;

	// Shadows
	GLuint depthMapFBO;
	GLuint depthMap;
	inline static GLuint depthMapShader = -1;

	void InitialiseDepthMap();
	void InitialiseDepthMapShader();

	void RenderDepthMap();

	vec3 LightTarget();
	mat4 LightSpaceMatrix();

	// All
	static void ApplyDirectionalLights(int shaderValue);
};