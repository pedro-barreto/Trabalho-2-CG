//PEDRO HENRIQUE BARRETO DOS SANTOS - 475626
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

//NOME DOS OBJETOS
static unsigned cenario;
static unsigned mesa;
static unsigned decoracao;
static unsigned cadeira;
static unsigned talher;

//TOTAL DE OBJETO NO CENARIO = 8
void imprimirObjetos(){//FUNCAO PARA IMPRIMIR OS OBJETOS  

    glPushMatrix();

        glColor3f(0, 0.7, 0.7);//COR DO OBJETO

        //DADOS CASO NECESSARIO UMA TRANSLACAO, ROTACAO OU ESCLA
        glm::mat4 cen_T  = glm::translate(glm::mat4(1.0),glm::vec3(0,0.4,0));
        glm::mat4 cen_R  = glm::rotate(glm::mat4(1.0),glm::radians(-90.f),glm::vec3(0,1,0));
        glm::mat4 cen_S  = glm::scale(glm::mat4(1.0),glm::vec3(4,4,4));

        glm::mat4 cen_M = cen_T * cen_R * cen_S;//CALCULO PARA A MATRIZ

        glMultMatrixf(glm::value_ptr(cen_M));//ATRIBUINDO AO OBJETO

        glCallList(cenario);//OBJETO SENDO IMPRIMIDO

    glPopMatrix();

    //OBS: APARTIR DAQUI TODOS TEM A MESMA FUNCIONALIDADE DA DE CIMA

    glPushMatrix();

        glColor3f(0.81, 0.57, 0.38);

        glm::mat4 mesa_T  = glm::translate(glm::mat4(1.0),glm::vec3(0,0.4,0));
        glm::mat4 mesa_R  = glm::rotate(glm::mat4(1.0),glm::radians(0.f),glm::vec3(0,1,0));
        glm::mat4 mesa_S  = glm::scale(glm::mat4(1.0),glm::vec3(1,1,1));

        glm::mat4 mesa_M = mesa_T *  mesa_R * mesa_S;

        glMultMatrixf(glm::value_ptr(mesa_M));

        glCallList(mesa);

    glPopMatrix();

    glPushMatrix();

        glColor3f(0.59, 0, 0.11);

        glm::mat4 dec_T  = glm::translate(glm::mat4(1.0),glm::vec3(1.5,0.7,0.5));
        glm::mat4 dec_R  = glm::rotate(glm::mat4(1.0),glm::radians(-90.f),glm::vec3(0,1,0));
        glm::mat4 dec_R2 = glm::rotate(glm::mat4(1.0),glm::radians(-20.f),glm::vec3(0,0,1)); 
        glm::mat4 dec_S  = glm::scale(glm::mat4(1.0),glm::vec3(1,1,1));  

        glm::mat4 dec_M = dec_T *  dec_R * dec_R2 * dec_S;

        glMultMatrixf(glm::value_ptr(dec_M));

        glCallList(decoracao);

    glPopMatrix();

    glPushMatrix();

        glColor3f(0.6,0.6,0.6);

        glm::mat4 cad_T  = glm::translate(glm::mat4(1.0),glm::vec3(-0.6,0.1,0.4));
        glm::mat4 cad_R  = glm::rotate(glm::mat4(1.0),glm::radians(0.f),glm::vec3(0,1,0));
        glm::mat4 cad_S  = glm::scale(glm::mat4(1.0),glm::vec3(1,1,1));

        glm::mat4 cad_M = cad_T * cad_R * cad_S;

        glMultMatrixf(glm::value_ptr(cad_M));

        glCallList(cadeira);

    glPopMatrix();

    glPushMatrix();

        glColor3f(0.6,0.6,0.6);

        glm::mat4 cad2_T  = glm::translate(glm::mat4(1.0),glm::vec3(-0.6,0.1,-0.6));
        glm::mat4 cad2_R  = glm::rotate(glm::mat4(1.0),glm::radians(0.f),glm::vec3(0,1,0));
        glm::mat4 cad2_S  = glm::scale(glm::mat4(1.0),glm::vec3(1,1,1));

        glm::mat4 cad2_M = cad2_T * cad2_R * cad2_S;

        glMultMatrixf(glm::value_ptr(cad2_M));

        glCallList(cadeira);

    glPopMatrix();

    glPushMatrix();

        glColor3f(0.9,0.9,0.9);

            glm::mat4 tal_T  = glm::translate(glm::mat4(1.0),glm::vec3(0,1,-0.5));
            glm::mat4 tal_R  = glm::rotate(glm::mat4(1.0),glm::radians(180.f),glm::vec3(0,1,0));
            glm::mat4 tal_S  = glm::scale(glm::mat4(1.0),glm::vec3(0.7,0.7,0.7));

        glm::mat4 tal_M = tal_T *  tal_R * tal_S;

        glMultMatrixf(glm::value_ptr(tal_M));

        glCallList(talher);

    glPopMatrix();

    glPushMatrix();

        glColor3f(0.9,0.9,0.9);

            glm::mat4 tal2_T  = glm::translate(glm::mat4(1.0),glm::vec3(0,1,0.5));
            glm::mat4 tal2_R  = glm::rotate(glm::mat4(1.0),glm::radians(180.f),glm::vec3(0,1,0));
            glm::mat4 tal2_S  = glm::scale(glm::mat4(1.0),glm::vec3(0.7,0.7,0.7));

            glm::mat4 tal2_M = tal2_T *  tal2_R * tal2_S;

        glMultMatrixf(glm::value_ptr(tal2_M));

        glCallList(talher);

    glPopMatrix();

}