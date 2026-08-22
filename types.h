#ifndef TYPES_H
#define TYPES_H
/* Limits keep the fixed-size arrays below a known maximum. */
#define MAX_ESCORTS 40
#define MAX_PATH 10
#define MAX_ACTIVE_SHOTS 1024
#define MAX_ATTACKS 1024
#define GRAVITY 9.81
#define PI 3.1415926535
/* Feature choices represent the assignment sections. */
enum FeatureLevel {
    PART_1A = 1,
    PART_1C,
    PART_2A,
    PART_2B,
    PART_2C
};
/* The battlefield can be stationary, moving or jammed. */
enum FieldStyle {
    STATIC_FIELD = 1,
    PATH_FIELD,
    JAM_FIELD
};
/* A position stores one x/y point on the square canvas. */
typedef struct {
    double x;
    double y;
} Position;
/* Values that describe one escort and its current battle state. */
typedef struct {
    int id;
    int type;
    int alive;
    int shots;
    int stepShots;
    Position position;
    double minSpeed;
    double maxSpeed;
    double minAngle;
    double maxAngle;
    double impact;
    double gamma;
    double health;
    double reload;
    double nextFire;
    double currentImpact;
} Escort;
/* Values that describe the player's selected battleship. */
typedef struct {
    int type;
    int alive;
    int shots;
    Position position;
    double maxSpeed;
    double gamma;
    double health;
    double reload;
    double nextFire;
    double currentImpact;
} Battleship;
/* One shell waiting to reach its target. */
typedef struct {
    int active;
    int fromBattle;
    int escortIndex;
    double impactTime;
    double damage;
} Shot;
/* Game holds the complete setup and changing simulation data. */
typedef struct {
    double canvas;
    int escortCount;
    int pathCount;
    int jamStep;
    double jamAngle;
    unsigned int seed;
    Battleship battle;
    Escort escorts[MAX_ESCORTS];
    Position path[MAX_PATH];
    Shot shots[MAX_ACTIVE_SHOTS];
    double currentTime;
} Game;
/* Result is the summary returned after one simulation run. */
typedef struct {
    int escortsHit;
    int sankBy;
    int battleShots;
    int escortShots;
    int attackCount;
    int attackOrder[MAX_ATTACKS];
    double duration;
    double damageBattle;
} Result;
/* End of the shared data-type declarations. */
#endif
