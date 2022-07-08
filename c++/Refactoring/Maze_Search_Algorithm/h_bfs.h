#pragma once

#include <list>
#include "Abstract.h"

struct H_bfs_Coor
{
	int x;
	int y;
	int dict;
	int cost;
	// manhattan distance
	int man_d;
};



class H_bfs : public Abstract
{
public:
	H_bfs(Map_Info map);
	~H_bfs() = default;
	void update() override;
	void draw() const override;
	void finalize() override;

private:
	// best first search
	void bfs();

	int _cost;

	//list for bfs saved branch
	std::list<H_bfs_Coor> _branch;

	// sort branch about man_d
	void branch_sort();

	// calculate man_d
	int man_d(int x, int y);

	// jubge whether it's road
	bool judge_road(int) const;

	// judge whether searching coordinates is branch
	bool judge_branch();

};
