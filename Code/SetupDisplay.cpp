#include "SetupDisplay.h"

SetupDisplay::SetupDisplay()
{
	rq_DestroySetup = false;
	rs_DestroySetup = CodeDestroyReasons::NORMAL_REASON;
}

void SetupDisplay::InitDisplay(BaseDisplayContext& bDisplayContext)
{
}

void SetupDisplay::InitGraphics(TypeDisplayDriver& tDisplayDriver)
{
}

void SetupDisplay::UpdateDisplay(BaseDisplayContext& bDisplayContext)
{
}

void SetupDisplay::UpdateGraphics(TypeDisplayDriver& tDisplayDriver)
{
}

void SetupDisplay::DestroyGraphics(TypeDisplayDriver& tDisplayDriver)
{
}

void SetupDisplay::DestroyDisplay(BaseDisplayContext& bDisplayContext)
{
}

bool SetupDisplay::RequestedDestroySetup() const
{
	return rq_DestroySetup;
}

SetupDisplay::CodeDestroyReasons SetupDisplay::GetDestroyReason() const
{
	return rs_DestroySetup;
}
