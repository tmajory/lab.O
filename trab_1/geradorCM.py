# UFC, Lab. de Otimizacao 2025.1
# Um gerador simples de instancias aleatorios para o problema de
# caminho minimo ponto-a-ponto.

import random as rd

#----------------------------------------------------------------------------------


def gerarInstancia(n, nArcos, nomeDoArquivo, C):
    saida = open(nomeDoArquivo, 'w+')
    
    saida.write(f'{n}\n')
    saida.write(f'0\n')
    saida.write(f'{n-1}\n')
    
    contArcos = 0
    A = dict()
    while contArcos < nArcos:
        a = rd.randint(0,n-1)
        b = rd.randint(0,n-1)
        while b == a:
            b = rd.randint(0,n-1)
        if (a,b) not in A:
            custo = rd.randint(1,C)
            A[(a,b)] = custo
            contArcos += 1

    
    for par,custo in A.items():
        saida.write(f'{par[0]} {par[1]} {custo}\n')
    
    saida.close()
#----------------------------------------------------------------------------------
    

def lerInstancia(nomeDoArquivo):
    entrada = open(nomeDoArquivo, 'r')
    
    n = int(entrada.readline())
    s = int(entrada.readline())
    t = int(entrada.readline())
    
    # Arcos de saida a partir de um dado vertice
    A = dict()
    
    infoArco = entrada.readline()
    while len(infoArco) > 0:
        partes = infoArco.split(' ')
        a, b, custo = [int(x) for x in partes]
        if a in A:
            A[a].append( (b,custo) )
        else:
            A[a] = [ (b,custo) ]
        infoArco = entrada.readline()
    
    entrada.close()
    
    return n, s, t, A
#----------------------------------------------------------------------------------


if __name__ == '__main__':
    
    # Semente do gerador pseudoaleatorio
    rd.seed(4987)
    
    # Numero de vertices, de arcos, e comprimento maximo de um arco.
    # (Os comprimentos dos arcos sao inteiros maiores ou iguais a 1.)
    n = 10000
    m = 15000
    C = 50
    
    nomeDoArquivo = 'umgrafo.txt'
    
    gerarInstancia(n, m, nomeDoArquivo, C)

    # Realizar uma leitura dos dados recem-gerados, apenas para verificar se
    # o arquivo e' bem formado.
    nn, s, t, A = lerInstancia( nomeDoArquivo )

