def createMatrix(m, n):
    return [[0 for _ in range(n)] for _ in range(m)]

def transpose(A):
    m, n = len(A), len(A[0])
    At = createMatrix(n, m)
    for i in range(n):
        for j in range(m):
            At[i][j] = A[j][i]
    return At

def matmul(A, B):
    mA, nA = len(A), len(A[0])
    mB, nB = len(B), len(B[0])

    if nA != mB:
        print('Número de colunas de A deve ser o mesmo que número de linhas em B')
        return None

    result = createMatrix(mA, nB)
    for i in range(mA):
        for j in range(nB):
            for k in range(nA):
                result[i][j] += A[i][k] * B[k][j]
    
    return result

def printMatrix(A):
    for i in range(len(A)):
        for j in range(len(A[0])):
            print(A[i][j], end=' ')
        print()
    print()

A = [
    [1, 2],
    [3, 4]
]

B = [
    [1, 2],
    [3, 4]
]

printMatrix(matmul(A, B))