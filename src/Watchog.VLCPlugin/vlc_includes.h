#pragma once

#pragma warning(push, 0)   

#define __PLUGIN__
#define MODULE_STRING "watchog"

#define LIBVLC_USE_PTHREAD_CANCEL 1
typedef __int64 ssize_t;

#include <vlc_common.h>
#include <vlc_plugin.h>
#include <vlc_variables.h>
#include <vlc_input.h>
#include <vlc_url.h>
#include "vlc_interface.h"

#pragma warning(pop)