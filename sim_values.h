#ifndef SIM_VALUES_H
#define SIM_VALUES_H
typedef struct{
    int sizeMemory; //cantidad de nodos i
    int partition; // a partir de la fila que son bloques de disco, antes referencias a los nodos i
    int a; //filas
    int b; //columnas
    int c; //cantidad de bytes por bloque
}sim_values;
#endif