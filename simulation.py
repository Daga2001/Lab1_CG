import math
from OpenGL.GL import *
from OpenGL.GLUT import *   
from OpenGL.GLU import *
import wx

# Se obtiene la resolución de la pantalla
app = wx.App(False)
width, height = wx.GetDisplaySize()

# Definir constantes
SCREEN_WIDTH = 640
SCREEN_HEIGHT = 480
GRAVITY = 9.81

# Definir variables de estado del proyectil
x_pos = -7.0
y_pos = -3.0
z_pos = 0.0
x_vel = 5.0
y_vel = 5.0
z_vel = 0.0
t = 0.0

# Función de dibujado
def draw():
    global x_pos, y_pos, z_pos, x_vel, y_vel, z_vel, t
    
    # Limpiar pantalla
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    
    # Definir posición del proyectil
    x_pos = x_vel * t
    y_pos = y_vel * t - 0.5 * GRAVITY * t ** 2
    z_pos = z_vel * t
    
    print("pos:", x_pos, y_pos, z_pos)
    
    # Dibujar proyectil
    glColor3f(1.0, 1.0, 1.0)
    glPointSize(10.0)
    glBegin(GL_POINTS)
    glVertex3f(x_pos, y_pos, z_pos)
    glEnd()
    
    # Dibuja el plano cartesiano
    glBegin(GL_LINES)
    glVertex2f(-10.0, 0.0)
    glVertex2f(10.0, 0.0)
    glVertex2f(0.0, -10.0)
    glVertex2f(0.0, 10.0)
    glEnd()

    # Actualizar tiempo
    t += 5 * 10 ** -4
    
    # Si el proyectil ha tocado el suelo, detener la simulación
    if y_pos < 0.0:
        t = 0.0
    
    # Intercambiar buffers y actualizar pantalla
    glutSwapBuffers()
    glutPostRedisplay()

# ----------------------------------------------------------------------------
# Función de inicialización
# ----------------------------------------------------------------------------
def init():
    # Establecer tamaño de la ventana y posición inicial del proyectil
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT)
    glutInitWindowPosition(100, 100)
    glutCreateWindow("Simulacion del movimiento de un proyectil")
    glClearColor(0.0, 0.0, 0.0, 0.0)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    gluPerspective(45.0, float(SCREEN_WIDTH) / float(SCREEN_HEIGHT), 0.1, 100.0)
    glMatrixMode(GL_MODELVIEW)
    glLoadIdentity()
    glTranslatef(0.0, 0.0, -10.0)
    glEnable(GL_DEPTH_TEST)

# ----------------------------------------------------------------------------
# Inicializar OpenGL y empezar simulación
# ----------------------------------------------------------------------------
def main():
    glutInit()
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH)
    init()
    glutDisplayFunc(draw)
    glutMainLoop()
