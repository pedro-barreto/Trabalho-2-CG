#include <GL/glut.h>
#include <iostream>
#include "ObjLoader.h"

glm::vec3 cam_pos(0,15,30);
glm::vec3 vis_pos(0,1,0);
GLfloat angle_center = 0;

static unsigned blenderModelId;

void inicio(){

    glClearColor(1,1,1,1);
    glLineWidth(3);
    glEnable(GL_DEPTH_TEST);

    ObjLoader::loadOBJ(blenderModelId, "Blender/monkey.obj");
 
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

    glRotatef(angle_center, 0, cam_pos[1], 0);

    glPushMatrix();
        glScalef(5,5,5);
        glColor3f(1,0,0);
        glCallList(blenderModelId);
    glPopMatrix();

    glutSwapBuffers();

}

int main(int argc, char** argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50,200);
    glutInitWindowSize(700,700);
    glutCreateWindow("Jogo de Damas");

    inicio();
    glutKeyboardFunc(teclado);
    glutDisplayFunc(desenha);
    glutMainLoop();

}

//cd Trabalho-Final-CG
//g++ main.cpp ObjLoader.cpp Vetor.cpp Material.cpp -o main.exe -lopengl32 -lfreeglut
//start main.exe
