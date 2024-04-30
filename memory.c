#include "memory.h"
i_node** initializeMemory(int sizeMemory) {
    i_node** memory = (i_node**)calloc(sizeMemory, sizeof(i_node*));
    return memory;
}

void destroyMemory(int sizeMemory, i_node** memory) {
    for (int i=0; i<sizeMemory; i++) {
        if (memory[i]!=0) {
            free(memory[i]->attr);
            for (int j=0; j<8; j++){
                free(memory[i]->positions[j]);
            }
            free(memory[i]->positions);
            free(memory[i]);
        }
    }
    free(memory);
}

int createINode(i_node** memory, sim_values* values, char* filename) {
    int posMemoria = -1;
    for (int i=0; i<values->sizeMemory && posMemoria == -1; i++){
        if (memory[i]==0){ //if the memory position is not being used
            memory[i] = (i_node*)calloc(1, sizeof(i_node));
            memory[i]->attr = (char*)calloc(128, sizeof(char)); //attributes like filename
            memory[i]->positions = (int**)calloc(8, sizeof(int*)); //directions to 8 disk blocks at most
            for (int j=0; j<8; j++) {
                memory[i]->positions[j] = (int*)calloc(2, sizeof(int)); 
                memory[i]->positions[j][0] = -1;
                memory[i]->positions[j][1] = -1;
            }
            strcpy(memory[i]->attr, filename);
            posMemoria = i;
        }
    }
    return posMemoria;
}