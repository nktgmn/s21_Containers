OS := $(shell uname)

GCC = gcc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = --std=c++17
LINKFLAGS = -lstdc++ -lm
GCOV_FLAGS = -fprofile-arcs -ftest-coverage --coverage

TEST_SRC = test/test.cpp

TEST_OUTPUT = test/test_bin
GCOV_OUTPUT = test/gcov/gcov_test
GCOV_FOLDER = test/gcov

ifeq ($(OS), Darwin)
	GTEST_FLAGS = -I/opt/homebrew/opt/googletest/include -L/opt/homebrew/opt/googletest/lib -lgtest -lgtest_main -pthread
	OPEN_CMD = open
	LCOV_FLAG = --ignore-errors inconsistent
else
	GTEST_FLAGS = -I/usr/include/gtest -L/usr/lib -lgtest -lgtest_main -pthread
	OPEN_CMD = xdg-open
	LCOV_FLAG = 
endif


.PHONY: test clean gcov_report clang_format clang_check


test:
	$(GCC) $(CFLAGS) $(CPPFLAGS) $(TEST_SRC) -o $(TEST_OUTPUT) $(GTEST_FLAGS) $(LINKFLAGS)
	./$(TEST_OUTPUT)


gcov_report:
	mkdir -p $(GCOV_FOLDER)
	$(GCC) $(CFLAGS) $(CPPFLAGS) $(TEST_SRC) -o $(GCOV_OUTPUT) $(GTEST_FLAGS) $(GCOV_FLAGS) $(LINKFLAGS)
	./$(GCOV_OUTPUT)
ifeq ($(OS), Darwin)
	mv *.gcno *.gcda $(GCOV_FOLDER)
endif
	lcov --capture --directory $(GCOV_FOLDER) --output-file $(GCOV_FOLDER)/coverage.info $(LCOV_FLAG)
	lcov --remove $(GCOV_FOLDER)/coverage.info '/opt/homebrew/opt/googletest/*' '/usr/*' --output-file $(GCOV_FOLDER)/coverage.info $(LCOV_FLAG)
	genhtml -o $(GCOV_FOLDER)/report $(GCOV_FOLDER)/coverage.info $(LCOV_FLAG)
	$(OPEN_CMD) $(GCOV_FOLDER)/report/index.html


leaks: test
ifeq ($(OS), Darwin)
	leaks --atExit -- $(TEST_OUTPUT)
else
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all $(TEST_OUTPUT)
endif


clang_format:
	# cp ../materials/linters/.clang-format ./.clang-format
	find . -name "*.tpp" -o -name "*.cpp" -o -name "*.h" | xargs clang-format -i
	#rm -f .clang-format


clang_check:
	# cp ../materials/linters/.clang-format ./.clang-format
	find . -name "*.tpp" -o -name "*.cpp" -o -name "*.h" | xargs clang-format -i
	#rm -f .clang-format

cppcheck:
	cppcheck --enable=all --inconclusive --std=c++17 --language=c++ .

clean:
	rm -rf $(GCOV_FOLDER) $(TEST_OUTPUT)
