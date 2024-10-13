#include <iostream>

#include "MainLoop.h"

int main() {
	BaseDisplayContext displayContext;
	TypeDisplayDriver displayDriver;

	/*Default*/
	displayDriver = OpenGLDisplayDriver{};

	/*Setup Frames*/
	SetupDisplay setupDisplay;
	setupDisplay.InitDisplay(displayContext);
	setupDisplay.InitGraphics(displayDriver);

	/*Setup Main Loop*/
	MainLoop mainLoop;
	mainLoop.Start(setupDisplay, displayContext, displayDriver);

	return mainLoop.Stop(setupDisplay, displayContext, displayDriver);
}