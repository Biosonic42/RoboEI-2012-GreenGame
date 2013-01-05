
#include <PA9.h>
#include "all_gfx.h"

#include "raguna.h"

#include "PtfmTab.h"
#include "model.h"

#include "Controller.h"
#include "RadioButton.h"
#include "CheckBox.h"

#include "Controllers.h"

PtfmTabController::PtfmTabController(Controller* superController)
: Controller(superController)
{
	mSuperController = superController;
}

PtfmTabController::~PtfmTabController()
{
}

void PtfmTabController::handleKey()
{
	
	if (mSuperController)
		mSuperController->handleKey();
}

void PtfmTabController::loadData(const PtfmData& PtfmInfo)
{
	OnPlatform->set_mFrame(PtfmInfo.OnPlatform);
	PlatformEqual->set_mFrame(PtfmInfo.PlatformEqual);
	StackAmount->set_CurRB(PtfmInfo.StackAmount);
}

void PtfmTabController::saveData(PtfmData* PtfmInfo)
{
	PtfmInfo->OnPlatform = OnPlatform->get_mFrame();
	PtfmInfo->PlatformEqual = PlatformEqual->get_mFrame();
	PtfmInfo->StackAmount = StackAmount->get_CurRB();
}

void PtfmTabController::set_OnPlatform(CheckBox* cb)
{
	OnPlatform = cb;
}

void PtfmTabController::set_PlatformEqual(CheckBox* cb)
{
	PlatformEqual = cb;
}

void PtfmTabController::set_StackAmount(RBGroup* rbg)
{
	StackAmount = rbg;
}

Tab* initPtfmTab()
{
	
	Tab* PtfmTab = new Tab(kBottomScreen, 128, 0, PtfmTab_Sprite, &FieldBackground, Controllers::ptfmTabController);
	
		CheckBox* OnPlatform = new CheckBox(kBottomScreen, 110, 82, OnPlatform_Sprite);
		
		PtfmTab->add(OnPlatform);
			Controllers::ptfmTabController->set_OnPlatform(OnPlatform);
			
		CheckBox* PlatformEqual = new CheckBox(kBottomScreen, 110, 130, PlatformEqual_Sprite);
		
		PtfmTab->add(PlatformEqual);
			Controllers::ptfmTabController->set_PlatformEqual(PlatformEqual);
		
		RBGroup* StackAmount = new RBGroup;
		
			RadioButton* OneBot = new RadioButton(kBottomScreen, 153, 68, One_Sprite);
			RadioButton* TwoBot = new RadioButton(kBottomScreen, 153, 100, Two_Sprite);
			RadioButton* ThreeBot = new RadioButton(kBottomScreen, 153, 132, Three_Sprite);
		
		StackAmount->add(OneBot);
		StackAmount->add(TwoBot);
		StackAmount->add(ThreeBot);
		
		PtfmTab->add(StackAmount);
			Controllers::ptfmTabController->set_StackAmount(StackAmount);
	
	return PtfmTab;
}