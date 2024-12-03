CC = g++
TESTFLAGS = -lgtest -lgmock -pthread
CFLAGS= -std=c++17 -Wall -Werror -Wextra
GCOVFLAGS = -fprofile-arcs -ftest-coverage
FUNC =  s21_matrix_oop.h s21_matrix.cpp

all: test

s21_matrix_oop.a : 
	$(CC) $(CFLAGS) -c $(FUNC)
	ar rcs s21_matrix_oop.a *.o
	rm -rf *.o

test: clean
	$(CC) $(CFLAGS) test.cpp $(FUNC) -o test $(TESTFLAGS)
	./test

test_obj:
	$(CC) $(CFLAGS) test.cpp $(FUNC) -c $(TESTFLAGS)

gcov_report: test_obj
	$(CC) $(GCOVFLAGS) $(CFLAGS) test.o $(FUNC) -o test $(TESTFLAGS)
	./test
	lcov -t "test" -o test.info -c -d . --ignore-errors mismatch
	genhtml -o report test.info
	rm -rf gcovreport gcovreport.info *.gcda *.gcno string_test.gcda string_test.gcno
	open report/index.html
rebuild: clean all

clean: 
	rm -rf *.o test *.a a.out *.gcno *.gcda test.dSYM *.info report *.h.gch test *.log

style:
	cp ../materials/linters/.clang-format ./
	clang-format -i --style=google *.cpp *.h
	rm -rf .clang-format

check_style:
	cp ../materials/linters/.clang-format ./
	clang-format -n --style=google *.cpp *.h
	rm -rf .clang-format

valgrind: test
	valgrind --tool=memcheck --leak-check=yes ./test
	make clean

