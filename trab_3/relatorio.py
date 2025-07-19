import pandas as pd
import matplotlib.pyplot as plt

class Relatorio:
    def __init__(self, arquivo_astar, arquivo_dijkstra, arquivo_metricas):
        # Lê os resultados dos algoritmos
        self.df_astar = pd.read_csv(arquivo_astar)
        self.df_astar["algoritmo"] = "A*"

        self.df_dijkstra = pd.read_csv(arquivo_dijkstra)
        self.df_dijkstra["algoritmo"] = "DijkstraHeap"

        self.df_resultados = pd.concat([self.df_astar, self.df_dijkstra], ignore_index=True)

        # Lê as métricas estruturais
        self.df_metricas = pd.read_csv(arquivo_metricas)

        # Merge e seleção do melhor algoritmo por instância
        self.df_completo = pd.merge(
            self.df_resultados,
            self.df_metricas,
            on=["n_v", "d", "n_inst"],
            how="inner"
        )

        self.melhores = self.df_completo.loc[
            self.df_completo.groupby(["n_v", "d", "n_inst"])["tempoExecucao"].idxmin()
        ].reset_index(drop=True)

    def comparar_metrica(self, eixo_x, eixo_y, titulo=None):
        cores = {"A*": "#1f77b4", "DijkstraHeap": "#ff7f0e"}

        plt.figure(figsize=(10, 6))
        for alg, grupo in self.melhores.groupby("algoritmo"):
            plt.scatter(grupo[eixo_x], grupo[eixo_y],
                        color=cores[alg], label=alg,
                        alpha=0.7, s=grupo["n_v"] / 10)  # Tamanho proporcional ao número de vértices


        plt.xlabel(eixo_x.replace("_", " ").capitalize())
        plt.ylabel(eixo_y.replace("_", " ").capitalize())
        plt.title(titulo or f"{eixo_x} vs {eixo_y} (cor: algoritmo mais rápido)")
        plt.legend(title="Algoritmo")
        plt.grid(True)
        plt.tight_layout()
        # plt.show()
        plt.savefig(f"{eixo_x}_x_{eixo_y}")

if __name__ == "__main__":
    relatorio = Relatorio(
        "trab_3/resultados_dijkstraHeap.csv",
        "trab_3/resultados_aestrela.csv",
        "trab_3/metricas_instancias.csv"
    )

    # Exemplo: Clusterização vs Excentricidade
    relatorio.comparar_metrica("clusterizacao", "excentricidade", titulo="Clusterização × Excentricidade")

    # Exemplo: Densidade vs Diâmetro
    relatorio.comparar_metrica("clusterizacao", "densidade", titulo="Clusterização × Densidade")

    relatorio.comparar_metrica("clusterizacao", "diametro", titulo="Clusterização × Diâmetro")