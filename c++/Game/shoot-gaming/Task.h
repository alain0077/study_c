#pragma once
#include <Dxlib.h>

class Task {
public:
	Task() = default;
	virtual ~Task() = default;
	virtual void init() = 0;
	virtual bool update() = 0;
	virtual void draw() const = 0;
};