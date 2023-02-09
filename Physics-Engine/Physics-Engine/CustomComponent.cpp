#include <Engine/Engine.h>
#include <CustomComponent.h>

void CustomComponent::Mainloop() {
	Text* TextComponent = ParentObject()->GetComponent<Text*>();
	Transform* PlanetTransform = PhysicsEngine::FindSceneObject("Mercury")->GetComponent<Transform*>();

	float VelocityMagnitude = glm::length(PlanetTransform->velocity);
	TextComponent->DisplayedText = "V = " + to_string(VelocityMagnitude).substr(0, 2);
}