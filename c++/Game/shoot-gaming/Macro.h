#pragma once

#include "Error.h"
#include "Print.h"
#include <Dxlib.h>

#define ERR(str) Error::finish(str,_T(__FUNCTION__),__LINE__)
#define DBG(x, y, t) Print::print(x, y, #t, t)