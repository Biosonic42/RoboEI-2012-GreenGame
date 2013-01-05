
/////////////////////////////
//  C++ NDSRAF and RoboEI  //
/////////////////////////////


// Includes
#include <PA9.h>
#include <fat.h>
#include "all_gfx.h"

/// NDSRAF includes
#include "raguna.h"

#include "Controller.h"

#include "View.h"
#include "Control.h"

#include "Tab.h"
#include "CheckBox.h"
#include "RadioButton.h"
#include "NumberSprite.h"

/// game includes
#include "main.h"
#include "IncludeTabs.h"
#include "Controllers.h"

// constants
const char* kMatchesFilename = "matches.txt";
const char* kDSFilename = "DS.txt";
const char* kCurMatchFilename = "savedmatch.txt";

// globals
struct TeamList MatchList[kMaxMatches];

int main()
{
	//int maxMatches;
	PA_Init();
	PA_InitVBL();
	fatInitDefault();
	int curMatch = 1;
	int maxMatches = Loadmatches();
	printf("after Loadmatches();\n");
	
	MatchData MatchInfo;
	
	View PickUpStix;
	
	PickUpStix.add(initGameTabs());
	PickUpStix.add(initInfoTabs());

	while(true)
	{
		PickUpStix.show();
		
		loadMatch(MatchInfo);
		
		curMatch = readMatch();
		
		while(!endMatch() && !switchMatch(curMatch))
		{
			PickUpStix.handle();
			PickUpStix.draw();
			PickUpStix.update();
			
			PA_WaitForVBL();
		}
		
		if(endMatch())
		{
			saveMatch(&MatchInfo);
			writeInfo(&MatchInfo);
			writeMatch(MatchInfo.InitInfo.MatchNum+1);
		}
		
		if(readMatch() > maxMatches)
		{
			MatchInfo.InitInfo.MatchNum = 1;
			writeMatch(1);
		}
		
		
		PickUpStix.hide();
		
		MatchInfo = MatchData();
		
		PA_WaitForVBL();
	}
}

int Loadmatches()
{
	
	FILE* testRead = fopen (kMatchesFilename, "rb")	;	// rb = read mode
	int result = 0;
	int i = 0;
	
	if(testRead)	// loads data
	{
		while(i < kMaxMatches)
		{
			result = fscanf(testRead, "%d,%d,%d,%d,%d,%d,%d,\n\r",
			&MatchList[i].MatchNo,
			&MatchList[i].RobotNo[0],
			&MatchList[i].RobotNo[1],
			&MatchList[i].RobotNo[2],
			&MatchList[i].RobotNo[3],
			&MatchList[i].RobotNo[4],
			&MatchList[i].RobotNo[5]);
			
			if(result == EOF || !result)
				break;	
			
			++i;
		}
	}
	else			// cant load data
		printf("Unable to load data");
	
	fclose(testRead);
	
	return i;
	
}
	
void Loadrobotpic(int robotnum)
{
	//PA_InitText(1, 0);
	//PA_OutputText(1, 0, 23, "Team:%d", MatchList[MatchInfo.InitInfo.MatchNum-1].RobotNo[dsnumber-1] );
	
 	char* imgName = "Images/0000.gif";
	sprintf(imgName, "Images/%d.gif", robotnum);
	FILE* imgFile = fopen (imgName, "rb");

	if(imgFile)  // Make sure there is a file to load
	{
		PA_Init16bitBg(1, 1); /* Changed to 16 bit image */
		u32 imgSize;
		fseek (imgFile, 0, SEEK_END);
		imgSize = ftell (imgFile);
		rewind (imgFile);
		
		char * buffer;
		buffer = (char*) malloc (sizeof(char)*imgSize);
		fread (buffer, 1, imgSize, imgFile);
		
		// close the file
		fclose (imgFile);
		PA_LoadGif(1, (void *)buffer); // Show GIF on top screen
		free ((void *)buffer);
	} 
	else 
	{
		char* imgName = "Images/nopic.gif";
		FILE* imgFile = fopen (imgName, "rb");
		
		if(imgFile) // Make sure there is a file to load
		{
			PA_Init16bitBg(1, 1); /* Changed to 16 bit image */
			u32 imgSize;
			fseek (imgFile, 0, SEEK_END);
			imgSize = ftell (imgFile);
			rewind (imgFile);
			
			char * buffer;
			buffer = (char*) malloc (sizeof(char)*imgSize);
			fread (buffer, 1, imgSize, imgFile);
			
			// close the file
			fclose (imgFile);
			PA_LoadGif(1, (void *)buffer); // Show GIF on top screen
			free ((void *)buffer);
		}
	}
}

void writeInfo(MatchData* MatchInfo)
{
	FILE* dataFile = fopen("data.txt", "ab");
	fprintf(dataFile, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n",
	
	MatchInfo->InitInfo.MatchNum,
	MatchInfo->InitInfo.TeamNum,
	MatchInfo->InitInfo.AllianceColor,
	
	MatchInfo->GameInfo.AutoInfo.HasAuto,
	MatchInfo->GameInfo.AutoInfo.AutoStrategy,
	MatchInfo->GameInfo.AutoInfo.RackP,
	MatchInfo->GameInfo.AutoInfo.TroughP,
	MatchInfo->GameInfo.AutoInfo.ZoneP,
	
	MatchInfo->GameInfo.TeleInfo.DisabledCounter,
	MatchInfo->GameInfo.TeleInfo.StixPU,
	MatchInfo->GameInfo.TeleInfo.RackP,
	MatchInfo->GameInfo.TeleInfo.TroughP,
	MatchInfo->GameInfo.TeleInfo.ZoneP,
	
	MatchInfo->GameInfo.PtfmInfo.OnPlatform,
	MatchInfo->GameInfo.PtfmInfo.PlatformEqual,
	MatchInfo->GameInfo.PtfmInfo.StackAmount,
	
	MatchInfo->GameInfo.EndInfo.Defensive,
	MatchInfo->GameInfo.EndInfo.Assistive,
	MatchInfo->GameInfo.EndInfo.Penalties,
	MatchInfo->GameInfo.EndInfo.YellowPenalty,
	MatchInfo->GameInfo.EndInfo.RedPenalty);
	
	fclose(dataFile);
}

void loadMatch(const MatchData& MatchToLoad)
{
	using namespace Controllers;
	
	Super->loadData();
		gameTabsController->loadData(MatchToLoad.GameInfo);
			autoTabController->loadData(MatchToLoad.GameInfo.AutoInfo);
			teleTabController->loadData(MatchToLoad.GameInfo.TeleInfo);
			ptfmTabController->loadData(MatchToLoad.GameInfo.PtfmInfo);
			endTabController->loadData(MatchToLoad.GameInfo.EndInfo);
		infoTabsController->loadData(MatchToLoad);
			initTabController->loadData(MatchToLoad.InitInfo);
			
}

void saveMatch(MatchData* MatchToSave)
{
	using namespace Controllers;
	
	Super->saveData();
		gameTabsController->saveData(&MatchToSave->GameInfo);
			autoTabController->saveData(&MatchToSave->GameInfo.AutoInfo);
			teleTabController->saveData(&MatchToSave->GameInfo.TeleInfo);
			ptfmTabController->saveData(&MatchToSave->GameInfo.PtfmInfo);
			endTabController->saveData(&MatchToSave->GameInfo.EndInfo);
		
		infoTabsController->saveData(MatchToSave);
			initTabController->saveData(&MatchToSave->InitInfo);
	
}

int readMatch()
{
	int result = 0;
	int matchNum = 1;
	FILE* f = fopen(kCurMatchFilename, "rb");	// "rb" = read
	if(f)
	{
		result = fscanf(f, "%d\n\r", &matchNum);
	}
	fclose(f);
	return matchNum;
}

void writeMatch(int matchNum)
{
	int result = 0;
	FILE* f = fopen(kCurMatchFilename, "wb");	// "wb" = write
	if(f)
	{
		result = fprintf(f, "%d", matchNum);
	}
	fclose(f);
}

int readDS()
{
	int result = 0;
	int dsnumber = 1;
	FILE* f = fopen(kDSFilename, "rb");	// "rb" = read
	if(f)
	{
		result = fscanf(f, "%d\n\r", &dsnumber);
	}
	fclose(f);
	return dsnumber;
}

bool switchMatch(int referenceMatch)
{
	return (readMatch() != referenceMatch);
}