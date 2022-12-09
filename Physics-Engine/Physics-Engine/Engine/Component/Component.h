#pragma once

class Component {
public:
	virtual ~Component() {};
	virtual void Mainloop() = 0;
};