#include <iostream>
#include <fstream>

int pobierz_plik(std::string nazwa_pliku, double*& tablica) {
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

double interpoluj(double* tablica, int wezly, double zmienna, double* wspolczynniki) {
	double** ilorazy = new double* [wezly];
	for (int i = 0; i < wezly; i++) {
		ilorazy[i] = new double[wezly];
		ilorazy[i][0] = tablica[i * 2 + 1];
		for (int j = 1; j < wezly; j++) {
			if (j > i) {
				ilorazy[i][j] = 0;
				continue;
			}
			ilorazy[i][j] = 1;
			double licznik = ilorazy[i][j - 1] - ilorazy[i - 1][j - 1];
			double mianownik = tablica[i * 2] - tablica[(i - j) * 2];
			ilorazy[i][j] = licznik / mianownik;
		}
	}
	double* tablicaP = new double[wezly];
	for (int i = 0; i < wezly; i++) {
		tablicaP[i] = 1;
		for (int j = 0; j < i; j++) {
			double p = zmienna - tablica[j * 2];
			tablicaP[i] = tablicaP[i] * p;
		}
	}
	double wynik = 0;
	for (int i = 0; i < wezly; i++) {
		wspolczynniki[i] = ilorazy[i][i];
		wynik += wspolczynniki[i] * tablicaP[i];
	}
	return wynik;
}

void wypisz_dane(double* tablica, int wezly, double zmienna, double wynik, double* wspolczynniki) {
	std::cout << "Liczba wezlow: " << wezly << std::endl;
	std::cout << "Dane wezlow:" << std::endl;
	for (int i = 0; i < wezly; i++) {
		std::cout << '(' << tablica[i * 2] << ", " << tablica[i * 2 + 1] << ')' << std::endl;
	}
	std::cout << "Punkt do obliczenia wartosci: " << zmienna << std::endl;
	std::cout << "Wartosc wielomianu Newtona w danym punkcie: " << wynik << std::endl;
	std::cout << "Wspolczynniki wielomianu Newtona: ";
	for (int i = 0; i < wezly; i++) {
		std::cout << wspolczynniki[i] << ' ';
	}
	std::cout << std::endl;
}

int main() {
	double* tablica;
	int wezly;

	// przyklad 1
	wezly = pobierz_plik("MN-2-p1.txt", tablica);
	for (int i = 0; i < 2; i++) {
		double zmienna = pobierz_zmienna();
		double* wspolczynniki = new double[wezly];
		double wynik = interpoluj(tablica, wezly, zmienna, wspolczynniki);
		wypisz_dane(tablica, wezly, zmienna, wynik, wspolczynniki);
	}

	// przyklad 2
	wezly = pobierz_plik("MN-2-p2.txt", tablica);
	for (int i = 0; i < 2; i++) {
		double zmienna = pobierz_zmienna();
		double* wspolczynniki = new double[wezly];
		double wynik = interpoluj(tablica, wezly, zmienna, wspolczynniki);
		wypisz_dane(tablica, wezly, zmienna, wynik, wspolczynniki);
	}
}