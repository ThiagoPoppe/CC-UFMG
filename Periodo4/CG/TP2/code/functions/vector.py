import numpy as np

# Função que retorna a norma ao quadrado de um vetor
def squared_norm(v):
    return v[0]**2 + v[1]**2 + v[2]**2

# Função que retorna um vetor normalizado
def normalize(v):
    norm = np.linalg.norm(v)

    if norm == 0:
        return v
    else:
        return v / norm