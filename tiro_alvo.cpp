/*
INSTRUÇÕES DE USO DO PROGRAMA
-> para INCLINAR o canhão, aperte a tecla 'c' para suspender, e 'b' para abaixar, caso tenha inclinado o canhão.
-> para ROTACIONAR o canhão para direita ou esquerda, aperte a tecla 'r' para esquerda e 'g' para direita.
-> para ATIRAR pressione a tecla 'p' e solte.
-> O disco começa a se movimentar automaticamente.
-> As teclas usadas para movimentar o observador na cena são 'a', 'z', 's' e 'x'.
*/



#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <iostream>

#include "objetos.h"

#define X 0
#define Y 1
#define Z 1
#define PI 3.141592654


using namespace std;

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
    glColor3f(0.139,0.69,0.19);
    terreno();
  glPopMatrix();

  // glPushMatrix();
  //   glColor3f(0.5f, 0.35f, 0.05f);
  //   cerca();
  // glPopMatrix();

  glPushMatrix();
    canhao();
  glPopMatrix();

  glFlush();
  glutSwapBuffers();

}

// Parêmetros da câmera
GLfloat pos[] = {0.0, 2.0, 0.0};  // altura inicial da camera = 2.0
//GLfloat dir[] = {0.0, 0.0, -1.0}; // direção de deslocamento (horizontal)
                                  // direção inicial coincide com -Z
GLfloat passo= 0.1;
GLfloat alfa = 0.0;  // angulo de inclinacao horizontal da direcao de observacao,
                     // com relacao a -z
GLfloat gama = 0.0;  // angulo de inclinacao vertical da direcao de observacao

void posicionaCamera()
{
   static float t = 180/PI;
   glLoadIdentity();
   glRotatef(-(gama*t), 1.0,0.0,0.0);
   glRotatef(-(alfa*t), 0.0, 1.0, 0.0);
   glTranslatef(-pos[X],-pos[Y],-pos[Z]);
}

void teclas (unsigned char k, int x, int y)
{
   static float pi2 = PI/2;
    switch (k) {
        case 'l': alfa += 0.02;      // camera gira para esquerda
                 break;
        case 'r': alfa -= 0.02;      // camera gira para direita
                 break;
        case 'u': gama += 0.02;      // camera inclina para cima
                 break;
        case 'd': gama -= 0.02;      // camera inclina para baixo
                 break;
        case 't': pos[Y] += passo*0.2;     // camera sobe
                 break;
        case 'b': pos[Y] -= passo*0.2;     // camera desce
    
   }
   posicionaCamera();
   glutPostRedisplay();
}

void myReshape(int w, int h)
{
    glClearColor(0.0, 0.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 0.1, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutCreateWindow("Tiro no disco");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(teclas);
    posicionaCamera();
    glutMainLoop();
}
