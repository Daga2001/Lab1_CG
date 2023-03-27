# ----------------------------------------------------------------------------
# Se importan las librerias necesarias
# ----------------------------------------------------------------------------
import glfw
import vec_operations as vec
import vec1D
import vec2D
import vec3D
import simulation as sim
from OpenGL.GL import *
import numpy as np

# ----------------------------------------------------------------------------
# Ejemplos de uso de operaciones entre vectores
# ----------------------------------------------------------------------------
v1 = [1, 2, 3]
v2 = [4, 5, 6]

# Suma de vectores
resultado = vec.suma_vectores(v1, v2)
print(f"La suma de los vectores {v1} y {v2} es {resultado}")

# Resta de vectores
resultado = vec.resta_vectores(v1, v2)
print(f"La resta de los vectores {v1} y {v2} es {resultado}")

# Normalizacion
resultado = vec.normalizar(v1)
print(f"El vector {v1} normalizado es: {resultado}")

# ----------------------------------------------------------------------------
# Dibujando vectores en 1, 2 y 3 dimensiones
# ----------------------------------------------------------------------------
# vec1D.draw_Vector()
# vec2D.draw_Vector()
# vec3D.draw_Vector()

# ----------------------------------------------------------------------------
# Simulación de proyectil
# ----------------------------------------------------------------------------
sim.main()