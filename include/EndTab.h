
#ifndef _game_EndTab_h
#define _game_EndTab_h

#include "Controller.h"

#include "model.h"

#include "Tab.h"
#include "NumberSprite.h"
#include "CheckBox.h"


class EndTabController : public Controller {

public:
	
	EndTabController(Controller* superController);
	
	~EndTabController();
	
	void handleKey();
	
	void loadData(const EndData& EndInfo);
	
	void saveData(EndData* EndInfo);
	
	void set_Defensive(CheckBox* cb);
	
	void set_Assistive(CheckBox* cb);
	
	void set_Penalties(NumberSprite* ns);
	
	void set_YellowPenalty(SpecialBox* sb);
	
	void set_RedPenalty(SpecialBox* sb);
	
	void set_Finish(SpecialBox* sb);
	
	bool getFinishFrame();
	
private:

	Controller* mSuperController;
	
	CheckBox* Defensive;
	CheckBox* Assistive;
	
	NumberSprite* Penalties;
	
	SpecialBox* YellowPenalty;
	SpecialBox* RedPenalty;
	SpecialBox* Finish;
	
};

Tab* initEndTab();

bool endMatch();

#endif