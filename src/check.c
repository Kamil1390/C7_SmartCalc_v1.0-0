#include "s21_calc.c"
#include "s21_calc.h"

int main() {
  char str[] = "1+1";
  int er = 0;
  printf("%s\n", str);
  double rez = s21_parser(str, &er, 0);
  printf("REZ = %lf Error = %d\n", rez, er);
  return 0;
}