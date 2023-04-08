#include <iostream>
#include <fstream>
#include <cmath>

double f1(double x) {
	return std::pow(x, 2) + 2 * x + 5;
}

double calc_rect(double func(double), double intervals, double a, double b) {
	double result = 0.;
	double step = std::abs(b - a) / intervals;
	double x = std::min(a, b);
	for (int i = 0; i < intervals; i++) {
		result += step * func(step / 2 + x);
		x += step;
	}
	return result;
}

double calc_trap(double func(double), double intervals, double a, double b) {
	double result = 0.;
	double step = std::abs(b - a) / intervals;
	double x = std::min(a, b);
	for (int i = 0; i < intervals; i++) {
		result += step * (func(x) + func(x + step)) / 2;
		x += step;
	}
	return result;
}

double calc_para(double func(double), double intervals, double a, double b) {
	double result = 0.;
	double step = std::abs(b - a) / intervals;
	double x = std::min(a, b);
	for (int i = 0; i < intervals; i++) {
		result += step / 6 * (func(x) + 4 * func((2 * x + step) / 2) + func(x + step));
		x += step;
	}
	return result;
}

double* calc_Gauss(double func(double), double a, double b) {
	double* results = new double[3];
	double sq_arr_2[] = {
		-sqrt(3.) / 3.,
		sqrt(3.) / 3.
	};
	double sq_wgt_2[] = {
		1.,
		1.
	};
	double result = 0.;
	for (int i = 0; i < 2; i++) {
		double t = (a + b) / 2. + (b - a) * sq_arr_2[i] / 2.;
		result += sq_wgt_2[i] * func(t);
	}
	result *= (b - a) / 2.;
	results[0] = result;

	double sq_arr_3[] = {
		-sqrt(3. / 5.),
		0.,
		sqrt(3. / 5.)
	};
	double sq_wgt_3[] = {
		5. / 9.,
		8. / 9.,
		5. / 9.
	};
	result = 0.;
	for (int i = 0; i < 3; i++) {
		double t = (a + b) / 2. + (b - a) * sq_arr_3[i] / 2.;
		result += sq_wgt_3[i] * func(t);
	}
	result *= (b - a) / 2.;
	results[1] = result;

	double sq_arr_4[] = {
		-sqrt(525. + (70. * sqrt(30.))) / 35.,
		-sqrt(525. - (70. * sqrt(30.))) / 35.,
		sqrt(525. - (70. * sqrt(30.))) / 35.,
		sqrt(525. + (70. * sqrt(30.))) / 35.
	};
	double sq_wgt_4[] = {
		(18. - sqrt(30.)) / 36.,
		(18. + sqrt(30.)) / 36.,
		(18. + sqrt(30.)) / 36.,
		(18. - sqrt(30.)) / 36.
	};
	result = 0.;
	for (int i = 0; i < 4; i++) {
		double t = (a + b) / 2. + (b - a) * sq_arr_4[i] / 2.;
		result += sq_wgt_4[i] * func(t);
	}
	result *= (b - a) / 2.;
	results[2] = result;
	return results;
}

void integral(std::string f, double func(double), double intervals, double a, double b, double result) {
	std::cout << "Wzor calkowanej funkcji: " << f << std::endl;
	std::cout << "Przedzial calkowania: [" << a << ", " << b << ']' << std::endl;
	std::cout << "Liczba przedzialow: " << intervals << std::endl;
	double* results_Gauss = calc_Gauss(func, a, b);
	std::cout << "Wynik calki metoda Gaussa-Legendre\'a:" << std::endl;
	std::cout << "kwadratury 2-wezlowej: " << results_Gauss[0] << std::endl;
	std::cout << "kwadratury 3-wezlowej: " << results_Gauss[1] << std::endl;
	std::cout << "kwadratury 4-wezlowej: " << results_Gauss[2] << std::endl;
	std::cout << "Wynik calki metoda prostokatow: " << calc_rect(func, intervals, a, b) << std::endl;
	std::cout << "Wynik calki metoda trapezow: " << calc_trap(func, intervals, a, b) << std::endl;
	std::cout << "Wynik calki metoda parabol: " << calc_para(func, intervals, a, b) << std::endl;
	std::cout << "Wynik dokladny calki: " << result << std::endl << std::endl;
}

int main() {
	integral("sin(x)", std::sin, 20, 0.5, 2.5, 1.67872);
	integral("x^2 + 2x + 5", f1, 20, 0.5, 5, 88.875);
	integral("exp(x)", std::exp, 20, 0.5, 5, 146.76443);
}