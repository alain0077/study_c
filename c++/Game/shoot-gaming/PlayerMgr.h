#pragma once

#include "Task.h"
#include "AbstractPlayer.h"
#include "IShootListener.h"
#include <string>
#include <vector>
#include <queue>

class IShootListener;

class PlayerMgr : public Task
{
public:
	PlayerMgr(IShootListener* ptr);
	~PlayerMgr() = default;
	void init();
	bool update();
	void draw() const;


private:
	std::vector<AbstractPlayer*> _player;

	void Load(std::string fname);

	IShootListener* _ptr;
};