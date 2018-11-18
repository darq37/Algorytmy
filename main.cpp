#include <random>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <climits>
#include <chrono>

using namespace std;

void wypiszMacierz(int n, int **macierzSasiedztwa);

void wypiszParyMiejscNaKrawedzie(const vector<pair<int, int>> &wektorPar);

void wstawSymetrycznieDoMacierzy(int **macierz, int i, int j, int wartosc);

int **stworzMacierzWypelnionaZerami(int n);

int *wygenerujLosowaPermutacjeIndeksowDoN(int n);

vector<pair<int, int>> znajdzMiejscaNaKrawedzie(int n, int *const *macierzSasiedztwa);

int **wygenerujSpojnyGraf(int n, int k);

int losowaWartoscWZakresie(int min, int max);

int znajdzKrotszyDystans(const int *dystans, const bool *znalezione, int n) {
    int min = INT_MAX;
    int min_index = -1;

    for (int i = 0; i < n; i++) {
        if (!znalezione[i] && dystans[i] <= min) {
            min = dystans[i];
            min_index = i;
        }
    }

    return min_index;
}

void printPath(int parent[], int i) {
    if (parent[i] == -1) {
        return;
    }
    printPath(parent, parent[i]);
    cout << i << " ";
}

int printSolution(int dist[], int n, int skad[], int cel) {
    int src = 0;
    cout << "\nTrasa\t\tWaga\tSciezka";
    if (cel != -1) {
        cout << "\n" << src << " -> " << cel << "\t\t" << dist[cel] << "\t\t\t" << src << " ";
        printPath(skad, cel);
    } else {
        for (int i = 0; i < n; i++) {
            cout << "\n" << src << " -> " << i << "\t\t" << dist[i] << "\t\t\t" << src << " ";
            printPath(skad, i);
        }
    }
}

void djikstra(int **graph, int zrodlo, int n, int cel, bool print) {
    int *dystans = new int[n]; // tablica dystansów od źrodłą (zrodlo) do danego wierzchołka
    bool *znalezione = new bool[n]; // tablica zawierajaca "true" dla danego indeksu wierzchołka dla którego znaleziono najkr. scieżkę
    int *parent = new int[n];
    for (int i = 0; i < n; i++) { // iteracja po wszystkich wierchołkach grafu
        dystans[i] = INT_MAX; // dla kazdego wierzchołka ustawiamy koszt drogi na INT_MAX
        znalezione[i] = false; // dla każdego wierzchołka, ustawiamy, że nie znaleźliśmy do niego jeszcze najkrótszej ścieżki (false)
    }
    parent[zrodlo] = -1;
    dystans[zrodlo] = 0; // ustawiamy punkt startowy ustalając dla niego dystans = 0
    for (int j = 0; j < n - 1; j++) {
        int u = znajdzKrotszyDystans(dystans, znalezione, n);
        znalezione[u] = true; //oznaczamy wybrany wierzcholek jako aktualnie sprawdzany
        for (int v = 0; v < n; v++) { // naspisujemy wartosc dystansu, gdy spelnimy wszystkie warunki
            if (!znalezione[v] && graph[u][v] && dystans[u] != INT_MAX && dystans[u] + graph[u][v] < dystans[v]) {
                // warunki, t.j
                // 1. Wierzcholek nie jest juz znaleziony,
                // 2. istnieje krawędź pomiędzy wierzcholkiem a nastepnym w kolejce,
                // 3. suma wag od źródła do aktualnego wierzcholka poprzez  u nie jest większa niz niz dotychczasowa wartosc  wagi wierzcholka v
                dystans[v] = dystans[u] + graph[u][v];
                parent[v] = u;
            }
        }
        if (u == cel) {
            break;
        }
    }
    if (print) {
        printSolution(dystans, n, parent, cel);
    }
}

int main() {
    int n; // wierzcholki <Vertex>
    int k; // krawedzie <Edges>
    char tryb;

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
            int **macierzSasiedztwa = wygenerujSpojnyGraf(n, k);
            cout << endl << "Zawartosc macierzy sąsiedztwa: " << endl;
            wypiszMacierz(n, macierzSasiedztwa);
            int cel;
            cout << endl << "Którego wierzchołka szukasz? (Wisz -1, by wyświetlić najkrótsze drogi do wszystkich wierzchołków_" << endl;
            cin >> cel;
            auto started = chrono::steady_clock::now();
            djikstra(macierzSasiedztwa, 0, n, cel, true);
            auto done = chrono::steady_clock::now();
            cout << '\n' << "Czas wykoania algorytmu: " << chrono::duration<double, nano>(done - started).count() << " ns\n";
            break;
        }
        case 'b': {
            cout << "Wybrano tryb B" << endl;
            cout << "Podaj dolną wartość zakresu:" << endl;
            int zakresMinimum;
            cin >> zakresMinimum;
            cout << "Podaj górną wartość zakresu:" << endl;
            int zakresMaksimum;
            cin >> zakresMaksimum;
            cout << "Podaj liczbę wykonań algorytmu (liczbę losowych grafów/ilość wierzchołków na liczbę z zakresu)" << endl;
            int liczbaWykonan;
            cin >> liczbaWykonan;
            double zapelnienie;
            cout << "Podaj zapelnenie grafu" << endl;
            cin >> zapelnienie;
            cout << "Zapełnienie grafu wynosi " << zapelnienie << "%." << endl;
            for (int i = zakresMinimum; i < zakresMaksimum; i++) {
                int maksymalnaIloscKrawedzi = i * (i - 1) / 2;
                k = static_cast<int>(maksymalnaIloscKrawedzi * zapelnienie / 100);
                cout << "Graf [" << i << "] ma teraz " << k << " krawędzi" << endl;
                double czas = 0;
                for (int j = 0; j < liczbaWykonan; j++) {
                    int **macierzSasiedztwa = wygenerujSpojnyGraf(i, k);
                    //wypiszMacierz(i, macierzSasiedztwa);
                    auto started = chrono::steady_clock::now();
                    djikstra(macierzSasiedztwa, 0, i, -1, false);
                    auto done = chrono::steady_clock::now();
                    czas += chrono::duration<double, nano>(done - started).count();
                }
                cout << '\n' << "Sredni czas: " << czas / liczbaWykonan << " s" << '\n';
            }


            break;
        }
        default: {
            cout << "Nie wybrano odpowiedniego trybu!" << endl;
            break;
        }
    }
    return 0;
}

int **wygenerujSpojnyGraf(int n, int k) {
    //cout << "Rezerwuje pamięć i wypełniam macierz sąsiedztwa zerami... " << endl;
    int **macierzSasiedztwa = stworzMacierzWypelnionaZerami(n);
    int *permutacjaIndeksow = wygenerujLosowaPermutacjeIndeksowDoN(n);
    //cout << endl << "Wypelniam tablice wedlug losowej permutacji... 0..n-1" << endl;
    for (int i = 0; i < n - 1; i++) {
        wstawSymetrycznieDoMacierzy(macierzSasiedztwa, permutacjaIndeksow[i], permutacjaIndeksow[i + 1], losowaWartoscWZakresie(1, 100));
    }
    int iloscBrakujacychKrawedzi = k - (n - 1);
    //cout << "Zabraklo nam: " << iloscBrakujacychKrawedzi << " krawedzi do wymaganych " << k << endl;
    vector<pair<int, int>> miejscaNaKrawedzie = znajdzMiejscaNaKrawedzie(n, macierzSasiedztwa);
    //cout << "Macierz przed wypelnianiem losowo " << iloscBrakujacychKrawedzi << " miejsc..";
    //wypiszMacierz(n, macierzSasiedztwa);
    shuffle(miejscaNaKrawedzie.begin(), miejscaNaKrawedzie.end(), mt19937(random_device()()));
    for (int i = 0; i < iloscBrakujacychKrawedzi; i++) {
        wstawSymetrycznieDoMacierzy(macierzSasiedztwa, miejscaNaKrawedzie[i].first, miejscaNaKrawedzie[i].second, losowaWartoscWZakresie(1, 100));
    }
    return macierzSasiedztwa;
}

vector<pair<int, int>> znajdzMiejscaNaKrawedzie(int n, int *const *macierzSasiedztwa) {
    vector<pair<int, int>> puste;
    for (int i = 0; i < n; i++) { // przejdz przez wiersze macierzy
        for (int j = 0; j < i; j++) { // przejdz przez elementy wiersza az do jego indeksu ( dla wiersza 2 - sprawdzimy [2][0] oraz [2][1]
            if (macierzSasiedztwa[i][j] == 0) { // jezeli to jest puste pole
                puste.emplace_back(i, j); //dodaj parę będącą współrzędnymi tego pola do wektora
            }
        }
    }
    //wypiszParyMiejscNaKrawedzie(puste);
    return puste;
}

int *wygenerujLosowaPermutacjeIndeksowDoN(int n) {
    //cout << "Tworze tablice permutacji krawędzi..." << endl;
    int *possibleEdges = new int[n];
    for (int i = 0; i < n; i++) {
        possibleEdges[i] = i;
    }
    shuffle(possibleEdges, possibleEdges + n, mt19937(random_device()()));
    /*cout << "Losowa permutacja: " << endl;
    for (int i = 0; i < n; i++) {
        cout << possibleEdges[i] << " ";
    }*/
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

void wypiszParyMiejscNaKrawedzie(const vector<pair<int, int>> &wektorPar) {
    cout << "Mozliwe miejsca na krawedz:" << wektorPar.size() << endl;
    for (int i = 0; i < wektorPar.size(); i++) {
        cout << "[" << wektorPar[i].first << "][" << wektorPar[i].second << "]" << endl;
    }
}

void wypiszMacierz(int n, int **macierzSasiedztwa) {
    for (int i = 0; i < n; i++) {
        cout << "\n";
        for (int j = 0; j < n; j++) {
            cout << macierzSasiedztwa[i][j] << "\t";
        }
    }
}

void wstawSymetrycznieDoMacierzy(int **macierz, int i, int j, int wartosc) {

    macierz[i][j] = wartosc;
    macierz[j][i] = wartosc;
}

int losowaWartoscWZakresie(int min, int max) {
    random_device rd; // obtain a random number from hardware
    mt19937 rng(rd()); // seed the generator
    uniform_int_distribution<> distr(min, max); // define the range
    return distr(rng);
}
