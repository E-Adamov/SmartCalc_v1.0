CC=gcc
CFLAGS=-Wall -Wextra -Werror
GCOV=-fprofile-arcs -ftest-coverage
OS=$(shell uname)
ifeq ($(OS), Linux)
	LIBS=-lcheck -lpthread -lrt -lm -lsubunit
	LEAKS=CK_FORK=no valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./test.out
	testS=$(CC) -g test.c s21_calc.a $(LIBS) -o test.out
else
	LIBS=-lcheck
	LEAKS=CK_FORK=no leaks --atExit -- ./test.out
	testS=$(CC) -g test.c s21_calc.a $(LIBS) -o test.out
endif

all: clean s21_calc.a test
test: clean s21_calc.a
	$(testS)
	./test.out

install: dist
	cp -rf calc_qt.pro *.c *.h *.cpp *.ui ../build
	cd ../build; qmake calc_qt.pro
	make -C ../build
	cp -rf ../build/calc_qt.app  $(HOME)/Desktop
uninstall:
	@rm -rf $(HOME)/Desktop/calc_qt.app
	@rm -rf ../build
dvi: 
	open dvi.html
dist:
	mkdir -p ../build
	tar -cvzf ../build/calc_qt.tgz Makefile *.c *.h *.pro *.user *.cpp *.ui *.html

gcov_report: s21_calc.a
	$(CC) --coverage -c s21_calc.c
	ar rc s21_calc.a *.o
	$(CC) test.c -L. s21_calc.a -lcheck -lpthread -lm -lgcov -o test_cov
	rm -rf *.o
	./test_cov
	gcov *.gcda
	lcov -t "gcov_report" -o gcov_report.info -c -d .
	mkdir -p ./report
	genhtml -o report gcov_report.info
	open ./report/index.html

s21_calc.a:
	$(CC) -c s21_calc.c -o s21_calc.o
	ar rcs s21_calc.a s21_calc.o

clean:
	rm -rf *.0 *.a *.gcno *.gcda *.info *.out report *.dSYM *.gch *.o test2.out
	rm -rf .vscode .DS_Store s21_calc.c.gcov test_cov CPPLINT.cfg s21_calc
	rm -rf ../.DS_Store ../.vscode a.out
	rm -rf .qtc_clangd .qmake.stash

leaks: clean test
	$(LEAKS)

codestyle:
	cp ../materials/linters/CPPLINT.cfg ./
	python3 ../materials/linters/cpplint.py --extensions=c s21_calc.c s21_calc.h test.c
	rm -rf CPPLINT.cfg

CPPcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem s21_calc.c s21_calc.h test.c

CH: clean leaks codestyle CPPcheck
	rm -rf *.0 *.a *.gcno *.gcda *.info *.out report *.dSYM test2.out *.gch *.o .vscode .DS_Store a.out s21_calc.c.gcov test_cov CPPLINT.cfg s21_calc ../.DS_Store ../.vscode 
