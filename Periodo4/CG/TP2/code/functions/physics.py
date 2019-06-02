import numpy as np

from functions.vector import normalize

# Função para refletir um raio
def reflect(v, n):
        return v - 2 * np.dot(v, n) * n

# Função que refrata um raio
def refract(v, n, factor):
    uv = normalize(v)
    dt = np.dot(uv, n)

    delta = 1 - (factor**2 * (1 - dt**2))
    if delta > 0:
        refracted = (factor * (uv - n * dt)) - (n * np.sqrt(delta))
        return [True, refracted]
    else:
        return [False, None]

# Função que implementa a equação de Schlick
def schlick(cos, ref_index):
    r0 = (1 - ref_index) / (1 + ref_index)
    r0 **= 2
    return r0 + (1 - r0) * np.power((1 - cos), 5)