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
	BFS(std::vector<std::vector<int>> map, int start_x, int start_y, int end_x, int end_y);
	~BFS() = default;
	void update() override;
	void draw() const override;
	void finalize() override;

	// breadth-first search
	void bfs();

private:
	// queue for bfs
	std::queue<Bfs_Coor> q;

	int depth;

	// map for bfs
	std::vector<std::vector<int>> bfs_map;

	// jubge whether it's load
	bool judge_road(int) const;
};