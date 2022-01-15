#include <GL/glut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "ObjLoader.h"

static unsigned mesa;
static unsigned decoracao;
static unsigned cadeira;
static unsigned talher;

int rotacaoX = 0;
int rotacaoY = 0;
int rotacaoZ = 0;

void inicio(){

    glClearColor(0.3,0.3,0.3,1);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glm::mat4x4 luz = {

        {0.1f, 0.1f, 0.1f, 1.0f},//ambient
        {0.6f, 0.6f, 0.6f, 1.0f},//difuse
        {1.0f, 1.0f, 1.0f, 1.0f},//specular
        {0.0f, 0.0f, 1.0f, 0.0f} //position
        
    };

    glLightfv(GL_LIGHT0, GL_AMBIENT , &luz[0][0]);
    glLightfv(GL_LIGHT0, GL_DIFFUSE , &luz[1][0]);
    glLightfv(GL_LIGHT0, GL_SPECULAR, &luz[2][0]);
    glLightfv(GL_LIGHT0, GL_POSITION, &luz[3][0]);

    ObjLoader::loadOBJ(mesa, "objetos/mesa.obj");
    ObjLoader::loadOBJ(decoracao, "objetos/decoracao.obj");
    ObjLoader::loadOBJ(cadeira, "objetos/cadeira.obj");
    ObjLoader::loadOBJ(talher, "objetos/talher.obj");

}

void teclado(unsigned char tecla, int x, int y){

    switch(tecla){

        case 'w':case 'W':
            
            rotacaoX -= 5;
            
        break;

        case 's':case 'S':

            rotacaoX += 5;

        break;

        case 'a':case 'A':

            rotacaoY += 5;

        break;

        case 'd':case 'D':

            rotacaoY -= 5;

        break;

           
    }

    glutPostRedisplay();

}

void desenha(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glm::mat4 projecaoMatrix = glm::frustum(-1,1,-1,1,2,50);
    glLoadMatrixf(glm::value_ptr(projecaoMatrix));

    glMatrixMode(GL_MODELVIEW);
    glm::mat4 cameraMatrix = glm::lookAt({0,2,4}, {0,0,0}, glm::vec3(0,1,0));
    glLoadMatrixf(glm::value_ptr(cameraMatrix));

    float matSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT,GL_SHININESS , 128);

    glRotatef(rotacaoY, 0 , 1 , 0);
    glRotatef(rotacaoX, 1 , 0 , 0);

    glPushMatrix();

        glColor3f(0.81, 0.57, 0.38);
        glCallList(mesa);

    glPopMatrix();

    glPushMatrix();

        glRotatef(90,0,1,0);
        glRotatef(-20,0,0,1);
        glTranslatef(0,0.75,0);
        glScalef(0.2,0.2,0.2);
        glColor3f(1,0,0);
        glCallList(decoracao);

    glPopMatrix();

    glPushMatrix();

        glTranslatef(-0.6,-0.2,0.4);
        glColor3f(0.6,0.6,0.6);
        glCallList(cadeira);

    glPopMatrix();

    glPushMatrix();

        glTranslatef(-0.6,-0.2,-0.4);
        glColor3f(0.6,0.6,0.6);
        glCallList(cadeira);

    glPopMatrix();

    glPushMatrix();

        glRotatef(180,0,1,0);
        glTranslatef(0,0.6,-0.5);
        glScalef(0.7,0.7,0.7);
        glColor3f(0.9,0.9,0.9);
        glCallList(talher);

    glPopMatrix();

    glutSwapBuffers();

}

int main(int argc, char** argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(300,50);
    glutInitWindowSize(700,700);
    glutCreateWindow("Teste");

    inicio();
    glutKeyboardFunc(teclado);
    glutDisplayFunc(desenha);
    glutMainLoop();

}

//cd Trabalho-2-CG
//g++ main.cpp ObjLoader.cpp Vetor.cpp -o main.exe -lopengl32 -lfreeglut
//start main.exe
