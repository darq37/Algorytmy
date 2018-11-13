#include <iostream>
#include <cstdio>
#include <ctime>

using namespace std;

int main() {
    int v; // wierzcholki <Vertex>
    int e; // krawedzie <Edges>

    double czas; // zmienna do liczenia czasu

    cout << "Wpisz liczbe wierzcholkow: " << endl;
    cin >> v;
    e = static_cast<int>(0.7 * v);
    clock_t start;
    start = clock();

    cout << "Zawartosc tablicy: " << endl;
    int tablica[e][v];
    for (int i = 0; i < e; i++) {
        cout << "\n";
        for (int j = 0; j < v; j++) {
            cout << 0 + (rand() % 2);
        }
    }
    czas = (clock() - start ) / (double) CLOCKS_PER_SEC;

    cout<< '\n' << "Czas wykoania: " << czas <<'\n';
    return 0;
}