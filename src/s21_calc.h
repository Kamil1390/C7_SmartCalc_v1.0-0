#ifndef SRC_S21_CALC_H
#define SRC_S21_CALC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
  NUMBER = 1,
  PLUS,
  MINUS,
  MUL,
  DIV,
  SCALE,
  SQR,
  CS,
  SN,
  TN,
  LN,
  LOG,
  ACS,
  ASN,
  ATN,
  MOD,
  OPBR,
  CLBR
};

typedef struct tValue {
  double number;
  int prioritet;
  int type;
  struct tValue* nextVal;
} tValue;

double s21_parser(char* str, int* error, double x);
void s21_push(tValue** top, double number, int prioritet, int type);
int s21_convert_to_double(int* index, char* str, double* val);
void s21_cpStr(char* src, char* dst);
double s21_pop(tValue** top);
int s21_getOper(int oper[2], int* index, char* str);

int s21_getFun(int oper[2], int* index, char* str);
void s21_crArr(int oper[2], int prioritet, int type);
void s21_revPolnat(tValue** ready, tValue** support, int oper[2]);
void s21_matStack(tValue** ready, tValue** support);
void s21_binOper(tValue** ready, tValue** support, double* rezVal);
void s21_unarOper(tValue** ready, tValue** support, double* rezVal);
void s21_closeBrac(tValue** ready, tValue** support);
double s21_calculate(tValue** ready, tValue** support, int* error);

int s21_checkStr(char* str);
int checkIns(char* str);
int checkBrac(char* str);
void pairBrac(char* str, int* resCode, int* index);
int checkSign(char* str);
int checkTrig(char* str);
int checkFun(char* str, int* index, char ch);

#endif  // SRC_S21_CALC_H
