Load-3d-model-from-OBJ-file
===========================
1.Most online source codes for modelLoading sucks!!!!!! So I write my own... it also sucks but at least it works!
2.You will only need to include <glut.h> and <glm.hpp> besides all those "normal" head files you can always find in your compiling environment( like stdio.h etc)
3.It is used to load 3d object and its texture and its material...only for OBJ file.( I worked 3 days to write a 3ds loader but failed...)
4.Attention!:
            一。Obj files must be exported in the form that there are only 3 vertices in each face
            二。Remember to edit your mtl file , change every '\' into '\\' (for example, change 'c\ywang170' to 'c\\ywang170')
            三. Don't forget: All textures you use must be in form of 24 bit bmp!!!!!!!!!!!!
            ↑this is extremely important!!!!!!!!!!!!!!!!!!!!!!!
            
5.most comments are in Chinese and some of them all wrong but I just feel lazy to recorrect them. Sorry about that



Happy modelLoading!

在命令行打中文真是爽啊！
不知道能不能显示出来了呢…………
