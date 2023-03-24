#include "s21_calc.h"

double s21_parser(char* str, int* error, double x) {
  double rezValue = 0;
  *error = 0;

  tValue* top = NULL;
  tValue* support = NULL;

  int oper[2] = {0};
  char buffer[256] = {'\0'};
  int i = 0, stopFlag = 1;
  double val = 0;
  s21_cpStr(str, buffer);
  stopFlag *= s21_checkStr(buffer);
  if (!stopFlag) *error = 2;
  while (i < (int)strlen(buffer) && stopFlag) {
    if (strchr("1234567890x", buffer[i])) {
      if (buffer[i] == 'x') {
        s21_push(&top, x, 0, NUMBER);
        i++;
      } else {
        stopFlag *= s21_convert_to_double(&i, buffer, &val);
        s21_push(&top, val, 0, NUMBER);
      }
    } else {
      if ((i == 0 && buffer[i] == '-') ||
          (buffer[i] == '-' && buffer[i - 1] == '('))
        s21_push(&top, 0, 0, NUMBER);

      stopFlag = s21_getOper(oper, &i, buffer);

      s21_revPolnat(&top, &support, oper);
    }
  }
  if (*error == 0) rezValue = s21_calculate(&top, &support, error);
  if ((rezValue == INFINITY) || (rezValue == NAN)) *error = 2;
  if (top != NULL) free(top);
  if (support != NULL) free(support);
  return rezValue;
}

void s21_push(tValue** top, double number, int prioritet, int type) {
  tValue* tmp = calloc(1, sizeof(tValue));
  if (tmp != NULL) {
    tmp->nextVal = *top;
    tmp->number = number;
    tmp->prioritet = prioritet;
    tmp->type = type;
    *top = tmp;
  }
}

double s21_pop(tValue** top) {
  tValue* prev = NULL;
  double val = 0;
  if (top != NULL) {
    prev = *top;
    val = prev->number;
    *top = (*top)->nextVal;
    free(prev);
  }

  return val;
}

int s21_convert_to_double(int* index, char* str, double* val) {
  *val = 0;
  char tmp[256] = {'\0'};
  int stopFlag = 1, i = 0;
  while (strchr("1234567890.", str[*index]) && stopFlag) {
    tmp[i] = str[*index];
    *index += 1;
    i++;
    if (*index >= (int)strlen(str)) stopFlag = 0;
  }
  tmp[i + 1] = '\0';
  *val = atof(tmp);
  return stopFlag;
}

int s21_getOper(int oper[2], int* index, char* str) {
  int stopFlag = 1;

  if (strchr("acstlm", str[*index]))
    stopFlag = s21_getFun(oper, index, str);
  else {
    if (str[*index] == '+') s21_crArr(oper, 1, PLUS);
    if (str[*index] == '-') s21_crArr(oper, 1, MINUS);
    if (str[*index] == '*') s21_crArr(oper, 2, MUL);
    if (str[*index] == '/') s21_crArr(oper, 2, DIV);
    if (str[*index] == '^') s21_crArr(oper, 3, SCALE);
    if (str[*index] == '(') s21_crArr(oper, 5, OPBR);
    if (str[*index] == ')') s21_crArr(oper, 5, CLBR);
    *index += 1;
  }
  if (*index >= (int)strlen(str)) stopFlag = 0;
  return stopFlag;
}

int s21_getFun(int oper[2], int* index, char* str) {
  int stopFlag = 1, i = 0;
  char word[5] = "";
  if (str[*index] == 'a' || (str[*index] == 's' && str[*index + 1] == 'q')) {
    for (i = 0; i < 4; i++) {
      word[i] = str[*index];
      *index += 1;
    }
    word[i + 1] = '\0';
  } else {
    if (str[*index] == 'c' || str[*index] == 's' || str[*index] == 't' ||
        str[*index] == 'm' || (str[*index] == 'l' && str[*index + 1] == 'o')) {
      for (int i = 0; i < 3; i++) {
        word[i] = str[*index];
        *index += 1;
      }

    } else if (str[*index] == 'l' && str[*index + 1] == 'n') {
      for (int i = 0; i < 2; i++) {
        word[i] = str[*index];
        *index += 1;
      }
    } else
      stopFlag = 0;
  }

  if (strcmp(word, "ln") == 0) s21_crArr(oper, 4, LN);
  if (strcmp(word, "log") == 0) s21_crArr(oper, 4, LOG);
  if (strcmp(word, "cos") == 0) s21_crArr(oper, 4, CS);
  if (strcmp(word, "sin") == 0) s21_crArr(oper, 4, SN);
  if (strcmp(word, "tan") == 0) s21_crArr(oper, 4, TN);
  if (strcmp(word, "mod") == 0) s21_crArr(oper, 2, MOD);
  if (strcmp(word, "acos") == 0) s21_crArr(oper, 4, ACS);
  if (strcmp(word, "asin") == 0) s21_crArr(oper, 4, ASN);
  if (strcmp(word, "atan") == 0) s21_crArr(oper, 4, ATN);
  if (strcmp(word, "sqrt") == 0) s21_crArr(oper, 4, SQR);

  if (*index >= (int)strlen(str)) stopFlag = 0;
  return stopFlag;
}

void s21_crArr(int oper[2], int prioritet, int type) {
  oper[0] = prioritet;
  oper[1] = type;
}

void s21_revPolnat(tValue** ready, tValue** support, int oper[2]) {
  int stopFlag = 1;
  while (stopFlag) {
    if ((*support == NULL || (oper[0] > (*support)->prioritet) ||
         (*support)->type == OPBR) &&
        (oper[1] != CLBR)) {
      s21_push(support, 0, oper[0], oper[1]);
      stopFlag = 0;
    } else {
      if (oper[1] == CLBR) {
        s21_push(support, 0, oper[0], oper[1]);
        s21_pop(support);
        s21_closeBrac(ready, support);
        stopFlag = 0;
      } else {
        s21_matStack(ready, support);
      }
    }
  }
}

double s21_calculate(tValue** ready, tValue** support, int* error) {
  double rez = 0;
  int stopFlag = 1;
  while (stopFlag && *error == 0) {
    if ((*ready == NULL) && (*support == NULL))
      *error = 2;
    else if (*support == NULL)
      stopFlag = 0;
    else {
      s21_matStack(ready, support);
      *error = 0;
      if (support == NULL) stopFlag = 0;
    }
  }
  if (*error != 2) rez = (*ready)->number;
  return rez;
}

void s21_matStack(tValue** ready, tValue** support) {
  double rezVal = 0;
  int oper = (*support)->type;
  if (oper == PLUS || oper == MINUS || oper == MUL || oper == DIV ||
      oper == MOD || oper == SCALE)
    s21_binOper(ready, support, &rezVal);
  if (oper == CS || oper == SN || oper == TN || oper == LN || oper == LOG ||
      oper == ACS || oper == ASN || oper == ATN || oper == SQR)
    s21_unarOper(ready, support, &rezVal);
  s21_push(ready, rezVal, 0, NUMBER);
  s21_pop(support);
}

void s21_binOper(tValue** ready, tValue** support, double* rezVal) {
  double val_1 = 0, val_2 = 0;
  val_2 = s21_pop(ready);
  val_1 = s21_pop(ready);
  if ((*support)->type == PLUS) *rezVal = val_1 + val_2;
  if ((*support)->type == MINUS) *rezVal = val_1 - val_2;
  if ((*support)->type == MUL) *rezVal = val_1 * val_2;
  if ((*support)->type == DIV) *rezVal = val_1 / val_2;
  if ((*support)->type == MOD) *rezVal = fmod(val_1, val_2);
  if ((*support)->type == SCALE) *rezVal = pow(val_1, val_2);
}

void s21_unarOper(tValue** ready, tValue** support, double* rezVal) {
  double val_1 = 0;
  val_1 = s21_pop(ready);
  if ((*support)->type == CS) *rezVal = cos(val_1);
  if ((*support)->type == SN) *rezVal = sin(val_1);
  if ((*support)->type == TN) *rezVal = tan(val_1);
  if ((*support)->type == LN) *rezVal = log(val_1);
  if ((*support)->type == LOG) *rezVal = log10(val_1);
  if ((*support)->type == ACS) *rezVal = acos(val_1);
  if ((*support)->type == ASN) *rezVal = asin(val_1);
  if ((*support)->type == ATN) *rezVal = atan(val_1);
  if ((*support)->type == SQR) *rezVal = sqrt(val_1);
}

void s21_closeBrac(tValue** ready, tValue** support) {
  int stopFlag = 1;
  while (stopFlag) {
    if ((*support)->type == OPBR) {
      s21_pop(support);
      stopFlag = 0;
    }
    if (stopFlag) s21_matStack(ready, support);
  }
}

void s21_cpStr(char* src, char* dst) {
  char buffer[256] = "";
  int len = (int)strlen(src), j = 0, countPoint = 0, stopFlag = 0;
  for (int i = 0; i < len; i++) {
    stopFlag = 0;
    if (src[i] == '.' || src[i] == ',') {
      if (i == 0 || i == len - 1) {
        stopFlag = 1;
        countPoint = 0;
      } else {
        countPoint++;
        if (countPoint > 1) {
          countPoint = 0;
          stopFlag = 1;
        }
        if ((countPoint == 1) && ((!strchr("0123456789", src[i - 1])) ||
                                  (!strchr("0123456789.,", src[i + 1])))) {
          stopFlag = 1;
          countPoint = 0;
        }
      }
    }
    if (!strchr("0123456789.,", src[i]) && countPoint > 0) countPoint = 0;
    if (!stopFlag) {
      if (src[i] == ',')
        buffer[j] = '.';
      else
        buffer[j] = src[i];
      j++;
    }
  }
  buffer[j + 1] = '\0';
  j = 0;
  for (int i = 0; i < (int)strlen(buffer); i++) {
    stopFlag = 0;
    if (buffer[i] == '.') {
      if ((!strchr("0123456789", buffer[i - 1])) ||
          (!strchr("0123456789", buffer[i + 1])))
        stopFlag = 1;
      if (i == ((int)strlen(buffer) - 1)) stopFlag = 1;
    }
    if (!stopFlag) {
      dst[j] = buffer[i];
      j++;
    }
  }
  dst[j + 1] = '\0';
}

int s21_checkStr(char* str) {
  int resCode = 1;

  resCode = checkIns(str);
  if (resCode) resCode *= checkBrac(str);

  if (resCode) resCode *= checkSign(str);

  if (resCode) resCode *= checkTrig(str);

  return resCode;
}

int checkIns(char* str) {
  int resCode = 1;
  for (int i = 0; i < (int)strlen(str) && resCode; i++) {
    if (!strchr("x1234567890.()+-*/^acstl", str[i])) {
      if (i == 0 || i == (int)strlen(str) - 1) resCode = 0;
    }
  }
  return resCode;
}

int checkBrac(char* str) {
  int resCode = 1, countFirst = 0, countSecond = 0;
  for (size_t i = 0; i < strlen(str) && resCode; i++) {
    if (str[i] == '(') {
      if (str[i + 1] == ')' || i == strlen(str) - 1) resCode = 0;

      countFirst++;
    }
    if (str[i] == ')' && resCode) {
      if (strchr("+-*/.^", str[i - 1]) || i == 0) resCode = 0;
      countSecond++;
    }
  }
  if (countFirst != countSecond) resCode = 0;
  int index = 0;

  while (index < (int)strlen(str) && resCode) {
    if (str[index] == '(')
      pairBrac(str, &resCode, &index);
    else
      index++;
  }

  return resCode;
}

void pairBrac(char* str, int* resCode, int* index) {
  int stopFlag = 0;
  *index += 1;
  size_t len = strlen(str);
  while (*index < (int)len && !stopFlag && *resCode == 1) {
    if (str[*index] == ')') {
      stopFlag = 1;
    }
    if (*index == (int)len - 1 && !stopFlag) *resCode = 0;

    if (str[*index] == '(' && resCode && !stopFlag) {
      pairBrac(str, resCode, index);

      if (*index == (int)len) *resCode = 0;

    } else
      *index += 1;
  }
}

int checkSign(char* str) {
  int resCode = 1;
  for (size_t i = 0; i < strlen(str) && resCode; i++) {
    if (strchr("+-*/.^", str[i])) {
      if (i == 0 &&
          (str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == '.'))
        resCode = 0;
      if ((str[i] != '+' && str[i] != '-') && str[i] == str[i + 1]) resCode = 0;
      if (i == strlen(str) - 1) resCode = 0;
      if (str[i - 1] == '(' && str[i + 1] == ')') resCode = 0;
      if (str[i] == '^' && str[i + 1] != '(') resCode = 0;
      if (strchr("+-*/.^", str[i + 1])) resCode = 0;
    }
  }
  return resCode;
}

int checkTrig(char* str) {
  int resCode = 1;
  for (int i = 0; i < (int)strlen(str); i++) {
    if (strchr("acstl", str[i])) {
      resCode *= checkFun(str, &i, str[i]);
    }
  }
  return resCode;
}

int checkFun(char* str, int* index, char ch) {
  int resCode = 1, i = 0;
  char word[6] = "";
  if (str[*index] == 'a' || (str[*index] == 's' && str[*index + 1] == 'q')) {
    for (i = 0; i < 5; i++) {
      word[i] = str[*index];
      *index += 1;
    }
    word[i + 1] = '\0';
  } else {
    if (ch == 'c' || ch == 's' || ch == 't' ||
        (ch == 'l' && str[*index + 1] == 'o')) {
      for (int i = 0; i < 4; i++) {
        word[i] = str[*index];
        *index += 1;
      }
    } else if (ch == 'l' && str[*index + 1] == 'n') {
      for (int i = 0; i < 3; i++) {
        word[i] = str[*index];
        *index += 1;
      }
    }
  }
  if (strlen(word) == 3) {
    if (strcmp(word, "ln(") != 0) resCode = 0;
  }
  if (strlen(word) == 4) {
    if (strcmp(word, "cos(") != 0 && strcmp(word, "sin(") != 0 &&
        strcmp(word, "tan(") != 0 && strcmp(word, "log(") != 0)
      resCode = 0;
  }
  if (strlen(word) == 5) {
    if (strcmp(word, "acos(") != 0 && strcmp(word, "asin(") != 0 &&
        strcmp(word, "atan(") != 0 && strcmp(word, "sqrt("))
      resCode = 0;
  }
  return resCode;
}
