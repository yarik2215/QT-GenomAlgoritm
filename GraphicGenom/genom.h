#ifndef GENOM_H
#define GENOM_H

//#include <stdint.h>
#include <QtCore>
#include <iostream>

typedef double gen_t;

#define GEN_LENGTH  100
#define PRECISSION 2
#define MAX_GEN 1000
#define MIN_MUTATE 0.01

class Genom
{
public:
    Genom();
    static void setEtalonArr(gen_t *arr);
    static void setMutateChance(float mutateChance);
    void operator = (Genom parent);
    Genom operator + (Genom& parent);
    gen_t *getGenArr();
    gen_t getEuqlidDist();
    void print();
    void fillRandom();

    void calcEuqlidDist();

private:
    void mutate();
    gen_t random(gen_t min, gen_t max);

    static gen_t etalonArr[GEN_LENGTH];
    static int mutateChance;
    gen_t genArr[GEN_LENGTH];
    gen_t euqlidDist;
};

#endif // GENOM_H
