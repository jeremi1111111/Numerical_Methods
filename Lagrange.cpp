#include <iostream>
#include <fstream>

int pobierz_plik(std::string nazwa_pliku, double *& tablica) {
	std::fstream plik;
	plik.open(nazwa_pliku);
	int wezly = 0;
	if (plik.good()) {
		plik >> wezly;
		tablica = new double[wezly * 2];
		for (int i = 0; i < wezly; i++) {
			plik >> tablica[i * 2] >> tablica[i * 2 + 1];
		}
	}
	plik.close();
	return wezly;
}

double pobierz_zmienna() {
	std::cout << "Podaj wartosc zmiennej x dla ktorej chcesz obliczyc wartosc wielomianu interpolacyjnego: ";
	double zmienna;
	std::cin >> zmienna;
	return zmienna;
}

double interpoluj(double * tablica, int wezly, double zmienna) {
	double wynik = 0.;
	for (int i = 0; i < wezly; i++) {
		double wynik_wielomianu = 1.;
		for (int j = 0; j < wezly; j++) {
			if (i == j) continue;
			double licznik = 0.;
			double mianownik = 0.;
			licznik = zmienna - tablica[j * 2];
			mianownik = tablica[i * 2] - tablica[j * 2];
			wynik_wielomianu = wynik_wielomianu * licznik / mianownik;
		}
		wynik += tablica[i * 2 + 1] * wynik_wielomianu;
	}
	return wynik;
}

void wypisz_dane(double * tablica, int wezly, double zmienna, double wynik) {
	std::cout << "Liczba wezlow: " << wezly << std::endl;
	std::cout << "Dane wezlow:" << std::endl;
	for (int i = 0; i < wezly; i++) {
		std::cout << '(' << tablica[i * 2] << ", " << tablica[i * 2 + 1] << ')' << std::endl;
	}
	std::cout << "Punkt do obliczenia wartosci: " << zmienna << std::endl;
	std::cout << "Wartosc wielomianu Lagrange'a w danym punkcie: " << wynik << std::endl;
}

int main() {
	double* tablica;
	int wezly;
	// wezly = pobierz_plik("funkcja.txt", tablica); // dane do zadania 1
	wezly = pobierz_plik("funkcja_2.txt", tablica); // dane do zadania 2
	double zmienna = pobierz_zmienna();
	double wynik = interpoluj(tablica, wezly, zmienna);
	wypisz_dane(tablica, wezly, zmienna, wynik);
}