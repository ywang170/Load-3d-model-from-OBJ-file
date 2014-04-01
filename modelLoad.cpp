//所有贴图必须是bmp！！！！！！！！！！！！！！！！！！！！！！！而且注意了！导出obj文件时必须是三顶点组成面！！！！！！
//贴图的名字里不能有空格！并且贴图必须必须是用//作为路径引导而不是/



#include "modelLoad.h"
//#include"bmpload.h"

bool Obj::loadObj(const char * path, const char * path2)
{
	
	file = fopen(path, "rb");
	filem = fopen(path2, "rb");
	if(file == NULL || filem == NULL)
		{
			printf("f**k you man its not a file you f**king idiot!");
			return false;
	}
	TextureGenerator();
	
	unsigned int currentTexID;
	t_object * currentObject = NULL;
	while(1)
	{
		
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if(res == EOF)
		
			break;
		

		if(strcmp(lineHeader, "v") == 0)
		{
			//printf("v");
			if(currentObject != NULL)//if we just finished scan one object
			{
				currentObject->textureID = currentTexID;
				objects.push_back(*currentObject);
				delete currentObject;
				currentObject = NULL;
			}
			t_vertex temp;
			fscanf(file, "%f %f %f\n", &temp.x, &temp.y, &temp.z);
			vertices.push_back(temp);
		}
		else
		if(strcmp(lineHeader, "vt") == 0)
		{
			//printf("vt");
			t_uvcoord temp;
			fscanf(file, "%f %f %f\n", &temp.u, &temp.v, &temp.wtf);
			uvcoords.push_back(temp);
			//printf("%f %f %f\n", temp.u, temp.v, temp.wtf);
		}
		else
		if(strcmp(lineHeader, "vn") == 0)
		{
			//printf("vn");
			t_normal temp;
			fscanf(file, "%f %f %f\n", &temp.x, &temp.y, &temp.z);
			normals.push_back(temp);
			//printf("%f %f %f\n", temp.x, temp.y, temp.z);
		}
		else
		if( strcmp( lineHeader, "g" ) == 0 )//换行加创建新的object加拷贝贴图内容
		{
			//printf("g");
			currentObject = new t_object;
		}
		else
		if( strcmp( lineHeader, "usemtl" ) == 0 )//换行加创建新的object加拷贝贴图内容
		{
			//printf("g");
			char materialHeader[128];
			currentObject = new t_object;
			fscanf(file, "%s\n", materialHeader);//读入纹理信息
			currentTexID = dealWithTex(materialHeader);//处理纹理信息，让currentObject的textureID得到得到信息

		}
		else
		if( strcmp( lineHeader, "f" ) == 0 )
		{
			//printf("f");						
			t_surface temp;
			fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &temp.point1.x,&temp.point1.y,&temp.point1.z,
														 &temp.point2.x,&temp.point2.y,&temp.point2.z,
														 &temp.point3.x,&temp.point3.y,&temp.point3.z);
			
			/*printf("%d/%d/%d %d/%d/%d %d/%d/%d\n", temp.point1.x,temp.point1.y,temp.point1.z,
														 temp.point2.x,temp.point2.y,temp.point2.z,
														temp.point3.x,temp.point3.y,temp.point3.z);*/
			currentObject->surfaces.push_back(temp);
			
		}
	}
	currentObject->textureID = currentTexID;
	objects.push_back(*currentObject);
	delete currentObject;
	//fclose(file);
	return true;
}

	void Obj::draw()
	{
		
		//printf("%f", vertices[1].z);
		for(int i = 0; i< objects.size(); i++)
		{
			
			glBindTexture(GL_TEXTURE_2D, textures[objects[i].textureID].number);
			for(int j = 0; j < objects[i].surfaces.size(); j ++)
			{
				glPushMatrix();

				GLfloat ambient[] = {textures[objects[i].textureID].Ka.x,
									textures[objects[i].textureID].Ka.y,
									textures[objects[i].textureID].Ka.z, 1.0f};
			GLfloat diffuse[] = {textures[objects[i].textureID].Kd.x,
									textures[objects[i].textureID].Kd.y,
									textures[objects[i].textureID].Kd.z, 1.0f};;
			GLfloat specular[] = {textures[objects[i].textureID].Ks.x,
									textures[objects[i].textureID].Ks.y,
									textures[objects[i].textureID].Ks.z, 1.0f};;
			glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
			if(textures[objects[i].textureID].illum != 1)
			glMaterialfv(GL_FRONT, GL_SPECULAR,specular);
			float temp;
			
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBegin(GL_TRIANGLES);
			glNormal3f(normals[objects[i].surfaces[j].point1.z-1].x,
					   normals[objects[i].surfaces[j].point1.z-1].y,
					   normals[objects[i].surfaces[j].point1.z-1].z);
			temp = uvcoords[objects[i].surfaces[j].point1.y-1].wtf;
			glTexCoord2f(uvcoords[objects[i].surfaces[j].point1.y-1].u / temp ,
					   uvcoords[objects[i].surfaces[j].point1.y-1].v / temp);
			glVertex3f(vertices[objects[i].surfaces[j].point1.x-1].x,
					   vertices[objects[i].surfaces[j].point1.x-1].y,
					   vertices[objects[i].surfaces[j].point1.x-1].z);
			//printf("\\%f\\ ",objects[i].surfaces[j].point1.y);

			glNormal3f(normals[objects[i].surfaces[j].point2.z-1].x,
					   normals[objects[i].surfaces[j].point2.z-1].y,
					   normals[objects[i].surfaces[j].point2.z-1].z);
			temp =  uvcoords[objects[i].surfaces[j].point2.y-1].wtf;
			glTexCoord2f(uvcoords[objects[i].surfaces[j].point2.y-1].u / temp,
					   uvcoords[objects[i].surfaces[j].point2.y-1].v / temp);
			glVertex3f(vertices[objects[i].surfaces[j].point2.x-1].x,
					   vertices[objects[i].surfaces[j].point2.x-1].y,
					   vertices[objects[i].surfaces[j].point2.x-1].z);
			//printf("\\%f\\ ",objects[i].surfaces[j].point2.y);

			glNormal3f(normals[objects[i].surfaces[j].point3.z-1].x,
					   normals[objects[i].surfaces[j].point3.z-1].y,
					   normals[objects[i].surfaces[j].point3.z-1].z);
			temp = uvcoords[objects[i].surfaces[j].point3.y-1].wtf;
			glTexCoord2f(uvcoords[objects[i].surfaces[j].point3.y-1].u / temp,
					   uvcoords[objects[i].surfaces[j].point3.y-1].v / temp);
			glVertex3f(vertices[objects[i].surfaces[j].point3.x-1].x,
					   vertices[objects[i].surfaces[j].point3.x-1].y,
					   vertices[objects[i].surfaces[j].point3.x-1].z);
			//printf("\\%f\\ ",objects[i].surfaces[j].point3.y);
					   
			glEnd();
			glPopMatrix();
	
			}
		}
		
	}

	unsigned int Obj::dealWithTex(char * name)
	{
		for(int i = 0; i< textures.size();i++)
		{
			if(strcmp(name, textures[i].name) == 0)
			return i;
		}
				
	}

	void Obj::TextureGenerator()
	{
		t_texture * currentTex = NULL;

		while(1)
	{
		char lineHeader[128];
		int res = fscanf(filem, "%s", lineHeader);

		if(res == EOF)
			break;
		if(strcmp(lineHeader, "newmtl") == 0)
		{
			//printf("newmtl");
			if(currentTex != NULL)
			{
				textures.push_back(*currentTex);//除了初始化的那个每个都要装进去
				delete currentTex;
				currentTex = NULL;
			}
			currentTex = new t_texture;
			currentTex->name = (char*)malloc(sizeof(char)*32);
			fscanf(filem, "%s\n",currentTex->name); 
		}
		else
		if(strcmp(lineHeader, "Ns") == 0)
		{
			//printf("Ns");
			fscanf(filem, "%f\n",&currentTex->Ns); 
		}
		else
		if(strcmp(lineHeader, "Ni") == 0)
		{
			//printf("Ni");
			fscanf(filem, "%f\n",&currentTex->Ni); 
		}
		else
		if(strcmp(lineHeader, "d") == 0)
		{
			//printf("d");
			fscanf(filem, "%f\n",&currentTex->d); 
		}
		else
		if(strcmp(lineHeader, "Tr") == 0)
		{
			//printf("Tr");
			fscanf(filem, "%f\n",&currentTex->Tr); 
		}
		else
		if(strcmp(lineHeader, "illum") == 0)
		{
			//printf("illum");
			fscanf(filem, "%d\n",&currentTex->illum); 
		}
		else
		if(strcmp(lineHeader, "Ka") == 0)
		{
			//printf("Ka");
			fscanf(filem, "%f%f%f\n",&currentTex->Ka.x, &currentTex->Ka.y, &currentTex->Ka.z ); 

		}
		else
		if(strcmp(lineHeader, "Tf") == 0)
		{
			//printf("Tf");
			fscanf(filem, "%f%f%f\n",&currentTex->Tf.x, &currentTex->Tf.y, &currentTex->Tf.z ); 

		}
		else
		if(strcmp(lineHeader, "Kd") == 0)
		{
			//printf("Kd");
			fscanf(filem, "%f%f%f\n",&currentTex->Kd.x, &currentTex->Kd.y, &currentTex->Kd.z ); 

		}
		else
		if(strcmp(lineHeader, "Ks") == 0)
		{
			//printf("Ks");
			fscanf(filem, "%f%f%f\n",&currentTex->Ks.x, &currentTex->Ks.y, &currentTex->Ks.z ); 

		}
		else
		if(strcmp(lineHeader, "Ke") == 0)
		{
			fscanf(filem, "%f%f%f\n",&currentTex->Ke.x, &currentTex->Ke.y, &currentTex->Ke.z ); 

		}
		else
		if(strcmp(lineHeader, "map_Ka") == 0)
		{
			//printf("mKa");
			currentTex->map_Ka = (char*)malloc(sizeof(char)*256);
			fscanf(filem, "%s\n",currentTex->map_Ka); 
			//printf("%s\n", currentTex->map_Ka);
		}
		else
		if(strcmp(lineHeader, "map_Kd") == 0)
		{
			//printf("mKd");
			currentTex->map_Kd = (char*)malloc(sizeof(char)*256);
			fscanf(filem, "%s\n",currentTex->map_Kd); 
		}
	}
		textures.push_back(*currentTex);//全读完之后还剩一个没装进去
		delete currentTex;

		
		GeneTex();	//生成贴图们
			

	}
	
	void Obj::GeneTex()
	{
		
		for(int i = 0; i< textures.size(); i++)
		{
			
			realTexs[i].LoadBMPFile(textures[i].map_Ka);
			textures[i].number = realTexs[i].ID;
		}
		
		
		
	}