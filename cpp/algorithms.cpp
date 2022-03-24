#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>

using namespace std;

int flag = 1;
vector<vector<pair<int, int>>> graph;
int** M;
struct stR {
    int num1;
    int num2;
    int weight;
};
stR* mass;
vector<int> shortest, pred;

void Dijkstra(int s, int num_vert);                                   // вектор векторов
void Bellman_Ford(int s, int num_vert);
void Floyd_Warshall(int s, int num_vert);
int Relax(int u, int v);
void Prima(int s, int num_vert);
void Kruskala(int num_vert);

void M_Dijkstra(int s, int num_vert);                                 // матрица смежности
void M_Bellman_Ford(int s, int num_vert);
void M_Floyd_Warshall(int s, int num_vert);
int M_Relax(int u, int v);
void M_Prima(int s, int num_vert);
void M_Kruskala(int num_vert);

void str_Dijkstra(int s, int num_vert, int e);                                   // массив структур
void str_Bellman_Ford(int s, int num_vert, int e);
void str_Floyd_Warshall(int s, int num_vert, int e);
int str_Relax(int u, int v, int e);
void str_Prima(int s, int num_vert, int e);
void str_Kruskala(int num_vert, int e);

int main() {
    int n, e;
    setlocale(LC_ALL, "rus");
    ifstream file("C:\\Users\\Lida\\source\\repos\\Struct_laba_2_graph\\Struct_laba_2_graph\\Graph.txt");
    if (!file) {
        cout << endl << "Ошибка открытия файла для чтения." << endl;
    }
    file >> e >> n;                  // кол-во рёбер и вершин в графе
    shortest.resize(n);
    pred.resize(n);
    M = new int* [n];
    for (int i = 0; i < n; i++) {
        M[i] = new int[n];
        for (int j = 0; j < n; j++) {
            M[i][j] = 0;
        }
    }
    mass = new stR[e];
    vector<pair<int, int>> v;
    pair<int, int> t;
    int num_v, g = 0;
    file >> num_v;
    int lss = num_v;
    while (!file.eof()) {
        while ((num_v == lss) && !file.eof()) {
            file >> t.first >> t.second;
            v.emplace_back(t);
            M[num_v - 1][t.first - 1] = t.second;
            mass[g].num1 = num_v;
            mass[g].num2 = t.first;
            mass[g].weight = t.second;
            file >> num_v;
            g++;
        }
        graph.emplace_back(v);
        v.clear();
        lss = num_v;
    }
    int s = 1;
    file.close();
    DWORD t1, t2;
    int size_gr = 0;
    for (int i = 0; i < n; i++) {
        size_gr += sizeof(pair<int, int>) * graph[i].size();
    }
    cout << "------------------------------------------------" << endl << "Количество вершин в графе: " << n << endl;
    cout << "------------------------------------------------" << endl;
    cout << "Способ хранения графа | Матрица смежности | КМИ через массив структур | КМИ через вектор векторов";
    cout << endl << "Объём памяти\t\t|\t" << sizeof(int) * n * n << "\t\t|\t" << sizeof(stR) * e << "\t\t|\t" << size_gr;
    if (flag == 0) {
        cout << endl << "------------------------------------------------";
        cout << endl << endl << "АЛГОРИТМ ДЕЙКСТРЫ" << endl;
    }
    t1 = GetTickCount();
    M_Dijkstra(s, n);
    t2 = GetTickCount();
    if (flag == 0) {
        cout << "Время выполнения|\t" << (t2 - t1) << " | ";
    }
    t1 = GetTickCount();
    str_Dijkstra(s, n, e);
    t2 = GetTickCount();
    if (flag == 0) {
        cout << t2 - t1 << " | ";
    }
    t1 = GetTickCount();
    Dijkstra(s, n);
    t2 = GetTickCount();
    if (flag == 0) {
        cout << t2 - t1;
        cout << endl << "------------------------------------------------";
        cout << endl << endl << "АЛГОРИТМ БЕЛЛМАНА-ФОРДА" << endl;
    }
    t1 = GetTickCount();
    M_Bellman_Ford(s, n);
    t2 = GetTickCount();
    if (flag == 0) {
        cout << "Время выполнения|\t" << (t2 - t1) << " | ";
    }
    t1 = GetTickCount();
    str_Bellman_Ford(s, n, e);
    t2 = GetTickCount();
    if (flag == 0) {
        cout << t2 - t1 << " | ";
    }
    t1 = GetTickCount();
    Bellman_Ford(s, n);
    t2 = GetTickCount();
    if (flag == 0) {
        cout << t2 - t1;
        cout << endl << "------------------------------------------------";
        cout << endl << endl << "АЛГОРИТМ ФЛОЙДА-УОРШЕЛЛА" << endl;
    }
    t1 = GetTickCount();
    M_Floyd_Warshall(s, n);
    t2 = GetTickCount();
    if (flag == 0) {
        cout << "Время выполнения|\t" << (t2 - t1) << " | ";
    }
    t1 = GetTickCount();
    str_Floyd_Warshall(s, n, e);
    t2 = GetTickCount();
    if (flag == 0) {
        cout << t2 - t1 << " | ";
    }
    t1 = GetTickCount();
    Floyd_Warshall(s, n);
    t2 = GetTickCount();
    if (flag == 0) {
        cout << t2 - t1;
        cout << endl << "------------------------------------------------";
        cout << endl << endl << "АЛГОРИТМ ПРИМА" << endl;
    }
    t1 = GetTickCount();
    M_Prima(s, n);
    t2 = GetTickCount();
    if (flag == 0) {
        cout << "Время выполнения|\t" << (t2 - t1) << " | ";
    }
    t1 = GetTickCount();
    str_Prima(s, n, e);
    t2 = GetTickCount();
    if (flag == 0) {
        cout << t2 - t1 << " | ";
    }
    t1 = GetTickCount();
    Prima(s, n);
    t2 = GetTickCount();
    if (flag == 0) {
        cout << t2 - t1;
        cout << endl << "------------------------------------------------";
        cout << endl << endl << "АЛГОРИТМ КРУСКАЛА" << endl;
    }
    t1 = GetTickCount();
    M_Kruskala(n);
    t2 = GetTickCount();
    if (flag == 0) {
        cout << "Время выполнения|\t" << (t2 - t1) << " | ";
    }
    t1 = GetTickCount();
    str_Kruskala(n, e);
    t2 = GetTickCount();
    if (flag == 0) {
        cout << t2 - t1 << " | ";
    }
    t1 = GetTickCount();
    Kruskala(n);
    t2 = GetTickCount();
    if (flag == 0) {
        cout << t2 - t1;
    }
    
    for (int i = 0; i < n; i++) {
        delete[] M[i];
    }
    delete[] mass;
    return 0;
}
/**************************** АЛГОРИТМЫ С МАТРИЦЕЙ СМЕЖНОСТИ ******************************************/
void M_Dijkstra(int s, int num_vert) {
    for (int v = 0; v < num_vert; v++) {
        shortest[v] = 100000;         // бесконечность
        pred[v] = NULL;
    }
    shortest[s - 1] = 0;
    vector<int> Q(num_vert);
    for (int i = 0; i < num_vert; i++) {
        Q[i] = i + 1;
    }
    while (Q.size() > 0) {
        int u = Q[0], ii = 0;
        for (unsigned int i = 0; i < Q.size(); i++) {
            if (shortest[Q[i] - 1] < shortest[u - 1]) {
                u = Q[i];
                ii = i;
            }
        }
        Q[ii] = Q[Q.size() - 1];
        Q.pop_back();
        for (int j = 0; j < num_vert; j++) {
            if (M[u - 1][j] != 0) {
                int v = j + 1;             // номер смежной с u вершины
                M_Relax(u, v);
            }
        }
    }
    if (flag == 1) {
        cout << endl << "АЛГОРИТМ ДЕЙКСТРЫ" << endl;
        cout << endl << "shortest: ";
        for (int i = 0; i < num_vert; i++) {
            cout << shortest[i] << " ";
        }
        cout << endl << "pred: ";
        for (int i = 0; i < num_vert; i++) {
            cout << pred[i] << " ";
        }
    }
}
void M_Bellman_Ford(int s, int num_vert) {
    for (int v = 0; v < num_vert; v++) {
        shortest[v] = 100000;         // бесконечность
        pred[v] = NULL;
    }
    shortest[s - 1] = 0;            // если пути к v нет, то shortest[v] = беск., pred[v] = NULL
    for (int i = 0; i < num_vert - 1; i++) {
        int check = 0;
        for (int u = 1; u <= num_vert; u++) {
            for (int j = 0; j < num_vert; j++) {
                if (M[u - 1][j] != 0) {
                    int check1 = 0, v = j + 1;
                    check1 += M_Relax(u, v);
                    check += check1;
                }
            }
        }
        if (check == 0) {
            break;
        }
    }
    if (flag == 1) {
        cout << endl << "АЛГОРИТМ БЕЛЛМАНА-ФОРДА" << endl;
        cout << endl << "shortest: ";
        for (int i = 0; i < num_vert; i++) {
            cout << shortest[i] << " ";
        }
        cout << endl << "pred: ";
        for (int i = 0; i < num_vert; i++) {
            cout << pred[i] << " ";
        }
    }
}
int M_Relax(int u, int v) {
    int b = M[u - 1][v - 1];                      // путь от u до v
    if (shortest[u - 1] + b < shortest[v - 1]) {
        shortest[v - 1] = shortest[u - 1] + b;
        pred[v - 1] = u;
        return 1;
    }
    return 0;
}
void M_Floyd_Warshall(int s, int num_vert) {
    int** shortest = new int* [num_vert], ** pred = new int* [num_vert];
    for (int i = 0; i < num_vert; i++) {
        shortest[i] = new int[num_vert];
        pred[i] = new int[num_vert];
    }
    for (int u = 0; u < num_vert; u++) {
        for (int k = 0; k < num_vert; k++) {       
            if (M[u][k] != 0) {
                shortest[u][k] = M[u][k];
                pred[u][k] = u + 1;
            }
            else {
                shortest[u][k] = 100000;
                pred[u][k] = NULL;
            }
        }
    }
    for (int k = 0; k < num_vert; k++) {
        for (int i = 0; i < num_vert; i++) {
            for (int j = 0; j < num_vert; j++) {
                if (shortest[i][k] + shortest[k][j] < shortest[i][j]) {
                    shortest[i][j] = shortest[i][k] + shortest[k][j];
                    pred[i][j] = k + 1;
                }
            }
        }
    }
    if (flag == 1) {
        cout << endl << "АЛГОРИТ ФЛОЙДА_УОРШЕЛЛА" << endl;
        cout << endl << "shortest:" << endl;
        for (int i = 0; i < num_vert; i++) {
            for (int j = 0; j < num_vert; j++) {
                cout << shortest[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl << "pred:" << endl;
        for (int i = 0; i < num_vert; i++) {
            for (int j = 0; j < num_vert; j++) {
                cout << pred[i][j] << " ";
            }
            cout << endl;
        }
    }
    for (int i = 0; i < num_vert; i++) {
        delete[] shortest[i];
        delete[] pred[i];
    }
    delete[] shortest;
    delete[] pred;
}
void M_Prima(int s, int num_vert) {
    vector<int> U(1, s), V, predv;
    int weight = 0;
    for (int i = 1; i <= num_vert; i++) {
        if (i != s) {
            V.push_back(i);
        }
    }
    for (int i = 0; i < num_vert - 1; i++) {
        int u, w, min_w = 100000;
        for (unsigned int j = 0; j < U.size(); j++) {
            int u1 = U[j];
            for (unsigned int k = 0; k < V.size(); k++) {
                int v1 = V[k];
                if ((M[u1 - 1][v1 - 1] != 0) && (M[u1 - 1][v1 - 1] < min_w)) {
                    min_w = M[u1 - 1][v1 - 1];
                    u = u1;
                    w = v1;
                }
                else if ((M[v1 - 1][u1 - 1] != 0) && (M[v1 - 1][u1 - 1] < min_w)) {
                    min_w = M[v1 - 1][u1 - 1];
                    u = u1;
                    w = v1;
                }
            }
        }
        U.push_back(w);
        predv.push_back(u);
        for (unsigned int i = 0; i < V.size(); i++) {
            if (V[i] == w) {
                V[i] = V[V.size() - 1];
                V.pop_back();
                break;
            }
        }
    }
    if (flag == 1) {
        cout << endl << "АЛГОРИТМ ПРИМА" << endl;
        cout << endl << "Рёбра ост. дерева: ";
        for (unsigned int i = 0; i < predv.size(); i++) {
            cout << predv[i] << "-" << U[i + 1] << " ";
        }
        cout << endl << endl;
    }
}
void M_Kruskala(int num_vert) {
    vector<int> edge, vert1, vert2;
    vector<pair<int, int>> uv;
    for (int i = 0; i < num_vert; i++) {
        for (int j = 0; j < num_vert; j++) {
            if (M[i][j] != 0) {
                vert1.push_back(i + 1);
                vert2.push_back(j + 1);
                edge.push_back(M[i][j]);
            }
        }
    }
    for (int i = edge.size() / 2; i >= 1; i /= 2) {
        for (int j = i; j < edge.size(); j++) {
            for (int k = j; k - i >= 0; k -= i) {
                if (edge[k] < edge[k - i]) {
                    int m = edge[k];
                    edge[k] = edge[k - i];
                    edge[k - i] = m;
                    m = vert1[k];
                    vert1[k] = vert1[k - i];
                    vert1[k - i] = m;
                    m = vert2[k];
                    vert2[k] = vert2[k - i];
                    vert2[k - i] = m;
                }
            }
        }
    }
    vector<int> tree(num_vert);
    for (int i = 0; i < num_vert; i++) {
        tree[i] = i + 1;
    }
    for (unsigned int i = 0; i < edge.size(); i++) {
        int u = vert1[i], v = vert2[i];
        if (tree[u - 1] != tree[v - 1]) {
            uv.push_back(make_pair(u, v));
            int h = tree[v - 1];
            for (unsigned int j = 0; j < num_vert; j++) {
                if (tree[j] == h) {
                    tree[j] = tree[u - 1];
                }
            }
        }
    }
    if (flag == 1) {
        cout << endl << "АЛГОРИТМ КРУСКАЛА" << endl;
        cout << endl << "Рёбра ост. дерева: ";
        for (unsigned int i = 0; i < uv.size(); i++) {
            cout << uv[i].first << "-" << uv[i].second << " ";
        }
        cout << endl << endl;
    }
}
/**************************** АЛГОРИТМЫ С МАССИВОМ СТРУКТУР *******************************************/
void str_Dijkstra(int s, int num_vert, int e) {
    for (int v = 0; v < num_vert; v++) {
        shortest[v] = 100000;         // бесконечность
        pred[v] = NULL;
    }
    shortest[s - 1] = 0;
    vector<int> Q(num_vert);
    for (int i = 0; i < num_vert; i++) {
        Q[i] = i + 1;
    }
    while (Q.size() > 0) {
        int u = Q[0], ii = 0;
        for (unsigned int i = 0; i < Q.size(); i++) {
            if (shortest[Q[i] - 1] < shortest[u - 1]) {
                u = Q[i];
                ii = i;
            }
        }
        Q[ii] = Q[Q.size() - 1];
        Q.pop_back();
        for (unsigned int j = 0; j < e; j++) {
            int v;
            if (mass[j].num1 == u) {
                v = mass[j].num2;
                str_Relax(u, v, e);
            }
        }
    }
    if (flag == 1) {
        cout << endl << "АЛГОРИТМ ДЕЙКСТРЫ" << endl;
        cout << endl << "shortest: ";
        for (int i = 0; i < num_vert; i++) {
            cout << shortest[i] << " ";
        }
        cout << endl << "pred: ";
        for (int i = 0; i < num_vert; i++) {
            cout << pred[i] << " ";
        }
    }
}
void str_Bellman_Ford(int s, int num_vert, int e) {
    for (int v = 0; v < num_vert; v++) {
        shortest[v] = 100000;         // бесконечность
        pred[v] = NULL;
    }
    shortest[s - 1] = 0;            // если пути к v нет, то shortest[v] = беск., pred[v] = NULL
    for (int i = 0; i < num_vert - 1; i++) {
        int check = 0;
        for (int u = 1; u <= num_vert; u++) {
            for (unsigned int j = 0; j < e; j++) {
                int v, check1 = 0;
                if (mass[j].num1 == u) {
                    v = mass[j].num2;
                    check1 += str_Relax(u, v, e);
                }
                check += check1;
            }
        }
        if (check == 0) {
            break;
        }
    }
    if (flag == 1) {
        cout << endl << "АЛГОРИТМ БЕЛЛМАНА-ФОРДА" << endl;
        cout << endl << "shortest: ";
        for (int i = 0; i < num_vert; i++) {
            cout << shortest[i] << " ";
        }
        cout << endl << "pred: ";
        for (int i = 0; i < num_vert; i++) {
            cout << pred[i] << " ";
        }
    }
}
int str_Relax(int u, int v, int e) {
    int b = 0;                             // путь от u до v
    for (unsigned int j = 0; j < e; j++) {
        if (mass[j].num1 == u && mass[j].num2 == v) {
            b = mass[j].weight;
            break;
        }
    }
    if (shortest[u - 1] + b < shortest[v - 1]) {
        shortest[v - 1] = shortest[u - 1] + b;
        pred[v - 1] = u;
        return 1;
    }
    return 0;
}
void str_Floyd_Warshall(int s, int num_vert, int e) {
    int** shortest = new int *[num_vert], ** pred = new int* [num_vert];
    for (int i = 0; i < num_vert; i++) {
        shortest[i] = new int [num_vert];
        pred[i] = new int [num_vert];
    }
    for (int u = 0; u < num_vert; u++) {
        for (int k = 0; k < num_vert; k++) {
            shortest[u][k] = 100000;
            pred[u][k] = NULL;
        }
    }
    for (int j = 0; j < e; j++) {
        int u = mass[j].num1, k = mass[j].num2;
        shortest[u - 1][k - 1] = mass[j].weight;
        pred[u - 1][k - 1] = u;
    }
    for (int k = 0; k < num_vert; k++) {
        for (int i = 0; i < num_vert; i++) {
            for (int j = 0; j < num_vert; j++) {
                if (shortest[i][k] + shortest[k][j] < shortest[i][j]) {
                    shortest[i][j] = shortest[i][k] + shortest[k][j];
                    pred[i][j] = k + 1;
                }
            }
        }
    }
    if (flag == 1) {
        cout << endl << "АЛГОРИТ ФЛОЙДА_УОРШЕЛЛА" << endl;
        cout << endl << "shortest:" << endl;
        for (int i = 0; i < num_vert; i++) {
            for (int j = 0; j < num_vert; j++) {
                cout << shortest[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl << "pred:" << endl;
        for (int i = 0; i < num_vert; i++) {
            for (int j = 0; j < num_vert; j++) {
                cout << pred[i][j] << " ";
            }
            cout << endl;
        }
    }
    for (int i = 0; i < num_vert; i++) {
        delete[] shortest[i];
        delete[] pred[i];
    }
    delete[] shortest;
    delete[] pred;
}
void str_Prima(int s, int num_vert, int e) {
    vector<int> U(1, s), V, predv;
    int weight = 0;
    for (int i = 1; i <= num_vert; i++) {
        if (i != s) {
            V.push_back(i);
        }
    }
    for (int i = 0; i < num_vert - 1; i++) {
        int u, w, min_w = 100000;
        for (unsigned int j = 0; j < U.size(); j++) {
            int u1 = U[j];
            for (unsigned int k = 0; k < V.size(); k++) {
                int v1 = V[k];
                for (int m = 0; m < e; m++) {
                    if (((mass[m].num1 == u1 && mass[m].num2 == v1) || (mass[m].num1 == v1 && mass[m].num2 == u1)) && mass[m].weight < min_w) {
                        min_w = mass[m].weight;
                        u = u1;
                        w = v1;
                    }
                }
            }
        }
        U.push_back(w);
        predv.push_back(u);
        for (unsigned int i = 0; i < V.size(); i++) {
            if (V[i] == w) {
                V[i] = V[V.size() - 1];
                V.pop_back();
                break;
            }
        }
    }
    if (flag == 1) {
        cout << endl << "АЛГОРИТМ ПРИМА" << endl;
        cout << endl << "Рёбра ост. дерева: ";
        for (unsigned int i = 0; i < predv.size(); i++) {
            cout << predv[i] << "-" << U[i + 1] << " ";
        }
        cout << endl << endl;
    }
}
void str_Kruskala(int num_vert, int e) {
    vector<int> edge, vert1, vert2;
    vector<pair<int, int>> uv;
    for (int i = 0; i < e; i++) {
        vert1.push_back(mass[i].num1);
        vert2.push_back(mass[i].num2);
        edge.push_back(mass[i].weight);
    }
    for (int i = edge.size() / 2; i >= 1; i /= 2) {
        for (int j = i; j < edge.size(); j++) {
            for (int k = j; k - i >= 0; k -= i) {
                if (edge[k] < edge[k - i]) {
                    int m = edge[k];
                    edge[k] = edge[k - i];
                    edge[k - i] = m;
                    m = vert1[k];
                    vert1[k] = vert1[k - i];
                    vert1[k - i] = m;
                    m = vert2[k];
                    vert2[k] = vert2[k - i];
                    vert2[k - i] = m;
                }
            }
        }
    }
    vector<int> tree(num_vert);
    for (int i = 0; i < num_vert; i++) {
        tree[i] = i + 1;
    }
    for (unsigned int i = 0; i < edge.size(); i++) {
        int u = vert1[i], v = vert2[i];
        if (tree[u - 1] != tree[v - 1]) {
            uv.push_back(make_pair(u, v));
            int h = tree[v - 1];
            for (unsigned int j = 0; j < num_vert; j++) {
                if (tree[j] == h) {
                    tree[j] = tree[u - 1];
                }
            }
        }
    }
    if (flag == 1) {
        cout << endl << "АЛГОРИТМ КРУСКАЛА" << endl;
        cout << endl << "Рёбра ост. дерева: ";
        for (unsigned int i = 0; i < uv.size(); i++) {
            cout << uv[i].first << "-" << uv[i].second << " ";
        }
        cout << endl << endl;
    }
}
/**************************** АЛГОРИТМЫ С ВЕКТОРАМИ ***************************************************/
void Dijkstra(int s, int num_vert) {
    for (int v = 0; v < num_vert; v++) {
        shortest[v] = 100000;         // бесконечность
        pred[v] = NULL;
    }
    shortest[s - 1] = 0;
    vector<int> Q(num_vert);
    for (int i = 0; i < num_vert; i++) {
        Q[i] = i + 1;
    }
    while (Q.size() > 0) {
        int u = Q[0], ii = 0;
        for (unsigned int i = 0; i < Q.size(); i++) {
            if (shortest[Q[i] - 1] < shortest[u - 1]) {
                u = Q[i];
                ii = i;
            }
        }
        Q[ii] = Q[Q.size() - 1];
        Q.pop_back();
        for (unsigned int j = 0; j < graph[u - 1].size(); j++) {
            int v = graph[u - 1][j].first;     // номер смежной с u вершины
            Relax(u, v);
        }
    }
    if (flag == 1) {
        cout << endl << "АЛГОРИТМ ДЕЙКСТРЫ" << endl;
        cout << endl << "shortest: ";
        for (int i = 0; i < num_vert; i++) {
            cout << shortest[i] << " ";
        }
        cout << endl << "pred: ";
        for (int i = 0; i < num_vert; i++) {
            cout << pred[i] << " ";
        }
    }
}
void Bellman_Ford(int s, int num_vert) {
    for (int v = 0; v < num_vert; v++) {
        shortest[v] = 100000;         // бесконечность
        pred[v] = NULL;
    }
    shortest[s - 1] = 0;            // если пути к v нет, то shortest[v] = беск., pred[v] = NULL
    for (int i = 0; i < num_vert - 1; i++) {
        int check = 0;
        for (int u = 1; u <= num_vert; u++) {
            for (unsigned int j = 0; j < graph[u - 1].size(); j++) {
                int check1 = 0;
                int v = graph[u - 1][j].first;     // номер смежной с u вершины
                check1 += Relax(u, v);
                check += check1;
            }
        }
        if (check == 0) {
            break;
        }
    }
    if (flag == 1) {
        cout << endl << "АЛГОРИТМ БЕЛЛМАНА-ФОРДА" << endl;
        cout << endl << "shortest: ";
        for (int i = 0; i < num_vert; i++) {
            cout << shortest[i] << " ";
        }
        cout << endl << "pred: ";
        for (int i = 0; i < num_vert; i++) {
            cout << pred[i] << " ";
        }
    }
}
int Relax(int u, int v) {
    int b = 0;                             // путь от u до v
    for (int j = 0; j < graph[u - 1].size(); j++) {
        if (graph[u - 1][j].first == v) {
            b = graph[u - 1][j].second;
        }
    }
    if (shortest[u - 1] + b < shortest[v - 1]) {
        shortest[v - 1] = shortest[u - 1] + b;
        pred[v - 1] = u;
        return 1;
    }
    return 0;
}
void Floyd_Warshall(int s, int num_vert) {
    int** shortest = new int *[num_vert], ** pred = new int* [num_vert];
    for (int i = 0; i < num_vert; i++) {
        shortest[i] = new int [num_vert];
        pred[i] = new int [num_vert];
    }
    for (int u = 0; u < num_vert; u++) {
        for (int k = 0; k < num_vert; k++) {
            shortest[u][k] = 100000;
            pred[u][k] = NULL;
        }
    }
    for (int u = 0; u < num_vert; u++) {
        for (unsigned int j = 0; j < graph[u].size(); j++) {
            int v = graph[u][j].first;                        // номер смежной с u вершины
            shortest[u][v - 1] = graph[u][j].second;
            pred[u][v - 1] = u + 1;
        }
    }
    for (int k = 0; k < num_vert; k++) {
        for (int i = 0; i < num_vert; i++) {
            for (int j = 0; j < num_vert; j++) {
                if (shortest[i][k] + shortest[k][j] < shortest[i][j]) {
                    shortest[i][j] = shortest[i][k] + shortest[k][j];
                    pred[i][j] = k + 1;
                }
            }
        }
    }
    if (flag == 1) {
        cout << endl << "АЛГОРИТ ФЛОЙДА_УОРШЕЛЛА" << endl;
        cout << endl << "shortest:" << endl;
        for (int i = 0; i < num_vert; i++) {
            for (int j = 0; j < num_vert; j++) {
                cout << shortest[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl << "pred:" << endl;
        for (int i = 0; i < num_vert; i++) {
            for (int j = 0; j < num_vert; j++) {
                cout << pred[i][j] << " ";
            }
            cout << endl;
        }
    }
    for (int i = 0; i < num_vert; i++) {
        delete[] shortest[i];
        delete[] pred[i];
    }
    delete[] shortest;
    delete[] pred;
}
void Prima(int s, int num_vert) {
    vector<int> U(1, s), V, predv;
    int weight = 0;
    for (int i = 1; i <= num_vert; i++) {
        if (i != s) {
            V.push_back(i);
        }
    }
    for (int i = 0; i < num_vert - 1; i++) {
        int u, w, min_w = 100000;
        for (unsigned int j = 0; j < U.size(); j++) {
            int u1 = U[j];
            for (unsigned int k = 0; k < V.size(); k++) {
                int v1 = V[k];
                for (unsigned int m = 0; m < graph[u1 - 1].size(); m++) {
                    if ((v1 == graph[u1 - 1][m].first) && (graph[u1 - 1][m].second < min_w)) {
                        min_w = graph[u1 - 1][m].second;
                        u = u1;
                        w = v1;
                    }
                }
                for (int m = 0; m < graph[v1 - 1].size(); m++) {
                    if ((u1 == graph[v1 - 1][m].first) && (graph[v1 - 1][m].second < min_w)) {
                        min_w = graph[v1 - 1][m].second;
                        u = u1;
                        w = v1;
                    }
                }
            }
        }
        U.push_back(w);
        predv.push_back(u);
        for (unsigned int i = 0; i < V.size(); i++) {
            if (V[i] == w) {
                V[i] = V[V.size() - 1];
                V.pop_back();
                break;
            }
        }
    }
    if (flag == 1) {
        cout << endl << "АЛГОРИТМ ПРИМА" << endl;
        cout << endl << "Рёбра ост. дерева: ";
        for (unsigned int i = 0; i < predv.size(); i++) {
            cout << predv[i] << "-" << U[i + 1] << " ";
        }
        cout << endl << endl;
    }
}
void Kruskala(int num_vert) {
    vector<int> edge, vert1, vert2;
    vector<pair<int, int>> uv;
    for (int i = 0; i < num_vert; i++) {
        for (unsigned int j = 0; j < graph[i].size(); j++) {
            vert1.push_back(i + 1);
            vert2.push_back(graph[i][j].first);
            edge.push_back(graph[i][j].second);
        }
    }
    for (int i = edge.size() / 2; i >= 1; i /= 2) {
        for (int j = i; j < edge.size(); j++) {
            for (int k = j; k - i >= 0; k -= i) {
                if (edge[k] < edge[k - i]) {
                    int m = edge[k];
                    edge[k] = edge[k - i];
                    edge[k - i] = m;
                    m = vert1[k];
                    vert1[k] = vert1[k - i];
                    vert1[k - i] = m;
                    m = vert2[k];
                    vert2[k] = vert2[k - i];
                    vert2[k - i] = m;
                }
            }
        }
    }
    vector<int> tree(num_vert);
    for (int i = 0; i < num_vert; i++) {
        tree[i] = i + 1;
    }
    for (unsigned int i = 0; i < edge.size(); i++) {
        int u = vert1[i], v = vert2[i];
        if (tree[u - 1] != tree[v - 1]) {
            uv.push_back(make_pair(u, v));
            int h = tree[v - 1];
            for (unsigned int j = 0; j < num_vert; j++) {
                if (tree[j] == h) {
                    tree[j] = tree[u - 1];
                }
            }
        }
    }
    if (flag == 1) {
        cout << endl << "АЛГОРИТМ КРУСКАЛА" << endl;
        cout << endl << "Рёбра ост. дерева: ";
        for (unsigned int i = 0; i < uv.size(); i++) {
            cout << uv[i].first << "-" << uv[i].second << " ";
        }
        cout << endl << endl;
    }
}
