from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

class Vector:
    def __init__(self, x) -> None:
        self.x = x
        pass
   
    def draw_Vector(self):
        def draw():
            glClear(GL_COLOR_BUFFER_BIT)
            glBegin(GL_LINES)
            glVertex2f(-1.0, 0.0)
            glVertex2f(self.x, 0.0)
            glEnd()
            glutSwapBuffers()

        glutInit()
        glutInitDisplayMode(GLUT_RGBA)
        glutInitWindowSize(640, 480)
        glutCreateWindow("1D Vector")
        glutDisplayFunc(draw)
        glutMainLoop()
