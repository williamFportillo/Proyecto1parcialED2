//
// Created by WilliamPC on 5/2/2019.
//
#ifndef PROYECTOIPARCIAL_ED2_ARCHIVOS_H
#define PROYECTOIPARCIAL_ED2_ARCHIVOS_H
#include "Disk.h"
#include "bitmap.h"

class archivos {
public:
    int size;
    int posActual=-1;
    int cantidad_bloques;
    int sizeArchivos;
    string discname, UbicacionActual;
    archivos(int,int,string);
    void CrearDirectorio(file_entry array[]);
    void listarDirectorio(file_entry array[]);
    void cambiarDirectorio(file_entry array[]);
    void eliminarDirectorio(file_entry array[], string n, bitmap*);
    void actualizarDisco(string,superbloque *md ,file_entry array[]);
    void carpetaAnterior(file_entry array[]);
};
#endif //PROYECTOIPARCIAL_ED2_ARCHIVOS_H
