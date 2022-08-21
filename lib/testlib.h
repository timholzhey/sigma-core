//
// Created by tholz on 28.11.2021.
//

#ifndef TESTLIB_TEST_H
#define TESTLIB_TEST_H

#define LOG_LEVEL_OFF		0
#define LOG_LEVEL_ERROR		1
#define LOG_LEVEL_WARNING	2
#define LOG_LEVEL_INFO		3
#define LOG_LEVEL_SUCCESS	4
#define LOG_LEVEL_HIGHLIGHT	5
#define LOG_LEVEL_DEBUG		6
#define LOG_LEVEL_TRACE		7

#ifndef LOG_LEVEL
#define LOG_LEVEL LOG_LEVEL_INFO
#endif

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_TEST_COUNT 100
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define TEST_ASSERT(assertion) \
    if (!(assertion)) { \
        log_error("\tAssertion failed: Expected 1, got 0 at %s:%d", __FILE__, __LINE__); \
        test_failed();          \
        return 1; \
    }
#define TEST_EXPECT(assertion) \
    if (!(assertion)) { \
        log_error("\tAssertion failed: Expected 1, got 0 at %s:%d", __FILE__, __LINE__); \
        test_failed();          \
    }

#define TEST_FAIL_WITH_MSG(msg, ...) \
	log_raw_error("\tAssertion failed: "); \
	log_raw_error(msg, ##__VA_ARGS__); \
	log_raw_error(" at %s:%d\n", __FILE__, __LINE__); \
	test_failed(); \
	return 1;

#define TEST_ERROR_WITH_MSG(msg, ...) \
	log_raw_error("\tAssertion failed: "); \
	log_raw_error(msg, ##__VA_ARGS__); \
	log_raw_error(" at %s:%d\n", __FILE__, __LINE__); \
	test_failed();


#define TEST_ASSERT_TRUE(assertion) \
	if (!(assertion)) { \
        TEST_FAIL_WITH_MSG("Expected true, got false"); \
    }
#define TEST_EXPECT_TRUE(assertion) \
	if (!(assertion)) { \
		TEST_ERROR_WITH_MSG("Expected true, got false"); \
	}

#define TEST_ASSERT_FALSE(assertion) \
	if (assertion) { \
		TEST_FAIL_WITH_MSG("Expected false, got true"); \
	}
#define TEST_EXPECT_FALSE(assertion) \
	if (assertion) { \
		TEST_ERROR_WITH_MSG("Expected false, got true"); \
	}

#define TEST_ASSERT_EQ(a, b) \
	if ((a) != (b)) { \
		TEST_FAIL_WITH_MSG("Expected %d, got %d", (a), (b)); \
	}
#define TEST_EXPECT_EQ(a, b) \
	if ((a) != (b)) { \
		TEST_ERROR_WITH_MSG("Expected %d, got %d", (a), (b)); \
	}

#define TEST_ASSERT_EQ_U8(a, b) \
	if ((a) != (b)) { \
		TEST_FAIL_WITH_MSG("Expected %u, got %u", (uint8_t)(b), (uint8_t)(a)); \
	}
#define TEST_EXPECT_EQ_U8(a, b) \
	if ((a) != (b)) { \
		TEST_ERROR_WITH_MSG("Expected %u, got %u", (uint8_t)(b), (uint8_t)(a)); \
	}
#define TEST_ASSERT_EQ_U16(a, b) \
	if ((a) != (b)) { \
		TEST_FAIL_WITH_MSG("Expected %u, got %u", (uint16_t)(b), (uint16_t)(a)); \
	}
#define TEST_EXPECT_EQ_U16(a, b) \
	if ((a) != (b)) { \
		TEST_ERROR_WITH_MSG("Expected %u, got %u", (uint16_t)(b), (uint16_t)(a)); \
	}
#define TEST_ASSERT_EQ_U32(a, b) \
	if ((a) != (b)) { \
		TEST_FAIL_WITH_MSG("Expected %u, got %u", (uint32_t)(b), (uint32_t)(a)); \
	}
#define TEST_EXPECT_EQ_U32(a, b) \
	if ((a) != (b)) { \
		TEST_ERROR_WITH_MSG("Expected %u, got %u", (uint32_t)(b), (uint32_t)(a)); \
	}
#define TEST_ASSERT_EQ_U64(a, b) \
	if ((a) != (b)) { \
		TEST_FAIL_WITH_MSG("Expected %lu, got %lu", (uint64_t)(b), (uint64_t)(a)); \
	}
#define TEST_EXPECT_EQ_U64(a, b) \
	if ((a) != (b)) { \
		TEST_ERROR_WITH_MSG("Expected %lu, got %lu", (uint64_t)(b), (uint64_t)(a)); \
	}

#define TEST_ASSERT_EQ_I8(a, b) \
	if ((a) != (b)) { \
		TEST_FAIL_WITH_MSG("Expected %d, got %d", (int8_t)(b), (int8_t)(a)); \
	}
#define TEST_EXPECT_EQ_I8(a, b) \
	if ((a) != (b)) { \
		TEST_ERROR_WITH_MSG("Expected %d, got %d", (int8_t)(b), (int8_t)(a)); \
	}
#define TEST_ASSERT_EQ_I16(a, b) \
	if ((a) != (b)) { \
		TEST_FAIL_WITH_MSG("Expected %d, got %d", (int16_t)(b), (int16_t)(a)); \
	}
#define TEST_EXPECT_EQ_I16(a, b) \
	if ((a) != (b)) { \
		TEST_ERROR_WITH_MSG("Expected %d, got %d", (int16_t)(b), (int16_t)(a)); \
	}
#define TEST_ASSERT_EQ_I32(a, b) \
	if ((a) != (b)) { \
		TEST_FAIL_WITH_MSG("Expected %d, got %d", (int32_t)(b), (int32_t)(a)); \
	}
#define TEST_EXPECT_EQ_I32(a, b) \
	if ((a) != (b)) { \
		TEST_ERROR_WITH_MSG("Expected %d, got %d", (int32_t)(b), (int32_t)(a)); \
	}
#define TEST_ASSERT_EQ_I64(a, b) \
	if ((a) != (b)) { \
		TEST_FAIL_WITH_MSG("Expected %ld, got %ld", (int64_t)(b), (int64_t)(a)); \
	}
#define TEST_EXPECT_EQ_I64(a, b) \
	if ((a) != (b)) { \
		TEST_ERROR_WITH_MSG("Expected %ld, got %ld", (int64_t)(b), (int64_t)(a)); \
	}

#define TEST_ASSERT_EQ_FLOAT(a, b) \
	if ((a) != (b)) { \
		TEST_FAIL_WITH_MSG("Expected %f, got %f", (float)(b), (float)(a)); \
	}
#define TEST_EXPECT_EQ_FLOAT(a, b) \
	if ((a) != (b)) { \
		TEST_ERROR_WITH_MSG("Expected %f, got %f", (float)(b), (float)(a)); \
	}
#define TEST_ASSERT_EQ_DOUBLE(a, b) \
	if ((a) != (b)) { \
		TEST_FAIL_WITH_MSG("Expected %f, got %f", (double)(b), (double)(a)); \
	}
#define TEST_EXPECT_EQ_DOUBLE(a, b) \
	if ((a) != (b)) { \
		TEST_ERROR_WITH_MSG("Expected %f, got %f", (double)(b), (double)(a)); \
	}

#define TEST_ASSERT_NOT_NULL(ptr) \
	if (!(ptr)) { \
		TEST_FAIL_WITH_MSG("Expected non-NULL pointer, got NULL"); \
	}
#define TEST_EXPECT_NOT_NULL(ptr) \
	if (!(ptr)) { \
		TEST_ERROR_WITH_MSG("Expected non-NULL pointer, got NULL"); \
	}

#define TEST_ASSERT_EQ_STRING(actual, expect, len) \
	for (int _i = 0; _i < len; _i++) { \
		if ((expect)[_i] != (actual)[_i]) { \
			TEST_FAIL_WITH_MSG("Expected \"%s\", got \"%s\" (%u/%u)", expect, actual, _i, (uint16_t) len); \
		} \
	}
#define TEST_EXPECT_EQ_STRING(actual, expect, len) \
	for (int _i = 0; _i < len; _i++) { \
		if ((expect)[_i] != (actual)[_i]) { \
			TEST_ERROR_WITH_MSG("Expected \"%s\", got \"%s\" (%u/%u)", expect, actual, _i, (uint16_t) len); \
        	break; \
		} \
	}

#define TEST_DEF(test_group_name, test_name) \
    int test_group_name##_##test_name()

#define TEST_REG(test_group_name, test_name) \
    register_test(#test_group_name, #test_name, test_group_name##_##test_name)

#define TEST_RUNNER(test_group_name) \
	void test_group_name##_run()

#define TEST_GROUP_REG(test_group_name) \
	void test_group_name##_run();

#define TEST_GROUP_RUN(test_group_name) \
    reset_tests();                      \
	test_group_name##_run();             \
	run_tests();

#define TESTS_RUN() \
    return run_tests()

#define STRINGIFY(x) #x

// read file using fopen, log_error and return 1 if failed to open or failed to allocate, create _size variable
#define TEST_READ_FILE(file_buffer, file_path) \
	char* file_buffer = NULL; \
	size_t file_buffer##_size = 0; \
	FILE* file_buffer##_file = fopen(file_path, "r"); \
	if (!file_buffer##_file) { \
		log_error("\tFailed to open file: %s", file_path); \
		return 1; \
	} \
	fseek(file_buffer##_file, 0, SEEK_END); \
	file_buffer##_size = ftell(file_buffer##_file); \
	rewind(file_buffer##_file); \
	file_buffer = malloc(file_buffer##_size + 1); \
	if (!file_buffer) { \
		log_error("\tFailed to allocate memory for file: %s", file_path); \
		return 1; \
	} \
    g_current_test.allocated_memory[g_current_test.allocated_memory_count++] = file_buffer; \
	if (fread(file_buffer, file_buffer##_size, 1, file_buffer##_file) != 1) { \
		log_error("\tFailed to read file: %s", file_path); \
		return 1; \
	} \
	file_buffer[file_buffer##_size] = '\0'; \
	fclose(file_buffer##_file);

#define TEST_PRINT_BUFFER(buffer_name) \
	for (size_t i = 0; i < buffer_name##_size; i++) { \
		if (isprint(buffer_name[i]) || isspace(buffer_name[i])) { \
			printf("%c", buffer_name[i]); \
		} else { \
			printf("[%02X]", buffer_name[i]); \
		} \
	} \
	printf("\n");

#define TEST_CLEAN_UP() \
	for (size_t i = 0; i < g_current_test.allocated_memory_count; i++) { \
		free(g_current_test.allocated_memory[i]); \
	} \

#define TEST_CLEAN_UP_AND_RETURN(return_value) \
	TEST_CLEAN_UP(); \
	return return_value;

#define log_error(message, ...) \
    if (LOG_LEVEL >= LOG_LEVEL_ERROR) { \
		printf("\033[0;31m" message "\033[0m\n", ##__VA_ARGS__); \
	}
#define log_success(message, ...) \
    if (LOG_LEVEL >= LOG_LEVEL_SUCCESS) { \
		printf("\033[0;32m" message "\033[0m\n", ##__VA_ARGS__); \
	}
#define log_warning(message, ...) \
	if (LOG_LEVEL >= LOG_LEVEL_WARNING) { \
		printf("\033[0;33m" message "\033[0m\n", ##__VA_ARGS__); \
	}
#define log_highlight(message, ...) \
    if (LOG_LEVEL >= LOG_LEVEL_HIGHLIGHT) { \
		printf("\033[0;34m" message "\033[0m\n", ##__VA_ARGS__); \
	}
#define log_info(message, ...) \
    if (LOG_LEVEL >= LOG_LEVEL_INFO) { \
		printf("\033[0;37m" message "\033[0m\n", ##__VA_ARGS__); \
	}
#define log_debug(message, ...) \
	if (LOG_LEVEL >= LOG_LEVEL_DEBUG) { \
		printf("\033[0;37m" message "\033[0m\n", ##__VA_ARGS__); \
	}
#define log_trace(message, ...) \
	if (LOG_LEVEL >= LOG_LEVEL_TRACE) { \
		printf("\033[0;37m" message "\033[0m\n", ##__VA_ARGS__); \
	}
#define log_raw_error(message, ...) \
    if (LOG_LEVEL >= LOG_LEVEL_ERROR) { \
		printf("\033[0;31m" message "\033[0m", ##__VA_ARGS__); \
	}
#define log_raw_success(message, ...) \
    if (LOG_LEVEL >= LOG_LEVEL_SUCCESS) { \
		printf("\033[0;32m" message "\033[0m", ##__VA_ARGS__); \
	}
#define log_raw_warning(message, ...) \
	if (LOG_LEVEL >= LOG_LEVEL_WARNING) { \
		printf("\033[0;33m" message "\033[0m", ##__VA_ARGS__); \
	}
#define log_raw_highlight(message, ...) \
    if (LOG_LEVEL >= LOG_LEVEL_HIGHLIGHT) { \
		printf("\033[0;34m" message "\033[0m", ##__VA_ARGS__); \
	}
#define log_raw_info(message, ...) \
    if (LOG_LEVEL >= LOG_LEVEL_INFO) { \
		printf("\033[0;37m" message "\033[0m", ##__VA_ARGS__); \
	}
#define log_raw_debug(message, ...) \
	if (LOG_LEVEL >= LOG_LEVEL_DEBUG) { \
		printf("\033[0;37m" message "\033[0m", ##__VA_ARGS__); \
	}
#define log_raw_trace(message, ...) \
	if (LOG_LEVEL >= LOG_LEVEL_TRACE) { \
		printf("\033[0;37m" message "\033[0m", ##__VA_ARGS__); \
	}

typedef struct {
    const char* test_group_name;
    const char* test_name;
    int (*test_function)(void);
    int test_passed;
	char* allocated_memory[10];
	uint8_t allocated_memory_count;
} test_t;

typedef struct {
    test_t tests[MAX_TEST_COUNT];
    int test_count;
    int test_passed;
    int test_failed;
} test_registry_t;

extern test_t g_current_test;

void register_test(const char* test_group_name, const char* test_name, void* test_function);
void register_test_group(const char* test_group_name);
void reset_tests();
int run_tests();
void test_failed();

#endif //TESTLIB_TEST_H
