import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import matplotlib.animation as animation

# Define positions for our three nodes
pos = {"a": (-1, 0), "b": (1, 0), "c": (0, 1)}

fig, ax = plt.subplots(figsize=(6, 6))

# Set dark background colors for the figure and axes.
fig.patch.set_facecolor('black')
ax.set_facecolor('black')

def update(frame):
    ax.cla()
    ax.axis('equal')
    ax.axis('off')
    ax.set_xlim(-2, 2)
    ax.set_ylim(-2, 2)
    # Set dark background for the axes
    ax.set_facecolor('black')

    # Increase node size from 500 to 1000 for bigger nodes
    if frame >= 20:
        x_a, y_a = pos["a"]
        ax.scatter(x_a, y_a, s=1000, color='skyblue', edgecolors='white', zorder=3)
        ax.text(x_a, y_a, "a", fontsize=12, ha='center', va='center', color='white', zorder=4)

    if frame >= 40:
        x_b, y_b = pos["b"]
        ax.scatter(x_b, y_b, s=1000, color='skyblue', edgecolors='white', zorder=3)
        ax.text(x_b, y_b, "b", fontsize=12, ha='center', va='center', color='white', zorder=4)

    if frame >= 60:
        x_c, y_c = pos["c"]
        ax.scatter(x_c, y_c, s=1000, color='skyblue', edgecolors='white', zorder=3)
        ax.text(x_c, y_c, "c", fontsize=12, ha='center', va='center', color='white', zorder=4)

    if frame >= 80:
        x_a, y_a = pos["a"]
        x_b, y_b = pos["b"]
        progress = min((frame - 80) / 20.0, 1)
        x_edge = x_a + progress * (x_b - x_a)
        y_edge = y_a + progress * (y_b - y_a)
        ax.plot([x_a, x_edge], [y_a, y_edge], color='gray', linewidth=2, zorder=2)

    ax.set_title(f"Frame {frame}", fontsize=14, color='white')
    return ax

# Increase animation speed:
# - Use a lower interval (30 ms instead of 50 ms)
# - Save with a higher fps (30 instead of 20)
ani = animation.FuncAnimation(fig, update, frames=range(0, 101), interval=30, blit=False)
ani.save("graph_animation.mp4", writer="ffmpeg", fps=30)
