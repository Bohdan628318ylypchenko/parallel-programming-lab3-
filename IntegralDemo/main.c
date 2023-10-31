#include "integral.h"

#include <omp.h>
#include <math.h>
#include <stdio.h>

#define N_TEST_SMALL 500
#define N_TEST_BIG   2000000
#define E_TEST       0.001
#define A_TEST       1.0
#define B_TEST       9.0
#define S_EXPECTED   172.0

static double f_test(double x);
static void test(double (*simpson)(double(*)(double), double, double, int), int n);

int main(int argc, char * argv)
{
	test(simpson_1t, N_TEST_SMALL);
	test(simpson_1t, N_TEST_BIG);

	puts("=======");

	test(simpson_mt, N_TEST_SMALL);
	test(simpson_mt, N_TEST_BIG);

	return 0;
}

static void test(double (*simpson)(double(*)(double), double, double, int), int n)
{
	// Calculating integral
	double s_time = omp_get_wtime();
	double s_actual = simpson(f_test, A_TEST, B_TEST, n);
	double e_time = omp_get_wtime();

	// Asserting
	printf("s_actual = %lf, time = %lf | n = %d\n", s_actual, e_time - s_time, n);
	if (fabs(s_actual - S_EXPECTED) <= E_TEST)
		puts("Assertion succeeded");
	else
		puts("Assertion failed");
}

static double f_test(double x)
{
	long double sqrt_x = sqrt(x);
	return 3.0 * sqrt_x * (1 + sqrt_x);
}