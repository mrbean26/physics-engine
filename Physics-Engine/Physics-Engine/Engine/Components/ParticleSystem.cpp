#include <Engine/Engine.h>
#include <Engine/Components/ParticleSystem.h>

#include <GLM/gtc/matrix_transform.hpp>

void ParticleSystem::Mainloop() {
	Initialise();

	GenerateParticles();
	ScaleParticles();
	RemoveParticles();
}
void ParticleSystem::Initialise() {
	if (initialised) {
		return;
	}

	CurrentProductionCountdown = ProductionInterval;

	initialised = true;
}

void ParticleSystem::GenerateParticles() {
	int CurrentParticleCount = AllParticles.size();

	if (CurrentProductionCountdown <= 0.0f && CurrentParticleCount < MaxParticleCount) {
		CreatedParticleCount = CreatedParticleCount + 1;
		string NewParticleName = ParentObjectName + "_Particle_" + to_string(CreatedParticleCount);

		Object* NewParticle = PhysicsEngine::CreateNewSceneObject(NewParticleName);
		
		ParticleViewmodel.ParentObjectName = NewParticleName;
		NewParticle->allComponents.viewModel = ParticleViewmodel;
		NewParticle->components["ViewModel"] = &NewParticle->allComponents.viewModel;

		NewParticle->GetComponent<Transform*>()->ParentTransform = ParentObject()->GetComponent<Transform*>();

		vec3 ParticleDirection = GetParticleDirection();
		NewParticle->GetComponent<Transform*>()->velocity = ParticleDirection;
		NewParticle->GetComponent<Transform*>()->rotation = ParticleDirection;

		CurrentProductionCountdown = ProductionInterval;

		AllParticles.push_back(make_pair(ParticleLifetime, NewParticle));
	}

	CurrentProductionCountdown = CurrentProductionCountdown - PhysicsEngine::deltaTime;
}
vec3 ParticleSystem::GetParticleDirection() {
	vec3 Forward = vec3(0.0f, 0.0f, -ParticleVelocity);

	mat4 MultiplyMatrix = mat4(1.0f);

	float x = MaxAngleGeneration.x + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (MaxAngleGeneration.x - MinAngleGeneration.y)));
	float y = MaxAngleGeneration.y + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (MaxAngleGeneration.y - MinAngleGeneration.y)));

	MultiplyMatrix = rotate(MultiplyMatrix, radians(x), vec3(1.0f, 0.0f, 0.0f));
	MultiplyMatrix = rotate(MultiplyMatrix, radians(y), vec3(0.0f, 1.0f, 0.0f));

	return MultiplyMatrix * vec4(Forward, 1.0f);
}

void ParticleSystem::ScaleParticles() {
	int CurrentParticleCount = AllParticles.size();
	
	for (int i = 0; i < CurrentParticleCount; i++) {
		AllParticles[i].second->GetComponent<Transform*>()->scale *= vec3(1.0f - ScalingMultiplier * PhysicsEngine::deltaTime);
	}
}
void ParticleSystem::RemoveParticles() {
	int CurrentParticleCount = AllParticles.size();
	
	for (int i = 0; i < CurrentParticleCount; i++) {
		AllParticles[i].first -= PhysicsEngine::deltaTime;

		if (AllParticles[i].first <= 0.0f) {
			PhysicsEngine::DeleteSceneObject(AllParticles[i].second->name);
			AllParticles.erase(AllParticles.begin() + i);

			i = i - 1;
			CurrentParticleCount = CurrentParticleCount - 1;
		}
	}
}