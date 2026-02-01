#pragma

#include "core/platform_detection.h"

#ifdef SO_PLATFORM_LINUX

#include <signal.h>

#endif

#include <memory.h>
#include <functional>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <filesystem>
#include <fstream>

#include "core/core.h"
