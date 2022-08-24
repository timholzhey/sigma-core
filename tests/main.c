//
// Created by Tim Holzhey on 21.08.22.
//

#include "testlib.h"

TEST_GROUP_REG(test_lexer);
TEST_GROUP_REG(test_parser);
TEST_GROUP_REG(test_preprocessor);

int main() {
	TEST_GROUP_RUN(test_lexer);
	TEST_GROUP_RUN(test_parser);
	TEST_GROUP_RUN(test_preprocessor);
}
