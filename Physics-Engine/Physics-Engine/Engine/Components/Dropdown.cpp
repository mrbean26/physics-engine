#include <Engine/Engine.h>
#include <Engine/Components/Dropdown.h>

#include <GLM/gtc/matrix_transform.hpp>

void Dropdown::Mainloop() {
	Initialise();
	
	OpenCloseDropdown();
	CheckEntryPress();
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