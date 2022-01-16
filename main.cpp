#include "teclado.h"
#include "ObjLoader.h"

static unsigned cenario;
static unsigned mesa;
static unsigned decoracao;
static unsigned cadeira;
static unsigned talher;

void inicio(){

    glClearColor(0.8,0.8,0.8,1);
    glPointSize(30.0);
    glLineWidth(5);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

        glm::mat4x4 luz = {

            {0.1f, 0.1f, 0.1f, 1.0f},//ambient
            {0.8f, 0.8f, 0.8f, 1.0f},//difuse
            {1.0f, 1.0f, 1.0f, 1.0f},//specular
            {10.0f, 10.0f, 10.0f, 1.0f} //position
            
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

        P_cam = glm::vec3(0,2,8);
        V_cam = glm::vec3(P_cam.x + Z_cam.x, P_cam.y + Y_cam.y , P_cam.z + Z_cam.z);
        X_cam = glm::vec3(-1,0,0);
        Y_cam = glm::vec3(0,1,0);
        Z_cam = glm::vec3(0,0,-1);

        M_cam = glm::mat4(1);

        M_cam[0] = glm::vec4(X_cam,0) ; M_cam[1] = glm::vec4(Y_cam,0);
        M_cam[2] = glm::vec4(Z_cam,0) ; M_cam[3] = glm::vec4(P_cam,1);

        M_cam = glm::transpose(M_cam);

}

void quadrado(){

    glPushMatrix();

        glBegin(GL_TRIANGLE_STRIP);

            glColor3f(1,1,1);
            glVertex3f(0,0,0);
            glVertex3f(1,0,0);
            glVertex3f(0,0,1);
            glVertex3f(1,0,1);

        glEnd();

        glBegin(GL_LINE_LOOP);

            glColor3f(0,0,0);
            glVertex3f(0,0,0);
            glVertex3f(0,0,1);
            glVertex3f(1,0,1);
            glVertex3f(1,0,0);

        glEnd();

    glPopMatrix();

}

void chao(){

    for (int i = -30; i < 30; i++){

        for (int j = -30; j < 30; j++){
        
            glPushMatrix();

                glm::mat4 quad_T  = glm::translate(glm::mat4(1.0),glm::vec3(i,-0.4,j));
    
                glm::mat4 quad_M = quad_T;

                glMultMatrixf(glm::value_ptr(quad_M));

                quadrado();

            glPopMatrix();

        }
        
    }

}

void desenha(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glm::mat4 projecaoMatrix = glm::frustum(-1,1,-1,1,2,50);
        glLoadMatrixf(glm::value_ptr(projecaoMatrix));

        glMatrixMode(GL_MODELVIEW);
        glm::mat4 cameraMatrix = glm::lookAt( P_cam, {0,0,0} , glm::vec3(0,1,0));
        glLoadMatrixf(glm::value_ptr(cameraMatrix));

        float matSpecular[] = {1.0f , 1.0f , 1.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
        glMaterialf(GL_FRONT,GL_SHININESS , 80);

        chao();

        /*glPushMatrix();

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

        glPushMatrix();

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
                glVertex3f(P_cam.x + Z_cam.x, P_cam.y + Y_cam.y , P_cam.z + Z_cam.z);

            glEnd();

        glPopMatrix();*/

        glPushMatrix();

            glColor3f(0, 0.7, 0.7);

            glm::mat4 cen_T  = glm::translate(glm::mat4(1.0),glm::vec3(0,0,0));
            glm::mat4 cen_R  = glm::rotate(glm::mat4(1.0),glm::radians(-90.f),glm::vec3(0,1,0));
            glm::mat4 cen_S  = glm::scale(glm::mat4(1.0),glm::vec3(4,4,4));

            glm::mat4 cen_M = cen_T * cen_R * cen_S;

            glMultMatrixf(glm::value_ptr(cen_M));

            glCallList(cenario);

        glPopMatrix();

        glPushMatrix();

            glColor3f(0.81, 0.57, 0.38);

            glm::mat4 mesa_T  = glm::translate(glm::mat4(1.0),glm::vec3(0,0,0));
            glm::mat4 mesa_R  = glm::rotate(glm::mat4(1.0),glm::radians(0.f),glm::vec3(0,1,0));
            glm::mat4 mesa_S  = glm::scale(glm::mat4(1.0),glm::vec3(1,1,1));

            glm::mat4 mesa_M = mesa_T *  mesa_R * mesa_S;

            glMultMatrixf(glm::value_ptr(mesa_M));

            glCallList(mesa);

        glPopMatrix();

        glPushMatrix();

            glColor3f(0.59, 0, 0.11);

            glm::mat4 dec_T  = glm::translate(glm::mat4(1.0),glm::vec3(1.5,0.3,0.5));
            glm::mat4 dec_R  = glm::rotate(glm::mat4(1.0),glm::radians(-90.f),glm::vec3(0,1,0));
            glm::mat4 dec_R2 = glm::rotate(glm::mat4(1.0),glm::radians(-20.f),glm::vec3(0,0,1)); 
            glm::mat4 dec_S  = glm::scale(glm::mat4(1.0),glm::vec3(1,1,1));  

            glm::mat4 dec_M = dec_T *  dec_R * dec_R2 * dec_S;

            glMultMatrixf(glm::value_ptr(dec_M));

            glCallList(decoracao);

        glPopMatrix();

        glPushMatrix();

            glColor3f(0.6,0.6,0.6);

            glm::mat4 cad_T  = glm::translate(glm::mat4(1.0),glm::vec3(-0.6,-0.3,0.4));
            glm::mat4 cad_R  = glm::rotate(glm::mat4(1.0),glm::radians(0.f),glm::vec3(0,1,0));
            glm::mat4 cad_S  = glm::scale(glm::mat4(1.0),glm::vec3(1,1,1));

            glm::mat4 cad_M = cad_T * cad_R * cad_S;

            glMultMatrixf(glm::value_ptr(cad_M));

            glCallList(cadeira);

        glPopMatrix();

        glPushMatrix();

            glColor3f(0.6,0.6,0.6);

            glm::mat4 cad2_T  = glm::translate(glm::mat4(1.0),glm::vec3(-0.6,-0.3,-0.6));
            glm::mat4 cad2_R  = glm::rotate(glm::mat4(1.0),glm::radians(0.f),glm::vec3(0,1,0));
            glm::mat4 cad2_S  = glm::scale(glm::mat4(1.0),glm::vec3(1,1,1));

            glm::mat4 cad2_M = cad2_T * cad2_R * cad2_S;

            glMultMatrixf(glm::value_ptr(cad2_M));

            glCallList(cadeira);

        glPopMatrix();

        glPushMatrix();

            glColor3f(0.9,0.9,0.9);

                glm::mat4 tal_T  = glm::translate(glm::mat4(1.0),glm::vec3(0,0.6,-0.5));
                glm::mat4 tal_R  = glm::rotate(glm::mat4(1.0),glm::radians(180.f),glm::vec3(0,1,0));
                glm::mat4 tal_S  = glm::scale(glm::mat4(1.0),glm::vec3(0.7,0.7,0.7));

            glm::mat4 tal_M = tal_T *  tal_R * tal_S;

            glMultMatrixf(glm::value_ptr(tal_M));

            glCallList(talher);

        glPopMatrix();

        glPushMatrix();

            glColor3f(0.9,0.9,0.9);

                glm::mat4 tal2_T  = glm::translate(glm::mat4(1.0),glm::vec3(0,0.6,0.5));
                glm::mat4 tal2_R  = glm::rotate(glm::mat4(1.0),glm::radians(180.f),glm::vec3(0,1,0));
                glm::mat4 tal2_S  = glm::scale(glm::mat4(1.0),glm::vec3(0.7,0.7,0.7));

                glm::mat4 tal2_M = tal2_T *  tal2_R * tal2_S;

            glMultMatrixf(glm::value_ptr(tal2_M));

            glCallList(talher);

        glPopMatrix();

    glutSwapBuffers();

}

int main(int argc, char** argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(300,50);
    glutInitWindowSize(700,700);
    glutCreateWindow("Cenario - CG T2");

    inicio();
    glutKeyboardFunc(teclado);
    glutDisplayFunc(desenha);
    glutMainLoop();

}

//cd Trabalho-2-CG
//g++ main.cpp ObjLoader.cpp Vetor.cpp -o main.exe -lopengl32 -lfreeglut
//start main.exe
