#include "s21_credCalc.h"

aut_outPut autetCalc(double summa, double stavka, int countMoth) {
  aut_outPut cr_outPut = {0};
  double prStavka = (stavka / 12) / 100;
  double k = (prStavka * pow((1 + prStavka), countMoth)) /
             (pow((1 + prStavka), countMoth) - 1);

  cr_outPut.aut = summa * k;
  cr_outPut.generalSumma = cr_outPut.aut * countMoth;
  cr_outPut.pereplata = cr_outPut.generalSumma - summa;

  return cr_outPut;
}

dif_outPut diferCalc(double summa, double stavka, int countMoth) {
  dif_outPut cr_outPut = {0};
  double procent = 0, bodyLoan = 0, Sn = 0, dif = 0;
  int countPay = 0;
  bodyLoan = summa / countMoth;
  while (countMoth > 0) {
    Sn = summa - (bodyLoan * countPay);
    procent = Sn * (stavka / 100) / 12;
    dif = bodyLoan + procent;
    if (countPay == 0) cr_outPut.firstPay = dif;
    countPay++;
    countMoth--;
    if (countMoth == 0) cr_outPut.lastPay = dif;
    cr_outPut.generalSumma += dif;
  }
  cr_outPut.pereplata = cr_outPut.generalSumma - summa;

  return cr_outPut;
}
