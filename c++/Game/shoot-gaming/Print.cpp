#include "Print.h"
#include <string>
#include <DxLib.h>
#include "Define.h"

using namespace std;

void Print::print(int x, int y, string name, int t)
{
	name += " : %d";
	DrawFormatString(x, y, GetColor(255, 255, 255), name.c_str(), t);
}

void Print::print(int x, int y, string name, double t)
{
	name += " : %f";
	DrawFormatString(x, y, GetColor(255, 255, 255), name.c_str(), t);
}

void Print::print(int x, int y, string name, string t)
{
	name += " : %s";
	DrawFormatString(x, y, GetColor(255, 255, 255), name.c_str(), t);
}