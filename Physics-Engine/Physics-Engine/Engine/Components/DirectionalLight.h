#pragma once

#include <Engine/Object/Component.h>
#include <Engine/Engine.h>

class DirectionalLight : public Component {
public:
	inline static GLuint depthMapFBO;
	inline static const int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	inline static GLuint depthMap;
	inline static GLuint depthMapShader;
	static void initialiseDepthMap();
	static void renderDepthMap();
	inline static bool initialisedDepthMap = false;

	float intensity = 1.0f;

	float attenuationConstant = 1.0f;
	float attenuationLinear = 0.09f;
	float attenuationQuadratic = 0.032f;

	float ambient = 0.05f;
	float diffuse = 0.8f;
	float specular = 1.0f;

	float lowerAngleLight = 12.5f;
	float upperAngleLight = 15.0f;

	static void ApplyDirectionalLights(int shaderValue);
};