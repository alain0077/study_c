#pragma once

#include "Abstract.h"
#include <queue>

// coordinates_imfo
struct Bfs_Coor
{
	int x;
	int y;
	int depth;
};

class BFS : public Abstract
{
public:
	BFS(Map_Info map);
	~BFS() = default;
	void update() override;
	void draw() const override;
	void finalize() override;

private:
	// breadth-first search
	void bfs();

	int _depth;

	// queue for bfs
	std::queue<Bfs_Coor> _q;

	// map for bfs
	std::vector<std::vector<int>> _bfs_map;

	// jubge whether it's load
	bool judge_road(int) const;
};