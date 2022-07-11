#include "ScoreMgr.h"
#include <DxLib.h>

using namespace std;

ScoreMgr::ScoreMgr() : _score(0), _time(GetNowCount())
{
}

void ScoreMgr::init()
{
	_score = 0, _time = 0;
}

bool ScoreMgr::update()
{
	return true;
}

void ScoreMgr::IncScore(int n)
{
	_score += n;
}

void ScoreMgr::draw() const
{
	DrawFormatString(400, 120, GetColor(255, 255, 255), "score : %d", _score);
	DrawFormatString(400, 140, GetColor(255, 255, 255), " time : %d", (GetNowCount() - _time) / 1000);
}