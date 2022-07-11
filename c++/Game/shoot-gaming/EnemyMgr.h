#pragma once

#include "Task.h"
#include "AbstractEnemy.h"
#include "IShootListener.h"
#include "IIncScoreListener.h"
#include <string>
#include <vector>
#include <queue>

struct E_info
{
	int pattern,
		hp;

	double x, y;

	std::string img;
};

class IShootListener;
class IIncScoreListener;

class EnemyMgr : public Task
{
public:
	EnemyMgr(IShootListener* pshot, IIncScoreListener* pscore, std:: string stages);
	~EnemyMgr() = default;
	void init();
	bool update();
	void draw() const;
	// 次のステージの敵への切り替え
	bool NextStage();

private:
	int _nowStage;
	std::vector<std::string> _stage;
	std::vector<std::string> _stages;
	std::vector<AbstractEnemy*> _enemy;

	std::vector<std::string> FileLoad(std::string fname);
	bool StageLoad(std::vector<std::string> stage);

	IShootListener* _ptr_shot;
	IIncScoreListener* _ptr_score;
};