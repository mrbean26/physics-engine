#pragma once

class Object;

class Component {
public:
	bool initialised = false;
	const char* componentObjectParentName;

	virtual void Mainloop();
	Object* parentObject;
};

#include <Engine/Object/Object.h>
