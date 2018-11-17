#include <random>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;

void wypiszMacierz(int n, int **macierzSasiedztwa);

void wypiszParyBrakujacychKrawedzi(const vector<pair<int, int>> &puste);

void wstawSymetrycznieDoMacierzy(int **macierz, int i, int j, int wartosc);


int **stworzMacierzWypelnionaZerami(int n);

int *permutacjaIndeksow(int n);

int main() {
    int n; // wierzcholki <Vertex>
    int k; // krawedzie <Edges>
    char tryb;
    double czas; // zmienna do liczenia czasu

    cout << "wybierz tryb działania programu:" << '\n';
    cout << "Tryb A - wybierz a" << endl;
    cout << "Tryb B - wybierz b" << endl;
    cin >> tryb;
    switch (tryb) {
        case 'a': {
            cout << "Wybrano tryb A!" << endl;
            cout << "Podaj liczbą wierzchołków: " << endl;
            cin >> n;
            int maksymalnaIloscKrawedzi = n * (n - 1) / 2;
            int minimalnaIloscKrawedzi = static_cast<int>(ceil(0.25 * n * (n - 1)));
            cout << "minimalna liczba krawędzi to: " << minimalnaIloscKrawedzi << endl;
            cout << "Maksymalna liczba krawędzi to: " << maksymalnaIloscKrawedzi << endl;
            cout << "podaj liczbe krawędzi" << endl;
            cin >> k;
            while (k > maksymalnaIloscKrawedzi || k < minimalnaIloscKrawedzi) {
                cout << "Podałeś liczbę wierzchołków spoza zakresu!!!" << endl;
                cout << "Wprowadź nową wartosć: " << endl;
                cin >> k;
            }
            cout << "Rezerwuje pamięć i wypełniam macierz sąsiedztwa zerami... " << endl;
            int **macierzSasiedztwa = stworzMacierzWypelnionaZerami(n);
            cout << "Tworze tablice permutacji krawędzi..." << endl;
            int *possibleEdges = permutacjaIndeksow(n);

            cout << endl << "Wypelniam tablice wedlug losowej permutacji... 0..n-1" << endl;
            for (int i = 0; i < n - 1; i++) {
                wstawSymetrycznieDoMacierzy(macierzSasiedztwa, possibleEdges[i], possibleEdges[i + 1], 1);
            }
            int iloscBrakujacychKrawedzi = k - (n - 1);
            cout << "Zabraklo nam: " << iloscBrakujacychKrawedzi << " krawedzi do wymaganych " << k << endl;
            vector<pair<int, int>> puste;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < i; j++) {
                    if (macierzSasiedztwa[i][j] == 0) {
                        puste.emplace_back(i, j);
                    }
                }
            }
            cout << "Mozliwe miejsca na krawedz:" << puste.size() << endl;
            wypiszParyBrakujacychKrawedzi(puste);
            cout << "Macierz przed wypelnianiem losowo " << iloscBrakujacychKrawedzi << " miejsc..";
            wypiszMacierz(n, macierzSasiedztwa);
            shuffle(puste.begin(), puste.end(), std::mt19937(std::random_device()()));
            for (int i = 0; i < iloscBrakujacychKrawedzi; i++) {
                wstawSymetrycznieDoMacierzy(macierzSasiedztwa, puste[i].first, puste[i].second, 1);
            }
            cout << endl << "Zawartosc macierzy sąsiedztwa: " << endl;
            wypiszMacierz(n, macierzSasiedztwa);
            break;
        }
        case 'b': {
            cout << "Wybrano tryb B" << endl;
            cout << "Podaj liczbą wierzchołków: " << endl;
            cin >> n;
            double zapelnienie;
            cout << "Podaj zapelnenie grafu: (0.5 - 1.0)" << endl;
            cin >> zapelnienie;
            k = static_cast<int>(zapelnienie * n);
            cout << "Zapełnienie grafu wynosi " << zapelnienie * 100 << "%." << endl;
            cout << "Graf ma teraz " << k << " krawędzi" << endl;
            break;
        }
        default: {
            cout << "Nie wybrano odpowiedniego trybu!" << endl;
            break;
        }
    }

    /*clock_t start;
    start = clock();

    cout << "Zawartosc tablicy: " << endl;
    int tablica[k][n];
    for (int i = 0; i < k; i++) {
        cout << "\n";
        for (int j = 0; j < n; j++) {
            cout << 0 + (rand() % 2);
        }
    }
    czas = (clock() - start) / (double) CLOCKS_PER_SEC;

    cout << '\n' << "Czas wykoania: " << czas << '\n';
     */

    return 0;
}

int *permutacjaIndeksow(int n) {
    int *possibleEdges = new int[n];
    for (int i = 0; i < n; i++) {
        possibleEdges[i] = i;
    }
    shuffle(possibleEdges, possibleEdges + n, mt19937(random_device()()));
    cout << "Losowa permutacja: " << endl;
    for (int i = 0; i < n; i++) {
        cout << possibleEdges[i] << " ";
    }
    return possibleEdges;
}

int **stworzMacierzWypelnionaZerami(int n) {
    int **macierzSasiedztwa;
    macierzSasiedztwa = new int *[n];
    for (int i = 0; i < n; i++) {
        macierzSasiedztwa[i] = new int[n];
        for (int j = 0; j < n; j++) {
            macierzSasiedztwa[i][j] = 0;
        }
    }
    return macierzSasiedztwa;
}

void wypiszParyBrakujacychKrawedzi(const vector<pair<int, int>> &puste) {
    for (int i = 0; i < puste.size(); i++) {
        cout << "[" << puste[i].first << "][" << puste[i].second << "]" << endl;
    }
}

void wypiszMacierz(int n, int **macierzSasiedztwa) {
    for (int i = 0; i < n; i++) {
        cout << "\n";
        for (int j = 0; j < n; j++) {
            cout << macierzSasiedztwa[i][j] << " ";
        }
    }
}

void wstawSymetrycznieDoMacierzy(int **macierz, int i, int j, int wartosc) {
    macierz[i][j] = wartosc;
    macierz[j][i] = wartosc;
}
