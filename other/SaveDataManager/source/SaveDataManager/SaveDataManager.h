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

#include <Object.h>
#include "../config.h"


//---------------------------------------------------------------------------------------------------------
//											TYPE DEFINITIONS
//---------------------------------------------------------------------------------------------------------

// this struct is never instantiated, its sole purpose is to determine offsets of its members.
// therefore it acts as kind of like a map of sram content.
typedef struct SaveData
{
	/// flag to know if there is data from this game saved
	uint8 saveStamp[__SAVE_DATA_MANAGER_SAVE_STAMP_LENGTH];

	/// checksum over sram content to prevent save data manipulation
	uint32 checksum;

	/// active language id
	uint8 languageId;

	/// auto pause status (0: on, 1: off)
	uint8 autoPauseStatus;

} SaveData;


//---------------------------------------------------------------------------------------------------------
//											CLASS'S DECLARATION
//---------------------------------------------------------------------------------------------------------

/**
 * Class that handles SRAM save data, including checksum mechanism to detect manipulation or corruption of
 * such data. Easily extendable with custom data, see VUEngine Barebone project for an example.
 *
 * @ingroup vuengine-plugins-other
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
	 * Class constructor.
	 */
	void constructor();

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
	uint8 getLanguage();

	/**
	 *
	 */
	virtual void restoreSettings();

	/**
	 * Write automatic pause status flag to SRAM.
	 *
	 * @param	autoPauseStatus		Automatic pause status flag
	 */
	void setAutomaticPauseStatus(uint8 autoPauseStatus);

	/**
	 * Write ID of currently active language to SRAM.
	 *
	 * @param	languageId	Language ID
	 */
	void setLanguage(uint8 languageId);

	/**
	 * Write given checksum to SRAM.
	 */
	void writeChecksum();

	/**
	 * Recompute checksum and compare to that stored in SRAM.
	 */
	bool verifyChecksum();

	/**
	 * Return size of SaveData
	 */
	virtual int32 getSaveDataSize();


	/// @privatesection

	/**
	 * Class destructor.
	 *
	 * @fn			void SaveDataManager::destructor()
     * @memberof 	SaveDataManager
	 */

	/**
	 * Read save stamp from SRAM and compare to game's stamp to verify that save is from this game.
	 *
	 * @fn			bool SaveDataManager::verifySaveStamp()
     * @memberof 	SaveDataManager
     * @return 	  	Valid save stamp found?
	 */

	/**
	 * Write then immediately read save stamp to check for SRAM presence and validity.
	 *
	 * @fn			bool SaveDataManager::checkSRAM()
     * @memberof 	SaveDataManager
     * @return 	  	SRAM detected?
	 */

	/**
	 * Computes a CRC32 checksum over whole SRAM content, starting right after the previously saved
	 * checksum's address.
	 *
	 * @fn			uint32 computeChecksum()
     * @memberof 	SaveDataManager
     * @return 	  	CRC32 checksum
	 */

	/**
	 *
	 *
	 * @fn			void initialize()
     * @memberof 	SaveDataManager
	 */

}


#endif
