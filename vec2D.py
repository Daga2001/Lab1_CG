from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

class Vector:
    def __init__(self, x, y) -> None:
        self.x = x
        self.y = y
        pass

    def draw_Vector(self):
        def draw():
            glClear(GL_COLOR_BUFFER_BIT)
            glBegin(GL_LINES)
            glVertex2f(0, 0)
            glVertex2f(self.x, self.y)
            glEnd()
            glutSwapBuffers()

        glutInit()
        glutInitDisplayMode(GLUT_RGBA)
        glutInitWindowSize(640, 480)
        glutCreateWindow("2D Vector")
        glutDisplayFunc(draw)
        glutMainLoop()
