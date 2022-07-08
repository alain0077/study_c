#pragma once

#include "Abstract.h"
#include <stack>

// coordinates_imfo
struct Dfs_Coor
{
	int x;
	int y;
};

class DFS : public Abstract
{
public:
	DFS(std::vector<std::vector<int>> map, int start_x, int start_y, int end_x, int end_y);
	~DFS() = default;
	void update() override;
	void draw() const override;
	void finalize() override;

private:
	// depth-first search
	void dfs();

	std::stack<Dfs_Coor> s;

	// map for dfs
	std::vector<std::vector<int>> dfs_map;

	// jubge whether it's wall
	bool judge_wall(int) const;

	// judge whether searching coordinates is dead end
	bool judge_end() const;
};