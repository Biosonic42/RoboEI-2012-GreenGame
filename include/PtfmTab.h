
#ifndef _game_PtfmTab_h
#define _game_PtfmTab_h

#include "Controller.h"

#include "model.h"

#include "Tab.h"
#include "RadioButton.h"
#include "CheckBox.h"

class PtfmTabController : public Controller {

public:
	
	PtfmTabController(Controller* superController);
	
	~PtfmTabController();
	
	void handleKey();
	
	void loadData(const PtfmData& PtfmInfo);
	
	void saveData(PtfmData* PtfmInfo);
	
	void set_OnPlatform(CheckBox* cb);
	
	void set_PlatformEqual(CheckBox* cb);
	
	void set_StackAmount(RBGroup* rbg);
	
private:

	Controller* mSuperController;
	
	CheckBox* OnPlatform;
	CheckBox* PlatformEqual;
	RBGroup* StackAmount;
	
};

Tab* initPtfmTab();

#endif