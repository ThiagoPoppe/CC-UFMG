from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *

# Definindo o nosso ângulo de rotação
sentido = 1
angle = 0

# Definindo o tamanho da nossa janela
width, height = 500, 500
mx, my = 0, 0
ax, ay = 250, 250
start = 0

# # Definindo os pontos do nosso pentágono
vertices = [[-20, -20], # x + 0 , y + 0
            [20, -20], # x + 40, y + 0
            [30, 10], # x + 50, y + 30
            [0, 30], # x + 20, y + 50
            [-30, 10]] # x - 10, y + 30

# Função callback para a nossa glutTimerFunc
def update(value):
    global angle

    if start == 1:
        angle += 1 * sentido
        angle %= 360

    glutPostRedisplay()
    glutTimerFunc(10, update, 0)

# Função de inicializar o nosso desenho em 2D (ajuste da projeção)
def init2D():
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(0, width, 0, height, 0, 1)

# Função que rotaciona o nosso pentágono dado um eixo de rotação
def myRotate(x, y):
    glTranslate(x, y, 0)
    glRotate(angle, 0, 0, 1)
    glTranslate(-x, -y, 0)

# Função callback que manipula os eventos do nosso mouse
def mouseFunc(button, state, x, y):
    global start, sentido, mx, my
    correct_y = abs(y - height)

    # Caso o botão esquerdo do mouse for solto
    if button == GLUT_LEFT_BUTTON:
        sentido = -1
    
    elif button == GLUT_RIGHT_BUTTON:
        sentido = 1

    if state == GLUT_UP:
        start = 1
        mx, my = x, correct_y

# Função callback que manipula os eventos do teclado
def keyboardFunc(key, x, y):
    global start
    if key == b' ':
        start = 0
        
# Função que desenha um pentágono
def drawPentagon():
    init2D()

    myRotate(mx, my)
    glTranslate(ax, ay, 0)
    
    glBegin(GL_POLYGON)
    for v in vertices:
        glVertex2fv(v)
    glEnd()

# Loop principal para realizar o desenho
def draw():
    glClear(GL_COLOR_BUFFER_BIT)
    glLoadIdentity()

    glutMouseFunc(mouseFunc)
    glutKeyboardFunc(keyboardFunc)

    glColor3f(1.0, 1.0, 1.0)
    drawPentagon()

    glutSwapBuffers()

# Função principal
def main():
    glutInit()
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)

    glutInitWindowSize(width, height)
    glutInitWindowPosition(0, 0)
    glutCreateWindow('TP1')

    glutTimerFunc(10, update, 0)
    glutDisplayFunc(draw)
    glutIdleFunc(draw)
    glutMainLoop()

# Chamando nossa funçao principal
if __name__ == '__main__':
    main()