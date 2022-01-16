//PEDRO HENRIQUE BARRETO DOS SANTOS - 475626
#pragma once
#include <fstream>
#include <glm/glm.hpp>

struct face{//FUNCAO PARA DETECTAR FACE

	unsigned index;//face
	int vertice[3];//3 VERTICES

	face(int a, int b, int c, int d){//'A', 'B' e 'C' SAO VERTICES,'D' E A FACE DA JUNCAO DE 'A', 'B' e 'C'  

		vertice[0] = a; vertice[1] = b; 
		vertice[2] = c; index = d;

	}

};

namespace ObjLoader{//FUNCAO PARA LER O OBJETO

	glm::vec3 getVertice(std::string s);//FUNCAO DETECTAR VERTICE
	glm::vec3 getNormal(std::string s);//FUNCAO DETECTAR NORMAL
	face getFace(std::string s);//FUNCAO DETECTAR FACE

	void loadOBJ(unsigned& id, const char* filePath);//FUNCAO LER OBJETO, PRECISA DO NOME E DIRETORIO QUE ESTA O OBJETO
	
};