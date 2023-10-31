#pragma once

double simpson_1t(double (*f)(double x), double a, double b, int n);

double simpson_mt(double (*f)(double x), double a, double b, int n);
