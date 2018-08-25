/* VUEngine - Virtual Utopia Engine <http://vuengine.planetvb.com/>
 * A universal game engine for the Nintendo Virtual Boy
 *
 * Copyright (C) 2007, 2018 by Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <chris@vr32.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <string.h>
#include <stddef.h>
#include <Game.h>
#include <I18n.h>
#include <SRAMManager.h>
#include <Utilities.h>
#include <AutoPauseManager.h>
#include <SaveDataManager.h>


//---------------------------------------------------------------------------------------------------------
//												CLASS'S METHODS
//---------------------------------------------------------------------------------------------------------

void SaveDataManager::constructor()
{
	// construct base object
	Base::constructor();

	// init class variables
	this->sramAvailable = false;

	// initialize
	SaveDataManager::initialize(this);
}

void SaveDataManager::destructor()
{
	// destroy base
	Base::destructor();
}

bool SaveDataManager::verifySaveStamp()
{
	char saveStamp[__SAVE_DATA_MANAGER_SAVE_STAMP_LENGTH];

	// write save stamp
	SRAMManager::save(SRAMManager::getInstance(), (BYTE*)__SAVE_DATA_MANAGER_SAVE_STAMP, offsetof(struct SaveData, saveStamp), sizeof(saveStamp));

	// read save stamp
	SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&saveStamp, offsetof(struct SaveData, saveStamp), sizeof(saveStamp));

	return !strncmp(saveStamp, __SAVE_DATA_MANAGER_SAVE_STAMP, __SAVE_DATA_MANAGER_SAVE_STAMP_LENGTH);
}

u32 SaveDataManager::computeChecksum()
{
	u32 crc32 = ~0;

	// iterate over whole save data, starting right after the previously saved checksum
	int i = (offsetof(struct SaveData, checksum) + sizeof(crc32));
	for(; i < (int)sizeof(SaveData); i++)
	{
		// get the current byte
		u8 currentByte;
		SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&currentByte, i, sizeof(currentByte));

		// loop over all bits of the current byte and add to checksum
		u8 bit = 0;
		for(; bit < sizeof(currentByte); bit++)
		{
			if((crc32 & 1) != GET_BIT(currentByte, bit))
			{
				crc32 = (crc32 >> 1) ^ 0xEDB88320;
			}
			else
			{
				crc32 = (crc32 >> 1);
			}
		}
	}

	return ~crc32;
}

void SaveDataManager::writeChecksum()
{
	u32 checksum = SaveDataManager::computeChecksum(this);
	SRAMManager::save(SRAMManager::getInstance(), (BYTE*)&checksum, offsetof(struct SaveData, checksum), sizeof(checksum));
}

bool SaveDataManager::verifyChecksum()
{
	u32 computedChecksum = SaveDataManager::computeChecksum(this);
	u32 savedChecksum = 0;
	SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&savedChecksum, offsetof(struct SaveData, checksum), sizeof(savedChecksum));

	return (computedChecksum == savedChecksum);
}

void SaveDataManager::initialize()
{
	// verify sram validity
	if(SaveDataManager::verifySaveStamp(this))
	{
		// set sram available flag
		this->sramAvailable = true;

		// verify saved progress presence and integrity
		if(!SaveDataManager::verifyChecksum(this))
		{
			// if no previous save could be verified, completely erase sram to start clean
			SRAMManager::clear(SRAMManager::getInstance(), offsetof(struct SaveData, checksum), (int)sizeof(SaveData));

			// write checksum
			SaveDataManager::writeChecksum(this);
		}
	}
}

void SaveDataManager::restoreSettings()
{
	if(this->sramAvailable)
	{
		// load and set active language
		I18n::setActiveLanguage(I18n::getInstance(), SaveDataManager::getLanguage(this));

		// load and set auto pause state
		AutoPauseManager::setActive(AutoPauseManager::getInstance(), SaveDataManager::getAutomaticPauseStatus(this));
	}
}

u8 SaveDataManager::getLanguage()
{
	u8 languageId = 0;
	if(this->sramAvailable)
	{
		SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&languageId, offsetof(struct SaveData, languageId), sizeof(languageId));
	}

	return languageId;
}

void SaveDataManager::setLanguage(u8 languageId)
{
	if(this->sramAvailable)
	{
		// write language
		SRAMManager::save(SRAMManager::getInstance(), (BYTE*)&languageId, offsetof(struct SaveData, languageId), sizeof(languageId));

		// write checksum
		SaveDataManager::writeChecksum(this);
	}
}

bool SaveDataManager::getAutomaticPauseStatus()
{

	u8 autoPauseStatus = 0;
	if(this->sramAvailable)
	{
		SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&autoPauseStatus, offsetof(struct SaveData, autoPauseStatus), sizeof(autoPauseStatus));
	}

	return !autoPauseStatus;
}

void SaveDataManager::setAutomaticPauseStatus(u8 autoPauseStatus)
{
	if(this->sramAvailable)
	{
		// we save the inverted status, so that 0 = enabled, 1 = disabled.
		// that way, a blank value means enabled, which is the standard setting.
		autoPauseStatus = !autoPauseStatus;

		// write auto pause status
		SRAMManager::save(SRAMManager::getInstance(), (BYTE*)&autoPauseStatus, offsetof(struct SaveData, autoPauseStatus), sizeof(autoPauseStatus));

		// write checksum
		SaveDataManager::writeChecksum(this);
	}
}
