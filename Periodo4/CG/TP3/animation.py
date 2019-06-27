import numpy as np

class MD2Header:
    """ Classe para o Header de um arquivo MD2 """

    # Método construtor da classe
    def __init__(self, data):
        self.ident = data[0]       # magic number. must be equal to "IDP2"
        self.version = data[1]     # md2 version. must be equal to 8

        self.skinwidth = data[2]   # width of the texture
        self.skinheight = data[3]  # height of the texture
        self.framesize = data[4]   # size of one frame in bytes

        self.num_skins = data[5]   # number of textures
        self.num_xyz = data[6]     # number of vertices
        self.num_st = data[7]      # number of texture coordinates
        self.num_tris = data[8]    # number of triangles
        self.num_glcmds = data[9]  # number of opengl commands
        self.num_frames = data[10] # total number of frames

        self.ofs_skins = data[11]  # offset to skin names (64 bytes each)
        self.ofs_st = data[12]     # offset to s-t texture coordinates
        self.ofs_tris = data[13]   # offset to triangles
        self.ofs_frames = data[14] # offset to frame data
        self.ofs_glcmds = data[15] # offset to opengl commands
        self.ofs_end = data[16]    # offset to end of file

class MD2Model:
    """ Classe para um modelo MD2 """

    # Método construtor da classe
    def __init__(self):
        # Lista de vértices, normais para iluminação e comandos da OpenGL
        self.vertices = []
        self.normals = []
        self.gl_cmds = []

        # Escala do objeto (1.0 -> sem escala) e o id da textura
        self.scale = 1.0
        self.tex_id = 0

        # Iniciamos o modelo com a animação 0
        self.set_animation(0)

    # Método para carregar um modelo MD2
    def load_model(self, filename):
        # Abrindo o arquivo .md2 (arquivo binário)
        with open(filename, 'rb') as f:
            # Criando uma lista para conter os dados do header
            header_data = []

            # Lendo os 17 dados
            for _ in range(0, 17):
                # Leitura do dado (cada um com offset de 4)
                data = f.read(4)
                data = int.from_bytes(data, byteorder='little')
                header_data.append(data)

            # Passando a lista com os dados para a classe MD2Header
            header = MD2Header(header_data)

            # Verificando se o arquivo possui ident = IPD2 e versão = 8
            if header.ident != 844121161 and header.version != 8:
                f.close()
                return False

            # Lendo o frame data
            f.seek(header.ofs_frames, 0)
            self.buffer = f.read(header.num_frames * header.framesize)

            # Lendo os comandos da OpenGL (4 representa o sizeof(int))
            f.seek(header.ofs_glcmds, 0)
            self.gl_cmds = f.read(header.ofs_glcmds * 4)



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
    model = MD2Model()
    model.load_model('q2 md2 loader us/bin/models/Ogros.md2')

# Chamando a função principal
if __name__ == '__main__':
    main()
