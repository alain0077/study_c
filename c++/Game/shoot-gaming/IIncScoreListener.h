#pragma once
#include <iostream>
#include <vector>

class IIncScoreListener
{
public:
	IIncScoreListener() = default;
	virtual ~IIncScoreListener() = default;

	// Add N to the score.
	virtual void IncScore(int n) = 0;
};