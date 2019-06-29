import sys
import struct
import numpy as np

# Definindo o tamanho em bytes dos tipos de dados
sizeof = {
    'char': 1, 'short': 2, 'int': 4, 'float': 4,
    'md2_t': 68, 'vec3_t': 12, 'vertex_t': 4, 'texCoord_t': 4,
    'frame_t': 40, 'triangle_t': 12, 'anim_t': 12, 'animState_t': 36
}

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
        self.scale = 1.0
        self.texid = 0

        # Iniciamos o modelo com a animação 0
        self.set_animation(0)

    # Método para carregar um modelo MD2
    def load_model(self, filename):
        # Abrindo o arquivo .md2 (arquivo binário)
        with open(filename, 'rb') as f:            
            # Lendo o header do arquivo
            data = f.read(sizeof['md2_t'])
            fmt = '17i'
            header = struct.unpack(fmt, data)

            # Verificando se o arquivo possui ident = IPD2 e versão = 8
            if header[0] != 844121161 and header[1] != 8:
                print('Bad version or identifier')
                f.close()
                return False

            # Lendo as skins do modelo
            f.seek(header[11])
            data = f.read(header[5] * 64)
            fmt = header[5] * '64s'
            self.skins = struct.unpack(fmt, data)

            # Lendo as coordenadas da textura
            f.seek(header[12])
            data = f.read(header[7] * sizeof['texCoord_t'])
            fmt = header[7] * '2h'

            temp = struct.unpack(fmt, data)
            self.texcoords = [TexCoord(temp[i], temp[i+1]) for i in range(0, len(temp), 2)]

            # Lendo os triângulos do modelo
            f.seek(header[13])
            data = f.read(header[8] * sizeof['triangle_t'])
            fmt = header[8] * '6H'

            temp = struct.unpack(fmt, data)
            self.triangles = [Triangle(temp[i:i+3], temp[i+3:i+6]) for i in range(0, len(temp), 6)]

            # Lendo os comandos da OpenGL
            f.seek(header[15])
            data = f.read(header[9] * sizeof['int'])
            fmt = header[9] * 'i'
            self.glcmds = struct.unpack(fmt, data)

            # Criando uma lista para guardar os frames do modelo
            self.frames = []

            # Lendo os frames do modelo
            f.seek(header[14])
            for _ in range(header[10]):
                # Lendo os campos scale, translate e name do frame
                data = f.read(sizeof['frame_t'])
                fmt = '3f3f16s'
                temp = struct.unpack(fmt, data)
                
                # Salvando esses valores lidos
                scl = temp[0:3]
                translate = temp[3:6]
                name = temp[6:22][0]

                # Lendo os vértices do frame
                data = f.read(header[6] * sizeof['vertex_t'])
                fmt = header[6] * '3B1B'
                temp = struct.unpack(fmt, data)

                # Construindo uma lista de vértices
                vertices = [Vertex(temp[i:i+3], temp[i+3]) for i in range(0, len(temp), 4)]
                
                # Adicionando o novo frame à lista
                frame = Frame(scl, translate, name, vertices)
                self.frames.append(frame)
            
            return True
            
    # Método para carregar texturas
    def load_texture(self, filename):
        pass

    # Método para exibir o modelo
    def draw_model(self, time):
        pass

    # Método para desenhar o frame
    def draw_frame(self, frame):
        pass

    # Método para definirmos a animação
    def set_animation(self, type):
        pass

    # Método para escalar o modelo
    def scale_model(self, scl):
        pass

    # Método para animar o modelo
    def animate(self, time):
        pass

    # Método para aplicar efeitos de luz no modelo
    def process_light(self):
        pass

    # Método para interpolar os valores
    def interpolate(self, vertices):
        pass

    # Método para renderizar o frame
    def render_frame(self):
        pass

# Função principal
def main():
    # Criando nosso modelo
    model = MD2Model()

    # Carregando o modelo
    model.load_model(sys.argv[1])    

# Chamando a função principal
if __name__ == '__main__':
    main()
