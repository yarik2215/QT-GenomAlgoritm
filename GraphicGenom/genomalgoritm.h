#ifndef GENOMALGORITM_H
#define GENOMALGORITM_H

#include <QObject>
#include "genom.h"

#define POPULATION 20

class GenomAlgoritm : public QObject
{
    Q_OBJECT
public:
    GenomAlgoritm();
    GenomAlgoritm(qreal *arr);
    ~GenomAlgoritm();
    void setMutateChance(float chance);
    void setEuqlidDist(gen_t dist);
    void print();
    void printEuqlid();
    void fillRandom();
    Genom *getGenom();

    void sort();
    void reproduce();

public slots:
    void calculate(int maxItterations);

signals:
    void plot();

private:
    Genom *genomArr[POPULATION];
    gen_t euqlidDist;

};

#endif // GENOMALGORITM_H
