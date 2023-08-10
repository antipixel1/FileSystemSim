#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "i_node.h"
#include "sim_values.h"
#ifndef MEMORY_H
#define MEMORY_H
    i_node** initializeMemory(int sizeMemory);
    void destroyMemory(int sizeMemory, i_node** memory);
    int createINode(i_node** memory, sim_values* values, char* filename);
#endif //MEMORY_H