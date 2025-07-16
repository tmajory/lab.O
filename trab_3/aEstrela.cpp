#include <unordered_map>
#include <vector>
#include <algorithm>
#include <limits>
#include <fstream>
#include <chrono>
#include <functional>
#include "grafo.hpp"
#include "heapBin.hpp"

//estrutura que representa as informacoes de um nó no caminho
struct NoInfo{
    int vertice;
    int custoAcumulado;
    int estimativaTotal;
    void* anterior;//referencia para o nó anterior, armazenado para retorno do caminho gerado.

    bool operator>(const NoInfo& other) const{
        return estimativaTotal > other.estimativaTotal;
    }

};

struct Resultado{
    double custoTotal;
    vector<char> caminho;    

};



class AEstrela {
    private:
        Grafo& grafo;
        int objetivo;
    
    int H(int atual, int objetivo){
        //Implementar heuristica usando distância euclidiana
        return 0;
    }

    public:
        AEstrela(Grafo& g): grafo(g){}

        Resultado encontrarCaminho(int inicio, int fim){
            objetivo = fim;
            Heap heap(grafo.getNumVertices());
            unordered_map<int, int> custoParcial;
            unordered_map<int, int> noAnterior;
            
            //inicialização de variaveis
            NoInfo noInicial;
            noInicial.vertice = inicio;
            noInicial.custoAcumulado = 0;
            noInicial.estimativaTotal = H(inicio, fim);
            noInicial.anterior = nullptr;

            heap.inserir(noInicial.estimativaTotal, new NoInfo(noInicial));

            custoParcial[inicio] = 0;
            noAnterior[inicio] = -1;

            while (heap.getTamanho() > 0){
                HeapItem item = heap.removerMinimo();
                NoInfo* atual = static_cast<NoInfo*>(item.data);
                Resultado resolucao;
                
                if (atual->vertice == fim){
                    vector<char> caminho;
                    int vertice = fim;
                    while (vertice != -1){
                        caminho.push_back(vertice);
                        vertice = noAnterior[vertice];
                    }

                    reverse(caminho.begin(), caminho.end());
                    resolucao.caminho = caminho;
                    resolucao.custoTotal = atual->custoAcumulado;

                    delete atual;
                    while (heap.getTamanho() > 0){
                        HeapItem temp = heap.removerMinimo();
                        delete static_cast<NoInfo*>(temp.data);
                    }

                    return resolucao;
                }

                for (const Aresta& aresta: grafo.getNeighbors(atual->vertice)){
                    int vizinho = aresta.destino;
                    int novoCusto = atual->custoAcumulado + aresta.custo;

                    if (custoParcial.find(vizinho) == custoParcial.end() || novoCusto < custoParcial[vizinho]){
                        custoParcial[vizinho] = novoCusto;
                        noAnterior[vizinho] = atual->vertice;

                        NoInfo* novoNo = new NoInfo;
                        novoNo->vertice = vizinho;
                        novoNo->custoAcumulado = novoCusto;
                        novoNo->estimativaTotal = novoCusto + H(vizinho, fim);
                        novoNo->anterior=atual;

                        heap.inserir(novoNo->estimativaTotal, novoNo);
                        
                    }
                }
                

                delete atual;
            }

            return {};

        }
};

int main(int argc, char* argv[]){
        
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <arquivo_entrada> <arquivo_saida>\n";
        return 1;
    }
    
    ifstream inFile(argv[1]);
    ofstream outFile(argv[2], ios::app);

    int n, origem, destino;
    inFile >> n;
    inFile >> origem;
    inFile >> destino;

    Grafo g(n);
    int u, v, custo;
    while (inFile >> u >> v >> custo){
        g.addAresta(u, v, custo);
    }

    AEstrela  aestrela(g);

    Resultado resultado = aestrela.encontrarCaminho(origem,destino);

    outFile << resultado.custoTotal << '\n';
    

    return 0;

}