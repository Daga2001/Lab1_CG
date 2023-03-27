from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

class Vector:
    def __init__(self, x, y, z) -> None:
        self.x = x
        self.y = y
        self.z = z
        pass

    def draw_Vector(self):
        def draw():
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
            glBegin(GL_LINES)
            glVertex3f(0.0, 0.0, 0.0)
            glVertex3f(self.x, self.y, self.z)
            glEnd()
            glutSwapBuffers()

        glutInit()
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH)
        glutInitWindowSize(640, 480)
        glutCreateWindow("3D Vector")
        glutDisplayFunc(draw)
        glutMainLoop()
