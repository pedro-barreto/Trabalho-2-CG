#pragma once
#include<iostream>
#include<gl/GL.h>
#include<fstream>
#include<sstream>
#include "Vetor.h"

struct face{

	unsigned index;
	int vertice[3];

	face(int a, int b, int c, int d){

		vertice[0] = a; vertice[1] = b; 
		vertice[2] = c; index = d;

	}

};

namespace ObjLoader{

	vec3 getVertice(std::string s);
	vec3 getNormal(std::string s);
	face getFace(std::string s);

	void loadOBJ(unsigned& id, const char* filePath);
	
};