#include <iostream>
#include <vector>
#include <list>
#include <stack>

using namespace std;

class Grafo{
    int V;//Vértices
    list<int>* adj;//Lista de adjacência dos vértices

    void ordenacaoTopologicaUtil(int v, bool visitado[], stack<int>& pilha){
        visitado[v] = true;
        cout << "Visitando o vértice: " << v << endl;

        for (auto i = adj[v].begin(); i != adj[v].end(); i++){
            if (!visitado[*i]){
                ordenacaoTopologicaUtil(*i, visitado, pilha);
            
            }
        }

        pilha.push(v);
    }


    public:
    Grafo(int V) {
        this->V = V;
        adj = new list<int>[V];

    }


    void adicionaAresta(int v, int w){
        adj[v].push_back(w);

    }

    void ordenacaoTopologica(){
        stack<int> pilha;
        bool* visitado = new bool[V];
        
        //iniciando nós como não visitados
        for (int i = 0; i < V; i++){
            visitado[i] = false;
        }

        //chama a função recursiva para cada nó não visitado
        for (int i = 0; i < V; i++){
            if (!visitado[i]){
                ordenacaoTopologicaUtil(i, visitado, pilha);
            }
        }

        //imprime a ordenação topológica
        cout << "Ordenação Topológica do Grafo:\n ";

        while (!pilha.empty()){
            cout << pilha.top() << " ";
            pilha.pop();
        }
        cout << endl;
        delete[] visitado;
    }

    void buscaProfundidade() {
        string* cor = new string[V]; // "Branca", "Cinza", "Preta"

        // Inicializa todos os vértices como "Branca"
        for (int i = 0; i < V; i++) {
            cor[i] = "Branca";
        }

        // Visita cada vértice não explorado
        for (int v = 0; v < V; v++) {
            if (cor[v] == "Branca") {
                visitar(v, cor);
            }
        }

        delete[] cor; // Libera a memória
    }

private:
    // Função auxiliar para visitar vértices recursivamente
    void visitar(int v, string* cor) {
        cor[v] = "Cinza";
        cout << "Visitando vértice: " << v << endl;

        // Percorre todos os vértices adjacentes
        for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
            int u = *it; // Vértice adjacente
            if (cor[u] == "Branca") {
                visitar(u, cor);
            }
        }

        cor[v] = "Preta";
    }


};

int main(){
    Grafo g(5);
    g.adicionaAresta(0, 2);
    g.adicionaAresta(0, 1);
    g.adicionaAresta(1, 3);
    g.adicionaAresta(2, 3);
    g.adicionaAresta(3, 4); 
    g.adicionaAresta(2, 4);


    g.ordenacaoTopologica();
    g.buscaProfundidade();
    

    return 0;

}
