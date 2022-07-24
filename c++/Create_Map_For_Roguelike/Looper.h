#pragma once

#include <stack>
#include <memory>
#include "AbstractMethod.h"

class Looper
{
public:
	Looper();
	~Looper() = default;
	bool update();

private:
	std::stack<std::shared_ptr<AbstractMethod>> _method;
};