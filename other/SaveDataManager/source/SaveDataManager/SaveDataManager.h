/**
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef SAVE_DATA_MANAGER_H_
#define SAVE_DATA_MANAGER_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <ListenerObject.h>
#include "../config.h"


//---------------------------------------------------------------------------------------------------------
//											TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// this struct is never instantiated, its sole purpose is to determine offsets of its members.
// therefore it acts as kind of like a map of sram content.
typedef struct SaveData
{
	// flag to know if there is data from this game saved
	uint8 saveStamp[__SAVE_DATA_MANAGER_SAVE_STAMP_LENGTH];

	// checksum over sram content to prevent save data manipulation
	uint32 checksum;

	// active language id
	uint8 languageId;

	// auto pause status (0: on, 1: off)
	uint8 autoPauseStatus;

} SaveData;


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

/**
 * Class that handles SRAM save data, including checksum mechanism to detect 
 * manipulation or corruption of such data. Easily extendable with custom data,
 * see VUEngine Barebone project for an example.
 */
singleton class SaveDataManager : ListenerObject
{
	// flag that tells if sram is available on the current cartridge
	bool sramAvailable;

	static SaveDataManager getInstance();
	void constructor();

	void getValue(BYTE* destination, int32 memberOffset, int32 dataSize);
	void setValue(const BYTE* const source, int32 memberOffset, int32 dataSize);
	bool verifyChecksum();
	void writeChecksum();
	virtual void writeDefaults();
	virtual int32 getSaveDataSize();

	// TODO: remove hard dependencies to i18n and auto pause plugins 
	// 		 and get rid of the following methods
	virtual void restoreSettings();
	bool getAutomaticPauseStatus();
	void setAutomaticPauseStatus(uint8 autoPauseStatus);
	uint8 getLanguage();
	void setLanguage(uint8 languageId);
}


#endif
