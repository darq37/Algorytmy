#include <iostream>
#include <cstdio>
#include <ctime>

using namespace std;

int main() {
    int n; // wierzcholki <Vertex>
    int k; // krawedzie <Edges>
    char tryb;
    double czas; // zmienna do liczenia czasu
    int tablica[k][n];

    cout << "wybierz tryb działania programu:" << '\n';
    cout << "Tryb A - wybierz a" << endl;
    cout << "Tryb B - wybierz b" << endl;
    cin >> tryb;
    switch (tryb){
        case 'a':
            cout << "Wybrano tryb A!"<< endl;
            int n;
            cout << "Podaj liczbą wierzchołków: " << endl;
            cin >> n;
            int k;
            k = static_cast<int>(0.7 * n);
            cout <<"Wylosowano ilosc krawedzi: " << k << endl;
            cout << "Zawartosc tablicy: " << endl;
            for (int i = 0; i < n; i++) {
                cout << "\n";
                for (int j = 0; j < k; j++) {
                    cout << 0 + (rand() % 2);
                }
            }
            break;
        case 'b':
            cout << "Wybrano tryb B" << endl;
            cout << "Podaj liczbą wierzchołków: " << endl;
            cin >> n;
            double zapelnienie;
            cout << "Podaj zapelnenie grafu: (0.5 - 1.0)" << endl;
            cin >> zapelnienie;
            k = static_cast<int>(zapelnienie * n);
            cout << "Zapełnienie grafu wynosi " << zapelnienie*100 <<"%." << endl;
            cout << "Graf ma teraz " << k << " krawędzi" << endl;
            break;

        default:
            cout << "Nie wybrano odpowiedniego trybu!" << endl;
            break;
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

    /*int score;

    cout << "Score:";
    cin >> score;

    switch(score){
        case 0:
            cout << "a";
            break;
        case 1 ... 9:
            cout << "b";
            break;
        case 11 ... 24:
            cout << "c";
            break;
        case 25 ... 49:
            cout << "d";
            break;
        case 50 ... 100:
            cout << "e";
            break;
        default:
            cout << "BAD VALUE";
            break;
    }
    cout << endl;*/



    return 0;
}

