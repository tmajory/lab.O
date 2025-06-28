import random as rd
import os

def gerarInstancia(n, densidade, instancia_id, pasta_saida, C):
    m = int(densidade * n * (n - 1))  # número de arcos
    s = 0
    t = n - 1
    
    rd.seed(1000 * n + int(densidade * 10000) + instancia_id)  # Seed única por configuração
    
    A = dict()
    vertices_no_caminho = list(range(s, t + 1))  # Caminho garantido de s até t
    for i in range(len(vertices_no_caminho) - 1):
        a = vertices_no_caminho[i]
        b = vertices_no_caminho[i + 1]
        custo = rd.randint(1, C)
        A[(a, b)] = custo

    contArcos = len(A)
    while contArcos < m:
        a = rd.randint(0, n - 1)
        b = rd.randint(0, n - 1)
        if a == b:
            continue
        if (a, b) in A:
            continue
        custo = rd.randint(1, C)
        A[(a, b)] = custo
        contArcos += 1

    nomeDoArquivo = os.path.join(
        pasta_saida,
        f'grafo_n{n}_d{int(densidade * 1000):04d}_inst{instancia_id}.txt'
    )

    with open(nomeDoArquivo, 'w') as saida:
        saida.write(f'{n}\n')
        saida.write(f'{s}\n')
        saida.write(f'{t}\n')
        for (a, b), custo in A.items():
            saida.write(f'{a} {b} {custo}\n')

if __name__ == '__main__':
    tamanhos = [100, 500, 1000, 5000, 10000, 50000]
    densidades = [0.001, 0.0025, 0.003, 0.005]  # 0.1%, 0.25%, 0.3%, 0.5%
    num_instancias = 10
    C = 5

    pasta_saida = 'instancias'
    os.makedirs(pasta_saida, exist_ok=True)

    for n in tamanhos:
        for d in densidades:
            for i in range(num_instancias):
                print(f'Gerando grafo n={n}, d={d:.4f}, instância={i}')
                gerarInstancia(n, d, i, pasta_saida, C)
