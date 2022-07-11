#pragma once
#include "Task.h"
#include "IIncScoreListener.h"
#include <vector>

class ScoreMgr final : public Task, public IIncScoreListener
{
public:
	ScoreMgr();
	~ScoreMgr() = default;
	void init();
	bool update();
	void draw() const;
	// Add N to the score.
	void IncScore(int) override;
	/*
	* return final score
	* Will change to add according to survival time dependence
	*/
	int getFilalScore() { return _score; }
	
	// return final time
	int getTime() { return (GetNowCount() - _time) / 1000; }

private:
	int _time;
	int _score;
};