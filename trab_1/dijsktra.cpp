#include "grafo.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

struct ResultadoDijkstra {
    vector<int> custos;
    vector<int> predecessores;
    int verticesVisitados;
    double tempoExecucao;
};

ResultadoDijkstra dijkstraBasico(const Grafo& g, int origem, int destino, ofstream& outfile) {
    int n = g.getNumVertices();
    ResultadoDijkstra resultado;
    resultado.custos.resize(n, INT_MAX);
    resultado.predecessores.resize(n, -1);
    resultado.verticesVisitados = 0;
    vector<bool> visitado(n, false);

    resultado.custos[origem] = 0;

    auto inicio = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; ++i) {
        // Encontra o vértice não visitado com menor custo atual
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!visitado[j] && (u == -1 || resultado.custos[j] < resultado.custos[u])) {
                u = j;
            }
        }

        // Condição de parada: chegou no destino ou não há mais vértices alcançáveis
        if (u == destino || resultado.custos[u] == INT_MAX) {
            break;
        }

        visitado[u] = true;
        resultado.verticesVisitados++;

        // Relaxamento das arestas
        for (const Aresta& a : g.getNeighbors(u)) {
            int v = a.destino;
            int custo_uv = a.custo;
            int novo_custo = resultado.custos[u] + custo_uv;

            if (novo_custo < resultado.custos[v]) {
                resultado.custos[v] = novo_custo;
                resultado.predecessores[v] = u;
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

    int n, origem, destino;
    inFile >> n >> origem >> destino;

    Grafo g(n);
    int u, v, custo;
    while (inFile >> u >> v >> custo) {
        g.addAresta(u, v, custo);
    }

    // Chamada para a versão básica
    ResultadoDijkstra resultado = dijkstraBasico(g, origem, destino, outFile);
    
    // Escreve resultados no mesmo formato que a versão com heap
    outFile << resultado.custos[destino] << ", " 
            << resultado.verticesVisitados << ", " 
            << resultado.tempoExecucao << "\n";

    return 0;
}