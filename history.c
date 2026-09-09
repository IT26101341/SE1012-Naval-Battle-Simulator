#include <stdio.h>
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif
#include "core.h"
#include "files.h"

/* Add one short summary line after a simulation finishes. */
void append_history(const char *fileName, int feature, int field,
                    const Result *result)
{
    FILE *file;
#ifdef _WIN32
    _mkdir("results");
#else
    mkdir("results", 0777);
#endif
    file = fopen("results/history.txt", "a");
    if (file == NULL) {
        printf("Could not save simulation history.\n");
        return;
    }
    fprintf(file, "%s | %s | %s | ", fileName,
            feature_name(feature), field_name(field));
    if (result->sankBy >= 0) {
        /* Escort numbers begin at zero internally, so the report adds E. */
        fprintf(file, "B sank by E%d | ", result->sankBy);
    } else {
        fprintf(file, "B survived | ");
    }
    fprintf(file, "time %.2f | E hit %d | shots B:%d E:%d | damage %.3f\n",
            result->duration, result->escortsHit, result->battleShots,
            result->escortShots, result->damageBattle);
    fclose(file);
}

/* Read the history file one line at a time and display every saved result. */
void show_statistics(void)
{
    FILE *file;
    char line[512];
    int found = 0;
    file = fopen("results/history.txt", "r");
    show_stats_art();
    if (file == NULL) {
        printf("No saved simulation history was found.\n");
        return;
    }
    while (fgets(line, sizeof(line), file) != NULL) {
        /* fgets keeps the newline, so another newline is not needed here. */
        printf("%s", line);
        found = 1;
    }
    if (!found) {
        printf("No simulations have been saved yet.\n");
    }
    fclose(file);
}
