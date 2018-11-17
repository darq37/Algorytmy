#include <iostream>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstdlib>

using namespace std;

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
            bool tablica[n][n];
            int edges[n];
            for (int i = 0; i < n; ++i) {
                edges[i] = i;
            }

            double kmin = 0.25 * n * (n - 1);
            double kmax = 0.5 * n * (n - 1);
            cout << "minimalna liczba krawędzi(by stworzyc spojny,pełny graf) dla danej liczny wierzcholkow to: "
                 << ceil(kmin) << endl;
            cout << "Maksymalna liczba krawędzi to: " << kmax << endl;
            cout << "podaj liczbe krawędzi" << endl;
            cin >> k;
            while (k > kmax || k < kmin) {
                cout << "Podałeś liczbę wierzchołków spoza zakresu!!!" << endl;
                cout << "Wprowadź nową wartosć: " << endl;
                cin >> k;
            }
            cout << "Wypelniam tablice... " << endl;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    tablica[i][j] = false;
                }
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    tablica[i][i-1] = true;
                    tablica[j][j+1] = true;
                }
            }


            cout << "Zawartosc tablicy po wypelnieniu zerami: " << endl;
            for (int i = 0; i < n; i++) {
                cout << "\n";
                for (int j = 0; j < n; j++) {
                    cout << tablica[i][j];
                }
            }
        }
            break;

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
