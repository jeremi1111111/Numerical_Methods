#include <iostream>
#include <fstream>

int get_file(std::string file_name, double**& arr) {
	std::fstream file;
	file.open(file_name);
	int size = 0;
	if (file.good()) {
		file >> size;
		arr = new double*[size];
		for (int i = 0; i < size; i++) {
			arr[i] = new double[size + 1];
			for (int j = 0; j < size + 1; j++) {
				file >> arr[i][j];
			}
		}
	}
	file.close();
	return size;
}

void show_arr(double** arr, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size + 1; j++) {
			std::cout << arr[i][j] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool check_zero_diagonal(double** arr, int size) {
	for (int i = 0; i < size; i++) {
		if (arr[i][i] == 0) return true;
	}
	return false;
}

void solve_gauss(double** arr, int size) {
	std::cout << "Macierz wejsciowa" << std::endl;
	show_arr(arr, size);
	for (int i = 0; i < size - 1; i++) {
		if (check_zero_diagonal(arr, size) == true) {
			std::cout << "Zero na przekatnej, przerwano dzialanie programu" << std::endl;
			return;
		}
		double* subtracting = arr[i];
		for (int j = i + 1; j < size; j++) {
			double* modifying = arr[j];
			double multiplier = modifying[i] / subtracting[i];
			for (int k = i; k < size + 1; k++) {
				modifying[k] -= subtracting[k] * multiplier;
			}
		}
	}
	std::cout << "Macierz po pierwszym etapie obliczen" << std::endl;
	show_arr(arr, size);

	double* solution = new double[size] {};
	for (int i = size - 1; i >= 0; i--) {
		double* solving = arr[i];
		double counter = solving[size];
		double denominator = solving[i];
		for (int j = i + 1; j < size; j++) {
			counter -= solving[j] * solution[j];
		}
		solution[i] = counter / denominator;
	}
	std::cout << "Rozwiazanie ukladu rownan" << std::endl;
	for (int i = 0; i < size; i++) {
		std::cout << solution[i] << '\t';
	}
	std::cout << std::endl;
}

void clear_arr(double**& arr, int size) {
	for (int i = 0; i < size; i++) {
		delete[] arr[i];
	}
	delete[] arr;
	arr = nullptr;
}

int main() {
	double** arr;
	int size = get_file("RURL_dane1.txt", arr);
	std::cout << "Plik RURL_dane1.txt" << std::endl;
	solve_gauss(arr, size);
	clear_arr(arr, size);
	std::cout << std::endl << "Plik RURL_dane2.txt" << std::endl;
	size = get_file("RURL_dane2.txt", arr);
	solve_gauss(arr, size);
}