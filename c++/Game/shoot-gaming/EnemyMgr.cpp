#include <fstream>
#include <sstream>
#include "EnemyMgr.h"
#include "NormalEnemy.h"
#include "eEnemyData.h"
#include "Macro.h"

using namespace std;

EnemyMgr::EnemyMgr(IShootListener* shot, IIncScoreListener* score, string stages) :
_ptr_shot(shot), _ptr_score(score), _nowStage(0), _cnt(0)
{
	_stages = FileLoad(stages);
	_stage = FileLoad(_stages.at(_nowStage));
	StageLoad(_stage);
}

vector<string> EnemyMgr::FileLoad(string filename)
{
	ifstream fs(filename);
	string buf; 
	vector<string> res;

	if (!fs.is_open()) {
		ERR("ファイルが見つかりません！");
	}

	//読み飛ばし
	getline(fs, buf);

	while (getline(fs, buf)) {
		res.push_back(buf);
	}

	fs.close();

	return res;
}

bool EnemyMgr::StageLoad(vector<string> stage)
{
	for (auto buf : stage) {
		istringstream streambuf(buf);
		string s;
		vector<string> v;

		while (getline(streambuf, s, ','))
		{
			v.push_back(s);
		}

		_Schedule.push_back(v);
	}

	return true;
}

void EnemyMgr::init()
{
	_enemy.clear();
	_stage.clear();
	_stages.clear();
}

bool EnemyMgr::NextStage()
{
	_nowStage++;
	
	if (_nowStage >= _stages.size())
	{
		return false;
	}

	_stage = FileLoad(_stages.at(_nowStage));
	StageLoad(_stage);

	return true;
}

bool EnemyMgr::update()
{
	_cnt++;

	auto it = _Schedule.begin();

	while (it != _Schedule.end())
	{
		if (stoi(it->at(eEnemyData::wait)) * 10 <= _cnt) {
			_enemy.push_back(new NormalEnemy(_ptr_shot, stoi(it->at(eEnemyData::hp)), stoi(it->at(eEnemyData::pattern)), stoi(it->at(eEnemyData::x)), stoi(it->at(eEnemyData::y)), it->at(eEnemyData::img)));
			it = _Schedule.erase(it);
			_cnt = 0;
		}
		else {
			break;
		}
	}

	auto itr = _enemy.begin();

	while (itr != _enemy.end())
	{
		if (!itr[0]->update()) {
			_ptr_score->IncScore(1000);
			itr = _enemy.erase(itr);
		}
		else if (itr[0]->IsOutside())
		{
			itr = _enemy.erase(itr);
		}
		else
		{
			itr++;
		}
	}

	if (!_enemy.size())
	{
		return false;
	}

	return true;
}

void EnemyMgr::draw() const
{
	for (auto e : _enemy) e->draw();
}