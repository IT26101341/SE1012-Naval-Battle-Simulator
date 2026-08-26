#include "core.h"
/* Convert the battleship letter into a name for menus and reports. */
const char *battle_name(int type)
{
    switch (type) {
        case 'U': return "USS Iowa (BB-61)";
        case 'M': return "MS King George V";
        case 'R': return "Richelieu";
        case 'S': return "Sovetsky Soyuz-class";
        default: return "Unknown battleship";
    }
}
/* Return the gun used by the selected battleship. */
const char *battle_gun(int type)
{
    switch (type) {
        case 'U': return "50-caliber Mark 7 gun";
        case 'M': return "356 mm Mark VII gun";
        case 'R': return "15 inch Mle 1935 gun";
        case 'S': return "16 inch B-37 gun";
        default: return "Unknown gun";
    }
}
/* Escort types use numbers from 0 to 4. */
const char *escort_name(int type)
{
    switch (type) {
        case 0: return "EA 1936A-class Destroyer";
        case 1: return "EB Gabbiano-class Corvette";
        case 2: return "EC Matsu-class Destroyer";
        case 3: return "ED F-class Escort Ship";
        case 4: return "EE Japanese Kaibokan";
        default: return "Unknown escort";
    }
}
/* Match each escort type with its gun name. */
const char *escort_gun(int type)
{
    switch (type) {
        case 0: return "SK C/34 naval gun";
        case 1: return "L/47 dual-purpose gun";
        case 2: return "Type 89 dual-purpose gun";
        case 3: return "SK C/32 naval gun";
        case 4: return "4.7 inch naval gun";
        default: return "Unknown gun";
    }
}
/* Give each assignment feature a readable title. */
const char *feature_name(int feature)
{
    switch (feature) {
        case PART_1A: return "Part 1-A: one hit damage";
        case PART_1C: return "Part 1-C: escort impact power";
        case PART_2A: return "Part 2-A: battleship reload";
        case PART_2B: return "Part 2-B: escort reload";
        case PART_2C: return "Part 2-C: degrading power";
        default: return "Unknown feature";
    }
}
/* Give each battlefield option a readable title. */
const char *field_name(int field)
{
    switch (field) {
        case STATIC_FIELD: return "Static battlefield";
        case PATH_FIELD: return "Battleship path";
        case JAM_FIELD: return "Jammed gun path";
        default: return "Unknown battlefield";
    }
}
