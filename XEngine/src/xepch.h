#pragma once

#include "XEngine/Core/PlatformDetection.h"

#ifdef XE_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
	#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

#include "XEngine/Core/Base.h"

#include "XEngine/Core/Log.h"

#include "XEngine/Debug/Instrumentor.h"

#ifdef XE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif