#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <limits>
#include <unordered_set>
#include <chrono>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;
using namespace std;
using namespace std::chrono;

typedef pair<int, int> Par;
const int INF = numeric_limits<int>::max();

struct Grafo {
    int n, s, t;
    vector<vector<Par>> adj, adjReverso;
    int num_arestas = 0;

    void lerArquivo(const string& nomeArquivo) {
        ifstream entrada(nomeArquivo);
        if (!entrada.is_open()) {
            cerr << "Erro ao abrir " << nomeArquivo << endl;
            exit(1);
        }

        entrada >> n >> s >> t;
        adj.assign(n, {});
        adjReverso.assign(n, {});
        num_arestas = 0;

        int a, b, custo;
        while (entrada >> a >> b >> custo) {
            adj[a].emplace_back(b, custo);
            adjReverso[b].emplace_back(a, custo);
            num_arestas++;
        }

        entrada.close();
    }
};

struct ResultadoExecucao {
    int custo;
    int iteracoes;
    double tempo_ms;
};

ResultadoExecucao dijkstraBidirecionalHeap(const Grafo& g) {
    vector<int> dist_s(g.n, INF), dist_t(g.n, INF);
    vector<bool> visitado_s(g.n, false), visitado_t(g.n, false);
    priority_queue<Par, vector<Par>, greater<Par>> fila_s, fila_t;
    unordered_set<int> intersecao;
    int iteracoes = 0;

    dist_s[g.s] = 0; fila_s.emplace(0, g.s);
    dist_t[g.t] = 0; fila_t.emplace(0, g.t);

    auto ini = high_resolution_clock::now();

    while (!fila_s.empty() || !fila_t.empty()) {
        if (!fila_s.empty()) {
            auto [ds, u] = fila_s.top(); fila_s.pop();
            if (visitado_s[u]) continue;
            visitado_s[u] = true;
            iteracoes++;
            if (visitado_t[u]) intersecao.insert(u);
            for (auto [v, peso] : g.adj[u]) {
                if (dist_s[v] > dist_s[u] + peso) {
                    dist_s[v] = dist_s[u] + peso;
                    fila_s.emplace(dist_s[v], v);
                }
            }
        }

        if (!fila_t.empty()) {
            auto [dt, u] = fila_t.top(); fila_t.pop();
            if (visitado_t[u]) continue;
            visitado_t[u] = true;
            iteracoes++;
            if (visitado_s[u]) intersecao.insert(u);
            for (auto [v, peso] : g.adjReverso[u]) {
                if (dist_t[v] > dist_t[u] + peso) {
                    dist_t[v] = dist_t[u] + peso;
                    fila_t.emplace(dist_t[v], v);
                }
            }
        }

        if (!intersecao.empty()) break;
    }

    int menor = INF;
    for (int u : intersecao) {
        if (dist_s[u] != INF && dist_t[u] != INF) {
            menor = min(menor, dist_s[u] + dist_t[u]);
        }
    }

    auto fim = high_resolution_clock::now();
    duration<double, milli> tempo = fim - ini;

    return {menor == INF ? -1 : menor, iteracoes, tempo.count()};
}

double mediaTresMelhores(const vector<double>& tempos) {
    vector<double> copia = tempos;
    sort(copia.begin(), copia.end());
    return (copia[1] + copia[2] + copia[3]) / 3.0;
}

int main() {
    ofstream saida("resultados.csv");
    saida << "arquivo,n_vertices,n_arestas,tempo_medio_ms,custo_minimo,n_iteracoes\n";

    string pasta = "instancias";
    for (const auto& entrada : fs::directory_iterator(pasta)) {
        if (entrada.path().extension() == ".txt") {
            string nomeArquivo = entrada.path().string();
            cout << "Processando " << nomeArquivo << endl;

            Grafo g;
            g.lerArquivo(nomeArquivo);

            vector<double> tempos;
            int custo_final = -1;
            int iteracoes_final = 0;

            for (int i = 0; i < 5; ++i) {
                ResultadoExecucao res = dijkstraBidirecionalHeap(g);
                tempos.push_back(res.tempo_ms);
                if (i == 2) { // Armazena uma execução intermediária como base
                    custo_final = res.custo;
                    iteracoes_final = res.iteracoes;
                }
            }

            double tempo_medio = mediaTresMelhores(tempos);

            saida << entrada.path().filename().string() << ","
                  << g.n << "," << g.num_arestas << ","
                  << tempo_medio << "," << custo_final << "," << iteracoes_final << "\n";
        }
    }

    saida.close();
    cout << "Concluido. Resultados em resultados.csv\n";
    return 0;
}
