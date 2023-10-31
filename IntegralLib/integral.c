#include "pch.h"
#include "integral.h"

double simpson_1t(double (*f)(double x), double a, double b, int n)
{
	// Calculation storage
	double p1 = 0, p2 = 0, p3 = 0, p4 = 0;

	// h value
	double h = (b - a) / (double)(n);

	// 1st part
	p1 = 0.5 * f(a);

	// 2nd part
	for (int i = 1; i <= n - 1; i++)
		p2 += f(a + (double)i * h);

	// 3rd part
	for (int i = 1; i <= n; i++)
		p3 += f((2.0 * a + (2 * (double)i - 1) * h) / 2.0);
	p3 *= 2.0;

	// 4th part
	p4 = 0.5 * f(b);

	// Return
	return (h / 3.0) * (p1 + p2 + p3 + p4);
}

double simpson_mt(double (*f)(double x), double a, double b, int n)
{
	// Calculation storage
	double p1 = 0, p2 = 0, p3 = 0, p4 = 0;
	int i;

	// h value
	double h = (b - a) / (double)(n);

	// 1st part
	p1 = 0.5 * f(a);

	// 2nd part
	#pragma omp parallel for reduction(+:p2) schedule(static)
	for (i = 1; i <= n - 1; i++)
		p2 += f(a + (double)i * h);

	// 3rd part
	#pragma omp parallel for reduction(+:p3) schedule(static)
	for (i = 1; i <= n; i++)
		p3 += f((2.0 * a + (2 * (double)i - 1) * h) / 2.0);
	p3 *= 2.0;

	// 4th part
	p4 = 0.5 * f(b);

	// Return
	return (h / 3.0) * (p1 + p2 + p3 + p4);
}
