import sys
import glfw
import struct
import numpy as np

import OpenGL.GL.shaders as gl_shaders

from OpenGL.GL import *
from OpenGL.GLU import *

width, height = 800, 600

# Definindo uma lista com as normais precalculadas
normals = [
    [ -0.525731,  0.000000,  0.850651], 
    [ -0.442863,  0.238856,  0.864188], 
    [ -0.295242,  0.000000,  0.955423], 
    [ -0.309017,  0.500000,  0.809017], 
    [ -0.162460,  0.262866,  0.951056], 
    [  0.000000,  0.000000,  1.000000], 
    [  0.000000,  0.850651,  0.525731], 
    [ -0.147621,  0.716567,  0.681718], 
    [  0.147621,  0.716567,  0.681718], 
    [  0.000000,  0.525731,  0.850651], 
    [  0.309017,  0.500000,  0.809017], 
    [  0.525731,  0.000000,  0.850651], 
    [  0.295242,  0.000000,  0.955423], 
    [  0.442863,  0.238856,  0.864188], 
    [  0.162460,  0.262866,  0.951056], 
    [ -0.681718,  0.147621,  0.716567], 
    [ -0.809017,  0.309017,  0.500000], 
    [ -0.587785,  0.425325,  0.688191], 
    [ -0.850651,  0.525731,  0.000000], 
    [ -0.864188,  0.442863,  0.238856], 
    [ -0.716567,  0.681718,  0.147621], 
    [ -0.688191,  0.587785,  0.425325], 
    [ -0.500000,  0.809017,  0.309017], 
    [ -0.238856,  0.864188,  0.442863], 
    [ -0.425325,  0.688191,  0.587785], 
    [ -0.716567,  0.681718, -0.147621], 
    [ -0.500000,  0.809017, -0.309017], 
    [ -0.525731,  0.850651,  0.000000], 
    [  0.000000,  0.850651, -0.525731], 
    [ -0.238856,  0.864188, -0.442863], 
    [  0.000000,  0.955423, -0.295242], 
    [ -0.262866,  0.951056, -0.162460], 
    [  0.000000,  1.000000,  0.000000], 
    [  0.000000,  0.955423,  0.295242], 
    [ -0.262866,  0.951056,  0.162460], 
    [  0.238856,  0.864188,  0.442863], 
    [  0.262866,  0.951056,  0.162460], 
    [  0.500000,  0.809017,  0.309017], 
    [  0.238856,  0.864188, -0.442863], 
    [  0.262866,  0.951056, -0.162460], 
    [  0.500000,  0.809017, -0.309017], 
    [  0.850651,  0.525731,  0.000000], 
    [  0.716567,  0.681718,  0.147621], 
    [  0.716567,  0.681718, -0.147621], 
    [  0.525731,  0.850651,  0.000000], 
    [  0.425325,  0.688191,  0.587785], 
    [  0.864188,  0.442863,  0.238856], 
    [  0.688191,  0.587785,  0.425325], 
    [  0.809017,  0.309017,  0.500000], 
    [  0.681718,  0.147621,  0.716567], 
    [  0.587785,  0.425325,  0.688191], 
    [  0.955423,  0.295242,  0.000000], 
    [  1.000000,  0.000000,  0.000000], 
    [  0.951056,  0.162460,  0.262866], 
    [  0.850651, -0.525731,  0.000000], 
    [  0.955423, -0.295242,  0.000000], 
    [  0.864188, -0.442863,  0.238856], 
    [  0.951056, -0.162460,  0.262866], 
    [  0.809017, -0.309017,  0.500000], 
    [  0.681718, -0.147621,  0.716567], 
    [  0.850651,  0.000000,  0.525731], 
    [  0.864188,  0.442863, -0.238856], 
    [  0.809017,  0.309017, -0.500000], 
    [  0.951056,  0.162460, -0.262866], 
    [  0.525731,  0.000000, -0.850651], 
    [  0.681718,  0.147621, -0.716567], 
    [  0.681718, -0.147621, -0.716567], 
    [  0.850651,  0.000000, -0.525731], 
    [  0.809017, -0.309017, -0.500000], 
    [  0.864188, -0.442863, -0.238856], 
    [  0.951056, -0.162460, -0.262866], 
    [  0.147621,  0.716567, -0.681718], 
    [  0.309017,  0.500000, -0.809017], 
    [  0.425325,  0.688191, -0.587785], 
    [  0.442863,  0.238856, -0.864188], 
    [  0.587785,  0.425325, -0.688191], 
    [  0.688191,  0.587785, -0.425325], 
    [ -0.147621,  0.716567, -0.681718], 
    [ -0.309017,  0.500000, -0.809017], 
    [  0.000000,  0.525731, -0.850651], 
    [ -0.525731,  0.000000, -0.850651], 
    [ -0.442863,  0.238856, -0.864188], 
    [ -0.295242,  0.000000, -0.955423], 
    [ -0.162460,  0.262866, -0.951056], 
    [  0.000000,  0.000000, -1.000000], 
    [  0.295242,  0.000000, -0.955423], 
    [  0.162460,  0.262866, -0.951056], 
    [ -0.442863, -0.238856, -0.864188], 
    [ -0.309017, -0.500000, -0.809017], 
    [ -0.162460, -0.262866, -0.951056], 
    [  0.000000, -0.850651, -0.525731], 
    [ -0.147621, -0.716567, -0.681718], 
    [  0.147621, -0.716567, -0.681718], 
    [  0.000000, -0.525731, -0.850651], 
    [  0.309017, -0.500000, -0.809017], 
    [  0.442863, -0.238856, -0.864188], 
    [  0.162460, -0.262866, -0.951056], 
    [  0.238856, -0.864188, -0.442863], 
    [  0.500000, -0.809017, -0.309017], 
    [  0.425325, -0.688191, -0.587785], 
    [  0.716567, -0.681718, -0.147621], 
    [  0.688191, -0.587785, -0.425325], 
    [  0.587785, -0.425325, -0.688191], 
    [  0.000000, -0.955423, -0.295242], 
    [  0.000000, -1.000000,  0.000000], 
    [  0.262866, -0.951056, -0.162460], 
    [  0.000000, -0.850651,  0.525731], 
    [  0.000000, -0.955423,  0.295242], 
    [  0.238856, -0.864188,  0.442863], 
    [  0.262866, -0.951056,  0.162460], 
    [  0.500000, -0.809017,  0.309017], 
    [  0.716567, -0.681718,  0.147621], 
    [  0.525731, -0.850651,  0.000000], 
    [ -0.238856, -0.864188, -0.442863], 
    [ -0.500000, -0.809017, -0.309017], 
    [ -0.262866, -0.951056, -0.162460], 
    [ -0.850651, -0.525731,  0.000000], 
    [ -0.716567, -0.681718, -0.147621], 
    [ -0.716567, -0.681718,  0.147621], 
    [ -0.525731, -0.850651,  0.000000], 
    [ -0.500000, -0.809017,  0.309017], 
    [ -0.238856, -0.864188,  0.442863], 
    [ -0.262866, -0.951056,  0.162460], 
    [ -0.864188, -0.442863,  0.238856], 
    [ -0.809017, -0.309017,  0.500000], 
    [ -0.688191, -0.587785,  0.425325], 
    [ -0.681718, -0.147621,  0.716567], 
    [ -0.442863, -0.238856,  0.864188], 
    [ -0.587785, -0.425325,  0.688191], 
    [ -0.309017, -0.500000,  0.809017], 
    [ -0.147621, -0.716567,  0.681718], 
    [ -0.425325, -0.688191,  0.587785], 
    [ -0.162460, -0.262866,  0.951056], 
    [  0.442863, -0.238856,  0.864188], 
    [  0.162460, -0.262866,  0.951056], 
    [  0.309017, -0.500000,  0.809017], 
    [  0.147621, -0.716567,  0.681718], 
    [  0.000000, -0.525731,  0.850651], 
    [  0.425325, -0.688191,  0.587785], 
    [  0.587785, -0.425325,  0.688191], 
    [  0.688191, -0.587785,  0.425325], 
    [ -0.955423,  0.295242,  0.000000], 
    [ -0.951056,  0.162460,  0.262866], 
    [ -1.000000,  0.000000,  0.000000], 
    [ -0.850651,  0.000000,  0.525731], 
    [ -0.955423, -0.295242,  0.000000], 
    [ -0.951056, -0.162460,  0.262866], 
    [ -0.864188,  0.442863, -0.238856], 
    [ -0.951056,  0.162460, -0.262866], 
    [ -0.809017,  0.309017, -0.500000], 
    [ -0.864188, -0.442863, -0.238856], 
    [ -0.951056, -0.162460, -0.262866], 
    [ -0.809017, -0.309017, -0.500000], 
    [ -0.681718,  0.147621, -0.716567], 
    [ -0.681718, -0.147621, -0.716567], 
    [ -0.850651,  0.000000, -0.525731], 
    [ -0.688191,  0.587785, -0.425325], 
    [ -0.587785,  0.425325, -0.688191], 
    [ -0.425325,  0.688191, -0.587785], 
    [ -0.425325, -0.688191, -0.587785], 
    [ -0.587785, -0.425325, -0.688191], 
    [ -0.688191, -0.587785, -0.425325]
]

# Definindo o tamanho em bytes dos tipos de dados
sizeof = {
    'char': 1, 'short': 2, 'int': 4, 'float': 4,
    'md2_t': 68, 'vec3_t': 12, 'vertex_t': 4, 'texCoord_t': 4,
    'frame_t': 40, 'triangle_t': 12, 'anim_t': 12, 'animState_t': 36
}

class MD2Header:
    """ Classe para o header do arquivo MD2"""

    # Método construtor da classe
    def __init__(self, header):
        self.ident = header[0].decode()  # String identificadora para o tipo IDP2
        self.version = header[1]  # Versão, deve ser 8

        self.skinWidth = header[2]  # Largura da textura
        self.skinHeight = header[3]  # Altura da textura 

        self.frameSize = header[4]  # Tamanho em bytes de cada frame

        self.numSkins = header[5]  # Quantidade de texturas
        self.numVertices = header[6]  # Quantidade de vértices de cada frame
        self.numSt = header[7]  # Quantidade de coordenadas de textura
        self.numTriangles = header[8]  # Quantidade de triângulos no modelo
        self.numGLCmds = header[9]  # Quantidade de comandos da OpenGL
        self.numFrames = header[10]  # Quantidade de frames

        # ----- OFFSETS ----- #
        self.offsetSkins = header[11]  # Offset para os dados das texturas
        self.offsetSt = header[12]  # Offset para os dados das coordenadas de textura
        self.offsetTriangles = header[13]  # Offset para os dados dos triângulos
        self.offsetFrames = header[14]  # Offset para os dados dos frames
        self.offsetGLCmds = header[15]  # Offset para os dados dos comandos da OpenGL

class TexCoord:
    """ Classe para as coordenadas de textura do modelo """
    
    # Método construtor da classe
    def __init__(self, s, t):
        self.s = s
        self.t = t

class Triangle:
    """ Classe para os triângulos do modelo """

    # Método construtor da classe
    def __init__(self, v, texCoord):
        self.v = v
        self.texCoord = texCoord

class Vertex:
    """ Classe para os vértices do frame """

    # Método construtor da classe
    def __init__(self, v, normalIndex):
        self.v = v
        self.normalIndex = normalIndex

class Frame:
    """ Classe para os frames do modelo """
    
    # Método construtor da classe
    def __init__(self, scl, translate, name, vertices):
        self.scl = scl
        self.translate = translate
        self.name = name
        self.vertices = vertices

class MD2Model:
    """ Classe para um modelo MD2 """

    # Método construtor da classe
    def __init__(self):
        # Escala do objeto (1.0 -> sem escala) e o id da textura
        self.scl = 1.0
        self.texId = 0

        # Iniciamos o modelo com a animação 0
        # self.set_animation(0)

    # Método para carregar um modelo MD2
    def loadModel(self, filename):
        # Abrindo o arquivo .md2 (arquivo binário)
        with open(filename, 'rb') as f:            
            # Lendo o header do arquivo
            data = f.read(sizeof['md2_t'])
            fmt = '4s16i'
            temp = struct.unpack(fmt, data)
            self.header = MD2Header(temp)

            # Verificando se o arquivo possui ident = IPD2 e versão = 8
            if self.header.ident == 'IPD2' and self.header.version != 8:
                print('Bad version or identifier')
                f.close()
                return False

            # Lendo as skins do modelo
            f.seek(self.header.offsetSkins)
            data = f.read(self.header.numSkins * 64)
            fmt = self.header.numSkins * '64s'
            self.skins = struct.unpack(fmt, data)

            # Lendo as coordenadas da textura
            f.seek(self.header.offsetSt)
            data = f.read(self.header.numSt * sizeof['texCoord_t'])
            fmt = self.header.numSt * '2h'

            temp = struct.unpack(fmt, data)
            self.texCoords = [TexCoord(temp[i], temp[i+1]) for i in range(0, len(temp), 2)]

            # Lendo os triângulos do modelo
            f.seek(self.header.offsetTriangles)
            data = f.read(self.header.numTriangles * sizeof['triangle_t'])
            fmt = self.header.numTriangles * '6H'

            temp = struct.unpack(fmt, data)
            self.triangles = [Triangle(temp[i:i+3], temp[i+3:i+6]) for i in range(0, len(temp), 6)]

            # Lendo os comandos da OpenGL
            f.seek(self.header.offsetGLCmds)
            data = f.read(self.header.numGLCmds * sizeof['int'])
            fmt = self.header.numGLCmds * 'i'
            self.glcmds = struct.unpack(fmt, data)

            # Criando uma lista para guardar os frames do modelo
            self.frames = []

            # Lendo os frames do modelo
            f.seek(self.header.offsetFrames)
            for _ in range(self.header.numFrames):
                # Lendo os campos scale, translate e name do frame
                data = f.read(sizeof['frame_t'])
                fmt = '3f3f16s'
                temp = struct.unpack(fmt, data)
                
                # Salvando esses valores lidos
                scl = temp[0:3]
                translate = temp[3:6]
                name = temp[6:22][0]

                # Lendo os vértices do frame
                data = f.read(self.header.numVertices * sizeof['vertex_t'])
                fmt = self.header.numVertices * '3B1B'
                temp = struct.unpack(fmt, data)

                # Construindo uma lista de vértices
                vertices = [Vertex(temp[i:i+3], temp[i+3]) for i in range(0, len(temp), 4)]
                
                # Adicionando o novo frame à lista
                frame = Frame(scl, translate, name, vertices)
                self.frames.append(frame)

            return True

    def renderFrame(self, n):
        # Verificando se o índice para o frame é válido
        if n < 0 or n > self.header.numFrames - 1:
            return

        # Obtendo o frame desejado
        frame = self.frames[n]
        
        glBindTexture(GL_TEXTURE_2D, self.texId)

        # Desenhando o modelo
        glBegin(GL_TRIANGLES)
        # Iterando sobre os triângulos
        for i in range(self.header.numTriangles):
            # Iterando sobre cada vértice
            for j in range(3):
                # Obtendo o i-esimo vértice daquele triângulo
                vertex = frame.vertices[self.triangles[i].v[j]]

                # Compute texture coordinates
                s = self.texCoords[self.triangles[i].texCoord[j]].s / self.header.skinWidth
                t = self.texCoords[self.triangles[i].texCoord[j]].t / self.header.skinHeight

                # /* Pass texture coordinates to OpenGL */
                glTexCoord2f(s, t)

                # Passando para a OpenGL a normal daquele vértice
                glNormal3fv(normals[vertex.normalIndex])

                # Calculando a posição real do vértice
                x = frame.scl[0] * vertex.v[0] + frame.translate[0]
                y = frame.scl[1] * vertex.v[1] + frame.translate[1]
                z = frame.scl[2] * vertex.v[2] + frame.translate[2]

                # Desenhando aquele vértice
                glVertex3f(x, y, z)
        glEnd()


# Criando o vertex_shader
vertex_shader_phong = """
#version 330 compatibility

// Iremos passar para o fragment shader as posições dos vértices e as suas normais
out vec4 position;
out vec3 normal;

void main() {
    // Computando a normal (aplicando a transposta da inversa)
    normal = normalize(gl_NormalMatrix * gl_Normal);
    
    // Computando as posições dos vértices (aplicando a matriz de ModelView)
    position = gl_ModelViewMatrix * gl_Vertex;
    
    // Aplicando a matriz de ModelView e Projection sobre o nosso vértice de entrada
    gl_Position = ftransform();
}
"""

# Criando o fragment_shader
fragment_shader_phong = """
#version 330 compatibility

// Recebemos do vertex shader os valores das posições dos vértices e as suas normais
in vec4 position;
in vec3 normal;

// Uniform para a posição da fonte luz
uniform vec3 lightPosition;

// Uniform para a cor do nosso objeto
uniform vec3 objColor;

// Váriaveis const float para guardar a contribuição especular e difusa
const float specularContrib = 0.4;
const float diffuseContrib = 1.0 - specularContrib;

// Cor de saída
out vec4 outColor;

void main() {
    // Vec3 para a posição do nosso vértice e normal
    vec3 p = vec3(gl_ModelViewMatrix * position);
    vec3 n = normalize(gl_NormalMatrix * normal);

    // Computando a direção da nossa luz
    vec3 lightDir = normalize(lightPosition - p);
    
    // Computando o R
    vec3 R = reflect(lightDir, n);
    
    // Computando o viewVec
    vec3 viewVec = normalize(-p);
    
    // Computando o componente difuso (produto escalar entre a direção da luz e a normal)
    float diffuse = max(0.0, dot(lightDir, n));
    
    // Computando o componente especular
    float spec = 0.0;
    if (diffuse > 0.0) {
        // Cosseno do ângulo entre R e viewVec (em outras palavras, produto escalar)
        spec = max(0.0, dot(R, viewVec));
        
        // Parte da fórmula do cosseno elevado a um "n"
        spec = pow(spec, 64.0);
    }

    // Calculando a intensidade da luz
    float intensity = (diffuse * diffuseContrib) + (spec * specularContrib);
    
    // Definindo uma luz de ambiente
    vec3 ambientLight = vec3(0.15, 0.1, 0.1);
    
    // Exibindo a cor
    outColor = vec4(ambientLight + objColor * intensity, 1.0);
}
"""

# Função principal
def main():
    # Criando nosso modelo
    model = MD2Model()

    # Carregando o modelo
    if not model.loadModel(sys.argv[1]):
        print('Não foi possível carregar o arquivo', sys.argv[1])
        exit(1)

    # Inicializando o glfw
    if not glfw.init():
        print('Não foi possível inicializar o glfw')
        exit(1)

    # Criando uma janela
    window = glfw.create_window(width, height, 'Testando código', None, None)
    if not window:
        print('Não foi possível criar a janela')
        glfw.terminate()
        exit(1)

    # Tornando a janela criada o contexto atual
    glfw.make_context_current(window)

    # Compilando e usando o shader
    shader = gl_shaders.compileProgram(gl_shaders.compileShader(vertex_shader_phong, GL_VERTEX_SHADER),
                                       gl_shaders.compileShader(fragment_shader_phong, GL_FRAGMENT_SHADER))
    glUseProgram(shader)

    # Definindo a cor de limpeza da tela
    glClearColor(0.2, 0.2, 0.2, 1.0)

    # Habilitando o DEPTH_TEST
    glEnable(GL_DEPTH_TEST)

    # Definindo a posição da nossa luz
    lightPositionLoc = glGetUniformLocation(shader, 'lightPosition')
    glUniform3f(lightPositionLoc, 100, -100, 0)

    # Definindo a cor do nosso objeto
    objColorLoc = glGetUniformLocation(shader, 'objColor')
    glUniform3f(objColorLoc, 1.0, 1.0, 1.0)

    # Definindo a cor de limpeza da tela
    glClearColor(0.2, 0.2, 0.2, 1.0)

    # Habilitando o DEPTH_TEST
    glEnable(GL_DEPTH_TEST)

    # Definindo o tipo de projeção
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(45.0, width/height, 0.1, 100.0)

    # Transladando a esfera para aparecer na tela

    glTranslatef(0.0, 0.0, -80.0)
    glRotatef(-65, 1, 0, 0)
    glRotatef(-100, 0, 0, 1)

    # MAIN LOOP
    while not glfw.window_should_close(window):
        # Capturando eventos
        glfw.poll_events()

        # Limpando os buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)

        model.renderFrame(0)

        # Desenhando na tela
        glfw.swap_buffers(window)

    # Terminando o glfw
    glfw.terminate()

# Chamando a função principal
if __name__ == '__main__':
    main()
