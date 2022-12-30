#include <Engine/Components/PointLight.h>

#include <Engine/Engine.h>
#include <Engine/Components/Transform.h>
#include <Engine/Background/Shaders.h>

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
	
			lightCount = lightCount + 1;
		}
	}

	SetShaderInt(shaderValue, "pointLightCount", lightCount);
}
