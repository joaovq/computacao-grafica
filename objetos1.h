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

GLfloat xBala = 0, yBala = 1.7, zBala = 40;
GLfloat xCan = 0, yCan = 0.15, zCan = 40;
int  giraDisco = 0;
float giraSol = 0;
GLfloat giroRoda = 0.0;

float angCan = 0, giroCan = 0;


GLfloat ufoColorRing [3] = {0.8274,0.8274,0.8274 };
GLfloat ufoColor   [3] = {0.5274,0.5274,0.5274 };
GLfloat sunColor   [3] = {0.988,0.83,0.2509 };
GLfloat moonColor   [3] = {1.0,1.0,1.0};
GLfloat red   [3] = {1.0,0.0,0.0 };
GLfloat blue   [3] = {0.0, 1.0, 0.0};

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

void esfera(){
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

void cilindroComTampa()
{
  float raio = 1.0;
  float alt = 1.0;
  static GLUquadric* quad;
  quad = gluNewQuadric();
  gluCylinder(quad, raio, raio, alt, 20, 10);

  // tampas para o cilindro
  glPushMatrix();
    glNormal3f(0.0,0.0,-1.0);
      glBegin(GL_POLYGON);
          for(int i = 0; i < 100; i++) {
             float ang = i*2*dPI/100;
             glVertex2f(cos(ang) * raio, sin(ang) * raio);
          }
      glEnd();
      glTranslatef(0.0,0.0,1.0);
    glNormal3f(0.0,0.0,1.0);
      glBegin(GL_POLYGON);
          for(int i = 0; i < 100; i++) {
             float ang = i*2*dPI/100;
             glVertex2f(cos(ang) * raio, sin(ang) * raio);
          }
      glEnd();
  glPopMatrix();

}

void modeloRoda()
{
    glPushMatrix();
    glTranslatef(0.0,0.1,0.0);
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glTranslatef(0.0,0.0,0.15);
        glColor3f(1.0,1.0,1.0);
        glBindTexture(GL_TEXTURE_2D, 15);

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

        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.1,0.1,0.1);
        glTranslatef(0.0,1.0,0.0);
        glScalef(1.02,1.02,0.3);
        cilindro();
    glPopMatrix();

    glPopMatrix();
}

void meiaEsfera()
{
    glEnable(GL_CLIP_PLANE0);
    GLdouble eqn[4] = {0.0, 1.0, 0.0, 0.0};
    glClipPlane(GL_CLIP_PLANE0, eqn);
    glutSolidSphere(2.0, 100, 10);
    glDisable(GL_CLIP_PLANE0);

}

void eixoCanhao()
{
    //Cor do eixo
    glColor3f(0.1,0.1,0.1);

    //Eixo
    glPushMatrix();
      glTranslatef(xCan-1.0,0.1,0.0);
      glRotatef(angCan,1.0,0.0,0.0);
      glRotatef(90,0.0,1.0,0.0);
      glScalef(0.2,0.2,2.3);
      cilindro();
    glPopMatrix();

    //Ponta daq esquerda
    glPushMatrix();

      glTranslatef(xCan-1.0,0.1,0.0);
      glRotatef(angCan,1.0,0.0,0.0);
      glRotatef(90,0.0,0.0,1.0);
      glScalef(0.1,0.1,0.1);
      meiaEsfera();
    glPopMatrix();

    //Ponta daq esquerda
    glPushMatrix();
      glTranslatef(xCan +1.25,0.1,0.0);
      glRotatef(angCan,1.0,0.0,0.0);
      glRotatef(-90,0.0,0.0,1.0);
      glScalef(0.1,0.1,0.1);
      meiaEsfera();
    glPopMatrix();
}

void rodaDoCanhao()
{

    glPushMatrix();

    glPushMatrix();
        glTranslatef(xCan +1.0,0.0,zCan);
        glTranslatef(0.0,1.0,0.0);
        glRotatef(giroRoda,1.0,0.0,0.0);
        glRotatef(-giroCan,1.0,0.0,0.0);
        glTranslatef(0.0,-1.0,0.0);
        glRotatef(90,0.0,1.0,0.0);
        modeloRoda();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(xCan -1.0,0.0,zCan);
        glTranslatef(0.0,1.0,0.0);
        glRotatef(giroCan,1.0,0.0,0.0);
        glRotatef(giroRoda,1.0,0.0,0.0);
        glTranslatef(0.0,-1.0,0.0);
        glRotatef(90,0.0,1.0,0.0);
        modeloRoda();
    glPopMatrix();


    glPopMatrix();
}

//desenha canhao
void canhao()
{
    GLfloat mat_ambient[]= {0.4, 0.3, 0.4, 0.3};
    GLfloat mat_diffuse[]= {0.8, 0.8, 0.8, 0.8};
    GLfloat mat_specular[]= {0.3,0.3,0.3, 1.0};
    GLfloat mat_shininess= {80.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    glTranslatef(0.0,yCan,0.0);

    glPushMatrix();
    //Tubo do canhao
      glPushMatrix();
        glTranslatef(xCan,1.5,zCan);
        glRotatef(angCan,1.0,0.0,0.0);

        glPushMatrix();
          glColor3f(0.1,0.1,0.1);

          glRotatef(180,0.0,1.0,0.0);
          glTranslatef(0.0,0.0,-1.2);
          glScalef(0.4,0.4,3.5);
          cilindro();
        glPopMatrix();

        glPushMatrix();
          glColor3f(0.1,0.1,0.1);
          glTranslatef(0.0,0.0,1.2);
          glRotatef(90,0.0,1.0,0.0);
          glRotatef(90,0.0,0.0,1.0);
          glScalef(0.2,0.2,0.2);
          meiaEsfera();
        glPopMatrix();
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-0.125,1.0,zCan);
      eixoCanhao();
      glPopMatrix();
    glPopMatrix();

    //Roda e eixo
    glPushMatrix();
    glTranslatef(-0.13,0.0,-0.0);
    rodaDoCanhao();
    glPopMatrix();

}

void roda()
{
  glPushMatrix();
    //gera raio
    glPushMatrix();
      glTranslatef(1.2,0.0,0.4);
      glRotatef(-90.0, 0.0, 1.0, 0.0);
      glScalef(0.1,0.1,2.4);
      cilindro();
    glPopMatrix();
    //gera pneu
    glPushMatrix();
      glTranslatef(0.0,-0.1,0.4);
      glRotatef(-90.0, 1.0, 0.0, 0.0);
      glScalef(1.2,1.2,0.2);
      cilindro();
    glPopMatrix();
  glPopMatrix();
}

GLfloat teta = 0.0f, angulo = 0.0f; 

void eixoRodas()
{
  glPushMatrix();
    glPushMatrix();     
      glRotatef(90.0, 0.0, 1.0, 0.0);
      glTranslatef(1.7,-0.4,-1.3);
      glScalef(0.1,0.1,2.6);
      cilindro();
    glPopMatrix();
    glPushMatrix(); 
      glTranslatef(1.3,0.0,-1.7);
      glRotatef(90+angulo, 0.0, 1.0, 0.0);
      glRotatef(90, 1.0, 0.0, 0.0); 
      glTranslatef(0.0,0.0,0.4);
      glRotatef(teta, 0.0, 1.0, 0.0);     
      glTranslatef(0.0,0.0,-0.4);   
      roda();
    glPopMatrix();
    glPushMatrix(); 
      glTranslatef(-1.3,0.0,-1.7);
      glRotatef(90+angulo, 0.0, 1.0, 0.0);
      glRotatef(90, 1.0, 0.0, 0.0); 
      glTranslatef(0.0,0.0,0.4);
      glRotatef(teta, 0.0, 1.0, 0.0);     
      glTranslatef(0.0,0.0,-0.4);   
      roda();
    glPopMatrix();
  glPopMatrix();
}


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
      glutSolidCube(1.0);
   glPopMatrix();
} 
