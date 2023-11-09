#include "integral.h"

#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define A_TEST     1.0
#define B_TEST     9.0
#define S_EXPECTED 172.0
#define TEST_COUNT 5

#define USAGE_MSG "Usage: [s]ingle-threaded segment_count:int | [m]ulti-threaded segment_count:int thread_count:int\n"

static double f_test(double x);
static void test(double (*simpson)(double(*)(double), double, double, int));

static int n = 0;

int main(int argc, char ** argv)
{
	if (argc < 3)
	{
		puts(USAGE_MSG);
		return 0;
	}

	switch (argv[1][0])
	{
		case 's':

			if (argc != 3)
			{
				puts(USAGE_MSG);
				return 0;
			}

			n = atoi(argv[2]);
			if (n <= 1)
			{
				printf("Invalid segment count: %s\n", argv[2]);
				return 0;
			}

			test(simpson_1t);

			break;

		case 'm':

			if (argc != 4)
			{
				puts(USAGE_MSG);
				return 0;
			}

			n = atoi(argv[2]);
			if (n <= 1)
			{
				printf("Invalid segment count: %s\n", argv[2]);
				return 0;
			}

			int num_threads = atoi(argv[3]);
			if (num_threads <= 0)
			{
				printf("Invalid thread count: %s\n", argv[3]);
				return 0;
			}

			omp_set_num_threads(num_threads);

			test(simpson_mt);

			break;

		default:
			puts(USAGE_MSG);
			return 0;
	}

	return 0;
}

static void test(double (*simpson)(double(*)(double), double, double, int))
{
	double s_time, e_time, time, min_time = DBL_MAX;
	double integral;
	for (int i = 0; i < TEST_COUNT; i++)
	{
		// Calculating integral
		s_time = omp_get_wtime();
		integral = simpson(f_test, A_TEST, B_TEST, n);
		e_time = omp_get_wtime();

		// Asserting
		time = e_time - s_time;
		printf("s_actual = %lf, time = %lf, diff = %lf\n", integral, time, fabs(integral - S_EXPECTED));

		// Comparing
		if (min_time > time)
			min_time = time;
	}
	printf("min time = %lf\n", min_time);
}

static double f_test(double x)
{
	double sqrt_x = sqrt(x);
	return 3.0 * sqrt_x * (1 + sqrt_x);
}