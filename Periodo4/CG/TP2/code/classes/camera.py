import numpy as np

from numpy import array as Vec3
from numpy.random import uniform as rand

from classes.ray import Ray

from functions.vector import normalize

# Função auxiliar que retorna um ponto aleatório em um disco (círculo)
def random_point_in_disk():
    r = np.sqrt(rand())
    theta = 2 * np.pi * rand()

    return Vec3([r * np.cos(theta), r * np.sin(theta), .0])

class Camera:
    """
        Classe para representar nossa camera
    """

    # Método para inicializar uma classe do tipo Camera
    def __init__(self, origin, look_at, vup, fov, aspect, aperture, focus_dist):
        theta = np.radians(fov)
        half_height = np.tan(theta / 2)
        half_width = aspect * half_height

        self.__w = normalize(origin - look_at)
        self.__u = normalize(np.cross(vup, self.__w))
        self.__v = np.cross(self.__w, self.__u)
        self.__len_radius = aperture / 2

        self.__origin = origin
        self.__lower_left_corner = origin - focus_dist * (self.__u * half_width + self.__v * half_height + self.__w)
        self.__horizontal = 2 * self.__u * focus_dist * half_width
        self.__vertical = 2 * self.__v * focus_dist * half_height

    # Método para retornar a posição da câmera
    def origin(self):
        return self.__origin

    # Método para dispararmos um raio
    def shoot_ray(self, s, t):
        rd = self.__len_radius * random_point_in_disk()
        offset = self.__u * rd[0] + self.__v * rd[1]

        origin = self.origin() + offset
        direction = self.__lower_left_corner + s * self.__horizontal + t * self.__vertical - self.__origin - offset
        return Ray(origin, direction)
