//
// Created by WilliamPC on 23/1/2019.
//

#ifndef PROYECTOIPARCIAL_ED2_DISK_H
#define PROYECTOIPARCIAL_ED2_DISK_H

#include <iostream>
using namespace std;
class Disk {
private:
    int tam;
    int actual_pos=-1;
    bool exist=false;
public:
    string raizaborrar;
    string raizh;
    void create_disk();
   bool existe(string);
    bool buscar_disk();
    void usar_disco(string nombre);
};
struct DATE{
    char day[2];
    char month[2];
    char year[4];
};
struct file_entry{
    char file_name[30];
    char file_type;
    DATE creation_DATE;
    int padre=-1;
    int primer_hijo=-1;
    int hermano_derecho=-1;
    bool ocupado=false;
    unsigned int size;
    unsigned int DB_directs[12];
    unsigned int DB_indirects[3];
};
struct Datablock_direct{
    char data[4096];
};

struct Datablock_I1{
    Datablock_direct pointers[16];
};

struct Datablock_I2{
    Datablock_I1 pointers[32];
};

struct Datablock_I3{
    Datablock_I2 pointers[64];
};
struct superbloque{
    string nombre;
    int cantidad_entradas;
    int tamano_bloque=4096;
    int cantidad_bloques;
    int bloquesL1;
    int bloquesL2;
    int bloquesL3;
    int tamano_disco;
    int capacidad_bitmap;
};
#endif //PROYECTOIPARCIAL_ED2_DISK_H
