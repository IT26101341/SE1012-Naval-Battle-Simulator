#ifndef CORE_H
#define CORE_H

#include "types.h"

/* Safe keyboard input functions used by all menus. */
int read_int(const char *message, int minimum, int maximum);
double read_double(const char *message, double minimum, double maximum);
char read_ship_type(const char *message);
int read_yes_no(const char *message);

/* ASCII-art headings for the different screens. */
void show_title_art(void);
void show_main_menu_art(void);
void show_start_menu_art(void);
void show_field_menu_art(void);
void show_ship_choice_art(void);
void show_setup_art(void);
void show_setup_menu_art(void);
void show_help_art(void);
void show_stats_art(void);
void show_exit_art(void);

/* Turn stored type numbers or letters into readable names. */
const char *battle_name(int type);
const char *battle_gun(int type);
const char *escort_name(int type);
const char *escort_gun(int type);
const char *feature_name(int feature);
const char *field_name(int field);

/* Create, change and display the game setup. */
void set_default_game(Game *game);
void set_ship_properties(Game *game);
void generate_battlefield(Game *game);
void generate_path(Game *game);
void reset_combat(Game *game);
void first_setup(Game *game);
void edit_setup(Game *game);
void show_setup(const Game *game);

/* Shared calculations used while selecting and firing at targets. */
double position_distance(Position first, Position second);
int find_shot(Position start, Position end, double minSpeed,
              double maxSpeed, double minAngle, double maxAngle,
              double *flightTime, double *usedAngle);
double degraded_power(double startPower, double gamma, int shotNumber);
double pending_damage(const Game *game, int escortIndex);
int choose_target(const Game *game, int feature, double minAngle,
                  double *flightTime);

#endif
