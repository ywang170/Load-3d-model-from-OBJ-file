
#ifndef _MODEL_H_
#define _MODEL_H_

#include <windows.h>   
#include <stdio.h>   
#include<stdlib.h>
#include<vector>
#include<GL/glut.h>
#include<glm\glm.hpp>
#include <math.h>
#include"bmpload.h"



typedef struct point{
	unsigned int x,y,z;
}t_point;

typedef struct vertex{
	float x,y,z;
}t_vertex;

typedef struct normal{
	float x,y,z;
}t_normal;

typedef struct uvcoord{
	float u,v,wtf;
}t_uvcoord;

typedef struct surface{
	t_point point1, point2, point3;
}t_surface;

typedef struct object{
	std::vector<t_surface> surfaces;//构成这个物体的所有面
	int textureID;//别忘了创建纹理哦，这个是他用的纹理的ID(并非是在现实中，而是在textures数组中）
}t_object;

typedef struct texture{
	char * name;
	GLuint number;
	float Ns, Ni, d, Tr;
	int illum;
	glm::vec3 Ka, Kd, Ks, Ke, Tf;
	char * map_Ka,* map_Kd;
}t_texture;




class Obj
{

public:

bool loadObj(const char * path, const char * path2);
void draw();

private:
	FILE * file;//文件
	FILE * filem;//材质文件
	std::vector<t_vertex> vertices;
	std::vector<t_normal> normals;
	std::vector<t_uvcoord> uvcoords;

	std::vector<t_object> objects;
	std::vector<t_texture> textures;

	CBMPLoader realTexs[100];

	unsigned int dealWithTex(char * filename);
	void TextureGenerator();
	void GeneTex();

};
#endif