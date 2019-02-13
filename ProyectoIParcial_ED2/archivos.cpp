//
// Created by WilliamPC on 5/2/2019.
//
#include <iostream>
#include <fstream>
#include <conio.h>
#include "archivos.h"
#include "Disk.h"
#include "bitmap.h"
using namespace std;
int aux=0;
int busy=0;
int Cantidad_Ocupados=0;
Disk d;
archivos::archivos(int m,int t, string disc) {
    this->size=t;
this->cantidad_bloques=m;
    this->discname=disc;
    this->posActual=-1;
}

void archivos::CrearDirectorio(file_entry array[]) {
    file_entry tmp;
    int actual = this->posActual;
    cout<<"Ingrese el nombre del directorio"<<endl;
    cin>>tmp.file_name ;
    tmp.file_type = 'D';
    tmp.padre=actual;
    int cont=0;
        for(int d=0; d<size;d++){
            if(array[d].ocupado==true)
                busy++;
        }

        for(int i=0; i<this->size ; i++){

            if(array[i].ocupado == false){
                if(i<busy){
                    array[i].ocupado = true;
                    tmp.ocupado = true;
                    tmp.primer_hijo = -1;
                    tmp.hermano_derecho = -1;
                    array[i] = tmp;
                    cout << "Se creo la carpeta: " << tmp.file_name << "\n";
                    for (int h = 0; h < this->size; h++) {

                        if (h != i && array[h].hermano_derecho == -1 && array[h].padre==array[i].padre) {
                            array[h].hermano_derecho = i;
                                return;
                        }
                        if(array[h].primer_hijo==-1 && h==actual){
                            array[h].primer_hijo=i;
                                return;
                        }
                    }
                    break;
                }
                array[i].ocupado = true;
                tmp.ocupado = true;
                tmp.primer_hijo = -1;
                tmp.hermano_derecho = -1;
                array[i] = tmp;
                cout << "Se creo la carpeta: " << tmp.file_name << "\n";
                getch();
                if(busy>0) {

                    for (int j = 0; j < this->size; j++) {

                        if (array[j].padre == array[i].padre && array[j].hermano_derecho == -1) {
                            array[j].hermano_derecho = i;
                            return;
                        }
                        if(array[j].primer_hijo==-1 && j==actual){
                            array[j].primer_hijo=i;
                            return;
                        }
                    }
                }
                    break;
                    }
                    cont++;
                    if(cont==this->size) {
                        cout << "Ya no hay suficiente espacio\n";
                        getch();
                    }

                    }
    busy=0;
}

void archivos::cambiarDirectorio(file_entry array[]){
    string nom;
    cout<<"Ingrese nombre de Carpeta:";
    cin>>nom;
    for(int i=0; i<this->size; i++) {
        if (array[i].file_name == nom&&array[i].padre==posActual&&array[i].ocupado==true) {
            UbicacionActual = nom;
            this->posActual=i;
            break;
        }
    }
}

void archivos::carpetaAnterior(file_entry array[]){
    for(int i=0; i<this->size ; i++){
        if(i==this->posActual) {
            if(array[i].padre==-1) {
                UbicacionActual = " ";
                this->posActual = -1;
            }
            else {
                UbicacionActual = array[array[i].padre].file_name;
                this->posActual = array[i].padre;
            }
            break;
        }
    }
}

void archivos::listarDirectorio(file_entry array[]) {

    cout << "Nombre de Carpteta \t Tipo\n";
    for (int i = 0; i < this->size; i++) {
        if (array[i].ocupado==true && array[i].padre == posActual) {
            cout << "   " << array[i].file_name << " \t\t " << array[i].file_type << "\n";
        }
    }
    getch();
}

void archivos::eliminarDirectorio(file_entry array[], string name,bitmap* bmap) {

    int actual = this->posActual;
    int x = 0;
    for (int i = 0; i < size; i++) {
        file_entry tmp, tmp2;
        if (array[i].file_name == name) {

            getch();
            file_entry entry;
            tmp = array[i];

            if(tmp.file_type=='A'){
                int a=tmp.size/4096;
                apagarBits(array,tmp.file_name,bmap,a);
            }
            if (tmp.primer_hijo!= -1) {
                if (tmp.hermano_derecho != -1) {
                    actual = tmp.hermano_derecho;
                    x = tmp.primer_hijo;
                    tmp2 = array[x];
                    eliminarDirectorio(array, array[actual].file_name,bmap);
                    eliminarDirectorio(array, tmp2.file_name,bmap);
                }else if(tmp.hermano_derecho==-1){
                    actual = tmp.primer_hijo;
                    eliminarDirectorio(array, array[actual].file_name,bmap);
                }
            }if(tmp.hermano_derecho!=-1){
                actual = tmp.hermano_derecho;
                eliminarDirectorio(array, array[actual].file_name,bmap);

            }
            entry.primer_hijo-1;
            entry.hermano_derecho-1;
            entry.ocupado = false;
            array[i] = entry;

        }

    }

}

void archivos::actualizarDisco(string n,superbloque *md, file_entry array[]) {
    ofstream disco("C:/Users/WilliamPC/CLionProjects/ProyectoIParcial_ED2/cmake-build-debug/discos/"+n, ios::out | ios::binary);
    if (!disco.is_open()) {
        cout<<"NO SE PUDO ABRIR\n";
    }
    disco.seekp(0, ios::end);
    disco.write(reinterpret_cast<char*>(md), sizeof(superbloque));
    // disco.write(reinterpret_cast<char*>(map), sizeof(BitMap));
    disco.seekp(sizeof(bitmap) , ios::end);
    cerr<<"Espere un momento..."<<endl;

    for(int a=0;a<size;a++) {
        file_entry arr=array[a];
        disco.write(reinterpret_cast<char *>(&arr),sizeof(file_entry));
    }
    for (int i = 0; i < md->cantidad_bloques; i++) {
        Datablock_direct *dataEscribir = new Datablock_direct();
        disco.write((char*)dataEscribir, sizeof(Datablock_direct));
    }
    disco.close();
}

