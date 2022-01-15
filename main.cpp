#include <GL/glut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "ObjLoader.h"

static unsigned cenario;
static unsigned mesa;
static unsigned decoracao;
static unsigned cadeira;
static unsigned talher;

float rotacaoX = 0, rotacaoY = 0 , rotacaoZ = 0;

glm::vec3 P_cam , V_cam , X_cam, Y_cam, Z_cam;
glm::vec3 Pos_cam(0,2,4);
glm::mat4 M_cam;

float velocidade = 0.1;

void inicio(){

    glClearColor(0.3,0.3,0.3,1);
    glPointSize(20.0);
    glLineWidth(3.0);

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

    ObjLoader::loadOBJ(cenario, "objetos/cenario.obj");
    ObjLoader::loadOBJ(mesa, "objetos/mesa.obj");
    ObjLoader::loadOBJ(decoracao, "objetos/decoracao.obj");
    ObjLoader::loadOBJ(cadeira, "objetos/cadeira.obj");
    ObjLoader::loadOBJ(talher, "objetos/talher.obj");

        P_cam = glm::vec3(0,0,0);
        V_cam = glm::vec3(0,1,0);
        X_cam = glm::vec3(-1,0,0);
        Y_cam = glm::vec3(0,1,0);
        Z_cam = glm::vec3(0,0,-1);

            M_cam = glm::mat4(1);

                M_cam[0] = glm::vec4(X_cam,0) ; M_cam[1] = glm::vec4(Y_cam,0);
                M_cam[2] = glm::vec4(Z_cam,0) ; M_cam[3] = glm::vec4(P_cam,1);

            M_cam = glm::transpose(M_cam);

}

glm::mat4 rotacao;

void teclado(unsigned char tecla, int x, int y){

    switch(tecla){

        case 'w':case 'W':
            
            P_cam += velocidade * Z_cam;
            
        break;

        case 's':case 'S':

            P_cam -= velocidade * Z_cam;

        break;

        case 'a':case 'A':

            P_cam += velocidade * X_cam;

        break;

        case 'd':case 'D':

            P_cam -= velocidade * X_cam;

        break;

        case 'j':case 'J':

            rotacaoY += 1;

            rotacao = glm::rotate(glm::mat4(1.0), glm::radians(rotacaoY),glm::vec3(0,Y_cam.y,0));

            X_cam = glm::vec3( rotacao * glm::vec4(X_cam,0));
            Y_cam = glm::vec3( rotacao * glm::vec4(Y_cam,0));
            Z_cam = glm::vec3( rotacao * glm::vec4(Z_cam,0));

            if (rotacaoY >= 360){
                
                rotacaoY = 0;

            }
            

        break;

        case 'l':case 'L':

            rotacaoY += 1;

        break;

        case 'i':case 'I':

            rotacaoX -= 1;

        break;

        case 'k':case 'K':

            rotacaoX += 1;

        break;
           
    }

    M_cam[0] = glm::vec4(X_cam,0) ; M_cam[1] = glm::vec4(Y_cam,0);
    M_cam[2] = glm::vec4(Z_cam,0) ; M_cam[3] = glm::vec4(P_cam,1);

    M_cam = glm::transpose(M_cam);

    glutPostRedisplay();

}

void desenha(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glm::mat4 projecaoMatrix = glm::frustum(-1,1,-1,1,2,100);
    glLoadMatrixf(glm::value_ptr(projecaoMatrix));

    glMatrixMode(GL_MODELVIEW);
    glm::mat4 cameraMatrix = glm::lookAt( Pos_cam , {0,0,0}, glm::vec3(0,1,0));
    glLoadMatrixf(glm::value_ptr(cameraMatrix));


    float matSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT,GL_SHININESS , 128);

    glPushMatrix();

        glMultMatrixf(glm::value_ptr(M_cam));

    glPopMatrix();

    glPushMatrix();

        glBegin(GL_LINES);
            glColor3f(1, 0, 0);
            glVertex3f(-50, 0, 0);
            glVertex3f(50, 0, 0);
            glColor3f(0, 1, 0);
            glVertex3f(0, -50, 0);
            glVertex3f(0, 50, 0);
            glColor3f(0, 0, 1);
            glVertex3f(0, 0, -50);
            glVertex3f(0, 0, 50);
        glEnd();

    glPopMatrix();

    glPushMatrix();

        //glRotatef(rotacaoX,X_cam);

        glBegin(GL_LINES);

            glColor3f(1, 0, 0);
            glVertex3f(P_cam.x, P_cam.y, P_cam.z);
            glVertex3f(P_cam.x + X_cam.x, P_cam.y + X_cam.y, P_cam.z + X_cam.z);
            glColor3f(0, 1, 0);
            glVertex3f(P_cam.x, P_cam.y, P_cam.z);
            glVertex3f(P_cam.x + Y_cam.x, P_cam.y + Y_cam.y, P_cam.z + Y_cam.z);
            glColor3f(0, 0, 1);
            glVertex3f(P_cam.x, P_cam.y, P_cam.z);
            glVertex3f(P_cam.x + Z_cam.x, P_cam.y + Z_cam.y , P_cam.z + Z_cam.z);
    
        glEnd();

        glBegin(GL_POINTS);

            glColor3f(0,1,1);
            glVertex3f(P_cam.x,P_cam.y + (Y_cam.y / 2), P_cam.z + Z_cam.z);

        glEnd();

    glPopMatrix();

    /*glPushMatrix();

        glRotatef(-90,0,1,0);
        glScalef(3,3,3);
        glColor3f(0.1, 0.2, 0.3);
        glCallList(cenario);

    glPopMatrix();

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

    glPopMatrix();*/

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
