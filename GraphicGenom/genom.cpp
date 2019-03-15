#include "genom.h"

gen_t Genom::etalonArr[GEN_LENGTH];
int Genom::mutateChance = 20;

Genom::Genom()
{
    fillRandom();
}

void Genom::setEtalonArr(gen_t *arr)
{
    for (int i = 0; i < GEN_LENGTH; ++i) {
        etalonArr[i] = arr[i];
    }
}

void Genom::setMutateChance(float mutateChance)
{
    Genom::mutateChance = static_cast<int>(abs(mutateChance * 10));
}

void Genom::operator = (Genom parent)
{
    gen_t *const parentArr = parent.getGenArr();
    for(int i = 0; i < GEN_LENGTH; ++i) {
        genArr[i] = parentArr[i];
    }
}

Genom Genom::operator +(Genom &parent)
{
    Genom child;
    for (int i = 0; i < (GEN_LENGTH/2); ++i) {
        child.getGenArr()[i] = genArr[i];
    }
    for (int i = (GEN_LENGTH/2); i < GEN_LENGTH; ++i) {
        child.getGenArr()[i] = parent.getGenArr()[i];
    }
    child.mutate();
    return child;
}

gen_t *Genom::getGenArr()
{
    return genArr;
}

gen_t Genom::getEuqlidDist()
{
    return euqlidDist;
}

void Genom::print()
{
    for (int i = 0; i < GEN_LENGTH; ++i) {
        qDebug() << genArr[i] << " ";
    }
    qDebug() << "\n";
}

void Genom::fillRandom()
{
    for (int i = 0; i < GEN_LENGTH; ++i) {
        genArr[i] = random(-MAX_GEN, MAX_GEN);
    }
}

void Genom::mutate()
{
    calcEuqlidDist();
    gen_t mutateValue = euqlidDist / GEN_LENGTH;
    if(mutateValue < MIN_MUTATE) mutateValue = MIN_MUTATE;
    for (int i = 0; i < GEN_LENGTH; ++i) {
        if(rand()%1000 < mutateChance) {
            if( (rand() % 100) < 50) {
                genArr[i] = genArr[i] + mutateValue;
            } else {
                genArr[i] = genArr[i] - mutateValue;
            }
        }
    }
}

void Genom::calcEuqlidDist()
{
    gen_t tempVal = 0.0;
    for (int i = 0; i < GEN_LENGTH; ++i) {
        tempVal += pow((genArr[i] - etalonArr[i]),2);
    }
    euqlidDist = sqrt(tempVal);
}

gen_t Genom::random(gen_t min, gen_t max)
{
    if(max < min) return 0;
    double precision = static_cast<int>(pow(10, static_cast<unsigned int>(PRECISSION)));
    return (static_cast<long int>(rand() * rand()) % static_cast<long int>((max - min) * precision) / precision + min);
}
