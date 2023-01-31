#pragma once

#include <Engine/Object/Component.h>

class ParticleSystem : public Component {
public:
	void Mainloop();
	void Initialise();

	void GenerateParticles();
	vec3 GetParticleDirection();

	void ScaleParticles();
	void RemoveParticles();

	vector<pair<float, Object*>> AllParticles;
	ViewModel ParticleViewmodel;
	Transform ParticleTransform;

	// Particle Lifetime
	float ScalingMultiplier = 0.75f;
	float ParticleLifetime = 5.0f;

	// Particle Generation
	float ProductionInterval = 0.05f;
	float CurrentProductionCountdown = 0.0f;

	vec2 MinAngleGeneration = vec2(0.0f);
	vec2 MaxAngleGeneration = vec2(360.0f);

	// Overall Particles
	int CreatedParticleCount = 0;
	int MaxParticleCount = 100;

	float ParticleVelocity = 5.0f;
};