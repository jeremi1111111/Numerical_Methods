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

void integral(std::string f, double func(double), double intervals, double a, double b) {
	std::cout << "Wzor calkowanej funkcji: " << f << std::endl;
	std::cout << "Przedzial calkowania: [" << a << ", " << b << ']' << std::endl;
	std::cout << "Liczba przedzialow: " << intervals << std::endl;
	std::cout << "Wynik calki metoda prostokatow: " << calc_rect(func, intervals, a, b) << std::endl;
	std::cout << "Wynik calki metoda trapezow: " << calc_trap(func, intervals, a, b) << std::endl;
	std::cout << "Wynik calki metoda parabol: " << calc_para(func, intervals, a, b) << std::endl << std::endl;
}

void analyse(std::string file_name, double func(double), double a, double b) {
	std::fstream file;
	file.open(file_name, std::ios::out);
	if (file.good()) {
		for (int i = 1; i <= 100; i++) {
			file << calc_rect(func, i, a, b) << ',';
			file << calc_trap(func, i, a, b) << ',';
			file << calc_para(func, i, a, b) << std::endl;
		}
	}
	file.close();
}

int main() {
	integral("sin(x)", std::sin, 4, 0.5, 2.5);
	integral("x^2 + 2x + 5", f1, 4, 0.5, 5);
	integral("exp(x)", std::exp, 4, 0.5, 5);
	//analyse("out1.txt", std::sin, 0.5, 2.5);
	//analyse("out2.txt", f1, 0.5, 5);
	//analyse("out3.txt", std::exp, 0.5, 5);
}