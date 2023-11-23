/**
 * VUEngine Plugins Library
 *
 * (c) Christian Radke and Jorge Eremiev
 *
 * For the full copyright and license information, please view the LICENSE file
 * that was distributed with this source code.
 */

#ifndef POST_PROCESSING_DWARF_PLANET_CONFIG_H_
#define POST_PROCESSING_DWARF_PLANET_CONFIG_H_


//---------------------------------------------------------------------------------------------------------
//											CONFIGURATION MACROS
//---------------------------------------------------------------------------------------------------------

#ifndef __DWARF_PLANET_STARTING_ROW
#define __DWARF_PLANET_STARTING_ROW		(0)
#endif

#ifdef __DWARF_PLANET_ENDING_ROW
#define __DWARF_PLANET_ENDING_ROW		(__SCREEN_HEIGHT)
#endif

#ifndef __DWARF_PLANET_STARTING_COLUMN
#define __DWARF_PLANET_STARTING_COLUMN	(0)
#endif

#ifdef __DWARF_PLANET_ENDING_COLUMN
#define __DWARF_PLANET_ENDING_COLUMN	(__SCREEN_WIDTH)
#endif


#endif


