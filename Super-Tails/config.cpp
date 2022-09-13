#include "stdafx.h"

int CurrentSuperMusic = Random;
int CurrentSFX = SADX_SFX;
bool AnimationTransfo = true;
bool RemoveLimitations = false;
bool AlwaysSuperMiles = false;
bool superAura = true;
bool customPhysics = true;
bool textureChanges = true;

Buttons TransformButton = Buttons_Y;

static const Buttons ButtonsList[]
{
	Buttons_B,
	Buttons_Y,
	Buttons_X,
};

void initConfig(const char* path)
{
	//Ini file configuration
	const IniFile* config = new IniFile(std::string(path) + "\\config.ini");

	textureChanges = config->getBool("General", "textureChanges", true);
	TransformButton = ButtonsList[config->getInt("General", "TransformButton", 1)];
	AnimationTransfo = config->getBool("General", "AnimationTransfo", true);
	RemoveLimitations = config->getBool("General", "RemoveLimitations", false);
	AlwaysSuperMiles = config->getBool("General", "AlwaysSuperMiles", false);
	superAura = config->getBool("General", "superAura", true);
	customPhysics = config->getBool("General", "customPhysics", true);

	CurrentSuperMusic = config->getInt("Audio", "CurrentSuperMusic", Random);
	CurrentSFX = config->getInt("Audio", "GetVoice", SADX_SFX);
	delete config;
}