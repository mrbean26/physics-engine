#pragma once

#include <map>
using namespace std;

#include <Engine/Component/Component.h>

class Object {
public:
	Object();
	void ObjectMainloop();

	map<const char*, Component> components;
};