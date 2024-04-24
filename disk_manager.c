#include "disk_manager.h"

void startSimulation(){
    sim_values* values = (sim_values*)calloc(1, sizeof(sim_values));
    values->a = 17;
    values->b = 8;
    values->c = 64;
    values->partition = 2;
    values->sizeMemory = 15;
    i_node** memory = initializeMemory(values->sizeMemory); //cada nodo i tiene 8 bloques
    char*** disk = initializeDisk(values);
    addNewFile(disk,memory, values, "prueba.txt", "Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magnia");
    showAll(disk, memory, values);
    addNewFile(disk,memory, values, "prueba2.txt", "poquitos datos que caben en 1 solo bloque");
    showAll(disk, memory, values);
    addToFile(disk, memory, values, "prueba.txt", "Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt. Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora");
    showAll(disk, memory, values);
    addNewFile(disk,memory, values, "prueba.txt", "caso para probar que no se pueden generar duplicados");
    addToFile(disk,memory, values, "prueba.txt", "");
    showAll(disk, memory, values);
    addNewFile(disk, memory, values, "prueba3.txt", "tercer archivo que agregamos, Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt. Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora");
    addToFile(disk,memory, values, "prueba.txt", "Sed ut perspiciatis unde omnis iste natus error sit voluptatem accusantium doloremque laudantium, totam rem aperiam, eaque ipsa quae ab illo inventore veritatis et quasi architecto beatae vitae dicta sunt explicabo. Nemo enim ipsam voluptatem quia voluptas sit aspernatur aut odit aut fugit, sed quia consequuntur magni dolores eos qui ratione voluptatem sequi nesciunt. Neque porro quisquam est, qui dolorem ipsum quia dolor sit amet, consectetur, adipisci velit, sed quia non numquam eius modi tempora");
    showAll(disk, memory, values);
    destroyDisk(values, disk);
    destroyMemory(values->sizeMemory, memory);
    free(values);
}