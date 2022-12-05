import matplotlib.pyplot as plt
import numpy as np
positions = []
solutions = []
with open("../heuristico/in-0.txt", "r") as file:
    for line in file:
        positions.append(line.split())

with open("../heuristico/out-0.txt", "r") as file:
    for line in file:
        solutions.append(line.split())

distance_out = solutions[0][0]
solutions.pop(0)
tour_out = solutions[0]

N = int(positions[0][0])
positions.pop(0)

x = [item[0] for item in positions]
y = [item[1] for item in positions]
fig, ax = plt.subplots(2, sharex=True, sharey=True)         # Prepare 2 plots
ax[0].set_title('Cidades')
ax[1].set_title('Caminho otimizado - heurística')
ax[0].scatter(x, y)             # plot A
ax[1].scatter(x, y)             # plot B
start_node = 0
distance = 0.

for i in range(N-1):
        ax[1].plot([x[i], x[i+1]], [y[i], y[i+1]])

ax[1].plot([x[-1], x[0]], [y[-1], y[0]])
#ax[1].set_xticklabels(ax[1].get_xticklabels(), rotation=40, ha="right")
#ax[1].set_yticklabels(ax[1].get_yticklabels(), rotation=40, ha="right")
ax[0].set_yticklabels([])
ax[0].set_xticklabels([])

ax[1].set_yticklabels([])
ax[1].set_xticklabels([])
plt.show()