//PEDRO HENRIQUE BARRETO DOS SANTOS - 475626
#include <vector>
#include <gl/GL.h>
#include <iostream>
#include "ObjLoader.h"

glm::vec3 ObjLoader::getVertice(std::string s){//DADOS DO VERTICE DO OBJETO

	float x, y, z;//3 VERTICES
	sscanf(s.c_str(), "v %f %f %f", &x, &y, &z);//ELE VAI PROCURAR UM PADRAO, NO CASO 'V ', APARTIR DISSO ELE CONSIDERA OS 3 NUMEROS ADIANTE COMO VERTICE
	glm::vec3 result(x, y, z);//SALVANDO O VALOR
	
	return result;//RETORNANDO O VALOR

}

glm::vec3 ObjLoader::getNormal(std::string s){//DADOS DA NORMAL DO OBJETO

	float x, y, z;//3 NORMAIS
	sscanf(s.c_str(), "vn %f %f %f", &x, &y, &z);//ELE VAI PROCURAR UM PADRAO, NO CASO 'VN ', APARTIR DISSO ELE CONSIDERA OS 3 NUMEROS ADIANTE COMO NORMAIS
	glm::vec3 result(x, y, z);//SALVANDO O VALOR
	
	return result;//RETORNANDO O VALOR

}

face ObjLoader::getFace(std::string s){//DADOS DA FACE DO OBJETO

	int v1, v2, v3, f;//3 VERTICES E 1 FACE
	sscanf(s.c_str(), "f %d//%d %d//%d %d//%d", &v1, &f, &v2, &f, &v3, &f);//ELE VAI PROCURAR O PADRAO "F ", DEPOIS ELE VAI PEGAR OS VALORES, CASO O OBJETO TENHA O VERTICE DE TEXTURA, ELE NAO SERA CARREGADO, CASO ESTEJA TUDO CERTO, ELE CARREGA NORMALMENTE
	face result(v1, v2, v3, f);//SALVANDO O VALOR
	
	return result;//RETORNANDO O VALOR

}

void ObjLoader::loadOBJ(unsigned & id, const char * filePath){//CARREGANDO OBJETO

	std::vector<glm::vec3> vertices;//VETOR VERTICE
	std::vector<glm::vec3> normals;//VETOR NORMAL
	std::vector<face> faces;//VETOR FACE

	std::fstream arq(filePath);//VARIAVEL 'ARQ' COM VALOR DO ARQUIVO QUE SERA LIDO
	std::string line = "";//VARIAVEL 'LINE' COM O VALOR VAZIO, PARA QUE POSSA LER O ARQUIVO ENQUANDO HOUVER ALGO

	if (!arq.is_open()){//ELE VAI TENTAR ABRIR O ARQUIVO, CASO ELA NAO ABRA, ELE VAI INFORMAR O ERRO

		std::cout << "ERRO::Nao foi possivel abrir o arquivo " << filePath << "\n";//MENSAGEM DE ERRO AO LER

	}

	while (getline(arq, line)){//ENQUANTO TIVER DADOS, ELE CONTINUARA A LER

		if(line.find("v ") != std::string::npos){//PROCURANDO O PADRAO 'V '

			glm::vec3 tempVertice = getVertice(line);//CRIANDO UMA VARIAVEL E ATRIBUINDO A FUNCAO ANTERIOR MOSTRADA
			vertices.push_back(tempVertice);//ADICIONA AO VETOR VERTICE SEMPRE QUE É LIDO

		}else if(line.find("vn ") != std::string::npos){//PROCURANDO O PADRAO 'VN '

			glm::vec3 tempNormal = getNormal(line);//CRIANDO UMA VARIAVEL E ATRIBUINDO A FUNCAO ANTERIOR MOSTRADA
			normals.push_back(tempNormal);//ADICIONA AO VETOR NORMAL SEMPRE QUE É LIDO

		}else if(line.find("f ") != std::string::npos){//PROCURANDO O PADRAO 'F '

			face tempFace = getFace(line);//CRIANDO UMA VARIAVEL E ATRIBUINDO A FUNCAO ANTERIOR MOSTRADA
			faces.push_back(tempFace);//ADICIONA AO VETOR FACE SEMPRE QUE É LIDO

		}

	}

	id = glGenLists(1);//ID DO OBJETO

	glNewList(id, GL_COMPILE);//CRIANDO LISTA
	glPolygonMode(GL_FRONT, GL_FILL);//EXECUTANDO O ARQUIVO
	for (int i = 0; i < faces.size(); i++) {//VAI LER TODAS AS FACES

		unsigned index = faces[i].index - 1;

		int v1 = faces[i].vertice[0] - 1;//VERTICE 1, -1 POIS O VETOR COMEÇA DO 0
		int v2 = faces[i].vertice[1] - 1;//VERTICE 2, -1 POIS O VETOR COMEÇA DO 0
		int v3 = faces[i].vertice[2] - 1;//VERTICE 3, -1 POIS O VETOR COMEÇA DO 0

		glNormal3fv(&normals[index].x);
		glBegin(GL_TRIANGLE_STRIP);//CRIANDO O OBJETO EM TRIANGULOS
		glVertex3fv(&vertices[v1].x);//VERTICE 1
		glVertex3fv(&vertices[v2].x);//VERTICE 2
		glVertex3fv(&vertices[v3].x);//VERTICE 3
		glEnd();//FIM, FOI CRIADO UMA FACE, E ASSIM CONTINUARA ATE QUE O WHILE SEJA FALSO
		
	}

	glEndList();//ENCERRAR A LISTA CRIADA

}