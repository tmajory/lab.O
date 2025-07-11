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
    void* anterior; //referencia para o nó anterior, armazenado para retorno do caminho gerado.

    bool operator>(const NoInfo& other) const{
        return estimativaTotal > other.estimativaTotal;
    }

};

//sobrecarga do operador << para impressão de valores dos vetores da estrutra resultado
ostream& operator<<(ostream& os, const vector<int>& vec) {
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
        if (i < vec.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
};

struct Resultado{
    double custoTotal;
    vector<int> caminho;
    vector<int> visitados;    

};


   
double H(int atual, int objetivo){
    //heurística usando a distância euclidiana, usando para o cálculo coordenadas geradas a partir do gerador de instâncias.
    return 0;
};


    
Resultado AEstrela(Grafo& g, int inicio, int fim){


    //inicialização de variaveis
    Heap heap(g.getNumVertices());
    unordered_map<int, int> custoParcial;
    unordered_map<int, int> noAnterior;
    Resultado resolucao;
    resolucao.visitados.reserve(g.getNumVertices());
    
    NoInfo noInicial;
    noInicial.vertice = inicio;
    noInicial.custoAcumulado = 0;
    noInicial.estimativaTotal = H(inicio, fim);
    noInicial.anterior = nullptr;

    heap.inserir(noInicial.estimativaTotal, new NoInfo(noInicial));

    custoParcial[inicio] = 0;
    noAnterior[inicio] = -1;

    /* Pecorre o heap enquanto houver nós a serem visitados
    e busca o caminho mais curto do nó inicial ao nó final
    utilizando a heurística H para estimar o custo restante
    e armazenando os nós visitados e o caminho encontrado.
    Se o nó final for encontrado, o caminho é reconstruído
    a partir dos nós anteriores e o custo total é calculado,
    Após encontrar o caminho, todos os nós restantes no heap são deletados.*/
    while (heap.getTamanho() > 0){
        HeapItem item = heap.removerMinimo();
        NoInfo* atual = static_cast<NoInfo*>(item.data);
        resolucao.visitados.push_back(atual->vertice);

        if (atual->vertice == fim){
            int vertice = fim;
            while (vertice != -1){
                resolucao.caminho.push_back(vertice);
                vertice = noAnterior[vertice];
            }

            reverse(resolucao.caminho.begin(), resolucao.caminho.end());
            // resolucao.caminho = caminho;
            resolucao.custoTotal = atual->custoAcumulado;

            delete atual;
            while (heap.getTamanho() > 0){
                HeapItem temp = heap.removerMinimo();
                delete static_cast<NoInfo*>(temp.data);
            }

            return resolucao;
        }

        for (const Aresta& aresta: g.getNeighbors(atual->vertice)){
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



    Resultado resultado = AEstrela(g,origem,destino);

    outFile << resultado.custoTotal << ',' << resultado.visitados << ',' << resultado.caminho;
    

    return 0;

}