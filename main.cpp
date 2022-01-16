//PEDRO HENRIQUE BARRETO DOS SANTOS - 475626
#include "funcoes/teclado.h"
#include "funcoes/objetos.h"
#include "funcoes/ObjLoader.h"
#include "funcoes/desenhosExtras.h"

void inicio(){

    glClearColor(0.8,0.8,0.8,1);
    glLineWidth(5);

    glEnable(GL_DEPTH_TEST);//NOCAO DE PROFUNDIDADE
    glEnable(GL_LIGHTING);//HABILITANDO LUZ
    glEnable(GL_COLOR_MATERIAL);//HABILITANDO COR AOS OBJETOS

    //CARREGANDO OS ARQUIVOS .OBJ OU .TXT
    ObjLoader::loadOBJ(cenario, "objetos/cenario.txt");
    ObjLoader::loadOBJ(mesa, "objetos/mesa.obj");
    ObjLoader::loadOBJ(decoracao, "objetos/decoracao.obj");
    ObjLoader::loadOBJ(cadeira, "objetos/cadeira.obj");
    ObjLoader::loadOBJ(talher, "objetos/talher.obj");

}

void resolucao(int widht, int height){}//SOMENTE PARA EVITAR DEFORMAR

void desenha(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glm::mat4 projecaoMatrix = glm::frustum(-1,1,-1,1,2,50);
        glLoadMatrixf(glm::value_ptr(projecaoMatrix));

        glMatrixMode(GL_MODELVIEW);
        glm::mat4 cameraMatrix = glm::lookAt( cam, {0,0,0} , glm::vec3(0,1,0));
        glLoadMatrixf(glm::value_ptr(cameraMatrix));

        luzes();

        //ATRIBUINDO OS DADOS DE LUZ DO OBJETO
        float matDiffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
        float matSpecular[] = {1.0f , 1.0f , 1.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_SPECULAR, matDiffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
        glMaterialf(GL_FRONT,GL_SHININESS , qunatLuz);
        
        //coordMund();
        chao();
        imprimirObjetos();

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
    glutReshapeFunc(resolucao);
    glutMainLoop();

}

//cd Trabalho-2-CG
//g++ main.cpp funcoes/ObjLoader.cpp -o main.exe -lopengl32 -lfreeglut
//start main.exe