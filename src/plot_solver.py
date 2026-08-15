import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import sys
import os

# ── Chargement des données ──────────────────────────────────────────────────
csv_file = sys.argv[1] if len(sys.argv) > 1 else "solver_log.csv"

if not os.path.exists(csv_file):
    print(f"Fichier '{csv_file}' introuvable.")
    print("Usage : python plot_solver.py solver_log.csv")
    sys.exit(1)

df = pd.read_csv(csv_file)
print(f"Données chargées : {len(df)} itérations")
print(df.describe())

# ── Figure avec 3 sous-graphes ──────────────────────────────────────────────
fig = plt.figure(figsize=(12, 10))
fig.suptitle("Convergence du solveur — Descente de gradient", fontsize=14, fontweight="bold")

gs = gridspec.GridSpec(3, 1, hspace=0.45)

# ── 1. Pas local (local_step) ───────────────────────────────────────────────
ax1 = fig.add_subplot(gs[0])
ax1.semilogy(df["k"], df["local_step"], color="#2563eb", linewidth=1.2, label="local_step")
ax1.set_ylabel("Pas local (log)", fontsize=11)
ax1.set_title("Évolution du pas en fonction des itérations", fontsize=11)
ax1.legend(fontsize=9)
ax1.grid(True, which="both", linestyle="--", alpha=0.4)

# Annoter les zones de backtracking (pas très petit)
seuil_bt = df["local_step"].median() * 1e-3
zones_bt = df[df["local_step"] < seuil_bt]
if not zones_bt.empty:
    ax1.axhline(y=seuil_bt, color="red", linestyle=":", linewidth=0.8, label="seuil backtracking")
    ax1.scatter(zones_bt["k"], zones_bt["local_step"], color="red", s=10, zorder=5, label="backtracking difficile")
    ax1.legend(fontsize=9)

# ── 2. Norme du gradient ────────────────────────────────────────────────────
ax2 = fig.add_subplot(gs[1])
ax2.semilogy(df["k"], df["gradient_norm"], color="#16a34a", linewidth=1.2, label="||grad||")
ax2.set_ylabel("||grad|| (log)", fontsize=11)
ax2.set_title("Norme du gradient", fontsize=11)
ax2.legend(fontsize=9)
ax2.grid(True, which="both", linestyle="--", alpha=0.4)

# Ligne de tolérance
tolerance = 1e-12
ax2.axhline(y=tolerance, color="orange", linestyle="--", linewidth=1, label=f"tolérance = {tolerance:.0e}")
ax2.legend(fontsize=9)

# ── 3. Erreur totale ────────────────────────────────────────────────────────
ax3 = fig.add_subplot(gs[2])
ax3.semilogy(df["k"], df["error"], color="#dc2626", linewidth=1.2, label="erreur totale")
ax3.set_xlabel("Itération k", fontsize=11)
ax3.set_ylabel("Erreur (log)", fontsize=11)
ax3.set_title("Erreur totale (violation de Kirchhoff)", fontsize=11)
ax3.legend(fontsize=9)
ax3.grid(True, which="both", linestyle="--", alpha=0.4)

# ── Statistiques textuelles ─────────────────────────────────────────────────
n_iter       = len(df)
step_min     = df["local_step"].min()
step_max     = df["local_step"].max()
grad_init    = df["gradient_norm"].iloc[0]
grad_final   = df["gradient_norm"].iloc[-1]
error_init   = df["error"].iloc[0]
error_final  = df["error"].iloc[-1]

stats_text = (
    f"Itérations : {n_iter}\n"
    f"Pas : [{step_min:.2e}, {step_max:.2e}]\n"
    f"||grad|| : {grad_init:.2e} → {grad_final:.2e}\n"
    f"Erreur   : {error_init:.2e} → {error_final:.2e}"
)
fig.text(0.72, 0.97, stats_text, fontsize=8.5,
         verticalalignment="top",
         bbox=dict(boxstyle="round,pad=0.4", facecolor="#f1f5f9", edgecolor="#94a3b8"))

# ── Sauvegarde et affichage ─────────────────────────────────────────────────
output_png = csv_file.replace(".csv", "_convergence.png")
plt.savefig(output_png, dpi=150, bbox_inches="tight")
print(f"Graphique sauvegardé : {output_png}")
plt.show()