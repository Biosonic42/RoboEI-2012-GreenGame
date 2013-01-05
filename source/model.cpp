
#include <PA9.h>
#include "main.h"
#include "model.h"

extern struct TeamList MatchList[kMaxMatches];

InitData::InitData()
: DSNum(readDS())
, MatchNum(readMatch())
, TeamNum(MatchList[MatchNum-1].RobotNo[DSNum-1])
, AllianceColor(DSNum < 4 && DSNum > 0 ? kRedAlliance : kBlueAlliance)
{
}

InitData::~InitData()
{
}

AutoData::AutoData()
: HasAuto(false)
, AutoStrategy(-1)
, RackP(0)
, TroughP(0)
, ZoneP(0)
{
}

AutoData::~AutoData()
{
}

TeleData::TeleData()
: Disabled(false)
, DisabledCounter(0)
, StixPU(0)
, RackP(0)
, TroughP(0)
, ZoneP(0)
{
}

TeleData::~TeleData()
{
}

PtfmData::PtfmData()
: OnPlatform(false)
, PlatformEqual(false)
, StackAmount(-1)
{
}

PtfmData::~PtfmData()
{
}

EndData::EndData()
: Defensive(false)
, Assistive(false)
, Penalties(0)
, YellowPenalty(false)
, RedPenalty(false)
, Finish(false)
{
}

EndData::~EndData()
{
}

GameData::GameData()
{
}

GameData::~GameData()
{
}

MatchData::MatchData()
{
}

MatchData::~MatchData()
{
}
