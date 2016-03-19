#pragma once

#include "../Watchog.IPC/PluginState.hpp"
#include "bsp.h"
#include "plugins\bspplg.h"

#define ARRAY_ENTIRES(a)  (sizeof(a) / sizeof(*a))

#define BSPLUGIN_TITLE		"Watchog BSPlayer Plugin"
#define BSPLUGIN_ABOUT		"Written by Ronen Sandler"
#define LEFT_TIME_SEC		(90)			