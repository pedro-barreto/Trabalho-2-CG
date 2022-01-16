//PEDRO HENRIQUE BARRETO DOS SANTOS - 475626
#include <GL/glut.h>
#include <glm/glm.hpp>

glm::vec3 cam(0,3,15);//POSICAO DA CAMERA INICIALMENTE

int qunatLuz = 80;//QUANTIDADE DE LUZ, SHINENESS. O EXPOENTE DA EQUACAO

//LUZES PARA SER LIGADS OU DESLIGADAS
bool luz0 = false, luz1 = false, luz2 = false, luz3 = false;

//POSICAO DAS LUZES
glm::vec4 posLuz0(-20.0f, 2.0f, 20.0f, 1.0f);
glm::vec4 posLuz1(20.0f, 2.0f, 20.0f, 1.0f);
glm::vec4 posLuz2(20.0f, 2.0f, -20.0f, 1.0f);
glm::vec4 posLuz3(0.0f, 20.0f, 0.0f, 1.0f);  

void teclado(unsigned char tecla, int x, int y){

    switch(tecla){
        
        //W e S MOVIMENTA A LUZ NO EIXO Z
        //A e D MOVIMENTA A LUZ NO EIXO X
        //Q e E MOVIMENTA A LUZ NO EIXO Y
        //Z e X AUMENTA E DIMINUIO SHININESS DO OBJETO
        // C, V, B, N SERVE PARA ATIVAR E DESATIVAR LUZES DIFERENTES
        //DE 0 A 9 TEM POSICOES DE CAMERA DIFERENTE

        case 'w': case 'W':

            if (luz0){posLuz0.z -= 2;}

            if (luz1){posLuz1.z -= 2;}

            if (luz2){posLuz2.z -= 2;}

            if (luz3){posLuz3.z -= 2;}
            

        break;

        case 's': case 'S':

            if (luz0){posLuz0.z += 2;}

            if (luz1){posLuz1.z += 2;}

            if (luz2){posLuz2.z += 2;}

            if (luz3){posLuz3.z += 2;}
            

        break;

        case 'a': case 'A':

            if (luz0){posLuz0.x -= 2;}

            if (luz1){posLuz1.x -= 2;}

            if (luz2){posLuz2.x -= 2;}

            if (luz3){posLuz3.x -= 2;}
            

        break;

        case 'd': case 'D':

            if (luz0){posLuz0.x += 2;}

            if (luz1){posLuz1.x += 2;}

            if (luz2){posLuz2.x += 2;}

            if (luz3){posLuz3.x += 2;}
            

        break;

        case 'q': case 'Q':

            if (luz0){posLuz0.y -= 2;}

            if (luz1){posLuz1.y -= 2;}

            if (luz2){posLuz2.y -= 2;}

            if (luz3){posLuz3.y -= 2;}
            

        break;

        case 'e': case 'E':

            if (luz0){posLuz0.y += 2;}

            if (luz1){posLuz1.y += 2;}

            if (luz2){posLuz2.y += 2;}

            if (luz3){posLuz3.y += 2;}
            

        break;

        case 'c': case 'C':

            if(luz0){

                glDisable(GL_LIGHT0);//DESABILITANDO LUZ 0
                luz0 = false;

            }else{

                glEnable(GL_LIGHT0);//HABILITANDO LUZ 0
                luz0 = true;

            } 

        break;

        case 'v': case 'V':

            if(luz1){

                glDisable(GL_LIGHT1);//DESABILITANDO LUZ 0
                luz1 = false;

            }else{

                glEnable(GL_LIGHT1);//HABILITANDO LUZ 0
                luz1 = true;

            } 

        break;

        case 'b': case 'B':

            if(luz2){

                glDisable(GL_LIGHT2);//DESABILITANDO LUZ 0
                luz2 = false;

            }else{

                glEnable(GL_LIGHT2);//HABILITANDO LUZ 0
                luz2 = true;

            } 

        break;

        case 'n': case 'N':

            if(luz3){

                glDisable(GL_LIGHT3);//DESABILITANDO LUZ 0
                luz3 = false;

            }else{

                glEnable(GL_LIGHT3);//HABILITANDO LUZ 0
                luz3 = true;

            } 

        break;

        case 'z': case 'Z':

            if(qunatLuz > 12){

                qunatLuz -= 4;

            } 

        break;

        case 'x': case 'X':

            if(qunatLuz < 128){

                qunatLuz += 4;
                
            } 

        break;

        case '1':

            cam = glm::vec3(5,5,15);

        break;

        case '2':

            cam = glm::vec3(-5,5,15);

        break;

        case '3':

            cam = glm::vec3(0,2,7);

        break;

        case '4':

            cam = glm::vec3(0,2,10);

        break;

        case '5':

            cam = glm::vec3(2.2,2,-2.8);

        break;

        case '6':

            cam = glm::vec3(-2.2,2,-2.8);

        break;

        case '7':

            cam = glm::vec3(0,2,-10);

        break;

        case '8':

            cam = glm::vec3(5,5,-15);

        break;

        case '9':

            cam = glm::vec3(-5,5,-15);

        break;

        case '0':

            cam = glm::vec3(0,2,10);

        break;
        
    }

    glutPostRedisplay();

}

void luzes(){

    glm::mat4x4 luz0 = {//CRIANDO DADOS DA LUZ 0

        {0.1f, 0.1f, 0.1f, 1.0f},//DADOS DO AMBIENT
        {0.8f, 0.8f, 0.8f, 1.0f},// DADOS DO DIFFUSE
        {1.0f, 1.0f, 1.0f, 1.0f},//DADOS DO SPECULAR
        {posLuz0} //DADOS DA POSITTION
              
    };

    //ATRIBUINDO OS DADOS DA LUZ
    glLightfv(GL_LIGHT0, GL_AMBIENT , &luz0[0][0]);
    glLightfv(GL_LIGHT0, GL_DIFFUSE , &luz0[1][0]);
    glLightfv(GL_LIGHT0, GL_SPECULAR, &luz0[2][0]);
    glLightfv(GL_LIGHT0, GL_POSITION, &luz0[3][0]);

    glm::mat4x4 luz1 = {//CRIANDO DADOS DA LUZ 1

        {0.1f, 0.1f, 0.1f, 1.0f},//DADOS DO AMBIENT
        {0.8f, 0.8f, 0.8f, 1.0f},// DADOS DO DIFFUSE
        {1.0f, 1.0f, 1.0f, 1.0f},//DADOS DO SPECULAR
        {posLuz1} //DADOS DA POSITTION
        
    };

    //ATRIBUINDO OS DADOS DA LUZ
    glLightfv(GL_LIGHT1, GL_AMBIENT , &luz1[0][0]);
    glLightfv(GL_LIGHT1, GL_DIFFUSE , &luz1[1][0]);
    glLightfv(GL_LIGHT1, GL_SPECULAR, &luz1[2][0]);
    glLightfv(GL_LIGHT1, GL_POSITION, &luz1[3][0]);

    glm::mat4x4 luz2 = {//CRIANDO DADOS DA LUZ 2

        {0.1f, 0.1f, 0.1f, 1.0f},//DADOS DO AMBIENT
        {0.8f, 0.8f, 0.8f, 1.0f},// DADOS DO DIFFUSE
        {1.0f, 1.0f, 1.0f, 1.0f},//DADOS DO SPECULAR
        {posLuz2} //DADOS DA POSITTION
                
    };

    //ATRIBUINDO OS DADOS DA LUZ
    glLightfv(GL_LIGHT2, GL_AMBIENT , &luz2[0][0]);
    glLightfv(GL_LIGHT2, GL_DIFFUSE , &luz2[1][0]);
    glLightfv(GL_LIGHT2, GL_SPECULAR, &luz2[2][0]);
    glLightfv(GL_LIGHT2, GL_POSITION, &luz2[3][0]);

    glm::mat4x4 luz3 = {//CRIANDO DADOS DA LUZ 3

        {0.1f, 0.1f, 0.1f, 1.0f},//DADOS DO AMBIENT
        {0.8f, 0.8f, 0.8f, 1.0f},// DADOS DO DIFFUSE
        {1.0f, 1.0f, 1.0f, 1.0f},//DADOS DO SPECULAR
        {posLuz3} //DADOS DA POSITTION
                
    };

    //ATRIBUINDO OS DADOS DA LUZ
    glLightfv(GL_LIGHT3, GL_AMBIENT , &luz3[0][0]);
    glLightfv(GL_LIGHT3, GL_DIFFUSE , &luz3[1][0]);
    glLightfv(GL_LIGHT3, GL_SPECULAR, &luz3[2][0]);
    glLightfv(GL_LIGHT3, GL_POSITION, &luz3[3][0]);

}