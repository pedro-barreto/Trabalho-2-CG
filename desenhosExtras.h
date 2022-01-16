//PEDRO HENRIQUE BARRETO DOS SANTOS - 475626
#include <GL/glut.h>
#include <glm/ext.hpp>

void chao(){//CRIANDO CHAO

    //3600 quadrados, 7200 triangulos

    for (int i = -30; i < 30; i++){

        for (int j = -30; j < 30; j++){
        
            glPushMatrix();

                glm::mat4 quad_T  = glm::translate(glm::mat4(1.0),glm::vec3(i,0,j));
    
                glm::mat4 quad_M = quad_T;

                glMultMatrixf(glm::value_ptr(quad_M));

                glBegin(GL_TRIANGLE_STRIP);//O CHAO E QUADRADO MAS E CRIDO COMO TRIANGULOS, POIS VAI TER MAIS FACE E VAI ILUMINAR MELHOR

                        glColor3f(1,1,1);
                        glVertex3f(0,0,0);
                        glVertex3f(1,0,0);
                        glVertex3f(0,0,1);
                        glVertex3f(1,0,1);

                    glEnd();

                    glBegin(GL_LINE_LOOP);//BORDA DE CADA QUADRADO

                        glColor3f(0,0,0);
                        glVertex3f(0,0,0);
                        glVertex3f(0,0,1);
                        glVertex3f(1,0,1);
                        glVertex3f(1,0,0);

                    glEnd();

            glPopMatrix();

        }
        
    }

}

void coordMund(){//COORDENADAS DO MUNDO, X, Y e Z... AQUELAS LINHAS COLORIDAS

    glPushMatrix();

        glBegin(GL_LINES);
            glColor3f(1, 0, 0);
            glVertex3f(-1000, 0, 0);
            glVertex3f(1000, 0, 0);
            glColor3f(0, 1, 0);
            glVertex3f(0, -1000, 0);
            glVertex3f(0, 1000, 0);
            glColor3f(0, 0, 1);
            glVertex3f(0, 0, -1000);
            glVertex3f(0, 0, 1000);
        glEnd();

    glPopMatrix();

}