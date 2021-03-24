#pragma once
#include "types.h"

// Basic dynamic movement behavior interface
class DynamicBehavior {

public:

	// All dynamic movement behavior must support getting dynamic output
	virtual dynamicOutput getDynamicSteering() = 0;
};