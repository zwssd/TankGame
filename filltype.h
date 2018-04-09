#ifndef FILLTYPE_H
#define FILLTYPE_H

enum class FillType
{
NOTHING=0,WALL=1,GRASS=2,STEEL=3,WATER=4

};
char getFillSym(int i);
FillType intToFill(int i);

#endif // FILLTYPE_H
