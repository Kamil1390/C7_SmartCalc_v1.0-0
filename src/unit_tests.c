#include <check.h>

#include "s21_calc.h"
#include "s21_credCalc.h"

#define OK 0

START_TEST(s21_smartCalc_test_1) {
  int resCode = 0;
  char valueStr[] = "2+2";
  double res = 0;
  res = s21_parser(valueStr, &resCode, 0);

  ck_assert_int_eq(res, 2 + 2);
  ck_assert_int_eq(resCode, OK);
}
END_TEST

START_TEST(s21_smartCalc_test_2) {
  int resCode = 0;
  char valueStr[] = "2+2-1";
  double res = 0;
  res = s21_parser(valueStr, &resCode, 0);

  ck_assert_int_eq(res, 2 + 2 - 1);
  ck_assert_int_eq(resCode, OK);
}
END_TEST

START_TEST(s21_smartCalc_test_3) {
  int resCode = 0;
  char valueStr[] = "2+2*1";
  double res = 0;
  res = s21_parser(valueStr, &resCode, 0);

  ck_assert_int_eq(res, 2 + 2 * 1);
  ck_assert_int_eq(resCode, OK);
}
END_TEST

START_TEST(s21_smartCalc_test_4) {
  int resCode = 0;
  char valueStr[] = "2^(3)";
  double res = 0;
  res = s21_parser(valueStr, &resCode, 0);

  ck_assert_int_eq(res, pow(2, 3));
  ck_assert_int_eq(resCode, OK);
}
END_TEST

START_TEST(s21_smartCalc_test_5) {
  int resCode = 0;
  char valueStr[] = "2^(2^(3))";
  double res = 0;
  res = s21_parser(valueStr, &resCode, 0);

  ck_assert_double_eq(res, pow(2, pow(2, 3)));
  ck_assert_int_eq(resCode, OK);
}
END_TEST

START_TEST(s21_smartCalc_test_6) {
  int resCode = 0;
  char valueStr[] = "5.+2^(2^(3))";
  double res = 0;
  res = s21_parser(valueStr, &resCode, 0);

  ck_assert_double_eq(res, 5 + pow(2, pow(2, 3)));
  ck_assert_int_eq(resCode, OK);
}
END_TEST

START_TEST(s21_smartCalc_test_7) {
  int resCode = 0;
  char valueStr[] = "cos(45.)+2^(sin(52))*5";
  double res = 0;
  res = s21_parser(valueStr, &resCode, 0);

  ck_assert_double_eq(res, cos(45.) + pow(2, sin(52)) * 5);
  ck_assert_int_eq(resCode, OK);
}
END_TEST

START_TEST(s21_smartCalc_test_8) {
  int resCode = 0;
  char valueStr[] = "5^(cos(45.)+2^(sin(52))*5)";
  double res = 0;
  res = s21_parser(valueStr, &resCode, 0);

  ck_assert_double_eq(res, pow(5, (cos(45.) + pow(2, sin(52)) * 5)));
  ck_assert_int_eq(resCode, OK);
}
END_TEST
START_TEST(s21_smartCalc_test_9) {
  int resCode = 0;
  char valueStr[] = "tan(250)-cos(45)+2^(sin(52))*5";
  double res = 0;
  res = s21_parser(valueStr, &resCode, 0);

  ck_assert_double_eq(res, tan(250) - cos(45) + pow(2, sin(52)) * 5);
  ck_assert_int_eq(resCode, OK);
}
END_TEST

START_TEST(s21_smartCalc_test_10) {
  int resCode = 0;
  char valueStr[] = "log(25)-ln(50)";
  double res = 0;
  res = s21_parser(valueStr, &resCode, 0);

  ck_assert_double_eq(res, log10(25) - log(50));
  ck_assert_int_eq(resCode, OK);
}
END_TEST

START_TEST(s21_smartCalc_test_13) {
  int resCode = 0;
  char valueStr[] = "cos(5.25)+sin(2.5)+tan(55.5)";
  double res = 0;
  res = s21_parser(valueStr, &resCode, 0);

  ck_assert_double_eq_tol(res / 0.5, (cos(5.25) + sin(2.5) + tan(55.5)) / 0.5,
                          7);
  ck_assert_int_eq(resCode, OK);
}
END_TEST

START_TEST(s21_smartCalc_test_14) {
  int resCode = 0;
  char valueStr[] = "-1+1/cos(250)";
  double res = 0;
  res = s21_parser(valueStr, &resCode, 0);

  ck_assert_double_eq(res, -1 + 1 / cos(250));
  ck_assert_int_eq(resCode, OK);
}
END_TEST

START_TEST(s21_smartCalc_test_15) {
  int resCode = 0;
  char valueStr[] = "tan(250)-cos(45)+2^(sin(52))*5";
  double res = 0;
  res = s21_parser(valueStr, &resCode, 0);

  ck_assert_double_eq(res, tan(250) - cos(45) + pow(2, (sin(52))) * 5);
  ck_assert_int_eq(resCode, OK);
}
END_TEST

START_TEST(s21_smartCalc_test_17) {
  int resCode = 0;
  char valueStr[] = "1/0";
  double res = 0;
  res = s21_parser(valueStr, &resCode, 0);

  ck_assert_double_infinite(res);
  ck_assert_int_eq(resCode, 2);
}
END_TEST

START_TEST(s21_smartCalc_test_18) {
  int resCode = 0;
  char valueStr[] = "9.5";
  double res = 0;
  res = s21_parser(valueStr, &resCode, 0);

  ck_assert_double_eq(res, 9.5);
  ck_assert_int_eq(resCode, 0);
}
END_TEST

START_TEST(s21_smartCalc_test_20) {
  int resCode = 0;
  char valueStr[] = "7mod3+5mod2/2^(9mod2)";
  double res = 0;
  res = s21_parser(valueStr, &resCode, 0);
  ck_assert_double_eq(res, 7 % 3 + 5 % 2 / pow(2, (9 % 2)));
  ck_assert_int_eq(resCode, OK);
}
END_TEST

START_TEST(s21_creditCalc_test) {
  aut_outPut autValue = {0};
  dif_outPut difValue = {0};

  autValue = autetCalc(100000, 9.5, 12);
  difValue = diferCalc(100000, 9.5, 12);

  ck_assert_double_eq_tol(autValue.aut, 8768.35, 7);
  ck_assert_double_eq_tol(autValue.generalSumma, 105220.20, 7);
  ck_assert_double_eq_tol(autValue.pereplata, 5220.20, 7);

  ck_assert_double_eq_tol(difValue.firstPay, 9125.00, 7);
  ck_assert_double_eq_tol(difValue.lastPay, 8399.31, 7);
  ck_assert_double_eq_tol(difValue.pereplata, 5145.83, 7);
  ck_assert_double_eq_tol(difValue.generalSumma, 105145.83, 7);
}
END_TEST

// Функция создания набора тестов.

Suite *s21_smartCalc_suite() {
  Suite *suite;

  suite = suite_create("s21_smartCalc");
  TCase *tcase_core = tcase_create("Core");

  // Добавление теста в группу тестов.
  tcase_add_test(tcase_core, s21_smartCalc_test_1);
  tcase_add_test(tcase_core, s21_smartCalc_test_2);
  tcase_add_test(tcase_core, s21_smartCalc_test_3);
  tcase_add_test(tcase_core, s21_smartCalc_test_4);
  tcase_add_test(tcase_core, s21_smartCalc_test_5);
  tcase_add_test(tcase_core, s21_smartCalc_test_6);
  tcase_add_test(tcase_core, s21_smartCalc_test_7);
  tcase_add_test(tcase_core, s21_smartCalc_test_8);
  tcase_add_test(tcase_core, s21_smartCalc_test_9);
  tcase_add_test(tcase_core, s21_smartCalc_test_10);
  tcase_add_test(tcase_core, s21_smartCalc_test_13);
  tcase_add_test(tcase_core, s21_smartCalc_test_14);
  tcase_add_test(tcase_core, s21_smartCalc_test_15);
  tcase_add_test(tcase_core, s21_smartCalc_test_17);
  tcase_add_test(tcase_core, s21_smartCalc_test_18);
  tcase_add_test(tcase_core, s21_smartCalc_test_20);

  // creditCalc
  tcase_add_test(tcase_core, s21_creditCalc_test);

  // Добавление теста в тестовый набор.
  suite_add_tcase(suite, tcase_core);

  return suite;
}

int main() {
  Suite *suite = s21_smartCalc_suite();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_VERBOSE);

  // Получаем количество проваленных тестов.

  int failed_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  // Сигнализируем о том, что тестирование прошло неудачно.

  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
