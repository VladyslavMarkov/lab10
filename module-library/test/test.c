#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <check.h>

START_TEST(test_lab05_standart)
{
	int test_x = 20;
	int test_y = 1;
	int test_result = 19;
	int actual_result = lab05(test_x, test_y);

	ck_assert_int_eq(test_result, actual_result);
}
END_TEST

START_TEST(test_lab05_y_more_x)
{
	int test_x = 1;
	int test_y = 20;
	int test_result = 19;
	int actual_result = lab05(test_x, test_y);

	ck_assert_int_eq(test_result, actual_result);
}
END_TEST

START_TEST(test_lab05_x_eq_y)
{
	int test_x = 20;
	int test_y = 20;
	int test_result = 0;
	int actual_result = lab05(test_x, test_y);

	ck_assert_int_eq(test_result, actual_result);
}
END_TEST

START_TEST(test_lab06_standart)
{
	int a = 1000;
	long int expected[63] = { 1001, 1010, 1102, 1111, 1120, 1203, 1212, 1221, 1230, 1304, 1313, 1322, 1331, 1340, 1405, 1414,
				  1423, 1432, 1441, 1450, 1506, 1515, 1524, 1533, 1542, 1551, 1560, 1607, 1616, 1625, 1634, 1643,
				  1652, 1661, 1670, 1708, 1717, 1726, 1735, 1744, 1753, 1762, 1771, 1780, 1809, 1818, 1827, 1836,
				  1845, 1854, 1863, 1872, 1881, 1890, 1919, 1928, 1937, 1946, 1955, 1964, 1973, 1982, 1991 };

	for (long int ticket = 0; ticket != 62; ticket++) {
		int actual = lab06(a, ticket);
		ck_assert_int_eq(actual, expected[ticket]);
	}
}
END_TEST

START_TEST(test_lab06_max_const)
{
	int a = 2000;
	long int expected = 0;
	long int ticket = 1;
	int actual = lab06(a, ticket);

	ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_lab06_a_less_mini_const)
{
	int a = 999;
	long int expected = 0;
	int actual = lab06(a, 0);

	ck_assert_int_eq(actual, expected);
}
END_TEST

START_TEST(test_lab06_a_more_max_const)
{
	int a = 2001;
	long int expected = 0;
	int actual = lab06(a, 0);

	ck_assert_int_eq(actual, expected);
}
END_TEST

Suite *lab_test_suite(void)
{
	Suite *s;
	TCase *tc_lab05;
	TCase *tc_lab06;

	s = suite_create("lab09");

	tc_lab05 = tcase_create("lab_05");

	tcase_add_test(tc_lab05, test_lab05_standart);
	tcase_add_test(tc_lab05, test_lab05_y_more_x);
	tcase_add_test(tc_lab05, test_lab05_x_eq_y);

	tc_lab06 = tcase_create("lab_06");

	tcase_add_test(tc_lab06, test_lab06_standart);
	tcase_add_test(tc_lab06, test_lab06_max_const);
	tcase_add_test(tc_lab06, test_lab06_a_less_mini_const);
	tcase_add_test(tc_lab06, test_lab06_a_more_max_const);

	suite_add_tcase(s, tc_lab05);
	suite_add_tcase(s, tc_lab06);

	return s;
}

int main(void)
{
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = lab_test_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
