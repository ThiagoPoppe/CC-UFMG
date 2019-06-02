import sys
import numpy as np

from numpy import array as Vec3
from numpy.random import uniform as rand

from functions.vector import normalize

from classes.ray import Ray
from classes.camera import Camera
from classes.hitable import HitableList

# Função que retorna a cor de um pixel
def raytrace(ray_in, world, depth):
    hit, _, point, normal, material = world.hit(ray_in, 0.001, sys.float_info.max)
    if hit:
        scattered, attenuation, ray_out = material.scatter(ray_in, point, normal)
        if depth < 50 and scattered:
            return attenuation * raytrace(ray_out, world, depth + 1)
        else:
            return Vec3([.0, .0, .0])

    else:
        unit_dir = normalize(ray_in.dir())
        t = 0.5 * (unit_dir[1] + 1)
        return (1 - t) * Vec3([1.0, 1.0, 1.0]) + t * Vec3([0.5, 0.7, 1.0])

# Definindo a main do programa
def main():
    # Obtendo o nome do arquivo via linha de comando
    filename = '../ppm_files/' + sys.argv[1]

    # Abrindo o arquivo em modo de escrita
    f = open(filename, 'w')

    # Definindo as dimensões da tela
    try:
        width, height = int(sys.argv[2]), int(sys.argv[3])
    except:
        width, height = 340, 480

    # Definindo o "fator" de antialiasing
    factor_antialiasing = 100

    # Inserindo o formato, dimensões e valor máximo para cor no arquivo
    print('P3', file=f)
    print('{} {}'.format(width, height), file=f)
    print('255', file=f)

    # Definindo nossa câmera
    cam_origin = Vec3([13.5, 1.5, 4.0])
    cam_look_at = Vec3([0.0, 0.5, -1])
    focus_dist = 10
    aperture = 0.16
    cam = Camera(cam_origin, cam_look_at, Vec3([0, 1, 0]), 20, width / height, aperture, focus_dist)

    # Definindo os objetos da nossa cena
    objects = HitableList.random_scene(200)
    world = HitableList(objects)

    # Loop para gerar a cor de cada pixel
    for j in range(height-1, -1, -1):
        for i in range(width):
            # Inicializando nosso vetor de cor
            col = Vec3([.0, .0, .0])

            # Loop para o processo de antialiasing (disparar vários raios para o mesmo pixel)
            for _ in range(factor_antialiasing):
                u = (i + rand()) / width
                v = (j + rand()) / height

                # Disparando um raio e acumulando a cor
                ray = cam.shoot_ray(u, v)
                col += raytrace(ray, world, 0)

            # Calculando a média da cor
            col /= factor_antialiasing

            # Aplicando o processo de gamma-2 correction
            col = np.sqrt(col)

            # Inserindo no arquivo a cor de cada pixel
            col *= 255.99
            print(*col, file=f)

    # Fechando o arquivo
    f.close()

# Chamando a nossa main
if __name__ == '__main__':
    import time
    start = time.time()
    main()
    print('----- {} seconds -----'.format(int(time.time() - start)))