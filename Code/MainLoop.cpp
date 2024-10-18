/*
DEPRECATED
*/

#include "MainLoop.h"

MainLoop::MainLoop()
{
    ml_FramesPerSeconds = 60;
    ml_Running = false;
    ml_Code = SetupDisplay::NORMAL_REASON;
}


void MainLoop::Start(SetupDisplay& setupDisplay, BaseDisplayContext& bDisplayDriver)
{
    ml_Running = true;

    while (ml_Running) {
        setupDisplay.UpdateDisplay(bDisplayDriver);

        if (setupDisplay.IsRequestedDestroySetup() == true) {
            ml_Running = false;
        }
    }
}

int MainLoop::Stop(SetupDisplay& setupDisplay, BaseDisplayContext& bDisplayContext)
{
    setupDisplay.DestroyDisplay(bDisplayContext);

    return ml_Code;
}
