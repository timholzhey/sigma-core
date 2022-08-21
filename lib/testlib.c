//
// Created by tholz on 28.11.2021.
//

#define LOG_LEVEL LOG_LEVEL_DEBUG

#include <string.h>
#include "testlib.h"

static test_registry_t m_tests = {0};
test_t g_current_test = {0};

void register_test(const char* test_group_name, const char* test_name, void* test_function) {
    test_t test = {
            .test_group_name = test_group_name,
            .test_name = test_name,
            .test_function = test_function,
            .test_passed = true,
			.allocated_memory_count = 0,
    };
	m_tests.tests[m_tests.test_count++] = test;
}

int run_tests() {
	if (m_tests.test_count == 0) {
		log_error("No tests registered");
		return 1;
	}
	log_info("Running test group %s", m_tests.tests[0].test_group_name);
    for (int i = 0; i < m_tests.test_count; i++) {
        g_current_test = m_tests.tests[i];
        log_info("> Running test: %s.%s", m_tests.tests[i].test_group_name, m_tests.tests[i].test_name);
        int ret = m_tests.tests[i].test_function();
        if (ret == 0 && g_current_test.test_passed) {
            log_success("\tTest %s.%s passed", m_tests.tests[i].test_group_name, m_tests.tests[i].test_name);
            m_tests.test_passed++;
        } else {
            log_error("\tTest %s.%s failed", m_tests.tests[i].test_group_name, m_tests.tests[i].test_name);
            m_tests.test_failed++;
        }
    }
    log_highlight("Summary: [%d/%d] tests passed\n", m_tests.test_passed, m_tests.test_count);
    return m_tests.test_passed == m_tests.test_count ? 0 : 1;
}

void reset_tests() {
	memset(&m_tests, 0, sizeof(m_tests));
	memset(&g_current_test, 0, sizeof(test_t));
}

void test_failed() {
    g_current_test.test_passed = false;
}
