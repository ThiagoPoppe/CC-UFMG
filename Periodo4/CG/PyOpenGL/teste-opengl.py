from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

import numpy as np
from math import cos, sin
from math import radians as rad

width, height = 800, 600

angle = 0.0

vertices = np.array([
    [-1, -1, -1, 1],
    [ 1, -1, -1, 1],
    [ 1,  1, -1, 1],
    [-1,  1, -1, 1],
    [-1, -1,  1, 1],
    [ 1, -1,  1, 1],
    [ 1,  1,  1, 1],
    [-1,  1,  1, 1],
])

edges = [
    [0, 1], [1, 2], [2, 3], [3, 0],
    [4, 5], [5, 6], [6, 7], [7, 4],
    [0, 4], [1, 5], [2, 6], [3, 7]
]

def rotate(angle, x=0, y=0, z=1):
    result = np.identity(4)
    angle = rad(angle)
    
    rotateX = np.array([
        [1, 0, 0, 0],
        [0, cos(angle), -sin(angle), 0],
        [0, sin(angle), cos(angle), 0],
        [0, 0, 0, 1]
    ])

    rotateY = np.array([
        [cos(angle), 0, -sin(angle), 0],
        [0, 1, 0, 0],
        [sin(angle), 0, cos(angle), 0],
        [0, 0, 0, 1]
    ])

    rotateZ = np.array([
        [cos(angle), -sin(angle), 0, 0],
        [sin(angle), cos(angle), 0, 0],
        [0, 0, 1, 0],
        [0, 0, 0, 1]
    ])

    if x != 0:
        result = rotateX @ result
    if y != 0:
        result = rotateY @ result
    if z != 0:
        result = rotateZ @ result

    return result

def scale(sx, sy, sz):
    return np.array([
        [sx, 0, 0, 0],
        [0, sy, 0, 0],
        [0, 0, sz, 0],
        [0, 0, 0, 1]
    ])

def translate(tx, ty, tz):
    return np.array([
        [1, 0, 0, tx],
        [0, 1, 0, ty],
        [0, 0, 1, tz],t
        [0, 0, 0, 1]
    ])

def simpleOrtho(v):
    Po = np.array([
        [1, 0, 0, 0],
        [0, 1, 0, 0],
        [0, 0, 0, 0],
        [0, 0, 0, 1]
    ])

    v = Po @ v

def transform(v, M, tx, ty, tz, px, py, pz):
    T = np.array([
        [M[0, 0], M[0, 1], M[0, 2], tx],
        [M[1, 0], M[1, 1], M[1, 2], ty],
        [M[2, 0], M[2, 1], M[2, 2], tz],
        [px, py, pz, 1],
    ])

    return T @ v

def update(value):
    global angle
    angle += 0.5
    angle %= 360

    glutPostRedisplay()
    glutTimerFunc(10, update, 0)

def cube():
    M = scale(0.3, 0.3, 0.3) @ rotate(angle, 1, 1, 1)
    result = transform(vertices.T, M, 0, 0, 0, 0, 0, 0)

    simpleOrtho(result)
    glBegin(GL_LINES)
    for e in edges:
        for v in e:
            glVertex2fv(result.T[v][:2])
    glEnd()

def draw():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

    glColor3f(1, 1, 1)
    cube()

    glutSwapBuffers()

def main():
    glutInit()

    glutInitWindowPosition(0, 0)
    glutInitWindowSize(width, height)
    glutCreateWindow('Testando OpenGL')

    glutTimerFunc(10, update, 0)

    glutDisplayFunc(draw)
    glutIdleFunc(draw)
    glutMainLoop()

if __name__ == '__main__':
    main()