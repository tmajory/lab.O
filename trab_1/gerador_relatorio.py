import pandas as pd
import matplotlib.pyplot as plt


def ler_resultados(arquivo):
    try:
        df = pd.read_csv(
            arquivo,
            sep=",",
            names=["Custo", "Vertices Visitados", "Tempo Execução (ms)"],
            engine="python"
        )
        return df
    except Exception as e:
        print(f"Erro ao ler o arquivo: {e}")
        return None


def gerar_relatorio(df):
    print("\n📊 ==== Relatório de Resultados ====\n")
    print(df)
    print("\nResumo estatístico:\n")
    print(df.describe())


def gerar_graficos(df):
    plt.figure(figsize=(10, 6))
    plt.subplot(2, 1, 1)
    plt.plot(df["Tempo Execução (ms)"], marker="o", label="Tempo (ms)", color="blue")
    plt.title("Tempo de Execução por Instância")
    plt.xlabel("Instância")
    plt.ylabel("Tempo (ms)")
    plt.grid(True)
    plt.legend()

    plt.subplot(2, 1, 2)
    plt.plot(df["Vertices Visitados"], marker="s", label="Vértices Visitados", color="green")
    plt.title("Vértices Visitados por Instância")
    plt.xlabel("Instância")
    plt.ylabel("Nº de Vértices Visitados")
    plt.grid(True)
    plt.legend()

    plt.tight_layout()
    plt.show()


def salvar_csv(df, nome_arquivo="relatorio.csv"):
    df.to_csv(nome_arquivo, index=False)
    print(f"\n✅ Relatório salvo como {nome_arquivo}\n")


if __name__ == "__main__":
    arquivo = input("resultadodijkstra.txt")

    df = ler_resultados(arquivo)

    if df is not None:
        gerar_relatorio(df)
        
        opcao_grafico = input("Deseja gerar gráficos? (s/n): ").lower()
        if opcao_grafico == 's':
            gerar_graficos(df)

        opcao_csv = input("Deseja salvar o relatório em CSV? (s/n): ").lower()
        if opcao_csv == 's':
            salvar_csv(df)
