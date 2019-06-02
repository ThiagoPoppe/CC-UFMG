import numpy as np

from numpy import array as Vec3
from numpy.random import uniform as rand

from classes.material import Lambertian, Metal, Dielectric

class Hitable:
    """
        Classe abstrata para representar "hits" nos objetos da cena
    """
    
    # Método abstrato para computar um hit de um raio em um objeto
    def hit(self, ray, t_min, t_max):
        raise NotImplementedError

class Sphere(Hitable):
    """
        Classe que vai representar uma esfera
    """

    # Método para inicializar uma classe do tipo Sphere
    def __init__(self, center, radius, material):
        self.__center = center
        self.__radius = radius
        self.__material = material

    # Método para retornar a posição do centro da esfera
    def center(self):
        return self.__center

    # Método para retornar o raio da esfera
    def radius(self):
        return self.__radius

    # Método para retornar o material da esfera
    def material(self):
        return self.__material

    # Método que define a função hit
    def hit(self, ray, t_min, t_max):
        # Definindo o vetor que parte do ponto de origem do raio até o centro da esfera
        oc = ray.origin() - self.center()

        # Definindo os coeficientes do polinômio para vermos os pontos de interseção
        a = np.dot(ray.dir(), ray.dir())
        b = 2.0 * np.dot(oc, ray.dir())
        c = np.dot(oc, oc) - self.radius()**2

        # Computando o discriminante
        delta = b**2 - 4 * a * c
        if delta > 0:
            # Computamos a menor raiz e vemos se ela está no intervalo
            t = (-1*b - np.sqrt(delta)) / (2*a)
            if t_min < t and t < t_max:
                # Computamos o ponto e a normal dado esse t
                point = ray.point(t)
                normal = (point - self.center()) / self.radius()

                return [True, t, point, normal]

            # Caso contrário, computamos a maior raiz e vemos se ela está no intervalo
            t = (-1*b + np.sqrt(delta)) / (2*a)
            if t_min < t and t < t_max:
                # Computamos o ponto e a normal dado esse t
                point = ray.point(t)
                normal = (point - self.center()) / self.radius()

                return [True, t, point, normal]

        # Caso o discriminante seja menor que 0, retornamos falso e coisas inválidas
        return [False, -1, -1, -1]

class HitableList(Hitable):
    """
        Classe para agrupar objetos do tipo Hitable
    """
    
    # Método para inicializar uma classe do tipo HitableList
    def __init__(self, l):
        self.__list = l

    # Método para retornar a lista de objetos
    def objects(self):
        return self.__list

    # Método que define a função hit
    def hit(self, ray, t_min, t_max):
        # Definindo o status do nosso hit e o ponto mais próximo
        hit_status = [False, -1, -1, -1, None]
        closest = t_max

        # Iterando sobre cada objeto da nossa lista
        for obj in self.objects():
            hit, t, point, normal = obj.hit(ray, t_min, closest)

            # Caso tivermos um hit, atualizamos hit_status e closest
            if hit:
                hit_status[0] = True
                hit_status[1] = t
                hit_status[2] = point
                hit_status[3] = normal
                hit_status[4] = obj.material()

                closest = t

        # Retornamos hit_status
        return hit_status

    # Método static para gerar uma cena aleatória
    @staticmethod
    def random_scene(n_obj):
        objects = []

        # Inserindo uma esfera que será o chão da nossa cena
        objects.append(Sphere(Vec3([0, -1000, 0]), 1000, Lambertian([0.5, 0.5, 0.5])))

        # Inserindo objetos
        for _ in range(n_obj):
            material = rand()
            center = Vec3([rand(-9, 9) + 0.9 * rand(), 0.2, rand(-9, 9) + 0.9 * rand()])
            if np.linalg.norm(center - Vec3([4, 0.2, 0])) > 0.9:
                # Escolhendo um material Lambertiano
                if material < 0.8:
                    objects.append(Sphere(center, 0.2, Lambertian([rand(), rand(), rand()])))
                
                # Escolhendo um material metálico
                elif material < 0.95:
                    albedo = Vec3([0.5 * (1 + rand()), 0.5 * (1 + rand()), 0.5 * (1 + rand())])
                    fuzz = 0.5 * rand()
                    objects.append(Sphere(center, 0.2, Metal(albedo, fuzz)))

                # Escolhendo um material dielétrico, mais especificamente vidro
                else:
                    objects.append(Sphere(center, 0.2, Dielectric(1.5)))

        # Inserindo uma esfera grande do tipo Dielectric
        objects.append(Sphere(Vec3([0, 1, 0]), 1, Dielectric(1.5)))

        # Inserindo uma esfera grande do tipo Lambertian
        objects.append(Sphere(Vec3([-4, 1, 0]), 1, Lambertian(Vec3([0.4, 0.2, 0.1]))))

        # Inserindo uma esfera grande do tipo Metal
        objects.append(Sphere(Vec3([4, 1, 0]), 1, Metal(Vec3([0.7, 0.6, 0.5]), 0.0)))

        return objects