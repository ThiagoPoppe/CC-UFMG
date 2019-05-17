import sys
from OpenGL.GLUT import *
from OpenGL.GL import *
from OpenGL.GLU import *

from math import pi

def display():
   # clear all pixels 
   glClear (GL_COLOR_BUFFER_BIT)
   # draw white polygon (rectangle) with corners at
   # (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)  
   glColor3d(255, 255, 255)
   glBegin(GL_POLYGON)
   glVertex3f(-1, -1, 0.0)
   glVertex3f(1, -1, 0.0)
   glVertex3f(1, 1, 0.0)
   glVertex3f(-1, 1, 0.0)
   glEnd()
   # don't wait!  
   # start processing buffered OpenGL routines 
   glFlush()

def init():
   # select clearing color         
   glClearColor (0.0, 0.0, 0.0, 0.0)
   # initialize viewing values  
   glMatrixMode(GL_PROJECTION)
   #glLoadIdentity()
   glOrtho(-5.0, 5.0, -5.0, 5.0, -1.0, 1.0)

def main():
   glutInit(sys.argv)
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
   glutInitWindowSize(500, 500)
   glutInitWindowPosition(100, 100)
   glutCreateWindow("Teste Inicial")
   init()
   glutDisplayFunc(display)
   while True:
      glRotate(pi, 1, 0, 0)

if __name__ == '__main__':
   main()