import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os
import warnings

# Ignore warnings for clean console output
warnings.filterwarnings('ignore')

def main():
    # Set style for academic look
    sns.set_theme(style="whitegrid")
    plt.rcParams.update({'font.size': 12})
    plt.rcParams['figure.dpi'] = 300

    results_path = '../results/benchmark_results.csv'
    if not os.path.exists(results_path):
        print(f"Error: {results_path} not found. Please run benchmarks first.")
        return

    try:
        df = pd.read_csv(results_path)
    except Exception as e:
        print(f"Error reading CSV: {e}")
        return

    # Convert avg_time_us to ms for better readability
    df['avg_time_ms'] = df['avg_time_us'] / 1000.0

    # Create output directory
    os.makedirs('figures', exist_ok=True)

    print("Generating LaTeX table...")
    # Generate Table
    # Rows: Representation, Algorithm, Density
    # Columns: Vertices
    # Values: avg_time_ms
    pivot_df = df.pivot_table(
        index=['representation', 'algorithm', 'density'], 
        columns='vertices', 
        values='avg_time_ms'
    )
    
    # Format the table directly to LaTeX
    latex_table = pivot_df.to_latex(
        float_format="%.2f",
        caption="Wyniki pomiarów czasu wykonania (w milisekundach)",
        label="tab:wyniki",
        multirow=True,
        multicolumn=True,
        escape=False
    )
    
    with open('benchmark_table.tex', 'w', encoding='utf-8') as f:
        f.write(latex_table)

    print("Generating charts...")

    # Chart 1: Adjacency List (X: Vertices, Y: Time)
    fig, ax = plt.subplots(figsize=(10, 6))
    df_list = df[df['representation'] == 'List'].copy()
    df_list['Algo_Dens'] = df_list['algorithm'] + " (" + df_list['density'].astype(int).astype(str) + "%)"
    sns.lineplot(data=df_list, x='vertices', y='avg_time_ms', hue='Algo_Dens', 
                 markers=True, style='Algo_Dens', dashes=False, ax=ax)
    ax.set_title('Czas wykonania algorytmów (Lista sąsiedztwa)')
    ax.set_xlabel('Liczba wierzchołków (V)')
    ax.set_ylabel('Średni czas (ms)')
    ax.legend(title='Algorytm (Gęstość)')
    fig.savefig('figures/Chart1_List.png', bbox_inches='tight')
    plt.close(fig)

    # Chart 2: Adjacency Matrix (X: Vertices, Y: Time)
    fig, ax = plt.subplots(figsize=(10, 6))
    df_matrix = df[df['representation'] == 'Matrix'].copy()
    df_matrix['Algo_Dens'] = df_matrix['algorithm'] + " (" + df_matrix['density'].astype(int).astype(str) + "%)"
    sns.lineplot(data=df_matrix, x='vertices', y='avg_time_ms', hue='Algo_Dens', 
                 markers=True, style='Algo_Dens', dashes=False, ax=ax)
    ax.set_title('Czas wykonania algorytmów (Macierz sąsiedztwa)')
    ax.set_xlabel('Liczba wierzchołków (V)')
    ax.set_ylabel('Średni czas (ms)')
    ax.legend(title='Algorytm (Gęstość)')
    fig.savefig('figures/Chart2_Matrix.png', bbox_inches='tight')
    plt.close(fig)

    # Charts 3-6: By Density (X: Vertices, Y: Time)
    densities = [25, 50, 75, 100]
    for i, d in enumerate(densities, start=3):
        fig, ax = plt.subplots(figsize=(10, 6))
        df_d = df[df['density'] == d].copy()
        df_d['Algo_Rep'] = df_d['algorithm'] + " (" + df_d['representation'] + ")"
        
        sns.lineplot(data=df_d, x='vertices', y='avg_time_ms', hue='Algo_Rep', 
                     markers=True, style='Algo_Rep', dashes=False, ax=ax)
        
        ax.set_title(f'Czas wykonania algorytmów dla gęstości {d}%')
        ax.set_xlabel('Liczba wierzchołków (V)')
        ax.set_ylabel('Średni czas (ms)')
        ax.legend(title='Algorytm (Reprezentacja)')
        fig.savefig(f'figures/Chart{i}_Density_{d}.png', bbox_inches='tight')
        plt.close(fig)

    print("Successfully generated all charts in 'figures/' directory.")

if __name__ == "__main__":
    main()
