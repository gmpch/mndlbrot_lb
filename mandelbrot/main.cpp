#include "glut.h"
#include <math.h>

double x, y;

class Complex
{
private:
    double r, i;
public:
    Complex(double r, double i)
        { this->r = r; this->i = i; }
    Complex operator+(const Complex &c)
        { return Complex(r + c.r, i + c.i); }
    Complex operator*(const Complex &c)
        { return Complex(r * c.r - i * c.i, 2 * r * c.i); }
    double abs(){return r * r + i * i;}
};
 
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();    
    gluOrtho2D(0, w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glBegin(GL_POINTS);
  for (int y = 0; y < 800; y++)
      for (int x = 0; x < 1200; x++)
      {
          Complex z(0, 0);
          int i = 0;
          while (i < 500 && z.abs() < 16){
              z = z * z + Complex((x - 600) / 180.0, (y - 400) / 180.0);
              i++;              
          }
          double r = 0.1 + i * 0.03 * 0.2;
          double g = 0.2 + i * 0.03 * 0.3;
          double b = 0.3 + i * 0.03 * 0.1;
          glColor3d(r, g, b);
          glVertex2d(x, y); 
      }
  glEnd();

  glutSwapBuffers();
}
 
int main (int argc, char *argv[])
{
      glutInit(&argc, argv);
      glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
      glutInitWindowSize(1200, 800);

      glutCreateWindow("Mandelbrot");

      glutDisplayFunc(display);
      glutReshapeFunc(reshape);

      glutMainLoop();
}