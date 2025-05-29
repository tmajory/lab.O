// Implementação de grafo
#pragma once // Trata possíveis inclusões circulares
#include <vector>
#include <climits>

using namespace std;

struct Aresta {
    int destino;
    int custo;
};

class Grafo {
private:
    vector<vector<Aresta>> listaAdj;
    int numVertices;

public:
    Grafo(int n) : numVertices(n), listaAdj(n) {}

    void addAresta(int origem, int destino, int custo) {
        listaAdj[origem].push_back({ destino, custo });
    }

    const vector<Aresta>& getNeighbors(int v) const {
        return listaAdj[v];
    }

    int getNumVertices() const {
        return numVertices;
    }

    /// ✅ Método novo: Retorna o maior custo de aresta do grafo
    int getMaxCustoAresta() const {
        int maxCusto = 0;
        for (const auto& vizinhos : listaAdj) {
            for (const auto& aresta : vizinhos) {
                if (aresta.custo > maxCusto) {
                    maxCusto = aresta.custo;
                }
            }
        }
        return maxCusto;
    }
};
