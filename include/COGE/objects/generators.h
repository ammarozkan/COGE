#ifndef COGE_GENERATORS_H
#define COGE_GENERATORS_H

GLS::MODEL* PlaneModelAllocator(unsigned int x, unsigned int y);

GLS::MODEL* PlaneModelGenerator(unsigned int x, unsigned int y, GLS::MODEL* model, float (*height_function)(float, float) = nullptr);

#endif