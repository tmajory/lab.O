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


};

int main(){
    Grafo g(6);
    g.adicionaAresta(5, 2);
    g.adicionaAresta(5, 0);
    g.adicionaAresta(4, 0);
    g.adicionaAresta(4, 1);
    g.adicionaAresta(2, 3);
    g.adicionaAresta(3, 1);


    g.ordenacaoTopologica();

    return 0;

}
