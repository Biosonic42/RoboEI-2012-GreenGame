
#include <PA9.h>
#include "all_gfx.h"

#include "raguna.h"

#include "AutoTab.h"
#include "model.h"

#include "Controller.h"
#include "NumberSprite.h"
#include "CheckBox.h"
#include "RadioButton.h"

#include "Controllers.h"


AutoTabController::AutoTabController(Controller* superController)
: Controller(superController)
{
	mSuperController = superController;
}

AutoTabController::~AutoTabController()
{
}

void AutoTabController::handleKey()
{
	
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
		
	if(HasAuto->get_mFrame() == false)
	{
		AutoStrategy->set_CurRB(-1);
		RScore->set_mFrame(0);
		TScore->set_mFrame(0);
		ZScore->set_mFrame(0);
	}
	
	if (mSuperController)
		mSuperController->handleKey();
}

void AutoTabController::loadData(const AutoData& AutoInfo)
{
	HasAuto->set_mFrame(AutoInfo.HasAuto);
	AutoStrategy->set_CurRB(AutoInfo.AutoStrategy);
	RScore->set_mFrame(AutoInfo.RackP);
	TScore->set_mFrame(AutoInfo.TroughP);
	ZScore->set_mFrame(AutoInfo.ZoneP);
}

void AutoTabController::saveData(AutoData* AutoInfo)
{
	AutoInfo->HasAuto = HasAuto->get_mFrame();
	AutoInfo->AutoStrategy = AutoStrategy->get_CurRB();
	AutoInfo->RackP = RScore->get_mFrame();
	AutoInfo->TroughP = TScore->get_mFrame();
	AutoInfo->ZoneP = ZScore->get_mFrame();
}

void AutoTabController::set_HasAuto(CheckBox* cb)
{
	HasAuto = cb;
}

void AutoTabController::set_AutoStrategy(RBGroup* rbg)
{
	AutoStrategy = rbg;
}

void AutoTabController::set_RScore(NumberSprite* ns)
{
	RScore = ns;
}

void AutoTabController::set_TScore(NumberSprite* ns)
{
	TScore = ns;
}

void AutoTabController::set_ZScore(NumberSprite* ns)
{
	ZScore = ns;
}

Tab* initAutoTab()
{
	Tab* AutoTab = new Tab(kBottomScreen, 0, 0, AutoTab_Sprite, &FieldBackground, Controllers::autoTabController);
	
		// checkboxes (Hybrid Type)
		CheckBox* HasAuto = new CheckBox(kBottomScreen, 170, 40, HasAuto_Sprite);
		
			AutoTab->add(HasAuto);
				Controllers::autoTabController->set_HasAuto(HasAuto);
		
		// special boxes (score type)
		
		RBGroup* AutoStrategy = new RBGroup();
		
			RadioButton* AutoDefense = new RadioButton(kBottomScreen, 32, 64, Defense_Sprite);
			RadioButton* AutoAssist = new RadioButton(kBottomScreen, 96, 64, AutoAssist_Sprite);
			RadioButton* Other = new RadioButton(kBottomScreen, 160, 64, Other_Sprite);
		
		AutoStrategy->add(AutoDefense);
		AutoStrategy->add(AutoAssist);
		AutoStrategy->add(Other);
		
			AutoTab->add(AutoStrategy);
				Controllers::autoTabController->set_AutoStrategy(AutoStrategy);
		
		// number_sprites (Score Locations)
		NumberSprite* RackScore = new NumberSprite(kBottomScreen, 140, 106, Rack_Sprite);
		NumberSprite* TroughScore = new NumberSprite(kBottomScreen, 140, 128, Trough_Sprite);
		NumberSprite* ZoneScore = new NumberSprite(kBottomScreen, 140, 150, Zone_Sprite);
		
			AutoTab->add(RackScore);
				Controllers::autoTabController->set_RScore(RackScore);
			
			AutoTab->add(TroughScore);
				Controllers::autoTabController->set_TScore(TroughScore);
			
			AutoTab->add(ZoneScore);
				Controllers::autoTabController->set_ZScore(ZoneScore);
	
	return AutoTab;
}