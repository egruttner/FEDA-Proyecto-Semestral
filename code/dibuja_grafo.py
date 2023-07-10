import numpy as np
import networkx as nx
import matplotlib.pyplot as plt

# Leer la matriz de adyacencia desde el archivo de texto
adjacency_matrix = np.loadtxt('matriz_adyacencia.txt', dtype=int)

# Crear un grafo a partir de la matriz de adyacencia
G = nx.from_numpy_array(adjacency_matrix)

# Dibujar el grafo
pos = nx.spring_layout(G)
nx.draw(G, pos, with_labels=True, node_color='lightblue', edge_color='gray')

# Obtener los pesos de las aristas
edge_labels = nx.get_edge_attributes(G, 'weight')

# Mostrar los pesos en el gráfico
nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)

plt.show()
