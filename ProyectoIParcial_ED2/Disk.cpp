//
// Created by WilliamPC on 23/1/2019.
//
#include "Disk.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <dirent.h>
#include <conio.h>
#include "bitmap.h"
#include "archivos.h"
using namespace std;

bool Disk::existe(string n) {
    DIR *dir;
    ifstream archivo;
    dirent *ent;
    string elemento;
    char nombre[30];
    char carpeta[30];
    char name[30];
    string tipo=".dat";
    string n2;
    if (DIR*dir = opendir("discos"))
    {
        while (dirent*ent = readdir(dir) ) {
            elemento=ent->d_name;
            strcpy(carpeta,elemento.c_str());
            n2=n+tipo;
            strcpy(name,n2.c_str());
            if (elemento != "." && elemento != "..") {
                if(strcmp(name,carpeta)==0){
                    cout<<"YA EXISTE UN DISCO CON ESTE NOMBRE\n";
                    getch();
                    exist=false;
                }


            }
        }
        closedir (dir);
    }
    exist=true;
}
void Disk::create_disk() {
    int cantidad_entradas;
    string n;
    superbloque metadata;

    cout<<"Ingrese el nombre del disco: ";
    cin>>n;
    existe(n);
    if(!exist) {
        ofstream disco_completo(
                "C:/Users/WilliamPC/CLionProjects/ProyectoIParcial_ED2/cmake-build-debug/discos/" + n + ".dat",
                ios::out | ios::binary);
        cout << "\n Ingrese la cantidad de entradas que desea: ";
        cin >> cantidad_entradas;
        metadata.nombre = n;
        metadata.cantidad_entradas = cantidad_entradas;
        metadata.cantidad_bloques = metadata.cantidad_entradas * 33308;
        metadata.bloquesL1 = 2081 * metadata.cantidad_entradas;
        metadata.bloquesL2 = 65 * metadata.cantidad_entradas;
        metadata.bloquesL3 = 1 * metadata.cantidad_entradas;
        metadata.capacidad_bitmap = metadata.cantidad_bloques / 8;
        metadata.tamano_disco = ((metadata.cantidad_bloques * 4096) / 1024) / 1024;


        bitmap *map = new bitmap();
        map->a = metadata.cantidad_bloques / 8;
        map->b = metadata.bloquesL1 / 8;
        map->c = metadata.bloquesL2 / 8;
        map->d = metadata.bloquesL3 / 8;
        map->bloquesOcupados = 0;
        map->DBlock = new char[map->a];
        map->initBitMap(map->DBlock, metadata.cantidad_bloques);

        disco_completo.seekp(0, ios::end);
        disco_completo.write(reinterpret_cast<char *>(&metadata), sizeof(superbloque));
        disco_completo.write(reinterpret_cast<char *>(map), sizeof(bitmap));
        for (int i = 0; i < metadata.cantidad_bloques; i++) {
            Datablock_direct *bloq = new Datablock_direct();
            disco_completo.write((char *) bloq, sizeof(Datablock_direct));
        }
        disco_completo.close();
    }
}

bool Disk::buscar_disk() {
    DIR *dir;
    ifstream archivo;
    dirent *ent;
    string elemento;
    char nombre[30];
    char carpeta[30];
    char name[30];
    string tipo=".dat";
    string n2;
    cout<<"\n Ingrese el nombre del disco: ";
    cin>>nombre;
    if (DIR*dir = opendir("discos"))
    {
        while (dirent*ent = readdir(dir) ) {
            elemento=ent->d_name;
            strcpy(carpeta,elemento.c_str());
            n2=nombre+tipo;
            strcpy(name,n2.c_str());
            if (elemento != "." && elemento != "..") {
                if(strcmp(name,carpeta)==0){
                    usar_disco(name);
                    return true;
                }


            }
        }
        closedir (dir);
    }
    cout<<"\nNo se encontro el disco\n";
    return false;
}
void Disk::usar_disco(string n) {
    ifstream archivo("C:/Users/WilliamPC/CLionProjects/ProyectoIParcial_ED2/cmake-build-debug/discos/"+n,ios::in|ios::binary);
    if(!archivo){
        cout<<"No se pudo abrir el archivo\n";
        getch();
    }
    string palabra;
    superbloque *metadata=new superbloque();
    bitmap *map = new bitmap();
    archivo.seekg(0,ios::beg);
    archivo.read(reinterpret_cast<char *>(metadata), sizeof(superbloque));
    cout<<"\n\n **** METADATA ***\n";
        cout<<"Nombre del Disco: "<<n<<"\n";
        cout<<"Cantidad de entradas soportadas: "<<metadata->cantidad_entradas<<"\n";
        cout<<"Peso Individual de cada bloque: "<<metadata->tamano_bloque<<" Bytes"<<"\n";
        cout<<"Cantidad de bloques en el disco: "<<metadata->cantidad_bloques<<"\n";
        cout<<"Cantidad de bloques de Nivel 1 en el disco: "<<metadata->bloquesL1<<"\n";
        cout<<"Cantidad de bloques de Nivel 2 en el disco: "<<metadata->bloquesL2<<"\n";
        cout<<"Cantidad de bloques de Nivel 3 en el disco: "<<metadata->bloquesL3<<"\n";
        cout<<"Capacidad del mapa de bits: "<<metadata->capacidad_bitmap<<" bytes"<<"\n";
        cout<<"Capacidad del Disco: "<<metadata->tamano_disco<<" mb"<<"\n";
    getch();
    system("cls");
    archivo.read(reinterpret_cast<char *>(map), sizeof(bitmap));
    archivos *dir = new archivos(metadata->cantidad_bloques,metadata->cantidad_entradas,n);
    file_entry array[metadata->cantidad_entradas];
    for (int i = 0; i <metadata->cantidad_entradas ; i++) {
        archivo.read(reinterpret_cast<char*>(&array[i]), sizeof(file_entry));
    }


    do{
        cout <<"Disco : "<<n<<"://"<<dir->UbicacionActual<< "\n\t"<<endl;
        cin>>palabra;
        string na;
        if(palabra=="mkdir")
            dir->CrearDirectorio(array);
        if(palabra=="cd")
            dir->cambiarDirectorio(array);
        if(palabra=="ls")
            dir->listarDirectorio(array);
        if(palabra=="rm") {
            file_entry tmp;
            cout << "Carpeta a borrar: ";
            cin >> na;
            raizaborrar=na;
            for (int i = 0; i <dir->size; ++i) {
                if(array[i].file_name==na){
                   raizh=array[array[i].primer_hijo].file_name;
                    dir->eliminarDirectorio(array, raizh,map);
                    tmp = array[i];
                    file_entry entry;
                   entry.primer_hijo-1;
                 entry.hermano_derecho-1;
                   entry.size=0;
                   entry.ocupado = false;
                    array[i] = entry;
                    for (int j = 0; j < dir->size; j++) {
                        if (array[j].padre == tmp.padre && tmp.hermano_derecho == -1 && array[j].hermano_derecho == i) {
                            array[j].hermano_derecho = -1;
                            break;
                        }
                        if (array[j].padre == tmp.padre && tmp.hermano_derecho != 1 && array[j].hermano_derecho == i) {
                            array[j].hermano_derecho = tmp.hermano_derecho;
                            break;
                        }
                        if (tmp.hermano_derecho != -1 && array[j].primer_hijo == i) {
                            array[j].primer_hijo = tmp.hermano_derecho;
                            break;
                        }
                        if (tmp.hermano_derecho == -1 && array[j].primer_hijo == i) {
                            array[j].primer_hijo = -1;
                            break;
                        }
                    }
                }
            }
        }
      
        if(palabra=="regresar")
            dir->carpetaAnterior(array);
        if(palabra=="exit")
            dir->actualizarDisco(n,metadata,array);
        system("cls");
    }while(palabra!="exit");

}
