#include <fstream>
#include <sstream>
#include "PlayerMgr.h"
#include "Player.h"
#include "Macro.h"

using namespace std;

PlayerMgr::PlayerMgr(IShootListener* ptr) :
	_ptr(ptr)
{
	_player.push_back(new Player(_ptr, 230.0, 500.0, 1, "test.png"));
}



void PlayerMgr::Load(std::string filename)
{
	fstream fs(filename);
	string buf;

	if (!fs.is_open()) {
		ERR("ファイルが見つかりません！");
	}

	//読み飛ばし
	getline(fs, buf);

	while (getline(fs, buf)) {
		istringstream streambuf(buf);
		string s;
		vector<int> _d;

		while (getline(streambuf, s, ','))
		{
			_d.push_back(int(s.c_str()));
		}

		/*
		E_info tmp(_d);
		_stage.push(tmp);
		*/
	}
	fs.close();
}

void PlayerMgr::init()
{

}

bool PlayerMgr::update()
{
	auto itr = _player.begin();

	while (itr != _player.end())
	{
		if (!itr[0]->update()) {
			itr = _player.erase(itr);
		}
		else
		{
			itr++;
		}
	}

	if (!_player.size())
	{
		return false;
	}

	return true;
}

void PlayerMgr::draw() const
{
	for (auto p : _player) p->draw();
}