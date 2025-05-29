#include "grafo.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <climits>

using namespace std;

struct ResultadoDijkstra {
    vector<int> custos;
    vector<int> predecessores;
    int verticesVisitados;
    double tempoExecucao;
};

ResultadoDijkstra dijkstraDial(const Grafo& g, int origem, int destino, ofstream& outfile) {
    int n = g.getNumVertices();
    int maxCustoAresta = g.getMaxCustoAresta();

    ResultadoDijkstra resultado;
    resultado.custos.resize(n, INT_MAX);
    resultado.predecessores.resize(n, -1);
    resultado.verticesVisitados = 0;

    if (maxCustoAresta == 0) {
        cerr << "Erro: O grafo não possui arestas.\n";
        return resultado;
    }

    int maxDistancia = maxCustoAresta * n;
    vector<list<int>> buckets(maxDistancia + 1);

    resultado.custos[origem] = 0;
    buckets[0].push_back(origem);

    auto inicio = chrono::high_resolution_clock::now();

    int bucketIndex = 0;
    while (bucketIndex <= maxDistancia) {
        if (buckets[bucketIndex].empty()) {
            bucketIndex++;
            continue;
        }

        int u = buckets[bucketIndex].front();
        buckets[bucketIndex].pop_front();
        resultado.verticesVisitados++;

        if (u == destino) break;

        for (const Aresta& a : g.getNeighbors(u)) {
            int v = a.destino;
            int custoUV = a.custo;
            int novoCusto = resultado.custos[u] + custoUV;

            if (novoCusto < resultado.custos[v]) {
                // Remove v do bucket antigo, se necessário
                if (resultado.custos[v] != INT_MAX) {
                    buckets[resultado.custos[v]].remove(v);
                }
                resultado.custos[v] = novoCusto;
                resultado.predecessores[v] = u;
                buckets[novoCusto].push_back(v);
            }
        }
    }

    auto fim = chrono::high_resolution_clock::now();
    resultado.tempoExecucao = chrono::duration_cast<chrono::milliseconds>(fim - inicio).count();

    return resultado;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <arquivo_entrada> <arquivo_saida>\n";
        return 1;
    }

    ifstream inFile(argv[1]);
    ofstream outFile(argv[2], ios::app);

    if (!inFile.is_open()) {
        cerr << "Erro ao abrir o arquivo de entrada.\n";
        return 1;
    }
    if (!outFile.is_open()) {
        cerr << "Erro ao abrir o arquivo de saída.\n";
        return 1;
    }

    int n, origem, destino;
    inFile >> n >> origem >> destino;

    Grafo g(n);
    int u, v, custo;
    while (inFile >> u >> v >> custo) {
        g.addAresta(u, v, custo);
    }

    ResultadoDijkstra resultado = dijkstraDial(g, origem, destino, outFile);

    if (resultado.custos[destino] == INT_MAX) {
        outFile << "Infinito (sem caminho), ";
    } else {
        outFile << resultado.custos[destino] << ", ";
    }

    outFile << resultado.verticesVisitados << ", "
            << resultado.tempoExecucao << "\n";

    cout << "Dijkstra Dial concluído. Resultado salvo.\n";

    return 0;
}
