import numpy as np

from math import cos, sin
from math import radians as rad

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

width, height = 500, 500
vertices = np.array([[-1, -1, -1],
                     [ 1, -1, -1],
                     [ 1,  1, -1],
                     [-1,  1, -1],
                     [-1, -1,  1],
                     [ 1, -1,  1],
                     [ 1,  1,  1],
                     [-1,  1,  1]])

def paralelepipedo():
    glBegin(GL_LINES)
    for v in vertices:
        glVertex3fv(vertices[v])
    glEnd()

def draw():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()

    glColor3f(0.0, 0.0, 1.0)
    paralelepipedo()

    glutSwapBuffers()
    pass

def main():
    glutInit()

    glutInitWindowSize(width, height)
    glutInitWindowPosition(0, 0)
    glutCreateWindow('Testes TP2')
    
    glutDisplayFunc(draw)
    glutIdleFunc(draw)
    glutMainLoop()
    pass

if __name__ == '__main__':
    main()