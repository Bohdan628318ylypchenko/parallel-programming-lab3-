#pragma once

/// <summary>
/// Numeric integration Simpson method
/// single-thread implementation.
/// </summary>
/// <param name="f"> Function to integrate as fpointer. </param>
/// <param name="a"> Integration segment start. </param>
/// <param name="b"> Integration segment end. </param>
/// <param name="n"> Elementary segment count. </param>
/// <returns> Integral value as double. </returns>
double simpson_1t(double (*f)(double x), double a, double b, int n);

/// <summary>
/// Numeric integration Simpson method
/// multi-thread implementation.
/// </summary>
/// <param name="f"> Function to integrate as fpointer. </param>
/// <param name="a"> Integration segment start. </param>
/// <param name="b"> Integration segment end. </param>
/// <param name="n"> Elementary segment count. </param>
/// <returns> Integral value as double. </returns>
double simpson_mt(double (*f)(double x), double a, double b, int n);
