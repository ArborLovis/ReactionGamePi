#pragma once

#if _WIN32 || _WIN64
#include "BlinkWin/winpi.h"
#else
#include <wiringPi.h>
#endif