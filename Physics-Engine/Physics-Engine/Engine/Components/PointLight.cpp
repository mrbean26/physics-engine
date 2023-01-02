#include <Engine/Components/PointLight.h>

#include <Engine/Engine.h>
#include <Engine/Components/Transform.h>
#include <Engine/Components/ViewModel.h>
#include <Engine/Background/Shaders.h>

#include <GLM/gtc/matrix_transform.hpp>

void PointLight::Mainloop() {
	Initialise();
	RenderCubeMap();
}
void PointLight::Initialise() {
	if (initialised) {
		return;
	}

	InitialiseCubemapShader();
	InitialiseCubeMap();

	initialised = true;
}

void PointLight::InitialiseCubemapShader() {
	if (cubemapShader > -1) {
		return;
	}

	int vertex = CreateShader("Assets/Shaders/CubeMap_v.txt", GL_VERTEX_SHADER);
	int geometry = CreateShader("Assets/Shaders/CubeMap_g.txt", GL_GEOMETRY_SHADER);
	int fragment = CreateShader("Assets/Shaders/CubeMap_f.txt", GL_FRAGMENT_SHADER);

	cubemapShader = CreateProgram({ vertex, geometry, fragment });
}
void PointLight::InitialiseCubeMap() {
	glGenFramebuffers(1, &cubeMapFBO);
	glGenTextures(1, &depthCubemap);

	glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
	for (int i = 0; i < 6; i++) {
		GLenum face = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
		glTexImage2D(face, 0, GL_DEPTH_COMPONENT, SHADOW_RESOLUTION, SHADOW_RESOLUTION, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
	glBindFramebuffer(GL_FRAMEBUFFER, cubeMapFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

vector<mat4> PointLight::ShadowTransforms() {
	// Projection
	mat4 shadowProjection = perspective(radians(90.0f), 1.0f, near, far);

	// Views
	Transform* objectTransform = parentObject->GetComponent<Transform*>("Transform");

	mat4 viewOne = lookAt(objectTransform->position, objectTransform->position + vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f));
	mat4 viewTwo = lookAt(objectTransform->position, objectTransform->position + vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f));
	mat4 viewThree = lookAt(objectTransform->position, objectTransform->position + vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f));
	mat4 viewFour = lookAt(objectTransform->position, objectTransform->position + vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f));
	mat4 viewFive = lookAt(objectTransform->position, objectTransform->position + vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f));
	mat4 viewSix = lookAt(objectTransform->position, objectTransform->position + vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, -1.0f, 0.0f));
	
	// Overalls
	vector<mat4> result = {
		shadowProjection * viewOne,
		shadowProjection * viewTwo,
		shadowProjection * viewThree,
		shadowProjection * viewFour,
		shadowProjection * viewFive,
		shadowProjection * viewSix
	};

	return result;
}
void PointLight::RenderCubeMap() {
	// Bind
	glViewport(0, 0, SHADOW_RESOLUTION, SHADOW_RESOLUTION);
	glBindFramebuffer(GL_FRAMEBUFFER, cubeMapFBO);
	
	glClear(GL_DEPTH_BUFFER_BIT);
	glUseProgram(cubemapShader);

	// Uniforms
	vector<mat4> shadowMatrices = ShadowTransforms();
	for (int i = 0; i < 6; i++) {
		string name = "shadowMatrices[" + to_string(i) + "]";
		SetShaderMat4(cubemapShader, name.data(), shadowMatrices[i]);
	}

	Transform* parentTransform = parentObject->GetComponent<Transform*>("Transform");

	SetShaderFloat(cubemapShader, "far_plane", far);
	SetShaderVec3(cubemapShader, "lightPos", parentTransform->position);
	
	// Draw
	Scene* currentScene = &PhysicsEngine::loadedScenes[PhysicsEngine::currentScene];
	map<const char*, Object>* sceneObjects = &currentScene->SceneObjects;

	for (map<const char*, Object>::iterator it = sceneObjects->begin(); it != sceneObjects->end(); it++) {
		if (it->second.HasComponent("ViewModel")) {
			ViewModel* currentViewModel = it->second.GetComponent<ViewModel*>("ViewModel");
			Transform* currentTransform = it->second.GetComponent<Transform*>("Transform");

			glBindVertexArray(currentViewModel->ObjectVAO);
			SetShaderMat4(cubemapShader, "model", currentTransform->getModelMatrix());

			glDrawArrays(GL_TRIANGLES, 0, currentViewModel->ObjectDrawSize);
		}
	}

	// End
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, PhysicsEngine::displayWidth, PhysicsEngine::displayHeight);
}

void PointLight::ApplyPointLights(int shaderValue) {
	int lightCount = 0;

	Scene* currentScene = &PhysicsEngine::loadedScenes[PhysicsEngine::currentScene];
	map<const char*, Object>* sceneObjects = &currentScene->SceneObjects;

	for (map<const char*, Object>::iterator it = sceneObjects->begin(); it != sceneObjects->end(); it++) {
		if (it->second.HasComponent("PointLight")) {
			PointLight* currentPointLight = it->second.GetComponent<PointLight*>("PointLight");
			Transform* currentLightTransform = it->second.GetComponent<Transform*>("Transform");
			string overallString = "allPointLights[" + to_string(lightCount) + "].";

			SetShaderVec3(shaderValue, (overallString + "position").data(), currentLightTransform->position);
			
			SetShaderFloat(shaderValue, (overallString + "intensity").data(), currentPointLight->intensity);
			SetShaderFloat(shaderValue, (overallString + "ambient").data(), currentPointLight->ambient);
			SetShaderFloat(shaderValue, (overallString + "diffuse").data(), currentPointLight->diffuse);
			SetShaderFloat(shaderValue, (overallString + "specular").data(), currentPointLight->specular);

			SetShaderFloat(shaderValue, (overallString + "attenuationConstant").data(), currentPointLight->attenuationConstant);
			SetShaderFloat(shaderValue, (overallString + "attenuationLinear").data(), currentPointLight->attenuationLinear);
			SetShaderFloat(shaderValue, (overallString + "attenuationQuadratic").data(), currentPointLight->attenuationQuadratic);
			
			// Shadows
			glActiveTexture(GL_TEXTURE16 + lightCount);
			glBindTexture(GL_TEXTURE_CUBE_MAP, currentPointLight->depthCubemap);
			SetShaderInt(shaderValue, ("pointShadowMaps[" + to_string(lightCount) + "]").data(), 16 + lightCount);
			SetShaderFloat(shaderValue, ("pointShadowFars[" + to_string(lightCount) + "]").data(), currentPointLight->far);

			lightCount = lightCount + 1;
		}
	}

	SetShaderInt(shaderValue, "pointLightCount", lightCount);
}
