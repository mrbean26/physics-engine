#pragma once

#include <Engine/Object/Component.h>

class Dropdown : public Component {
public:
	void Mainloop();
	void Initialise();

	string EntryButtonBackgroundTexturePath = "Assets/Defaults/ScrollbarBackground.png";
	string EntryTextFontPath = "Assets/Defaults/Font.ttf";

	vector<string> DropdownEntries = { "Entry 1", "Entry 2", "Entry 3" };
	vector<Object*> DropdownEntryObjectPointers;

	bool DropdownOpen = false;
	int DropdownEntryValueIndex = 0;

	void OpenCloseDropdown();
	void CheckEntryPress();

	void OpenDropdown();
	void CloseDropdown();

	void UpdateEntryTransforms();
};