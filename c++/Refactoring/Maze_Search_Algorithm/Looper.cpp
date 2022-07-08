#include "Looper.h"

using namespace std;

Looper::Looper()
{
    Map* _map = new Map();
	_map->CreatMap();

    _ptr.push_back(new DFS(_map->getMap()));
    _ptr.push_back(new H_bfs(_map->getMap()));
    _ptr.push_back(new BFS(_map->getMap()));
}

bool Looper::loop()
{
    if(!_ptr.size()) return false;

    if(!_ptr[0]->loop()){
        _ptr[0]->finalize();
        _ptr.erase(_ptr.begin());
    }

    return true;
}