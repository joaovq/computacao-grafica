GLfloat paredes[]={0.4, 0.4, 0.0, 1.0};
GLfloat piso[]={0.2, 0.5, 0.5, 1.0};

GLfloat vertices[][3] =
    {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
     {1.0,1.0,-1.0},  {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
     {1.0,-1.0,1.0},  {1.0,1.0,1.0},   {-1.0,1.0,1.0}
};

float angIncl = 0;
float angRot = 0;
float Xbala = 0.0,Ybala = 0.01,Zbala = -0.5;
double dPI = 4.0*atan(1.0);

//função genérica para desenhar polignos
void polygon(int a, int b, int c , int d){
  glBegin(GL_POLYGON);
    glVertex3fv(vertices[a]);
    glVertex3fv(vertices[b]);
    glVertex3fv(vertices[c]);
    glVertex3fv(vertices[d]);
  glEnd();
}

//função genérica para desenhar cubos
void cubo(){
  glScalef(0.5,0.5,0.5);
  glNormal3f(0.0,0.0,-1.0);
  polygon(0,3,2,1);

  glNormal3f(0.0,1.0,0.0);
  polygon(2,3,7,6);

  glNormal3f(-1.0,0.0,0.0);
  polygon(0,4,7,3);

  glNormal3f(1.0,0.0,0.0);
  polygon(1,2,6,5);

  glNormal3f(0.0,0.0,1.0);
  polygon(4,5,6,7);

  glNormal3f(0.0,-1.0,0.0);
  polygon(0,1,5,4);
}

void esfera()
{
  GLUquadricObj *quadric;
  quadric = gluNewQuadric();

  gluQuadricDrawStyle(quadric, GLU_FILL );
  gluSphere( quadric , 0.5 , 36 , 18 );

  gluDeleteQuadric(quadric);
}

void cilindro()
{
  GLfloat raio = 1.0;
  GLfloat alt = 1.0;
  static GLUquadric* quad;
  quad = gluNewQuadric();
  gluCylinder(quad, raio, raio, alt, 20, 10);
}

void modeloRoda()
{
    glPushMatrix();
      glTranslatef(0.0,0.1,0.0);
      glPushMatrix();
          glTranslatef(0.0,0.0,0.15);
          glColor3f(1.0,1.0,1.0);
          glPushMatrix();
              glTranslatef(0.0,1.0,0.0);
              glRotatef(-45.0,0.0,0.0,1.0);
              glScalef(0.08,1.0,0.1);
            cubo();
          glPopMatrix();

          glPushMatrix();
            glTranslatef(0.0,1.0,0.0);
            glRotatef(45.0,0.0,0.0,1.0);
            glScalef(0.08,1.0,0.1);
            cubo();
          glPopMatrix();

          glPushMatrix();
            glTranslatef(0.0,1.0,0.0);
            glRotatef(90.0,0.0,0.0,1.0);
            glScalef(0.08,1.0,0.1);
            cubo();
          glPopMatrix();

          glPushMatrix();
            glTranslatef(0.0,1.0,0.0);
            glScalef(0.08,1.,0.1);
            cubo();
          glPopMatrix();
      glPopMatrix();

      glPushMatrix();
          glColor3f(0.1,0.1,0.1);
          glTranslatef(0.0,1.0,0.0);
          glScalef(1.02,1.02,0.3);
          cilindro();
      glPopMatrix();

    glPopMatrix();
}

void rodaDoCanhao()
{
    glPushMatrix();
      glPushMatrix();
          glTranslatef(1.0,0.0,0.0);
          glTranslatef(0.0,1.0,0.0);
          glTranslatef(0.0,-1.0,0.0);
          glRotatef(90,0.0,1.0,0.0);
          modeloRoda();
      glPopMatrix();

      glPushMatrix();
          glTranslatef(-1.0,0.0,0.0);
          glTranslatef(0.0,1.0,0.0);
          glTranslatef(0.0,-1.0,0.0);
          glRotatef(90,0.0,1.0,0.0);
          modeloRoda();
      glPopMatrix();
    glPopMatrix();
}

void canhao(){
  glPushMatrix();
    rodaDoCanhao();
  glPopMatrix();
}

GLfloat teta = 0.0f, angulo = 0.0f; 

//desenha cerca ao redor do terreno
void cerca()
{
    //estaca 1
    glPushMatrix();
        glTranslatef(-4.9,0.3,-9.7);
        glScalef(0.2,1.5,0.1);
        cubo();
    glPopMatrix();

    //cerca de cima da frente
    glPushMatrix();
        glTranslatef(0.0,1.2,-8);
        glScalef(8.5,0.2,0.1);
        cubo();
    glPopMatrix();

    //certa de baixo da frente
    glPushMatrix();
        glTranslatef(0.0,0.6,-8);
        glScalef(8.5,0.2,0.1);
        cubo();
    glPopMatrix();

    //estaca 2
    glPushMatrix();
        glTranslatef(4.9,0.3,-9.7);
        glScalef(0.2,1.5,0.1);
        cubo();
    glPopMatrix();

    //cerca de cima da direita
    glPushMatrix();
        glTranslatef(4.7,1.1,-0.3);
        glRotatef(90,0,1,0);
        glScalef(18.0,0.2,0.1);
        cubo();
    glPopMatrix();

    //cerca de cima da direita
    glPushMatrix();
        glTranslatef(4.7,0.5,-0.3);
        glRotatef(90,0,1,0);
        glScalef(18.0,0.2,0.1);
        cubo();
    glPopMatrix();

    //estaca 3
    glPushMatrix();
        glTranslatef(4.9,0.3,9.0);
        glScalef(0.2,1.5,0.1);
        cubo();
    glPopMatrix();

    //cerca de cima da esquerda
    glPushMatrix();
        glTranslatef(-4.7,1.1,-0.3);
        glRotatef(90,0,1,0);
        glScalef(18.0,0.2,0.1);
        cubo();
    glPopMatrix();

    //cerca de baixo da esquerda
    glPushMatrix();
        glTranslatef(-4.7,0.5,-0.3);
        glRotatef(90,0,1,0);
        glScalef(18.0,0.2,0.1);
        cubo();
    glPopMatrix();

    //estaca 4
    glPushMatrix();
        glTranslatef(-4.9,0.3,9.0);
        glScalef(0.2,1.5,0.1);
        cubo();
    glPopMatrix();

    //cerca de cima de trás
    glPushMatrix();
        glTranslatef(0.0,1.2,8);
        glScalef(8.5,0.2,0.1);
        cubo();
    glPopMatrix();

    //certa de baixo de trás
    glPushMatrix();
        glTranslatef(0.0,0.6,8);
        glScalef(8.5,0.2,0.1);
        cubo();
    glPopMatrix();
}

//desenha o terreno onde ficarão o canhão e o lançador
void terreno(void)
{
   // piso: placa de espessura 0.1, com face superior no n�vel Y=0.0
   glPushMatrix();
      glScalef(8.0,0.1,15.0);
      glutSolidCube(4.0);
   glPopMatrix();
}