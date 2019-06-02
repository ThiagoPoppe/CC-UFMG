import numpy as np

class Ray:
    """
        Classe para representar um raio
    """

    # Método para inicializar um objeto Ray
    def __init__(self, origin, direction):
        self.__origin = origin
        self.__dir = direction

    # Método para retornarmos a origem do raio
    def origin(self):
        return self.__origin

    # Método para retornarmos a direção do raio
    def dir(self):
        return self.__dir

    # Método para retornamos um ponto no raio
    def point(self, t):
        return self.__origin + t * self.__dir