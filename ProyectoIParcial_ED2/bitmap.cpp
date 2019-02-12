//
// Created by WilliamPC on 6/2/2019.
//

#include "bitmap.h"

void bitmap::initBitMap(char *bitMap, int cantidad_bloques) {
    for(int i = 0; i < cantidad_bloques/8; i++){
        bitMap[i] = 0;
    }
}
void bitmap::setOn(char *bitMap, int nBlock) {
    int positionByte = nBlock/8;
    int iniPosition = (nBlock/8) * 8;

    for(int i = iniPosition, x = 7; i < (positionByte * 8) + 8; i++, x--){
        if(i == nBlock){
            bitMap[positionByte] |= 1 << x;
            break;
        }
    }
}
void bitmap::setOf(char *bitMap, int nBlock) {
    int positionByte = nBlock/8;
    int iniPosition = (nBlock/8) * 8;

    for(int i = iniPosition, x = 7; i < (positionByte * 8) + 8; i++, x--){
        if(i == nBlock){
            bitMap[positionByte] &= ~(1 << x);
            break;
        }
    }
}