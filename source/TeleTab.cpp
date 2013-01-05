
#include <PA9.h>
#include "all_gfx.h"

#include "raguna.h"

#include "TeleTab.h"
#include "model.h"

#include "Controller.h"
#include "NumberSprite.h"
#include "CheckBox.h"

#include "Controllers.h"

TeleTabController::TeleTabController(Controller* superController)
: Controller(superController)
, DisabledCounter(0)
{
	mSuperController = superController;
}

TeleTabController::~TeleTabController()
{
}

void TeleTabController::handleKey()
{
	if(!Disabled->get_mFrame())
	{
		if(Pad.Held.L && Pad.Newpress.Y)
		{
			StixPU->dec_mFrame();
			if(StixPU->get_mFrame() < 0)
				StixPU->set_mFrame(0);
		}
		else if(Pad.Newpress.Y)
		{
			StixPU->inc_mFrame();
		}
		
		if(Pad.Held.L && Pad.Newpress.X)
		{
			RScore->dec_mFrame();
			if(RScore->get_mFrame() < 0)
				RScore->set_mFrame(0);
		}
		else if(Pad.Newpress.X)
		{
			RScore->inc_mFrame();
		}
		
		if(Pad.Held.L && Pad.Newpress.A)
		{
			TScore->dec_mFrame();
			if(TScore->get_mFrame() < 0)
				TScore->set_mFrame(0);
		}
		else if(Pad.Newpress.A)
		{
			TScore->inc_mFrame();
		}
		
		if(Pad.Held.L && Pad.Newpress.B)
		{
			ZScore->dec_mFrame();
			if(ZScore->get_mFrame() < 0)
				ZScore->set_mFrame(0);
		}
		else if(Pad.Newpress.B)
		{
			ZScore->inc_mFrame();
		}
	}
	else
	{
	}
	
	// handle the Disabled Counter
	if(Stylus.Released && nsTT::wasTouched(Disabled))
	{
		PA_WaitForVBL();
		if(Disabled->get_mFrame())
			DisabledCounter->inc_mFrame();	
		if(Pad.Held.L && DisabledCounter->get_mFrame() > 0)
			DisabledCounter->dec_mFrame();
	}
	
	if (mSuperController)
		mSuperController->handleKey();
}

void TeleTabController::loadData(const TeleData& TeleInfo)
{
	Disabled->set_mFrame(TeleInfo.Disabled);
	DisabledCounter->set_mFrame(TeleInfo.DisabledCounter);
	StixPU->set_mFrame(TeleInfo.StixPU);
	RScore->set_mFrame(TeleInfo.RackP);
	TScore->set_mFrame(TeleInfo.TroughP);
	ZScore->set_mFrame(TeleInfo.ZoneP);
}

void TeleTabController::saveData(TeleData* TeleInfo)
{
	TeleInfo->Disabled = Disabled->get_mFrame();
	TeleInfo->DisabledCounter = DisabledCounter->get_mFrame();
	TeleInfo->StixPU = StixPU->get_mFrame();
	TeleInfo->RackP = RScore->get_mFrame();
	TeleInfo->TroughP = TScore->get_mFrame();
	TeleInfo->ZoneP = ZScore->get_mFrame();
}

void TeleTabController::set_Disabled(CheckBox* cb)
{
	Disabled = cb;
}

void TeleTabController::set_StixPU(NumberSprite* ns)
{
	StixPU = ns;
}

void TeleTabController::set_RScore(NumberSprite* ns)
{
	RScore = ns;
}

void TeleTabController::set_TScore(NumberSprite* ns)
{
	TScore = ns;
}

void TeleTabController::set_ZScore(NumberSprite* ns)
{
	ZScore = ns;
}

void TeleTabController::set_DisabledCounter(NumberSprite* ns)
{
	DisabledCounter = ns;
}


Tab* initTeleTab()
{	
	Tab* TeleTab = new Tab(kBottomScreen, 64, 0, TeleTab_Sprite, &FieldBackground, Controllers::teleTabController);
	
		// checkboxes (If Occured)
		CheckBox* Disabled = new CheckBox(kBottomScreen, 137, 44, Disabled_Sprite);
		
			TeleTab->add(Disabled);
				Controllers::teleTabController->set_Disabled(Disabled);
		
		// number sprites (Score Locations and Balls PU)
		NumberSprite* StixPU = new NumberSprite(kBottomScreen, 100, 127, StixPickedUp_Sprite);
		NumberSprite* RackScoreTele = new NumberSprite(kBottomScreen, 218, 100, Rack_Sprite);
		NumberSprite* TroughScoreTele = new NumberSprite(kBottomScreen, 218, 127, Trough_Sprite);
		NumberSprite* ZoneScoreTele = new NumberSprite(kBottomScreen, 218, 154, Zone_Sprite);
		
			TeleTab->add(StixPU);
				Controllers::teleTabController->set_StixPU(StixPU);
			
			TeleTab->add(RackScoreTele);
				Controllers::teleTabController->set_RScore(RackScoreTele);
			
			TeleTab->add(TroughScoreTele);
				Controllers::teleTabController->set_TScore(TroughScoreTele);
			
			TeleTab->add(ZoneScoreTele);
				Controllers::teleTabController->set_ZScore(ZoneScoreTele);
		
		// disabled counter display
		NumberSprite* DisabledCounter = new NumberSprite(kBottomScreen, 170, 44, BlankTitle_Sprite);
			
			TeleTab->add(DisabledCounter);
				Controllers::teleTabController->set_DisabledCounter(DisabledCounter);

	return TeleTab;
}

namespace nsTT
{
	bool wasTouched(CheckBox* cb)
	{
		return ((PA_SpriteStylusOver(cb->get_mSpriteNum())||PA_SpriteStylusOver(cb->get_mTitleSpriteNum()))&& cb->get_mScreen() == kBottomScreen);
	}
}