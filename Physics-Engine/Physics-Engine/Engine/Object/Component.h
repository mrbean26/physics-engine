#pragma once

class Component {
public:
	bool initialised = false;
	virtual ~Component() {};
	virtual void Mainloop() = 0;
};