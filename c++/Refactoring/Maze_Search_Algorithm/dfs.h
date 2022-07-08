#pragma once

#include "Abstract.h"
#include <stack>

class DFS : public Abstract
{
public:
	DFS(Map_Info map);
	~DFS() = default;
	void update() override;
	void draw() const override;
	void finalize() override;

private:
	// depth-first search
	void dfs();

	std::stack<Coor> _s;

	// map for dfs
	std::vector<std::vector<int>> _dfs_map;

	// jubge whether it's wall
	bool judge_wall(int) const;

	// judge whether searching coordinates is dead end
	bool judge_end() const;
};