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

} SaveData;


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

/**
 * Class that handles SRAM save data, including checksum mechanism to detect manipulation or corruption of
 * such data. Easily extendable with custom data, see VUEngine Barebone project for an example.
 *
 * @ingroup vuengine-components-other
 */
singleton class SaveDataManager : Object
{
	/// @protectedsection

	// flag that tells if sram is available on the current cartridge
	bool sramAvailable;


	/// @publicsection

	/**
	 * Get instance.
	 *
	 * @return	SaveDataManager instance
	 */
	static SaveDataManager getInstance();

	/**
	 * Retrieve automatic pause status flag.
	 *
	 * @return	flag
	 */
	bool getAutomaticPauseStatus();

	/**
	 * Retrieve ID of currently active language.
	 *
	 * @return	Language ID
	 */
	u8 getLanguage();

	/**
	 *
	 */
	void initialize();

	/**
	 * Write automatic pause status flag to SRAM.
	 *
	 * @param	autoPauseStatus		Automatic pause status flag
	 */
	void setAutomaticPauseStatus(u8 autoPauseStatus);

	/**
	 * Write ID of currently active language to SRAM.
	 *
	 * @param	languageId	Language ID
	 */
	void setLanguage(u8 languageId);


	/// @privatesection

	/**
	 * Class constructor.
	 *
	 * @fn 			void SaveDataManager::constructor()
     * @memberof 	SaveDataManager
	 */

	/**
	 * Class destructor.
	 *
	 * @fn			void SaveDataManager::destructor()
     * @memberof 	SaveDataManager
	 */

	/**
	 * Write then immediately read save stamp to check for SRAM presence and validity.
	 *
	 * @fn			bool SaveDataManager::verifySaveStamp()
     * @memberof 	SaveDataManager
     * @return 	  	Valid save stamp found?
	 */

	/**
	 * Computes a CRC32 checksum over whole SRAM content, starting right after the previously saved
	 * checksum's address.
	 *
	 * @fn			u32 computeChecksum()
     * @memberof 	SaveDataManager
     * @return 	  	CRC32 checksum
	 */

	/**
	 * Write given checksum to SRAM.
	 *
	 * @fn			void SaveDataManager::writeChecksum()
     * @memberof 	SaveDataManager
	 */

	/**
	 * Recompute checksum and compare to that stored in SRAM.
	 *
	 * @fn			bool SaveDataManager::verifyChecksum()
     * @memberof	SaveDataManager
     * @return 	  	Valid checksum found?
	 */
}


#endif
