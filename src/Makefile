.PHONY: all s21_matrix.a test gcov_report check rebuild clean unit_tests.o
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
GCOVFLAGS =  -fprofile-arcs -ftest-coverage 
LC = lcov -c -d .
C_FILES = s21*.c
O_FILES = s21*.o
LIBS=-lcheck
LINUX=-lcheck -lm -lpthread -lrt
OS=$(shell uname -s)


all : clean s21_calc.a 
clean : 
	rm -rf *.o *.gcno *.gcda *.info test.out s21_calc.a
	rm -rf ./report
	rm -rf *.dSYM
	rm -rf build
	rm -rf *tgz
	rm -rf gcov_test
rebuild : clean all

$(O_FILES) :
	$(CC) $(CFLAGS) -c $(C_FILES) s21_calc.h
unit_tests.o :
	$(CC) $(CFLAGS) -c -lcheck unit_tests.c
s21_calc.a :
	$(CC) $(CFLAGS) -c $(C_FILES)
	ar r s21_calc.a $(O_FILES)

test: clean s21_calc.a unit_tests.c
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) unit_tests.c s21_calc.a -o test.out $(LIBS)
else
	$(CC) $(CFLAGS) unit_tests.c s21_calc.a -o test.out $(LIBS) $(LINUX)
endif
	./test.out

gcov_report: s21_calc.a unit_tests.c
ifeq ($(OS), Darwin)
	$(CC) $(GCOVFLAGS) unit_tests.c $(C_FILES) -o report.out $(LIBS)
else
	$(CC) $(GCOVFLAGS) unit_tests.c $(C_FILES) -o report.out $(LINUX)
endif
	./report.out
	lcov -t "gcov_report" -o report.info --no-external -c -d .
	genhtml -o report/ report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./report/index.html

memcheck:
	make clean  test
	CK_FORK=no leaks -atExit -- ./test.out

check:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.c
	clang-format -n *.h
	rm -rf .clang-format

install:
	make clean
	mkdir build
	cd s21_smartCalc && qmake && make && make clean && rm Makefile && cd ../ && mv s21_smartCalc/s21_smartCalc.app build

uninstall:
	rm -rf build*

dist:
	rm -rf Archive_s21_smartCalc_v1.0/
	mkdir Archive_s21_smartCalc_v1.0/
	mkdir Archive_s21_smartCalc_v1.0/src
	mv ./build/s21_smartCalc.app Archive_s21_smartCalc_v1.0/src/
	tar cvzf Archive_s21_smartCalc_v1.0.tgz Archive_s21_smartCalc_v1.0/
	rm -rf Archive_s21_smartCalc_v1.0/

dvi:
	open readme.md
