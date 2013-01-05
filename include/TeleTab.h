
#ifndef _game_TeleTab_h
#define _game_TeleTab_h

#include "Controller.h"

#include "model.h"

#include "Tab.h"
#include "CheckBox.h"
#include "NumberSprite.h"

class TeleTabController : public Controller {

public:
	
	TeleTabController(Controller* superController);
	
	~TeleTabController();
	
	void handleKey();
	
	void loadData(const TeleData& TeleInfo);
	
	void saveData(TeleData* TeleInfo);
	
	void set_Disabled(CheckBox* cb);
	
	void set_StixPU(NumberSprite* ns);
	
	void set_RScore(NumberSprite* ns);
	
	void set_TScore(NumberSprite* ns);
	
	void set_ZScore(NumberSprite* ns);
	
	void set_DisabledCounter(NumberSprite* ns);
	
private:

	Controller* mSuperController;
	
	CheckBox* Disabled;
	
	NumberSprite* StixPU;
	NumberSprite* RScore;
	NumberSprite* TScore;
	NumberSprite* ZScore;
	
	NumberSprite* DisabledCounter;
};

Tab* initTeleTab();

namespace nsTT
{
	bool wasTouched(CheckBox* cb);
}

#endif