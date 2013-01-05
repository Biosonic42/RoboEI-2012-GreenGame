
#include "Controllers.h"

#include "IncludeTabs.h"

namespace Controllers
{
	Controller* Super = new Controller(NULL);
		GameTabsController* gameTabsController = new GameTabsController(Super);
			AutoTabController* autoTabController = new AutoTabController(gameTabsController);
			TeleTabController* teleTabController = new TeleTabController(gameTabsController);
			PtfmTabController* ptfmTabController = new PtfmTabController(gameTabsController);
			EndTabController* endTabController = new EndTabController(gameTabsController);
		InfoTabsController* infoTabsController = new InfoTabsController(Super);
			InitTabController* initTabController = new InitTabController(infoTabsController);
}