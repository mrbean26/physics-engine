#pragma once

#include <vector>
#include <string>
using namespace std;

class Object;

class Component {
public:
	bool initialised = false;
	string ParentObjectName;

	virtual void Mainloop();
	Object* ParentObject();
};

#include <Engine/Object/Object.h>
