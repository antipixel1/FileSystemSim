# FileSystemSim
## Simulador de un sistema de archivos en C
### Descripción general.
<p>En el archivo disk_manager.c, se encuentra el caso de prueba por defecto.<br>
Los tamaños definidos en el sim_values* values corresponden a:<br>
a - la cantidad de filas del disco<br>
b - la cantidad de columnas del disco<br>
c - la cantidad de bytes por bloque del disco, mínimo 3<br>
partition - fila a partir de la cuál los bloques se consideran reservados para archivos, y antes de ella,<br>
se consideran reservados para guardar la dirección de cada nodo i (excepto el bloque 0 que está reservado)<br>
sizeMemory - el tamaño de la memoria, por lo tanto la cantidad máxima de nodos i.</p>

<p>Se definieron los valores de a=17, b=8, partition = 2 y sizeMemory = 15 debido a lo siguiente:</p>

<p>El disco es de tamaño a*b, entonces, tiene 136 bloques.<br>
El bloque 0 del disco (disk[0][0]) está reservado y no se utiliza. Entonces se tienen 135 bloques utilizables.<br>
Como la memoria es de tamaño 15, y cada nodo i tiene 8 bloques a lo máximo, si todos los nodos i utilizaran <br>
8 bloques esto ocuparia 120 bloques de archivo. Y cada nodo i ocuparía un bloque para guardar su dirección,<br>
por lo tanto 15 bloques. 120+15 = 135, y como la cantidad de bloques utilizables es 135, el disco quedaría<br>
completamente lleno. De esta forma se garantiza que si se tiene la cantidad máxima de archivos (y por lo tanto<br>
de nodos i), cada archivo tenga asegurado 8 bloques.<br>
Se pueden utilizar otras configuraciones si se quisiera, pero para facilitar la revisión se decidió esta.<br>
Ahora, pasando al caso de prueba definido en disk_manager.c, línea por línea:<br>
En el addNewFile prueba.txt, agrega el archivo al disco con un contenido de 320 bytes por lo que ocupa 5 bloques.<br>
Luego, en el addNewFile prueba2.txt agrega el archivo al disco con un contenido de 41 bytes por lo que ocupa 1 bloque.<br>
En el addToFile prueba.txt, se modifican los datos del archivo prueba.txt, ahora con un contenido de 503 bytes por lo <br>
pasa a ocupar 8 bloques.<br>
En el addNewFile prueba.txt se demuestra que no se puede crear más de 1 archivo con el mismo nombre.<br>
En el addToFile prueba.txt, se modifican los datos del archivo prueba.txt, ahora con un contenido de 0 bytes por lo que<br>
el archivo se vacía, pero se le asigna 1 bloque como mínimo, solo que el bloque está vacío.<br>
En el addNewFile prueba3.txt se agrega el archivo al disco con un contenido de 150 bytes, por lo que ocupa 3 bloques,<br>
algunos de estos bloques fueron tomados al quedar libres por el addToFile anterior.<br>
En el último addToFile prueba.txt se vuelve a llenar el archivo, con un contenido de 503 bytes por lo que pasa a ocupar 8<br>
bloques de nuevo.<br>
Es importante mencionar que luego de cada addNewFile o addToFile se realiza un showAll para imprimir el contenido de los archivos<br>
almacenados.<br>
Con esto termina la simulación.<br>
Para ejecutarla, simplemente ejecutar los comandos en una terminal unix:</p>
<p>
make <br>
bin/Tarea_Programada_2<br>
<br>
Otra manera, que también funciona para Windows si se necesita ejecutar desde ahí:<br>
gcc -g main.c disk.c helpers.c disk_manager.c memory.c -o Tarea_Programada_2</p>
