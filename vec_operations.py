import math

class Operations:
    def __init__(self) -> None:
        pass

    # Definición de funciones para las operaciones vectoriales
    def suma_vectores(self, v1, v2):
        """
        Suma dos vectores de igual dimensión.
        """
        if len(v1) != len(v2):
            raise ValueError("Los vectores deben ser del mismo tamaño.")
        return [v1[i] + v2[i] for i in range(len(v1))]

    def resta_vectores(self, v1, v2):
        """
        Resta dos vectores de igual dimensión.
        """
        if len(v1) != len(v2):
            raise ValueError("Los vectores deben ser del mismo tamaño.")
        return [v1[i] - v2[i] for i in range(len(v1))]

    def producto_escalar(self, v, s):
        """
        Multiplica un vector por un escalar.
        """
        return [v[i] * s for i in range(len(v))]

    def division_escalar(self, v, s):
        """
        Divide un vector por un escalar.
        """
        if s == 0:
            raise ValueError("No se puede dividir por cero.")
        return [v[i] / s for i in range(len(v))]

    def producto_punto(self, v1, v2):
        """
        Calcula el producto punto de dos vectores de igual dimensión.
        """
        if len(v1) != len(v2):
            raise ValueError("Los vectores deben ser del mismo tamaño.")
        return sum([v1[i] * v2[i] for i in range(len(v1))])

    def producto_cruz(self, v1, v2):
        """
        Calcula el producto cruz de dos vectores de dimensión 3.
        """
        if len(v1) != 3 or len(v2) != 3:
            raise ValueError("Los vectores deben ser de dimensión 3.")
        return [
            v1[1] * v2[2] - v1[2] * v2[1],
            v1[2] * v2[0] - v1[0] * v2[2],
            v1[0] * v2[1] - v1[1] * v2[0]
        ]

    def angulo_entre_vectores(self, v1, v2):
        """
        Calcula el ángulo en radianes entre dos vectores.
        """
        if len(v1) != len(v2):
            raise ValueError("Los vectores deben ser del mismo tamaño.")
        magnitud_v1 = math.sqrt(sum([v1[i]**2 for i in range(len(v1))]))
        magnitud_v2 = math.sqrt(sum([v2[i]**2 for i in range(len(v2))]))
        producto_punto = sum([v1[i] * v2[i] for i in range(len(v1))])
        return math.acos(producto_punto / (magnitud_v1 * magnitud_v2))

    def normalizar(self, vector):
        """
        Normaliza el vector pasado como argumento
        """
        magnitud = math.sqrt(sum(i**2 for i in vector))
        return [i/magnitud for i in vector]

# # Ejemplo de uso
# v1 = [1, 2, 3]
# v2 = [4, 5, 6]

# # Suma de vectores
# resultado = suma_vectores(v1, v2)
# print(f"La suma de los vectores {v1} y {v2} es {resultado}")

# # Resta de vectores
# resultado = resta_vectores(v1, v2)
# print(f"La resta de los vectores {v1} y {v2} es {resultado}")

