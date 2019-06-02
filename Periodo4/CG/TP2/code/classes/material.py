import numpy as np

from numpy import array as Vec3
from numpy.random import uniform as rand

from functions.vector import normalize
from functions.physics import *

from classes.ray import Ray

def random_point_in_sphere():
    r = np.sqrt(rand())
    theta = 2 * np.pi * rand()

    x = r * np.cos(theta)
    y = r * np.sin(theta)
    z = rand()

    return Vec3([x, y, z])

class Material:
    """
        Classe abstrata para representar materiais
    """

    # Método abstrato para computar o comportamento o espalhamento de raios
    def scatter(self, ray):
        raise NotImplementedError

class Lambertian(Material):
    """
        Classe para representar materiais lambertianos
    """

    # Método para inicializar uma classe do tipo Lambertian
    def __init__(self, albedo):
        self.__albedo = albedo

    # Método para retornar o albedo do objeto
    def albedo(self):
        return self.__albedo

    # Método que define a função scatter
    def scatter(self, ray, point, normal):
        target = point + normal + random_point_in_sphere()
        scattered = Ray(point, target - point)
        attenuation = self.albedo()

        return [True, attenuation, scattered]

class Metal(Material):
    """
        Classe para representar materiais metálicos
    """

    # Método para inicializar uma classe do tipo Metal
    def __init__(self, albedo, fuzz):
        self.__albedo = albedo

        if fuzz < 1.0:
            self.__fuzz = fuzz
        else:
            self.__fuzz = 1.0

    # Método para retornar o albedo do objeto
    def albedo(self):
        return self.__albedo

    # Método para retornar o fuzz do objeto
    def fuzz(self):
        return self.__fuzz

    # Método que define a função scatter
    def scatter(self, ray, point, normal):
        reflected = reflect(normalize(ray.dir()), normal)
        scattered = Ray(point, reflected + self.fuzz() * random_point_in_sphere())
        attenuation = self.albedo()

        return [np.dot(scattered.dir(), normal) > 0, attenuation, scattered]

class Dielectric(Material):
    """
        Classe para representar materiais dielétricos
    """

    # Método para inicializar uma classe do tipo Dielectric
    def __init__(self, ref_index):
        self.__ri = ref_index

    # Método para retornar o índice de refração do objeto
    def ref_index(self):
        return self.__ri

    # Método que define a função scatter
    def scatter(self, ray, point, normal):
        reflected = reflect(ray.dir(), normal)
        attenuation = Vec3([1.0, 1.0, 1.0])
        
        outward_normal = normal
        factor = 1 / self.ref_index()
        cos = -1 * np.dot(ray.dir(), normal) / np.linalg.norm(ray.dir())

        if np.dot(ray.dir(), normal) > 0:
            outward_normal = -normal
            factor = self.ref_index()
            cos = self.ref_index() * np.dot(ray.dir(), normal) / np.linalg.norm(ray.dir())

        has_refracted, refracted = refract(ray.dir(), outward_normal, factor)
        if has_refracted:
            reflect_prob = schlick(cos, self.ref_index())
        else:
            reflect_prob = 1.0

        if rand() < reflect_prob:
            scattered = Ray(point, reflected)
        else:
            scattered = Ray(point, refracted)

        return [True, attenuation, scattered]