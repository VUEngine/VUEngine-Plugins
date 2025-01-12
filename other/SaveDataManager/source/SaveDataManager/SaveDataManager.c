/*
 * VUEngine Plugins Library
 *
 * © Jorge Eremiev <jorgech3@gmail.com> and Christian Radke <c.radke@posteo.de>
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// INCLUDES
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

#include <string.h>
#include <stddef.h>

#include <I18n.h>
#include <SRAMManager.h>
#include <Utilities.h>
#include <VUEngine.h>

#include "SaveDataManager.h"

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// DEFINITIONS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// The save data default values 
const SaveData SaveDataDefaults =
{
	// Save stamp
	__PLUGIN_SAVE_DATA_MANAGER_SAVE_STAMP,
	// Checksum
	0,
	// Active language id
	0,
	// Auto pause status (0: on, 1: off)
	0
};

//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// CLASS'S METHODS
//——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————

void SaveDataManager::constructor()
{
	// Always explicitly call the base's constructor 
	Base::constructor();

	// Init class variables
	this->sramAvailable = false;

	// Register with engine
	VUEngine::setSaveDataManager(ListenerObject::safeCast(this));

	// Initialize
	SaveDataManager::initialize(this);
}

void SaveDataManager::destructor()
{
	// Always explicitly call the base's destructor 
	Base::destructor();
}

bool SaveDataManager::verifySaveStamp()
{
	char saveStamp[__PLUGIN_SAVE_DATA_MANAGER_SAVE_STAMP_LENGTH];

	// Read save stamp
	SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&saveStamp, offsetof(struct SaveData, saveStamp), sizeof(saveStamp));

	return !strncmp(saveStamp, __PLUGIN_SAVE_DATA_MANAGER_SAVE_STAMP, __PLUGIN_SAVE_DATA_MANAGER_SAVE_STAMP_LENGTH);
}

bool SaveDataManager::checkSRAM()
{
	char saveStamp[__PLUGIN_SAVE_DATA_MANAGER_SAVE_STAMP_LENGTH];

	// Write save stamp
	SRAMManager::save
	(
		SRAMManager::getInstance(), (BYTE*)__PLUGIN_SAVE_DATA_MANAGER_SAVE_STAMP, offsetof(struct SaveData, saveStamp), sizeof(saveStamp)
	);

	return SaveDataManager::verifySaveStamp(this);
}

uint32 SaveDataManager::computeChecksum()
{
	uint32 crc32 = ~0;

	// Iterate over whole save data, starting right after the previously saved checksum
	int32 i = (offsetof(struct SaveData, checksum) + sizeof(crc32));
	int16 saveDataSize = SaveDataManager::getSaveDataSize(this);

	if(__PLUGIN_SAVE_DATA_MANAGER_CRC_CHECK_RANGE < saveDataSize)
	{
		saveDataSize = __PLUGIN_SAVE_DATA_MANAGER_CRC_CHECK_RANGE;
	}

	HardwareManager::suspendInterrupts();

	for(int16 limit = saveDataSize / sizeof(uint32); i < limit; i++)
	{
		// Get the current byte
		uint32 currentValue = 0;
		SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&currentValue, i, sizeof(currentValue));

		crc32 += currentValue ^ __PLUGIN_SAVE_DATA_MANAGER_CRC_MASK;
	}

	HardwareManager::resumeInterrupts();

	return ~crc32;
}

/*
 * Write given checksum to SRAM.
 */
void SaveDataManager::writeChecksum()
{
	uint32 checksum = SaveDataManager::computeChecksum(this);
	SRAMManager::save(SRAMManager::getInstance(), (BYTE*)&checksum, offsetof(struct SaveData, checksum), sizeof(checksum));
}

/*
 * Recompute checksum and compare to that stored in SRAM.
 */
bool SaveDataManager::verifyChecksum()
{
	uint32 computedChecksum = SaveDataManager::computeChecksum(this);
	uint32 savedChecksum = 0;
	SRAMManager::read(SRAMManager::getInstance(), (BYTE*)&savedChecksum, offsetof(struct SaveData, checksum), sizeof(savedChecksum));

	return (computedChecksum == savedChecksum);
}

void SaveDataManager::initialize()
{
	// First check if save data is from this game
	// (we have to do this before even checking for SRAM's existence because save stamp serves two
	// Purposes: marking a save as being from a certain game as well as checking for SRAM existence.
	// CheckSRAM() overwrites the previous save stamp, though.)
	bool saveIsFromThisGame = SaveDataManager::verifySaveStamp(this);

	// If existing save is from current game or sram is available
	if(saveIsFromThisGame || SaveDataManager::checkSRAM(this))
	{
		// Set sram available flag
		this->sramAvailable = true;

		// Verify saved progress presence and integrity
		if(!saveIsFromThisGame || !SaveDataManager::verifyChecksum(this))
		{
			// If no previous save could be verified, write default save values
			SaveDataManager::writeDefaults(this);

			// Write checksum
			SaveDataManager::writeChecksum(this);
		}
	}
}

void SaveDataManager::restoreSettings()
{
}

void SaveDataManager::writeDefaults()
{
	SRAMManager::save(SRAMManager::getInstance(), (BYTE*)&SaveDataDefaults, 0, sizeof(SaveDataDefaults));
}

void SaveDataManager::getValue(BYTE* destination, int32 memberOffset, int32 dataSize)
{
	if(this->sramAvailable)
	{
		SRAMManager::read(SRAMManager::getInstance(), destination, memberOffset, dataSize);
	}
}

void SaveDataManager::setValue(const BYTE* const source, int32 memberOffset, int32 dataSize)
{
	if(this->sramAvailable)
	{
		SRAMManager::save(SRAMManager::getInstance(), source, memberOffset, dataSize);
		SaveDataManager::writeChecksum(this);
	}
}

/*
 * Return overall size of save data
 *
 * Any game extending SaveData MUST override this method to return the correct value!
 */
int32 SaveDataManager::getSaveDataSize()
{
	return (int32)sizeof(SaveData);
}

uint8 SaveDataManager::getLanguage()
{
	uint8 languageId = 0;
	SaveDataManager::getValue(this, (BYTE*)&languageId, offsetof(struct SaveData, languageId), sizeof(languageId));

	return languageId;
}

void SaveDataManager::setLanguage(uint8 languageId)
{
	SaveDataManager::setValue(this, (BYTE*)&languageId, offsetof(struct SaveData, languageId), sizeof(languageId));
}

bool SaveDataManager::getAutomaticPauseStatus()
{

	uint8 autoPauseStatus = 0;
	SaveDataManager::getValue(this, (BYTE*)&autoPauseStatus, offsetof(struct SaveData, autoPauseStatus), sizeof(autoPauseStatus));

	return autoPauseStatus;
}

void SaveDataManager::setAutomaticPauseStatus(uint8 autoPauseStatus)
{
	// We save the inverted status, so that 0 = enabled, 1 = disabled.
	// That way, a blank value means enabled, which is the standard setting.
	autoPauseStatus = !autoPauseStatus;

	SaveDataManager::setValue(this, (BYTE*)&autoPauseStatus, offsetof(struct SaveData, autoPauseStatus), sizeof(autoPauseStatus));
}
