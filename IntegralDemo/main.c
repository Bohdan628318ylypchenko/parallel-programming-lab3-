#include "integral.h"

#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define E_TEST       0.001
#define A_TEST       1.0
#define B_TEST       9.0
#define S_EXPECTED   172.0

#define USAGE_MSG "Usage: test_count:int ([s]ingle-threaded n:int | [m]ulti-threaded segment_count:int thread_count:int)\n"

static double f_test(double x);
static void test(double (*simpson)(double(*)(double), double, double, int));

static int n = 0;

int main(int argc, char ** argv)
{
	if (argc < 4)
	{
		puts(USAGE_MSG);
		return 0;
	}

	int test_count = atoi(argv[1]);
	if (test_count <= 0)
	{
		printf("Invalid test count: %s\n", argv[1]);
		return 0;
	}

	switch (argv[2][0])
	{
		case 's':
			if (argc != 4)
			{
				puts(USAGE_MSG);
				return 0;
			}
			n = atoi(argv[3]);
			if (n <= 1)
			{
				printf("Invalid segment count: %s\n", argv[3]);
				return 0;
			}
			for (int i = 0; i < test_count; i++)
			{
				printf("Single-thread simpson demo #%d\n", i);
				test(simpson_1t);
				printf("Single-thread simpson demo #%d end\n\n", i);
			}
			break;
		case 'm':
			if (argc != 5)
			{
				puts(USAGE_MSG);
				return 0;
			}
			n = atoi(argv[3]);
			if (n <= 1)
			{
				printf("Invalid segment count: %s\n", argv[3]);
				return 0;
			}
			int num_threads = atoi(argv[4]);
			if (n <= 0)
			{
				printf("Invalid segment count: %s\n", argv[1]);
				return 0;
			}
			omp_set_num_threads(num_threads);
			for (int i = 0; i < test_count; i++)
			{
				printf("Multi-thread simpson demo #%d\n", i);
				test(simpson_mt);
				printf("Multi-thread simpson demo #%d end\n\n", i);
			}
			break;
		default:
			puts(USAGE_MSG);
			return 0;
	}

	return 0;
}

static void test(double (*simpson)(double(*)(double), double, double, int))
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