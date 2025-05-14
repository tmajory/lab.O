#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <climits>
#include <queue>
#include <utility>
#include <string>


using namespace std;

class Grafo{
    int V;//Vértices
    list <pair<int,int>>* adj;//Lista de adjacência dos vértices e seus pesos.

    // void ordenacaoTopologicaUtil(int v, bool visitado[], stack<int>& pilha){
    //     visitado[v] = true;
    //     cout << "Visitando o vértice: " << v << endl;

    //     for (auto i = adj[v].begin(); i != adj[v].end(); i++){
    //         if (!visitado[*i]){
    //             ordenacaoTopologicaUtil(*i, visitado, pilha);
            
    //         }
    //     }

    //     pilha.push(v);
    // }


    public:
    Grafo(int V) {
        this->V = V;
        adj = new list<pair<int,int>>[V];

    }


    void adicionaAresta(int v, int w, int peso = 1){
        // Adiciona uma aresta direcionada de v para w com peso
        adj[v].push_back(make_pair (w, peso));

    }

    // void ordenacaoTopologica(){
    //     stack<int> pilha;
    //     bool* visitado = new bool[V];
        
    //     //iniciando nós como não visitados
    //     for (int i = 0; i < V; i++){
    //         visitado[i] = false;
    //     }

    //     //chama a função recursiva para cada nó não visitado
    //     for (int i = 0; i < V; i++){
    //         if (!visitado[i]){
    //             ordenacaoTopologicaUtil(i, visitado, pilha);
    //         }
    //     }

    //     //imprime a ordenação topológica
    //     cout << "Ordenação Topológica do Grafo:\n ";

    //     while (!pilha.empty()){
    //         cout << pilha.top() << " ";
    //         pilha.pop();
    //     }
    //     cout << endl;
    //     delete[] visitado;
    // }

    // void buscaProfundidade() {
    //     string* cor = new string[V]; // "Branca", "Cinza", "Preta"

    //     // Inicializa todos os vértices como "Branca"
    //     for (int i = 0; i < V; i++) {
    //         cor[i] = "Branca";
    //     }

    //     // Visita cada vértice não explorado
    //     for (int v = 0; v < V; v++) {
    //         if (cor[v] == "Branca") {
    //             visitar(v, cor);
    //         }
    //     }

    //     delete[] cor; // Libera a memória
    // }

    // Função auxiliar para visitar vértices recursivamente
    // void visitar(int v, string* cor) {
    //     cor[v] = "Cinza";
    //     cout << "Visitando vértice: " << v << endl;
        
    //     // Percorre todos os vértices adjacentes
    //     for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
    //         int u = *it; // Vértice adjacente
    //         if (cor[u] == "Branca") {
    //             visitar(u, cor);
    //         }
    //     }
        
    //     cor[v] = "Preta";
    // }
    
    
    vector<int> dijskstra(int origem) {
        // Implementação do algoritmo de Dijkstra
        vector<int> distancia(V, INT_MAX); // Inicializa todas as distâncias como infinito
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> filaPrioridade;
        distancia[origem] = 0;
        filaPrioridade.push(make_pair(0, origem)); // Adiciona o vértice de origem à fila

        while (!filaPrioridade.empty()) {
            int u = filaPrioridade.top().second; // Vértice com a menor distância
            filaPrioridade.pop();

            // Percorre todos os vértices adjacentes
            for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
                int v = it->first; // Vértice adjacente
                int peso = it->second; // Peso da aresta

                // Relaxa a aresta se uma distância menor for encontrada
                if (distancia[u] + peso < distancia[v]) {
                    distancia[v] = distancia[u] + peso;
                    filaPrioridade.push(make_pair(distancia[v], v));
                }
            }
        }
        return distancia; // Retorna o vetor de distâncias
    }


};

int main(){
    Grafo g(5);
    g.adicionaAresta(0, 2, 2);
    g.adicionaAresta(0, 1, 3);
    g.adicionaAresta(1, 3, 5);
    g.adicionaAresta(2, 3, 0);
    g.adicionaAresta(3, 4, 9); 
    g.adicionaAresta(2, 4, 7);


    // g.ordenacaoTopologica();
    // g.buscaProfundidade();

    vector<int> distancia = g.dijskstra(0);

    cout << "Distâncias a partir do vértice 0:\n";
    for (int i = 0; i < distancia.size(); i++) {
        cout << "Vértice " << i << ": " << distancia[i] << endl;
    }
    

    return 0;

}
