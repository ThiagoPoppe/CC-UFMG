import sys
import numpy as np

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

from math import cos, sin
from math import radians as rad

# Definindo as dimensões da nossa janela
width, height = 1000, 720

# Definindo os eixos de rotação
r_axis = [False, False, False]

# Definindo nosso ângulo
angle = 0

# Definindo os vértices e arestas do nosso quadrado
vertices = np.array([
    [-1, -1, -1, 1],
    [ 1, -1, -1, 1],
    [ 1,  1, -1, 1],
    [-1,  1, -1, 1],
    [-1, -1,  1, 1],
    [ 1, -1,  1, 1],
    [ 1,  1,  1, 1],
    [-1,  1,  1, 1]
])

edges = [
    [0, 1],
    [1, 2],
    [2, 3],
    [3, 0],
    [4, 5],
    [5, 6],
    [6, 7],
    [7, 4],
    [0, 4],
    [1, 5],
    [2, 6],
    [3, 7]
]

# Função de callback para o glutTimerFunc
def update(value):
    global angle

    if np.any(r_axis):
        angle += 0.5
        angle %= 360

    glutPostRedisplay()
    glutTimerFunc(10, update, 0)

# Função sobre a projeção utilizada
def init3D():
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    # glOrtho(-5, 5, -5, 5, -5, 5)
    gluPerspective(45, width/height, 0.1, 50)

# Função que desenha pontos na tela
def drawPoints(size, dim, arr, start, end):
    glEnable(GL_POINT_SMOOTH)
    glEnableClientState(GL_VERTEX_ARRAY)
    glPointSize(size)
    glVertexPointer(dim, GL_FLOAT, 0, arr)
    glDrawArrays(GL_POINTS, start, end)
    glDisableClientState(GL_VERTEX_ARRAY)
    glDisable(GL_POINT_SMOOTH)

# Função para rotacionar dado um angulo
def rotate(vertices, angle, x, y, z):
    result = vertices

    rotateX = np.array([
        [1, 0, 0, 0],
        [0, cos(rad(angle)), -sin(rad(angle)), 0],
        [0, sin(rad(angle)),  cos(rad(angle)), 0],
        [0, 0, 0, 1]
    ])

    rotateY = np.array([
        [cos(rad(angle)), 0, -sin(rad(angle)), 0],
        [0, 1, 0, 0],
        [sin(rad(angle)), 0,  cos(rad(angle)), 0],
        [0, 0, 0, 1]
    ])

    rotateZ = np.array([
        [cos(rad(angle)), -sin(rad(angle)), 0, 0],
        [sin(rad(angle)),  cos(rad(angle)), 0, 0],
        [0, 0, 1, 0],
        [0, 0, 0, 1]
    ])

    if x == 1:
        result = rotateX @ result
    if y == 1:
        result = rotateY @ result
    if z == 1:
        result = rotateZ @ result

    return result

# Função que escala dado um valor
def scale(vertices, sx, sy, sz):
    s = np.array([
        [sx,  0,  0, 0],
        [ 0, sy,  0, 0],
        [ 0,  0, sz, 0],
        [ 0,  0,  0, 1]
    ])

    return s @ vertices

# Função que translada dado um valor
def translate(vertices, tx, ty, tz):
    t = np.array([
        [1, 0, 0, tx],
        [0, 1, 0, ty],
        [0, 0, 1, tz],
        [0, 0, 0,  1]
    ])

    return t @ vertices

# Função que desenha nosso cubo
def cube():
    init3D()

    result = rotate(vertices.T, angle, r_axis[0], r_axis[1], r_axis[2])
    result = scale(result, 2, 1, 3)
    result = translate(result, 0, 0, -10)

    result = result.T
    glBegin(GL_LINES)
    for e in edges:
        for v in e:
            glVertex3fv(result[v][:3])
    glEnd()

    drawPoints(5, len(result[0]), result, 0, 8)

# Função que lê entradas do teclado
def keyboardFunc(key, x, y):
    global r_axis
    if key == b'x':
        r_axis[0] = True
    if key == b'y':
        r_axis[1] = True
    if key == b'z':
        r_axis[2] = True

def draw():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()

    glutKeyboardFunc(keyboardFunc)

    glColor3f(1.0, 1.0, 1.0)
    cube()

    glutSwapBuffers()

def main():
    glutInit(sys.argv)

    glutInitWindowSize(width, height)
    glutInitWindowPosition(0, 0)
    glutCreateWindow('TP2')

    glutTimerFunc(10, update, 0)

    glutDisplayFunc(draw)
    glutIdleFunc(draw)
    glutMainLoop()

if __name__ == '__main__':
    main()