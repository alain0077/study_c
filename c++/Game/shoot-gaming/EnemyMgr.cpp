#include <fstream>
#include <sstream>
#include "EnemyMgr.h"
#include "NormalEnemy.h"
#include "Macro.h"

using namespace std;

EnemyMgr::EnemyMgr(IShootListener* shot, IIncScoreListener* score, string stages) :
_ptr_shot(shot), _ptr_score(score), _nowStage(0)
{
	_stages = FileLoad(stages);
	_stage = FileLoad(_stages.at(_nowStage));
	StageLoad(_stage);

	//_enemy.push_back(new NormalEnemy(shot, 10, 2, 50.0, 30.0, "test.png"));
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

		_enemy.push_back(new NormalEnemy(_ptr_shot, stoi(v[0]), stoi(v[1]), stoi(v[2]), stoi(v[3]), v[4]));
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
	if (!_stages.size())
		return false;
	else {
		_stages.erase(_stages.begin());
	}

	return true;
}

bool EnemyMgr::update()
{
	auto itr = _enemy.begin();

	while (itr != _enemy.end())
	{
		if (!itr[0]->update()) {
			_ptr_score->IncScore(1000);
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