import glfw
import numpy as np
import OpenGL.GL.shaders as glShaders

from OpenGL.GL import *
from ctypes import sizeof, c_float, c_void_p

# Função que compila nosso shader
def compileShader(vShader, fShader):
    return glShaders.compileProgram(glShaders.compileShader(vShader, GL_VERTEX_SHADER),
                                    glShaders.compileShader(fShader, GL_FRAGMENT_SHADER))

# Definindo a main
def main():
    # Inicializando o glfw
    if not glfw.init():
        print('Não foi possível iniciar o glfw')
        return

    # Criando nossa janela
    window = glfw.create_window(640, 480, 'Teste Inicial', None, None)
    if not window:
        print('Não foi possível criar uma janela')
        glfw.terminate()
        return

    # Indicar que iremos renderizar a cena nessa janela
    glfw.make_context_current(window)

    # Especificando as posições e cor do nosso triângulo
    triangle = np.array([
        -0.5, -0.5,    0.3, 0.2, 0.4,
         0.5, -0.5,    0.8, 0.4, 0.6,
         0.5,  0.5,    0.3, 0.2, 0.4,
        -0.5,  0.5,    0.8, 0.4, 0.6

    ], dtype=np.float32)

    # Criando o vertex shader
    vertex_shader = """
    #version 330 core

    in  vec4 position;
    in  vec4 color;
    out vec4 newColor;

    void main() {
        gl_Position = position;
        newColor = color;
    }
    """

    # Criando o fragment shader
    fragment_shader = """
    #version 330 core

    in  vec4 newColor;
    out vec4 outColor;

    void main() {
        outColor = newColor;
    }
    """

    # Compilando nossos shaders e usando
    shader = glShaders.compileProgram(glShaders.compileShader(vertex_shader, GL_VERTEX_SHADER),
                                      glShaders.compileShader(fragment_shader, GL_FRAGMENT_SHADER))
    glUseProgram(shader)

    # Criar nosso VBO
    VBO = glGenBuffers(1)

    # Fazendo o bind do nosso buffer do triangle
    glBindBuffer(GL_ARRAY_BUFFER, VBO)

    # Iniciando o buffer escolhido com dados do triangle
    glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(c_float), triangle, GL_STATIC_DRAW)

    # Definindo e ativando os atributos do buffer de position
    position = glGetAttribLocation(shader, 'position')
    glVertexAttribPointer(position, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(c_float), c_void_p(0))
    glEnableVertexAttribArray(position)

    # Definindo e ativando os atributos do buffer de position
    color = glGetAttribLocation(shader, 'color')
    glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(c_float), c_void_p(8))
    glEnableVertexAttribArray(color)

    # Definindo a cor para limparmos a tela
    glClearColor(0.2, 0.3, 0.2, 1.0)
    
    # GAME LOOP
    while not glfw.window_should_close(window):
        # Capturando eventos
        glfw.poll_events()

        # Limpando a tela
        glClear(GL_COLOR_BUFFER_BIT)

        # Desenhando o que está no nosso Vertex Buffer
        glDrawArrays(GL_POLYGON, 0, 4)

        # Fazendo o swap dos buffers para desenhar
        glfw.swap_buffers(window)

# Executando nossa main
if __name__ == '__main__':
    main()