#include "genomalgoritm.h"
#include <QThread>

GenomAlgoritm::GenomAlgoritm()
{
    for (int i = 0; i < POPULATION; ++i) {
        genomArr[i] = new Genom;
    }
}

GenomAlgoritm::GenomAlgoritm(qreal *arr)
{
    for (int i = 0; i < POPULATION; ++i) {
        genomArr[i] = new Genom;
    }
    Genom::setEtalonArr(arr);
}

/*
GenomAlgoritm::GenomAlgoritm(gen_t *arr)
{
    for (int i = 0; i < POPULATION; ++i) {
        genomArr[i] = new Genom;
    }
    Genom::setEtalonArr(arr);

}
*/

GenomAlgoritm::~GenomAlgoritm()
{
    for (int i = 0; i < POPULATION; ++i) {
        delete genomArr[i];
    }
}

void GenomAlgoritm::setMutateChance(float chance)
{
    Genom::setMutateChance(chance);
}

void GenomAlgoritm::setEuqlidDist(gen_t dist)
{
    euqlidDist = dist;
}

void GenomAlgoritm::calculate(int maxItterations)
{
    int i = 0;

    do {
        qDebug() << "populatio " << i << "\n";
        reproduce();
        sort();
        //printEuqlid();
        ++i;
        if(!(i % 100)) {
            emit plot();
            QThread::msleep(500);
        }

    } while (i < maxItterations && genomArr[0]->getEuqlidDist() > euqlidDist);
    emit plot();
}

void GenomAlgoritm::print()
{
    for (int i = 0; i < POPULATION; ++i) {
        genomArr[i]->print();
        qDebug() << "\n";
    }
}

void GenomAlgoritm::printEuqlid()
{
    for (int i = 0; i < POPULATION; ++i) {
        qDebug() << genomArr[i]->getEuqlidDist() << " ";
    }
    qDebug() << "\n";
}

void GenomAlgoritm::fillRandom()
{
    for (int i = 0; i < POPULATION; ++i) {
        genomArr[i]->fillRandom();
    }
}

Genom *GenomAlgoritm::getGenom()
{
    return genomArr[0];
}


void GenomAlgoritm::sort()
{
    for (int i = 1; i < POPULATION; ++i) {
        int j = i;
        while (j > 0 && genomArr[j]->getEuqlidDist() < genomArr[j-1]->getEuqlidDist()) {
            Genom *temp = genomArr[j];
            genomArr[j] = genomArr[j-1];
            genomArr[j-1] = temp;
            --j;
        }
    }
}

void GenomAlgoritm::reproduce()
{
    for (int i = 0; i < POPULATION/2; i+= 2) {
        *genomArr[POPULATION/2 + i] = *genomArr[i] + *genomArr[i + 1];
        *genomArr[POPULATION/2 + i + 1] = *genomArr[i + 1] + *genomArr[i];
    }
    for (int i = 0; i < POPULATION; ++i) {
        genomArr[i]->calcEuqlidDist();
    }
}
