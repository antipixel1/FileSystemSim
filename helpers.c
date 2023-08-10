#include "helpers.h"
void intToArray(int number, char* buffer) {
    int decimalActual = number;
    int cantDecimales = 0;
    do{
        decimalActual = decimalActual/10;
        cantDecimales++; //calcular la cantidad de decimales
    }while (decimalActual != 0);
    decimalActual = number;
    int posHilera = cantDecimales-1;
    while (posHilera != -1){
        int valorReal = decimalActual%10+48;
        buffer[posHilera] = valorReal;
        decimalActual = decimalActual/10;
        posHilera--;
    }
    buffer[cantDecimales] = '\0';
}

void substring(const char origin[], char* destination, int start, int end){
    int startDest = 0;
    for (int i=start; i<end; i++){
        destination[startDest] = origin[i];
        startDest++;
    }
}