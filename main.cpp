#include <GL/glut.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "ObjLoader.h"

glm::vec3 cam_pos(0,2,3);
glm::vec3 vis_pos(0,0,0);
GLfloat angle_center = 0;

static unsigned estatua;

void inicio(){

    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    float globalAmb[] = { 0.1f , 0.1f , 0.1f , 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);

    glm::mat4x4 luz = {
        {0.1f, 0.1f, 0.1f, 1.0f},//ambiente
        {0.8f, 0.8f, 0.8f, 1.0f},//difusa
        {1.0f, 1.0f, 1.0f, 1.0f},//especular
        {0.0f, 0.0f, 1.0f, 1.0f} //posição
    };

    glLightfv(GL_LIGHT0, GL_AMBIENT , &luz[0][0]);
    glLightfv(GL_LIGHT0, GL_DIFFUSE , &luz[1][0]);
    glLightfv(GL_LIGHT0, GL_SPECULAR, &luz[2][0]);
    glLightfv(GL_LIGHT0, GL_POSITION, &luz[3][0]);

    ObjLoader::loadOBJ(estatua, "modelos/fertility.obj");
 
    angle_center = 0.0;

}

void teclado(unsigned char tecla, int x, int y){

    switch(tecla){

        case 'w':
        case 'W':
            
            cam_pos.z -= 1;
            
        break;

        case 's':
        case 'S':

            cam_pos.z += 1;

        break;

        case 'a':
        case 'A':

            angle_center += 10;

        break;

        case 'd':
        case 'D':

            angle_center -= 10;

        break;

           
    }

    glutPostRedisplay();

}

void desenha(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glm::mat4 projecaoMatrix = glm::frustum(-1,1,-1,1,2,100);
    glLoadMatrixf(glm::value_ptr(projecaoMatrix));

    glMatrixMode(GL_MODELVIEW);
    glm::mat4 cameraMatrix = glm::lookAt(cam_pos, vis_pos, glm::vec3(0,1,0));
    glLoadMatrixf(glm::value_ptr(cameraMatrix));

    float matSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialf(GL_FRONT,GL_SHININESS , 128);

    glRotatef(angle_center, 0, cam_pos[1], 0);

    glPushMatrix();

        glColor3f(0,1,0);
        glCallList(estatua);

    glPopMatrix();

    glutSwapBuffers();

}

int main(int argc, char** argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50,200);
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
