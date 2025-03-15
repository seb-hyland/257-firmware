#ifndef INITIALIZATION_HELPERS_H
#define INITIALIZATION_HELPERS_H

#include <Arduino.h>
#include <vector>

void initTime();
int initDosage();
std::vector<long> initTiming();
std::vector<long> readCSV();

#endif
