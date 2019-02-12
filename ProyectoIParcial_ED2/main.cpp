#include <iostream>
#include "archivos.h"
using namespace std;
int main() {
    Disk d;

    int opc=0;
    cout<<"***** Sistema de archivos ******\n";
    do{
        cout<<"1. Crear Disco.\n";
        cout<<"2. Utilizar Disco Existente.\n";
        cout<<"3. Salir.\n";
        cin>>opc;
        if(opc==1){
            system("cls");
           d.create_disk();
        }else if(opc==2) {
            system("cls");
            d.buscar_disk();
        }
        system("cls");
    }while(opc!=3);
    return 0;
}