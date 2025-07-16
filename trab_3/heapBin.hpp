#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <utility>

using namespace std;


//Estrutura para armazenar os dados do heap
struct HeapItem {
    int pr;
    void* data;

    HeapItem(int prioridade, void* objeto) : pr(prioridade), data(objeto) {}
    HeapItem() : pr(0), data(nullptr) {}
};

class Heap {
    private:
        vector<HeapItem> vetor;
        int tamanho;
        int capacidade;

        int pai(int i) {
            return (i - 1) / 2;
        }

        int filhoEsquerdo(int i) {
            return 2 * i + 1;
        }
        int filhoDireito(int i) {
            return 2 * i + 2;
        }

        void subir(int posicao){
            int k = posicao;
            if(k > 0 && vetor[pai(k)].pr > vetor[k].pr){
                swap(vetor[pai(k)], vetor[k]);
                subir(pai(k));
            }
        }

        void descer(int posicao){
            int k = posicao;
            int d = filhoDireito(k);
            int e = filhoEsquerdo(k);

            if (e < tamanho){
                int menorFilho;
                if (d < tamanho){
                    menorFilho = (vetor[d].pr < vetor[e].pr) ? d : e;
                }
                else{
                    menorFilho = e;
                }
                if (vetor[k].pr > vetor[menorFilho].pr){
                    swap(vetor[k], vetor[menorFilho]);
                    descer(menorFilho);
                }
            }
            
        }

    public:
        Heap(int capacidade) : capacidade(capacidade), tamanho(0) {
            vetor.resize(capacidade);
        }

        void inserir(int prioridade, void* objeto) {
            if (tamanho >= capacidade) {
                throw runtime_error("Heap cheio");
            }
            vetor[tamanho] = {prioridade, objeto};
            tamanho++;
            subir(tamanho-1);
        }

        HeapItem removerMinimo() {
            if (tamanho == 0) {
                throw runtime_error("Heap vazio");
            }
            HeapItem minimo = vetor[0];
            vetor[0] = vetor[tamanho-1];
            tamanho--;
            descer(0);
            return minimo;
        }

        int getTamanho() const {
            return tamanho;
        }

        string toString() const{
            string s = "<<";
            for (int i = 0; i < tamanho; i++) {
                s += "(" + to_string(vetor[i].pr) + ","+ to_string(reinterpret_cast<size_t>(vetor[i].data)) + ")";       
            }
            s += "<<";
            return s;
        }
};
