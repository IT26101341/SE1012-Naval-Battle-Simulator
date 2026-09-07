#ifndef FILES_H
#define FILES_H

/* Shared declarations for report files and saved simulation history. */
#include <stdio.h>
#include "types.h"

FILE *open_report(int feature, int field, char fileName[], int size);
void write_initial(FILE *file, const Game *game, int feature, int field);
void write_final(FILE *file, const Game *game, const Result *result);
void append_history(const char *fileName, int feature, int field,
                    const Result *result);
void show_statistics(void);

#endif
