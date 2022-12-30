#include <Engine/Components/DirectionalLight.h>

#include <Engine/Engine.h>
#include <Engine/Components/Transform.h>
#include <Engine/Background/Shaders.h>

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

			lightCount = lightCount + 1;
		}
	}

	SetShaderInt(shaderValue, "directionalLightCount", lightCount);
}


