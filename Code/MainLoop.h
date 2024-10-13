#pragma once

#include "SetupDisplay.h"

class MainLoop
{
private:
	bool ml_Running;

	SetupDisplay::CodeDestroyReasons ml_Code;

public:
	unsigned short ml_FramesPerSeconds;

	MainLoop();
	
	void Start(SetupDisplay& steupDisplay, BaseDisplayContext& bDisplayContext, TypeDisplayDriver& tDisplayDriver);
	int  Stop(SetupDisplay& setupDisplay, BaseDisplayContext& bDisplayContext, TypeDisplayDriver& tDisplayDriver);
};

