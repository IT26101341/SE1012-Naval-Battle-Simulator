#include <stdio.h>
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif
#include "files.h"

/* This file creates a different numbered text report for every run. */
static const char *feature_file(int feature)
{
    /* Short names are safer and easier to read in file names. */
    const char *names[] = {"unknown", "part_1a", "part_1c",
                           "part_2a", "part_2b", "part_2c"};
    if (feature < PART_1A || feature > PART_2C) {
        return names[0];
    }
    return names[feature];
}

static const char *field_file(int field)
{
    const char *names[] = {"unknown", "static", "path", "jam"};
    if (field < STATIC_FIELD || field > JAM_FIELD) {
        return names[0];
    }
    return names[field];
}

FILE *open_report(int feature, int field, char fileName[], int size)
{
    FILE *countFile;
    FILE *report;
    int count = 0;
    /* The results folder is made when it does not already exist. */
#ifdef _WIN32
    _mkdir("results");
#else
    mkdir("results", 0777);
#endif
    /* Read, increase and save the persistent run number. */
    countFile = fopen("results/run_count.txt", "r");
    if (countFile != NULL) {
        fscanf(countFile, "%d", &count);
        fclose(countFile);
    }
    count++;
    countFile = fopen("results/run_count.txt", "w");
    if (countFile == NULL) {
        printf("Could not update the run counter.\n");
        return NULL;
    }
    fprintf(countFile, "%d\n", count);
    fclose(countFile);
    snprintf(fileName, (size_t)size, "results/run_%03d_%s_%s.txt", count,
             feature_file(feature), field_file(field));
    /* The caller receives both the open file and its completed name. */
    report = fopen(fileName, "w");
    if (report == NULL) {
        printf("Could not create %s.\n", fileName);
    }
    return report;
}
