//Implementação de grafo
#pragma once//Trata possiveis inclusões circulares
#include <vector>
#include <climits>

using namespace std;


struct Aresta{
    int destino;
    int custo;
};


class Graph{
    private:
        vector<vector<Aresta>> listaAdj;
        int numVertices;
    
    public:
        Graph(int n): numVertices(n), listaAdj(n){}

        void addAresta(int origem, int destino, int custo){
            listaAdj[origem].push_back({destino, custo});
        }

        const vector<Aresta>& getNeighbors(int v) const {
            return listaAdj[v];
        }

        int getNumVertices() const{
            return numVertices;
        }
};