//    Cargando TGA's. Seguimos con los problermas antig�os

 
/*! Carga un TGA en memoria. El TGA debe cumplir las siguientes caracter�sticas:
Ser de 24 bits + Canal ALPHA. (32 bits) y SIN COMPRIMIR
El tama�o debe ser cuadrado (x=y) y 32x32 o 64x64 o 128x128 o 256x256
Devuelve un puntero a la imagen y el tama�o (variable tam) de la imagen.*/ 

extern void *CargaTGA(char *filename, int *tam_x, int *tam_y);

