import glfw
import numpy
import OpenGL.GL.shaders as gl_shaders

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

width, height = 800, 600
angle = 0.0

def update(value):
    global angle
    angle += 0.5
    angle %= 360

    glutPostRedisplay()
    glutTimerFunc(10, update, 0)

def draw():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(45, width/height, -5, 5)
    glTranslate(0, 0, -15)

    # glBegin(GL_POLYGON)
    # glVertex2f(-1, -1)
    # glVertex2f( 1, -1)
    # glVertex2f( 1,  1)
    # glVertex2f(-1,  1)
    # glEnd()

    # Printa uma esfera vermelha
    # glColor3f(1, 0, 0)
    # glRotate(angle, 1, 0, 1)
    # quad = gluNewQuadric()
    # gluSphere(quad, 3, 100, 20)

    # Printa um cilindro verde
    # glColor3f(0, 1, 0)
    # glRotate(angle, 1, 0, 0)
    # quad = gluNewQuadric()
    # gluCylinder(quad, 3, 3, 3, 100, 20)

    # Printa uma Utah Teapot azul
    # glColor3f(0, 0, 1)
    # glRotate(angle, 0, 1, 1)
    # glutSolidTeapot(2)

    glutSwapBuffers()

def main():
    # glutInit()

    # glutInitWindowPosition(0, 0)
    # glutInitWindowSize(width, height)
    # glutCreateWindow('TP1')

    # glutTimerFunc(10, update, 0)

    # glutDisplayFunc(draw)
    # glutIdleFunc(draw)
    # glutMainLoop()

    # initialize glfw
    if not glfw.init():
        print('Não foi possível iniciar glfw')
        return

    window = glfw.create_window(width, height, 'Testando TP1', None, None)

    if not window:
        print('Não foi possível criar a janela')
        glfw.terminate()
        return

    glfw.make_context_current(window)
    #               positions          colors
    triangle = [-0.5, -0.5, 0.0,    1.0, 0.0, 0.0,
                 0.5, -0.5, 0.0,    0.0, 1.0, 0.0,
                 0.0,  0.5, 0.0,    0.0, 0.0, 1.0]

    triangle = numpy.array(triangle, dtype = numpy.float32)

    vertex_shader = """
    #version 330
    in vec3 position;
    in vec3 color;
    uniform float scale;
    out vec3 newColor;
    void main()
    {
        gl_Position = vec4(position*scale, 1.0f);
        newColor = color;
    }
    """

    fragment_shader = """
    #version 330
    in vec3 newColor;
    out vec4 outColor;
    void main()
    {
        if(newColor[0] > 0.3 && newColor[0] < 0.5 )
            discard;
        if (newColor[1] > 0.3 && newColor[1] < 0.5)
            discard;
        if (newColor[2] > 0.3 && newColor[2] < 0.5)
            discard;
        outColor = vec4(newColor,1.0);
    }
    """
    shader = OpenGL.GL.shaders.compileProgram(OpenGL.GL.shaders.compileShader(vertex_shader, GL_VERTEX_SHADER),
                                              OpenGL.GL.shaders.compileShader(fragment_shader, GL_FRAGMENT_SHADER))

    VBO = glGenBuffers(1)
    glBindBuffer(GL_ARRAY_BUFFER, VBO)
    glBufferData(GL_ARRAY_BUFFER, 72, triangle, GL_STATIC_DRAW)

    glUseProgram(shader)

    position = glGetAttribLocation(shader, "position")
    glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 24, ctypes.c_void_p(0))
    glEnableVertexAttribArray(position)

    color = glGetAttribLocation(shader, "color")
    #print(color)
    glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 24, ctypes.c_void_p(12))
    glEnableVertexAttribArray(color)

    scale = glGetUniformLocation(shader,"scale")
    glUniform1f(scale, 1.3)
   

    glClearColor(0.2, 0.3, 0.2, 1.0)

    while not glfw.window_should_close(window):
        glfw.poll_events()

        glClear(GL_COLOR_BUFFER_BIT)

        glDrawArrays(GL_TRIANGLES, 0, 3)

        glfw.swap_buffers(window)

    glfw.terminate()

# Executando a main
if __name__ == '__main__':
    main()