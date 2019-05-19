import glfw

import numpy as np
import OpenGL.GL.shaders as gl_shaders

from OpenGL.GL import *

width, height = 800, 600

def main():
    # Iniciando o glfw
    if not glfw.init():
        print('Não foi possível iniciar o glfw')
        return
    
    # Criando uma janela
    window = glfw.create_window(width, height, 'Teste Shader Quadrado', None, None)
    if not window:
        print('Não foi possível criar uma janela')
        glfw.terminate()
        return

    # Usar a janela criada para renderizar a cena
    glfw.make_context_current(window)
    

    # Indicando as coordenadas e cor dos vértices do nosso quadrado
    #                   position       color
    square = np.array([-0.5, -0.5, 0,     1, 1, 1,
                        0.5, -0.5, 0,     1, 0, 0,
                        0.5,  0.5, 0,     0, 1, 0,
                       -0.5,  0.5, 0,     0, 0, 1], dtype=np.float32)

    # Criando o vertex_shader
    vertex_shader = """
    #version 330
    in vec3 position;
    in vec3 color;

    out vec3 newColor;

    void main() {
        gl_Position = vec4(position, 1.0);
        newColor = color;
    }
    """

    # Criando o fragment_shader
    fragment_shader = """
    #version 330
    in vec3 newColor;

    out vec4 outColor;

    void main() {
        outColor = vec4(newColor, 1.0);
    }
    """

    # Compilando nossos shaders
    shader = gl_shaders.compileProgram(gl_shaders.compileShader(vertex_shader, GL_VERTEX_SHADER),
                                       gl_shaders.compileShader(fragment_shader, GL_FRAGMENT_SHADER))

    # Inicializando nosso glBuffer
    VBO = glGenBuffers(1)

    glBindBuffer(GL_ARRAY_BUFFER, VBO)
    glBufferData(GL_ARRAY_BUFFER, 4 * 24, square, GL_STATIC_DRAW)

    # Usando o shader que a gente criou
    glUseProgram(shader)

    # Pegando o atributo position no nosso shader
    position = glGetAttribLocation(shader, "position")

    # Passando os pontos para o shader usando nosso np.array triangle
    glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 4 * 6, ctypes.c_void_p(0))
    glEnableVertexAttribArray(position)

    # Pegando o atributo color no nosso shader
    color = glGetAttribLocation(shader, "color")

    # Passando as cores para o shader usando nosso np.array triangle
    glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 4 * 6, ctypes.c_void_p(4 * 3))
    glEnableVertexAttribArray(color)

    # Definindo a cor para limparmos a tela
    glClearColor(0.2, 0.3, 0.2, 1.0)

    # Enquanto não fecharmos a janela
    while not glfw.window_should_close(window):
        # Captura os eventos
        glfw.poll_events()

        # Limpamos o buffer de cor
        glClear(GL_COLOR_BUFFER_BIT)

        # Desenhando as posições do nosso quadrado
        glDrawArrays(GL_QUADS, 0, 4)

        # Realizando o swap dos buffers para exibir a cena
        glfw.swap_buffers(window)

    glfw.terminate()

# Executando a main
if __name__ == '__main__':
    main()