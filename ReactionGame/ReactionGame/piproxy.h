#pragma once

#if _WIN32 || _WIN64
#include "../Blink_win32/winpi.h"
#else
#include <wiringPi.h>
#endif