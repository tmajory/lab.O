#include "grafo.hpp"
#include "heapBin.hpp"
#include <chrono>
#include <fstream>
#include <vector>


struct ResultadoDijkstra{
    vector<int> custos;
    vector<int> predecessores;
    int verticesVisitados;
    double tempoExecucao;
};

ResultadoDijkstra dijkstraHeap(const Grafo& g, int origem, int destino, ofstream& outfile)
{
    int n = g.getNumVertices();
    ResultadoDijkstra resultado;
    resultado.custos.resize(n,INT_MAX);
    resultado.predecessores.resize(n,-1);
    resultado.verticesVisitados = 0;
    vector<bool> visited(n, false);

    Heap heap(n);
    heap.inserir(0, (void*)(long)origem);
    resultado.custos[origem]=0;

    auto inicio = chrono::high_resolution_clock::now();

    while (heap.getTamanho() > 0){
        HeapItem item = heap.removerMinimo();
        int u = (int)(long)item.data;

        if (u == destino) break;
        if (visited[u]) continue;
        visited[u] = true;
        resultado.verticesVisitados++;

        for (const Aresta& a: g.getNeighbors(u)){
            int v = a.destino;
            int custo_uv = a.custo;
            int newDist = resultado.custos[u] + custo_uv;

            if (newDist < resultado.custos[v]){
                resultado.custos[v] = newDist;
                resultado.predecessores[v] = u;
                heap.inserir(newDist, (void*)(long)v);
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
    ofstream outFile(argv[2], ios::app); // Modo append para adicionar resultados

    int n, origem, destino;
    inFile >> n;
    inFile >> origem; 
    inFile >> destino;

    Grafo g(n);
    int u, v, custo;
    while (inFile >> u >> v >> custo) {
        g.addAresta(u, v, custo);
    }

    // Chamada para a versão com heap
    ResultadoDijkstra resultado = dijkstraHeap(g, origem, destino, outFile);
    
    // Escreve resultados no arquivo
    outFile <<resultado.custos[destino] << ", " << resultado.verticesVisitados << ", " << resultado.tempoExecucao << "\n"; 
    // outFile << "Resultado Dijkstra com Heap:\n";
    // for (int i = 0; i < n; i++) {
    //     outFile << "Vertice " << i << " custo: " << resultado.custos[i] << " pred: " << resultado.predecessores[i]<<"\n";
    // }
    // outFile << "\n";

    return 0;
}