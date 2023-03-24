#ifndef SRC_S21_CREDCALC_H
#define SRC_S21_CREDCALC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct aut_outPut {
  double aut;
  double generalSumma;
  double pereplata;
} aut_outPut;

typedef struct dif_outPut {
  double generalSumma;
  double pereplata;
  double firstPay;
  double lastPay;
} dif_outPut;

aut_outPut autetCalc(double summa, double stavka, int countMoth);
dif_outPut diferCalc(double summa, double stavka, int countMoth);

#endif  // SRC_S21_CREDCALC_H