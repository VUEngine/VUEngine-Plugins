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

#ifndef SAVE_DATA_MANAGER_H_
#define SAVE_DATA_MANAGER_H_


//---------------------------------------------------------------------------------------------------------
//												INCLUDES
//---------------------------------------------------------------------------------------------------------

#include <Object.h>


//---------------------------------------------------------------------------------------------------------
//												MACROS
//---------------------------------------------------------------------------------------------------------

#define SAVE_STAMP			"VUEngine"
#define SAVE_STAMP_LENGTH	8


//---------------------------------------------------------------------------------------------------------
//											TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// forward declare game's custom save data struct
struct GameSaveData;

// this struct is never instantiated, its sole purpose is to determine offsets of its members.
// therefore it acts as kind of like a map of sram content.
typedef struct SaveData
{
	/// flag to know if there is data saved
	u8 saveStamp[SAVE_STAMP_LENGTH];

	/// checksum over sram content to prevent save data manipulation
	u32 checksum;

	/// active language id
	u8 languageId;

	/// auto pause status (0: on, 1: off)
	u8 autoPauseStatus;

	/// custom save data to be defined by the implementing game
//	GameSaveData gameSaveData;

} SaveData;


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

singleton class SaveDataManager : Object
{
	/// @protectedsection

	// flag that tells if sram is available on the current cartridge
	bool sramAvailable;


	/// @publicsection

	static SaveDataManager getInstance();
	bool getAutomaticPauseStatus();
	u8 getLanguage();
	void initialize();
	void setAutomaticPauseStatus(u8 autoPauseStatus);
	void setLanguage(u8 languageId);


	/// @privatesection

	void constructor();
	bool verifySaveStamp();
	u32 computeChecksum();
	void writeChecksum();
	bool verifyChecksum();
}


#endif
