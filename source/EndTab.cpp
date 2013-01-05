
#include <PA9.h>
#include "all_gfx.h"

#include "raguna.h"
#include "model.h"

#include "EndTab.h"

#include "Controller.h"
#include "NumberSprite.h"
#include "CheckBox.h"

#include "Controllers.h"

EndTabController::EndTabController(Controller* superController)
: Controller(superController)
{
	mSuperController = superController;
}

EndTabController::~EndTabController()
{
}

void EndTabController::handleKey()
{
	if(Pad.Held.L && Pad.Newpress.A)
	{
		Penalties->dec_mFrame();
		if(Penalties->get_mFrame() < 0)
			Penalties->set_mFrame(0);
	}
	else if(Pad.Newpress.A)
	{
		Penalties->inc_mFrame();
	}
	
	if (mSuperController)
		mSuperController->handleKey();
}

void EndTabController::loadData(const EndData& EndInfo)
{
	Defensive->set_mFrame(EndInfo.Defensive);
	Assistive->set_mFrame(EndInfo.Assistive);
	Penalties->set_mFrame(EndInfo.Penalties);
	YellowPenalty->set_mFrame(EndInfo.YellowPenalty);
	RedPenalty->set_mFrame(EndInfo.RedPenalty);
	Finish->set_mFrame(EndInfo.Finish);
}

void EndTabController::saveData(EndData* EndInfo)
{
	EndInfo->Defensive = Defensive->get_mFrame();
	EndInfo->Assistive = Assistive->get_mFrame();
	EndInfo->Penalties = Penalties->get_mFrame();
	EndInfo->YellowPenalty = YellowPenalty->get_mFrame();
	EndInfo->RedPenalty = RedPenalty->get_mFrame();
}

void EndTabController::set_Defensive(CheckBox* cb)
{
	Defensive = cb;
}

void EndTabController::set_Assistive(CheckBox* cb)
{
	Assistive = cb;
}

void EndTabController::set_Penalties(NumberSprite* ns)
{
	Penalties = ns;
}

void EndTabController::set_YellowPenalty(SpecialBox* sb)
{
	YellowPenalty = sb;
}

void EndTabController::set_RedPenalty(SpecialBox* sb)
{
	RedPenalty = sb;
}

void EndTabController::set_Finish(SpecialBox* sb)
{
	Finish = sb;
}

bool EndTabController::getFinishFrame()
{
	return Finish->get_mFrame();
}

Tab* initEndTab()
{
	Tab* EndTab = new Tab(kBottomScreen, 192, 0, EndTab_Sprite, &FieldBackground, Controllers::endTabController);
	
		CheckBox* Defensive = new CheckBox(kBottomScreen, 100, 50, Defensive_Sprite);
		
			EndTab->add(Defensive);
				Controllers::endTabController->set_Defensive(Defensive);
		
		CheckBox* Assistive = new CheckBox(kBottomScreen, 200, 50, Assistive_Sprite);
		
			EndTab->add(Assistive);
				Controllers::endTabController->set_Assistive(Assistive);
				
		NumberSprite* Penalties = new NumberSprite(kBottomScreen, 152, 82, Penalties_Sprite);
		
			EndTab->add(Penalties);
				Controllers::endTabController->set_Penalties(Penalties);
	
		SpecialBox* YellowPenalty = new SpecialBox(kBottomScreen, 146, 114, yellow_penalty_Sprite);
		
			EndTab->add(YellowPenalty);
				Controllers::endTabController->set_YellowPenalty(YellowPenalty);
		
		SpecialBox* RedPenalty = new SpecialBox(kBottomScreen, 42, 114, red_penalty_Sprite);
		
			EndTab->add(RedPenalty);
				Controllers::endTabController->set_RedPenalty(RedPenalty);
		
		SpecialBox* Finish = new SpecialBox(kBottomScreen, 96, 156, Finish_Sprite);
		
			EndTab->add(Finish);
				Controllers::endTabController->set_Finish(Finish);
	
	return EndTab;
}

bool endMatch()
{
	return Controllers::endTabController->getFinishFrame();
}