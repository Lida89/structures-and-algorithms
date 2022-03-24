#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    unsigned int n, edge = 0;
    setlocale(LC_ALL, "rus");
    ofstream f("Graph.txt");
    if (!f) {
        cout << endl << "Ошибка открытия файла для записи.";
    }
    cout << "Введите кол-во вершин в графе:" << endl;
    cin >> n;
    f << n << endl << n << endl;
    srand(time(NULL));
    int lim = 3;
    vector<int> limit(n);
    vector<vector<int>> M(n, vector<int>(n));
    for (unsigned int i = 1; i <= n; i++) {
        limit[i - 1] = i;
    }
    for (unsigned int i = 0; i < n; i++) {        // для каждой вершины вершины
        int gr = rand() % 3 + 1;         // кол-во исходящих рёбер
        edge += gr;
        for (int j = 0; j < gr; j++) {
            f << i + 1 << " ";
            int v = 0, weight = rand() % 1024, k = 0, check = 0;
            while (v == 0 || v == i + 1 || M[v - 1][i] != 0 || M[i][v - 1] != 0) {
                unsigned int a = rand() % 2;
                if ((a == 0 || (n - i - 1 <= limit.size())) && limit.size() > 0) {
                    k = rand() % limit.size();
                    v = limit[k];
                    check = 1;
                }
                else {
                    v = rand() % n + 1;
                }
            }
            M[i][v - 1] = weight;
            f << v << " " << weight << endl;
            if (check == 1) {
                limit[k] = limit[limit.size() - 1];
                limit.pop_back();
            }
            else {
                for (unsigned int l = 0; l < limit.size(); l++) {
                    if (limit[l] == v) {
                        limit[l] = limit[limit.size() - 1];
                        limit.pop_back();
                    }
                }
            }
        }
    }
    f.close();
    fstream of("Graph.txt");
    of.seekg(0, ios_base::beg);
    of << edge;
    of.close();
    return 0;
}
