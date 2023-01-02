#include <Engine/Engine.h>

#include <Engine/Components/DirectionalLight.h>
#include <Engine/Components/Transform.h>
#include <Engine/Background/Shaders.h>
#include <Engine/Components/ViewModel.h>

#include <GLM/gtc/matrix_transform.hpp>
using namespace glm;

void DirectionalLight::Mainloop() {
	Initialise();
	RenderDepthMap();
}
void DirectionalLight::Initialise() {
	if (initialised) {
		return;
	}

	InitialiseDepthMap();
	InitialiseDepthMapShader();

	initialised = true;
}


void DirectionalLight::InitialiseDepthMap() {
	glGenFramebuffers(1, &depthMapFBO);

	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_RESOLUTION, SHADOW_RESOLUTION, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void DirectionalLight::InitialiseDepthMapShader() {
	if (depthMapShader > -1) {
		return;
	}

	int vert = CreateShader("Assets/Shaders/DepthMap_v.txt", GL_VERTEX_SHADER);
	int frag = CreateShader("Assets/Shaders/DepthMap_f.txt", GL_FRAGMENT_SHADER);
	depthMapShader = CreateProgram({ vert, frag });
}

void DirectionalLight::RenderDepthMap() {
	glViewport(0, 0, SHADOW_RESOLUTION, SHADOW_RESOLUTION);
	
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(depthMapShader);

	Scene* currentScene = &PhysicsEngine::loadedScenes[PhysicsEngine::currentScene];
	map<const char*, Object>* sceneObjects = &currentScene->SceneObjects;
	
	for (map<const char*, Object>::iterator it = sceneObjects->begin(); it != sceneObjects->end(); it++) {
		if (it->second.HasComponent("ViewModel")) {
			ViewModel* currentViewModel = it->second.GetComponent<ViewModel*>("ViewModel");
			Transform* currentTransform = it->second.GetComponent<Transform*>("Transform");

			glBindVertexArray(currentViewModel->ObjectVAO);
			SetShaderMat4(depthMapShader, "model", currentTransform->getModelMatrix());
			SetShaderMat4(depthMapShader, "lightSpaceMatrix", LightSpaceMatrix());

			glDrawArrays(GL_TRIANGLES, 0, currentViewModel->ObjectDrawSize);
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, PhysicsEngine::displayWidth, PhysicsEngine::displayHeight);
}

vec3 DirectionalLight::LightTarget() {
	vec3 direction = vec3(0.0f, 0.0f, -1.0f);

	Transform* parentTransform = parentObject->GetComponent<Transform*>("Transform");

	mat4 rotationalMatrix = mat4(1.0f);
	rotationalMatrix = rotate(rotationalMatrix, -radians(parentTransform->rotation.x), vec3(0.0f, 1.0f, 0.0f));
	rotationalMatrix = rotate(rotationalMatrix, -radians(parentTransform->rotation.y), vec3(1.0f, 0.0f, 0.0f));
	rotationalMatrix = rotate(rotationalMatrix, radians(parentTransform->rotation.z), vec3(0.0f, 0.0f, 1.0f));

	return vec3(rotationalMatrix * vec4(direction, 1.0f));
}
mat4 DirectionalLight::LightSpaceMatrix() {
	// Projection
	float near_plane = 1.0f, far_plane = 50.0f;
	mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);

	// View
	Transform* parentTransform = parentObject->GetComponent<Transform*>("Transform");


	mat4 lightView = glm::lookAt(parentTransform->position, LightTarget(), glm::vec3(0.0f, 1.0f, 0.0f));

	// Overall
	mat4 lightSpaceMatrix = lightProjection * lightView;
	return lightSpaceMatrix;
}

void DirectionalLight::ApplyDirectionalLights(int shaderValue) {
	int lightCount = 0;
	
	Scene* currentScene = &PhysicsEngine::loadedScenes[PhysicsEngine::currentScene];
	map<const char*, Object>* sceneObjects = &currentScene->SceneObjects;

	for (map<const char*, Object>::iterator it = sceneObjects->begin(); it != sceneObjects->end(); it++) {
		if (it->second.HasComponent("DirectionalLight")) {
			DirectionalLight* currentDirectionalLight = it->second.GetComponent<DirectionalLight*>("DirectionalLight");
			Transform* currentLightTransform = it->second.GetComponent<Transform*>("Transform");
			string overallString = "allDirectionalLights[" + to_string(lightCount) + "].";

			SetShaderVec3(shaderValue, (overallString + "position").data(), currentLightTransform->position);

			SetShaderFloat(shaderValue, (overallString + "intensity").data(), currentDirectionalLight->intensity);
			SetShaderFloat(shaderValue, (overallString + "ambient").data(), currentDirectionalLight->ambient);
			SetShaderFloat(shaderValue, (overallString + "diffuse").data(), currentDirectionalLight->diffuse);
			SetShaderFloat(shaderValue, (overallString + "specular").data(), currentDirectionalLight->specular);

			SetShaderFloat(shaderValue, (overallString + "attenuationConstant").data(), currentDirectionalLight->attenuationConstant);
			SetShaderFloat(shaderValue, (overallString + "attenuationLinear").data(), currentDirectionalLight->attenuationLinear);
			SetShaderFloat(shaderValue, (overallString + "attenuationQuadratic").data(), currentDirectionalLight->attenuationQuadratic);

			SetShaderFloat(shaderValue, (overallString + "cutOff").data(), glm::cos(glm::radians(currentDirectionalLight->lowerAngleLight)));
			SetShaderFloat(shaderValue, (overallString + "outerCutOff").data(), glm::cos(glm::radians(currentDirectionalLight->upperAngleLight)));

			// Calculate Direction
			vec3 oldPosition = currentLightTransform->position;
			vec3 oldScale = currentLightTransform->scale;

			currentLightTransform->position = vec3(0.0f);
			currentLightTransform->scale = vec3(1.0f);

			vec3 lightDirectionPoint = vec3(currentLightTransform->getModelMatrix() * vec4(0.0f, 0.0f, -1.0f, 1.0f));
			SetShaderVec3(shaderValue, (overallString + "direction").data(), lightDirectionPoint);

			currentLightTransform->position = oldPosition;
			currentLightTransform->scale = oldScale;

			// Shadow Variables
			
			SetShaderMat4(shaderValue, ("lightSpaceMatrices[" + to_string(lightCount) + "]").data(), currentDirectionalLight->LightSpaceMatrix());

			glActiveTexture(GL_TEXTURE1 + lightCount);
			glBindTexture(GL_TEXTURE_2D, currentDirectionalLight->depthMap);
			SetShaderInt(shaderValue, ("directionalShadowMaps[" + to_string(lightCount) + "]").data(), lightCount + 1);

			lightCount = lightCount + 1;
		}
	}

	SetShaderInt(shaderValue, "directionalLightCount", lightCount);
}


