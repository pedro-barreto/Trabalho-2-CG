#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

float rotacaoVelocidade = 3;
float velocidade = 0.5;

glm::mat4 M_cam;
glm::mat4 rotacaoX;
glm::mat4 rotacaoY;

glm::vec3 P_cam , V_cam , X_cam, Y_cam, Z_cam;

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


            rotacaoY = glm::rotate(glm::mat4(1.0), glm::radians(rotacaoVelocidade),glm::vec3(Y_cam));

            X_cam = glm::vec3( rotacaoY * glm::vec4(X_cam,0));
            Y_cam = glm::vec3( rotacaoY * glm::vec4(Y_cam,0));
            Z_cam = glm::vec3( rotacaoY * glm::vec4(Z_cam,0));

        break;

        case 'l':case 'L':

            rotacaoY = glm::rotate(glm::mat4(1.0), glm::radians(-rotacaoVelocidade),glm::vec3(Y_cam));

            X_cam = glm::vec3( rotacaoY * glm::vec4(X_cam,0));
            Y_cam = glm::vec3( rotacaoY * glm::vec4(Y_cam,0));
            Z_cam = glm::vec3( rotacaoY * glm::vec4(Z_cam,0));

        break;

        case '1':

            P_cam = glm::vec3(5,5,15);

        break;

        case '2':

            P_cam = glm::vec3(-5,5,15);

        break;

        case '3':

            P_cam = glm::vec3(0,1,5);

        break;

        case '4':

            P_cam = glm::vec3(0,2,10);

        break;

        case '5':

            P_cam = glm::vec3(2.2,2,-2.8);

        break;

        case '6':

            P_cam = glm::vec3(-2.2,2,-2.8);

        break;

        case '7':

            P_cam = glm::vec3(0,2,-10);

        break;

        case '8':

            P_cam = glm::vec3(5,5,-15);

        break;

        case '9':

            P_cam = glm::vec3(-5,5,-15);

        break;

        case '0':

            P_cam = glm::vec3(0,2,10);

        break;
           
    }

    M_cam[0] = glm::vec4(X_cam,0) ; M_cam[1] = glm::vec4(Y_cam,0);
    M_cam[2] = glm::vec4(Z_cam,0) ; M_cam[3] = glm::vec4(P_cam,1);

    M_cam = glm::transpose(M_cam);

    glutPostRedisplay();

}