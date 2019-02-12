//
// Created by WilliamPC on 6/2/2019.
//

#ifndef PROYECTOIPARCIAL_ED2_BITMAP_H
#define PROYECTOIPARCIAL_ED2_BITMAP_H


class bitmap {
public:
    int a, b, c , d;
    int bloquesOcupados;
    char* DBlock = new char[a];
    char* BlockLvl1 = new char[b];
    char* BlockLvl2 = new char[c];
    char* BlockLvl3 = new char[d];

    void initBitMap(char * bitMap , int Block_Amount);
    void setOn(char *bitMap, int nBlock);
    void setOf(char *bitMap, int nBlock);
};


#endif //PROYECTOIPARCIAL_ED2_BITMAP_H
