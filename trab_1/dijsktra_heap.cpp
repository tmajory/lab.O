#include "grafo.hpp"
#include "heapBin.hpp"
#include <fstream>
#include <vector>

vector<int> dijskstraHeap(const Graph& g, int origem, ofstream& outfile)
{
    int n = g.getNumVertices();
    vector<int> dist(n, INT_MAX);
    vector<bool> visited(n, false);

    Heap heap(n);
    heap.inserir(0, (void*)(long)origem);
    dist[origem] = 0;

    while (heap.getTamanho() > 0){
        HeapItem item = heap.removerMinimo();
        int u = (int)(long)item.data;

        if (visited[u]) continue;
        visited[u] = true;

        for (const Aresta& a: g.getNeighbors(u)){
            int v = a.destino;
            int newDist = dist[u] + a.custo;

            if (newDist < dist[v]){
                dist[v] = newDist;
                heap.inserir(newDist, (void*)(long)v);
            }
        }
    }

    return dist;
}

int main(int argc, char* argv[]){
    
}