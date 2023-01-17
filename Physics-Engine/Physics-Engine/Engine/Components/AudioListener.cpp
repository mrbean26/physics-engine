#include <Engine/Engine.h>
#include <Engine/Components/AudioListener.h>

#include <Engine/Background/Shaders.h>

#include <GLM/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void AudioListener::Mainloop() {
	Transform* parentTransform = parentObject->GetComponent<Transform*>();
	vec3 parentPosition = parentTransform->position;

	alListener3f(AL_POSITION, parentPosition.x, parentPosition.y, parentPosition.z);

	// Orientation
	vec3 rotation = parentTransform->rotation;

	mat4 parentModelMatrix = mat4(1.0f);
	parentModelMatrix = rotate(parentModelMatrix, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
	parentModelMatrix = rotate(parentModelMatrix, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
	parentModelMatrix = rotate(parentModelMatrix, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));

	vec3 forward = parentModelMatrix * vec4(0.0f, 0.0f, -1.0f, 1.0f);
	vec3 up = parentModelMatrix * vec4(0.0f, 1.0f, 0.0f, 1.0f);

	float* orientation = new float[6] {forward.x, forward.y, forward.z, up.x, up.y, up.z};
	alListenerfv(AL_ORIENTATION, orientation);
}
