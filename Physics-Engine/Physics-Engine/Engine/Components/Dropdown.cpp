#include <Engine/Engine.h>
#include <Engine/Components/Dropdown.h>

#include <GLM/gtc/matrix_transform.hpp>

void Dropdown::Mainloop() {
	Initialise();
	
	OpenCloseDropdown();
	CheckEntryPress();
	UpdateEntryTransforms();
}
void Dropdown::Initialise() {
	if (initialised) {
		return;
	}
	ParentObject()->AddComponent<Text>();
	ParentObject()->AddComponent<Button>();
	
	ParentObject()->GetComponent<Button*>()->texturePath = EntryButtonBackgroundTexturePath;
	ParentObject()->GetComponent<Text*>()->FontFilePath = EntryTextFontPath;

	ParentObject()->GetComponent<Text*>()->DisplayedText = DropdownEntries[DropdownEntryValueIndex];

	initialised = true;
}

void Dropdown::OpenCloseDropdown() {
	if (ParentObject()->GetComponent<Button*>()->ButtonClicked) {
		if (!DropdownOpen) {
			OpenDropdown();
			return;
		}
		if (DropdownOpen) {
			CloseDropdown();
		}
	}
}
void Dropdown::CheckEntryPress() {
	if (!DropdownOpen) {
		return;
	}

	int EntryCount = DropdownEntryObjectPointers.size();
	for (int i = 0; i < EntryCount; i++) {
		if (DropdownEntryObjectPointers[i]->GetComponent<Button*>()->ButtonClicked) {
			DropdownEntryValueIndex = i;
			ParentObject()->GetComponent<Text*>()->DisplayedText = DropdownEntries[i];
			CloseDropdown();
			break;
		}
	}
}

void Dropdown::OpenDropdown() {
	int EntryCount = DropdownEntries.size();

	for (int i = 0; i < EntryCount; i++) {
		string NewObjectName = string(ParentObjectName) + "_DropdownEntry_" + to_string(i);
		Object* NewDropdownEntry = PhysicsEngine::loadedScenes[PhysicsEngine::currentScene].CreateSceneObject(NewObjectName);
		
		// Add Components
		NewDropdownEntry->AddComponent<Text>();
		NewDropdownEntry->GetComponent<Text*>()->FontFilePath = EntryTextFontPath;
		NewDropdownEntry->GetComponent<Text*>()->DisplayedText = DropdownEntries[i];
		
		NewDropdownEntry->AddComponent<Button>();
		NewDropdownEntry->GetComponent<Button*>()->texturePath = EntryButtonBackgroundTexturePath;

		NewDropdownEntry->GetComponent<Transform*>()->ParentTransform = ParentObject()->GetComponent<Transform*>();

		float DeltaY = -0.5f - 2.25f * (i + 1);
		NewDropdownEntry->GetComponent<Transform*>()->position = vec3(0.0f, DeltaY, 0.0f);
		
		// Append
		DropdownEntryObjectPointers.push_back(NewDropdownEntry);
	}
	
	DropdownOpen = true;
}
void Dropdown::CloseDropdown() {
	int EntryCount = DropdownEntryObjectPointers.size();

	for (int i = 0; i < EntryCount; i++) {
		PhysicsEngine::loadedScenes[PhysicsEngine::currentScene].DeleteObjectByID(DropdownEntryObjectPointers[i]->name);
	}
	DropdownEntryObjectPointers.clear();

	DropdownOpen = false;
}

void Dropdown::UpdateEntryTransforms() {
	if (!DropdownOpen) {
		return;
	}

	/*
	mat4 newMatrix = mat4(1.0f);
	vec3 rotation = ParentObject()->GetComponent<Transform*>()->rotation;
	
	newMatrix = scale(newMatrix, vec3(PhysicsEngine::displayHeight / PhysicsEngine::displayWidth, 1.0f, 1.0f));

	newMatrix = rotate(newMatrix, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
	newMatrix = rotate(newMatrix, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
	newMatrix = rotate(newMatrix, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));

	newMatrix = scale(newMatrix, ParentObject()->GetComponent<Transform*>()->scale * vec3(2.0f));

	int EntryCount = DropdownEntryObjectPointers.size();
	for (int i = 0; i < EntryCount; i++) {
		DropdownEntryObjectPointers[i]->allComponents.transform = *ParentObject()->GetComponent<Transform*>();

		// Adjust Position of Entry
		
		vec2 ShiftedUIPosition = newMatrix * vec4(0.0f, DeltaY, 0.0f, 1.0f);

		DropdownEntryObjectPointers[i]->GetComponent<Transform*>()->position += vec3(ShiftedUIPosition, 0.0f);
	}
	*/
}