#include "MainLoop.h"

MainLoop::MainLoop()
{
	ml_FramesPerSeconds = 60;
	ml_Running = false;
	ml_Code = SetupDisplay::NORMAL_REASON;
}


void MainLoop::Start(SetupDisplay& setupDisplay, BaseDisplayContext& bDisplayDriver, TypeDisplayDriver& tDisplayDriver)
{
	ml_Running = true;

	while (ml_Running) {
		setupDisplay.UpdateDisplay(bDisplayDriver);
		setupDisplay.UpdateGraphics(tDisplayDriver);

		if (setupDisplay.RequestedDestroySetup() == true) {
			ml_Running = false;
		}
	}
}

int MainLoop::Stop(SetupDisplay& setupDisplay, BaseDisplayContext& bDisplayContext, TypeDisplayDriver& tDisplayDriver)
{
	setupDisplay.DestroyGraphics(tDisplayDriver);
	setupDisplay.DestroyDisplay(bDisplayContext);

	return ml_Code;
}
