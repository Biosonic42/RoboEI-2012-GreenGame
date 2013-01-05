
#ifndef _game_AutoTab_h
#define _game_AutoTab_h

#include "Controller.h"

#include "model.h"

#include "Tab.h"
#include "CheckBox.h"
#include "NumberSprite.h"
#include "RadioButton.h"

class AutoTabController : public Controller {

public:
	
	AutoTabController(Controller* superController);
	
	~AutoTabController();
	
	void handleKey();
	
	void loadData(const AutoData& AutoInfo);
	
	void saveData(AutoData* AutoInfo);
	
	void set_HasAuto(CheckBox* cb);
	
	void set_AutoStrategy(RBGroup* rbg);
	
	void set_RScore(NumberSprite* ns);
	
	void set_TScore(NumberSprite* ns);
	
	void set_ZScore(NumberSprite* ns);
	
private:

	Controller* mSuperController;
	
	CheckBox* HasAuto;
	
	RBGroup* AutoStrategy;
	
	NumberSprite* RScore;
	NumberSprite* TScore;
	NumberSprite* ZScore;
};

Tab* initAutoTab();

#endif