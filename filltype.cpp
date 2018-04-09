#include "filltype.h"

char getFillSym(int i){
    const static char symbol[]={'.','W','m','S','w'};
    return symbol[i];
}
FillType intToFill(int i){
    const static FillType correspond[]={
        FillType::NOTHING,FillType::WALL,
        FillType::GRASS,FillType::STEEL,FillType::WATER
    };
    return correspond[i];
}
