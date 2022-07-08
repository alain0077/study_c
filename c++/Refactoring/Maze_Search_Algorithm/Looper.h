#pragma once

#include <DxLib.h>
#include <vector>
#include <random>
#include "Abstract.h"
#include "Map.h"

#include "dfs.h"
#include "bfs.h"
#include "h_bfs.h"

class Looper
{
public:
    Looper();
    ~Looper() = default;
    bool loop();

private:
    std::vector<Abstract*> _ptr;
    Map* _map;
};