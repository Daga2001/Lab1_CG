from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

def draw():
    glClear(GL_COLOR_BUFFER_BIT)
    glBegin(GL_LINES)
    glVertex2f(0.0, 0.0)
    glVertex2f(1.0, 1.0)
    glEnd()
    glutSwapBuffers()

def draw_Vector():
    glutInit()
    glutInitDisplayMode(GLUT_RGBA)
    glutInitWindowSize(640, 480)
    glutCreateWindow("2D Vector")
    glutDisplayFunc(draw)
    glutMainLoop()
