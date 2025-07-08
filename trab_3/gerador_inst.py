import random as rd
import os
import networkx as nx

def gerar_instancia(n, densidade, instancia_id, pasta_saida, C):
    m = int(densidade * n * (n - 1))
    s = 0
    t = n - 1

    rd.seed(1000 * n + int(densidade * 10000) + instancia_id)

    A = dict()
    vertices_no_caminho = list(range(s, t + 1))
    for i in range(len(vertices_no_caminho) - 1):
        a = vertices_no_caminho[i]
        b = vertices_no_caminho[i + 1]
        custo = rd.randint(1, C)
        A[(a, b)] = custo

    contArcos = len(A)
    while contArcos < m:
        a = rd.randint(0, n - 1)
        b = rd.randint(0, n - 1)
        if a == b or (a, b) in A:
            continue
        custo = rd.randint(1, C)
        A[(a, b)] = custo
        contArcos += 1

    nome_base = f'grafo_n{n}_d{int(densidade * 1000):04d}_inst{instancia_id}'
    nome_arquivo = os.path.join(pasta_saida, nome_base + '.txt')

    with open(nome_arquivo, 'w') as saida:
        saida.write(f'{n}\n')
        saida.write(f'{s}\n')
        saida.write(f'{t}\n')
        for (a, b), custo in A.items():
            saida.write(f'{a} {b} {custo}\n')

    G = nx.DiGraph()
    G.add_nodes_from(range(n))
    for (a, b), custo in A.items():
        G.add_edge(a, b, weight=custo)

    densidade_grafo = nx.density(G)

    componentes = list(nx.strongly_connected_components(G))
    maior_comp = max(componentes, key=len)
    H = G.subgraph(maior_comp)

    try:
        diametro = nx.diameter(H)
        excentricidades = nx.eccentricity(H)
        exc_media = sum(excentricidades.values()) / len(excentricidades)
    except:
        diametro = -1
        exc_media = -1

    try:
        clusterizacao = nx.average_clustering(G.to_undirected())
    except:
        clusterizacao = -1

    stats_path = os.path.join(pasta_saida, nome_base + '.stats')
    with open(stats_path, 'w') as f:
        f.write(f'Vertices: {n}\n')
        f.write(f'Arestas: {m}\n')
        f.write(f'Densidade: {densidade_grafo:.6f}\n')
        f.write(f'Diametro: {diametro}\n')
        f.write(f'Excentricidade media: {exc_media:.6f}\n')
        f.write(f'Clusterizacaoo global: {clusterizacao:.6f}\n')


if __name__ == '__main__':
    tamanhos = [#100, 500, 1000, 5000, 10000, 
                50000]
    densidades = [0.001, 0.0025, 0.003, 0.005]
    num_instancias = 5
    C = 5

    pasta_saida = 'instancias'
    os.makedirs(pasta_saida, exist_ok=True)

    for n in tamanhos:
        for d in densidades:
            for i in range(num_instancias):
                print(f'Gerando grafo n={n}, d={d:.4f}, instância={i}')
                gerarInstancia(n, d, i, pasta_saida, C)
