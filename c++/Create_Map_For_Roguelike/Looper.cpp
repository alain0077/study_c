#include "Looper.h"
#include "AreaDivisionMethod.h"

#include <DxLib.h>

using namespace std;

Looper::Looper()
{
	_method.push(make_shared<AreaDivisionMethod>());
}

bool Looper::update()
{
	if (!_method.size()) return false;

	return true;
}