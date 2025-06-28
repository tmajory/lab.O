import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from matplotlib.ticker import ScalarFormatter, AutoMinorLocator

# Lê o CSV
df = pd.read_csv("resultados.csv", encoding='utf-8')

# Extrai a densidade dos nomes dos arquivos
def extrair_densidade(nome_arquivo):
    partes = nome_arquivo.split("_")
    for p in partes:
        if p.startswith("d"):
            try:
                return float("0." + p[1:].zfill(4))
            except:
                return None
    return None

df["Densidade"] = df["arquivo"].apply(extrair_densidade)
df["Densidade"] = df["Densidade"].map(lambda x: f"{x:.4f}")
df["n_vertices"] = df["n_vertices"].astype(int)

# Estilo LaTeX
sns.set(style="whitegrid", font="serif", context="talk", font_scale=1.3)
plt.rcParams.update({
    "text.usetex": False,  # coloque True se você estiver usando compilador LaTeX completo
    "font.family": "serif",
    "axes.labelsize": 14,
    "axes.titlesize": 16,
    "legend.fontsize": 12,
    "xtick.labelsize": 12,
    "ytick.labelsize": 12
})

def plot_save(y, y_label, filename, log_y=False):
    plt.figure(figsize=(10, 6))
    ax = sns.lineplot(data=df, x="n_vertices", y=y, hue="Densidade", marker="o", palette="tab10")

    if log_y:
        ax.set_yscale("log")
    ax.set_xscale("log")

    ax.set_title(f"{y_label} por número de vértices")
    ax.set_xlabel("Número de vértices (n)")
    ax.set_ylabel(y_label)

    ax.xaxis.set_major_formatter(ScalarFormatter())
    ax.yaxis.set_major_formatter(ScalarFormatter())
    ax.xaxis.set_minor_locator(AutoMinorLocator())
    ax.yaxis.set_minor_locator(AutoMinorLocator())

    ax.legend(title="Densidade")
    plt.tight_layout()

    plt.savefig(f"{filename}.pdf")
    plt.savefig(f"{filename}.png", dpi=300)
    plt.close()

# Geração dos 3 gráficos
plot_save("tempo_medio_ms", "Tempo médio de execução (ms)", "tempo_vs_vertices", log_y=True)
plot_save("n_iteracoes", "Número médio de iterações", "iteracoes_vs_vertices", log_y=True)
plot_save("custo_minimo", "Custo médio do caminho mínimo", "custo_vs_vertices", log_y=False)
