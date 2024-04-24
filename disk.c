#include "disk.h"

char*** initializeDisk(sim_values* values) {
    char*** disk = (char***)calloc(values->a, sizeof(char**));
    for (int i=0; i<values->a; i++){
        disk[i] = (char**)calloc(values->b, sizeof(char*));
        for (int j=0; j<values->b; j++){
            disk[i][j] = (char*)calloc(values->c, sizeof(char));
            if (!(i==0 && j==0)) { //asume 3 bytes por bloque, mínimo
                disk[i][j][0] = '-';
                disk[i][j][1] = '1';
                disk[i][j][2] = '\0';
            }
        }
    }
    disk[0][0][0] = '$'; //carácter especial que indica que ese bloque está reservado al ser el primer bloque
    disk[0][0][1] = '\0'; //carácter terminador
    return disk;
}

void destroyDisk(sim_values* values, char*** disk) {
    for (int i=0; i<values->a; i++) {
        for (int j=0; j<values->b; j++) {
            free(disk[i][j]);
        }
        free(disk[i]);
    }
    free(disk);
}

void addToFile(char*** disk, i_node** memory, sim_values* values, char* filename, const char newData[]) {
    int salir = 0;
    printf("Nombre del archivo al que se quiere agregar:%s\n", filename);
    int posMemory = checkExistence(disk, memory, values, filename);
    if (posMemory!=-1){
        int sizeData = 0;
        while (newData[sizeData]!='\0'){
            sizeData++;
        }
        if (sizeData<8*values->c){ //si el tamaño de los datos es menor de 8 bloques
            int terminaronBloques = 0;
            int j = 0;
            for (j=0; j<8 && terminaronBloques !=1; j++){
                if (memory[posMemory]->positions[j][0]==-1){
                    j--;
                    terminaronBloques = 1;
                }
            }
            printf("Ese archivo tiene  %d bloques antes de ser modificado\n", j);
            editFileBlocks(disk, memory, values, newData, sizeData, posMemory,j);
        }else{
            printf("Ese archivo es demasiado grande, debe ser menor a c*8 bytes.\n");
        }
        salir = 1;
    }
    if (salir==0){
        printf("No se encontró ese archivo");
    }
}

void editFileBlocks(char*** disk, i_node** memory, sim_values* values, const char newData[], int sizeData, 
int posMemory, int cantBloques) {
    int savedData = 0;
    int terminoEscribir = 0;
    printf("El tamaño de los datos es de: %d\n", sizeData);
    for (int k=0; k<cantBloques; k++) {
        emptyBlock(disk[memory[posMemory]->positions[k][0]][memory[posMemory]->positions[k][1]], values->c);
        if (terminoEscribir == 1) {
            memory[posMemory]->positions[k][0] = -1;
            memory[posMemory]->positions[k][1] = -1;
        }
        for (int l=0; l<values->c &&terminoEscribir!=1; l++) {
            if (sizeData>1) {
                disk[memory[posMemory]->positions[k][0]][memory[posMemory]->positions[k][1]][l] = newData[savedData];
                savedData++;
                if (savedData>=sizeData){
                    terminoEscribir = 1;
                }
            }else if(sizeData==1){
                disk[memory[posMemory]->positions[k][0]][memory[posMemory]->positions[k][1]][0] = newData[savedData];
                disk[memory[posMemory]->positions[k][0]][memory[posMemory]->positions[k][1]][1] = 0;
                terminoEscribir = 1;
            }else{ //si los datos están vacíos, entonces se borra el nodo i correspondiente
                disk[memory[posMemory]->positions[k][0]][memory[posMemory]->positions[k][1]][0] = 0;
                disk[memory[posMemory]->positions[k][0]][memory[posMemory]->positions[k][1]][1] = 0;
                terminoEscribir = 1;
            }
        }
    }
    if (sizeData>=cantBloques*values->c) { //falta parte del archivo, se necesitan más bloques
        printf("El índice de los datos es: %d\n", savedData);
        char* missing_data = (char*)calloc(sizeData-savedData+1, sizeof(char));
        substring(newData, missing_data, savedData, sizeData);
        addDataToDisk(disk, memory[posMemory]->positions, values, missing_data, cantBloques);
        free(missing_data);
    }
}

void addNewFile(char*** disk, i_node** memory, sim_values* values, char* filename, const char data[]) {
    int salir = 0;
    if (checkExistence(disk, memory, values, filename) == -1) {
        for (int i=0; i< values->partition && salir != 1; i++){
            for (int j=0; j< values->b && salir != 1; j++){
                if (!(i==0 && j==0)) {
                    if (atoi(disk[i][j])==-1){ //significa que no tiene nodo i asignado
                        int posMemoria = createINode(memory,values,filename);
                        addDataToDisk(disk, memory[posMemoria]->positions, values, data, 0);
                        if (posMemoria!=-1) {
                            printf("Nombre del archivo que se esta creando:%s\n", memory[posMemoria]->attr);
                            intToArray(posMemoria, disk[i][j]); //esto guarda en el disco los punteros a memoria
                        }else{
                            printf("No se pudo agregar el nuevo archivo.. Espacio en memoria ram lleno");
                        }
                        salir = 1;
                    }
                }
            }
        }
    }else{
        printf("No se puede crear más de un archivo con el mismo nombre\n");
    }
}

void addDataToDisk(char*** disk, int** blocks, sim_values* values, const char* data, int countBlock) {
    int salir = 0;
    int sizeData = 0;
    int savedData = 0;
    while (data[sizeData]!='\0'){
        sizeData++;
    }
    if (sizeData<8*(values->c)){ //si el tamaño de los datos es menor de 8 bloques
        for (int i=values->partition; i<values->a &&salir!=1; i++){
            for(int j=0; j<values->b &&salir!=1; j++){
                if (atoi(disk[i][j])==-1){ //si el bloque está vacío
                    for (int k=0; k<values->c &&salir!=1; k++) {
                        disk[i][j][k] = data[savedData];
                        savedData++;
                        if (savedData>=sizeData){
                            salir = 1;
                        }
                    }
                    blocks[countBlock][0] = i;
                    blocks[countBlock][1] = j;
                    countBlock++;
                }
            }
        }   
    }else{
        printf("Ese archivo es demasiado grande, debe ser menor a 8*c bytes.\n");
    }
}
//checks all the memory addresses in the disk, then checks if the file is in one of them
int checkExistence(char*** disk, i_node** memory, sim_values* values, char* filename) {
    int exists = -1;
    for (int i=0; i<values->partition && exists==-1; i++) {
        for (int j=0; j<values->b && exists==-1; j++) {
            if (!(i==0 && j==0)) {
                int indexMemory = atoi(disk[i][j]);
                if (indexMemory!=-1) {//si ese bloque referencia a memoria
                    if (memory[indexMemory]!=0){
                        if ((strcmp(memory[i]->attr, filename))==0) {
                            exists = i;
                        }
                    }
                }
            }
        }
    }
    return exists;
}
//empties a block of the disk
void emptyBlock(char* block, int sizeBlock){
    for (int i=0; i<sizeBlock; i++){
        block[i] = 0;
    }
    block[0] = '-';
    block[1] = '1';
    block[2] = '\0';
}
//show all i node contents
void showAll(char*** disk, i_node** memory, sim_values* values) {
    printf("Ahora se imprimirán los nodos i existentes:\n");
    for (int i=0; i<values->sizeMemory; i++) {
        if (memory[i]!=0){
            printf("Nombre del archivo guardado en la posición %d de la memoria: %s\n", i, memory[i]->attr);
            printf("Ahora se imprimirán los bloques de disco asignados a ese archivo..\n");
            for (int j=0; j<8; j++){
                printf("%d ", memory[i]->positions[j][0]);
                printf("%d\n", memory[i]->positions[j][1]);
                if (memory[i]->positions[j][0]!=-1){
                    printf("Contenido de ese bloque en el disco:\n");
                    for (int k=0; k<values->c; k++) {
                        printf("%c", disk[memory[i]->positions[j][0]][memory[i]->positions[j][1]][k]);
                    }
                    printf("\n");
                }
            }
            printf("\n");
        }
    }
}