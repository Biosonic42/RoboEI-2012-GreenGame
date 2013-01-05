
#ifndef _game_Model_h
#define _game_Model_h

struct InitData
{
	InitData();
	
	~InitData();
	
	int DSNum;
	int MatchNum;
	int TeamNum;
	bool AllianceColor;
	
};

struct AutoData
{
	AutoData();
	
	~AutoData();
	
	bool HasAuto;
	int AutoStrategy;
	int RackP;
	int TroughP;
	int ZoneP;
	
};

struct TeleData
{
	TeleData();
	
	~TeleData();
	
	bool Disabled;
	int DisabledCounter;
	int StixPU;
	int RackP;
	int TroughP;
	int ZoneP;

};

struct PtfmData
{
	PtfmData();
	
	~PtfmData();
	
	bool OnPlatform;
	bool PlatformEqual;
	int StackAmount;

};

struct EndData
{
	EndData();
	
	~EndData();
	
	bool Defensive;
	bool Assistive;
	int Penalties;
	bool YellowPenalty;
	bool RedPenalty;
	bool Finish;
	
};
	
struct GameData
{
	GameData();
	
	~GameData();
	
	AutoData AutoInfo;
	TeleData TeleInfo;
	PtfmData PtfmInfo;
	EndData EndInfo;

};

struct MatchData
{
	MatchData();
	
	~MatchData();
	
	InitData InitInfo;
	GameData GameInfo;
	
};

#endif
