#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "i_node.h"
#include "sim_values.h"
#include "helpers.h"
#include "memory.h"
#ifndef DISK_H
#define DISK_H
    char*** initializeDisk(sim_values* values);
    void destroyDisk(sim_values* values, char*** disk);
    void addToFile(char*** disk, i_node** memory, sim_values* values, char* filename, const char newData[]);
    void editFileBlocks(char*** disk, i_node** memory, sim_values* values, const char newData[], int sizeData, 
    int posMemory, int cantBloques);
    void addNewFile(char*** disk, i_node** memory, sim_values* values, char* filename, const char data[]);
    void showAll(char*** disk, i_node** memory, sim_values* values);
    int checkExistence(char*** disk, i_node** memory, sim_values* values, char* filename);
    void addDataToDisk(char*** disk, int** blocks, sim_values* values, const char* data, int countBlock);
    void emptyBlock(char* block, int sizeBlock);
#endif //DISK_H