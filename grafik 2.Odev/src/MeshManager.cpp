#include "MeshManager.hpp"
#include "Mesh2D.hpp"
#include "Mesh3D.hpp"
#include<glm/glm.hpp>
#include<glad/glad.h>

Mesh3D* MeshManager::createCube()
{
    VertexArrayObject vao;

    if(!vaoMap.count("cube"))
    {
        unsigned int vertexArrayObjectId;
        int vertexCount = 24;
    
        TexturedVertexList vertices(vertexCount);
        int faceCount= 6;
        IndexList   indices(faceCount*6); 
        glm::vec3 v[8];
        v[0] = glm::vec3(-0.5,0.5,0.5);   
        v[1] = glm::vec3(0.5,0.5,0.5);
        v[2] = glm::vec3(0.5,-0.5,0.5);
        v[3] = glm::vec3(-0.5,-0.5,0.5);
        v[4] = glm::vec3(-0.5,0.5,-0.5);   
        v[5] = glm::vec3(0.5,0.5,-0.5);
        v[6] = glm::vec3(0.5,-0.5,-0.5);
        v[7] = glm::vec3(-0.5,-0.5,-0.5);
        //ön yüz
        vertices[0].pos = v[0]; vertices[0].tex= glm::vec2(0.0,1.0);
        vertices[1].pos = v[1]; vertices[1].tex= glm::vec2(1.0,1.0);
        vertices[2].pos = v[2]; vertices[2].tex= glm::vec2(1.0,0.0);
        vertices[3].pos = v[3]; vertices[3].tex= glm::vec2(0.0,0.0);
        //sağ
        vertices[4].pos = v[1]; vertices[4].tex= glm::vec2(0.0,1.0);
        vertices[5].pos = v[5]; vertices[5].tex= glm::vec2(1.0,1.0);
        vertices[6].pos = v[6]; vertices[6].tex= glm::vec2(1.0,0.0);
        vertices[7].pos = v[2]; vertices[7].tex= glm::vec2(0.0,0.0);  

        //ust
        vertices[8].pos  = v[4]; vertices[8].tex= glm::vec2(0.0,1.0);
        vertices[9].pos  = v[5]; vertices[9].tex= glm::vec2(1.0,1.0);
        vertices[10].pos = v[1]; vertices[10].tex= glm::vec2(1.0,0.0);
        vertices[11].pos = v[0]; vertices[11].tex= glm::vec2(0.0,0.0);   

        //sol
        vertices[12].pos = v[4]; vertices[12].tex= glm::vec2(0.0,1.0);
        vertices[13].pos = v[0]; vertices[13].tex= glm::vec2(1.0,1.0);
        vertices[14].pos = v[3];  vertices[14].tex= glm::vec2(1.0,0.0);
        vertices[15].pos = v[7];  vertices[15].tex= glm::vec2(0.0,0.0);  

        //alt
        vertices[16].pos = v[7];  vertices[16].tex= glm::vec2(0.0,1.0);
        vertices[17].pos = v[6];  vertices[17].tex= glm::vec2(1.0,1.0);
        vertices[18].pos = v[2];  vertices[18].tex= glm::vec2(1.0,0.0);
        vertices[19].pos = v[3];  vertices[19].tex= glm::vec2(0.0,0.0);   
        //arka
        vertices[20].pos = v[4];  vertices[20].tex= glm::vec2(0.0,1.0);
        vertices[21].pos = v[5];  vertices[21].tex= glm::vec2(1.0,1.0);
        vertices[22].pos = v[6];  vertices[22].tex= glm::vec2(1.0,0.0);
        vertices[23].pos = v[7];  vertices[23].tex= glm::vec2(0.0,0.0);   

        for(int i=0;i<faceCount;i++)
        {
            int index= i;
            indices[i*6]   =index*4; indices[i*6+1] =index*4+1; indices[i*6+2] =index*4+2;
            indices[i*6+3] =index*4; indices[i*6+4] =index*4+2; indices[i*6+5] =index*4+3;
        }
        vao = createTextureBuffers(vertices,indices);
        vaoMap["cube"] = vao;            
    }
    else
    {
        vao = vaoMap["box"];
    }
    Mesh3D *mesh= new Mesh3D;
    mesh->vertexArrayObject = vao;

    return mesh;
}
Mesh3D* MeshManager::createPyramid()
{
    VertexArrayObject vao;
    if(!vaoMap.count("pyramid"))
    {
        unsigned int vertexArrayObjectId;
        int vertexCount= 16;

        TexturedVertexList vertices(vertexCount);
        int TriangleCount= 6;
        IndexList   indices(6*3); 
        glm::vec3 v[5];
        v[0] = glm::vec3(-0.5f,-0.5f,-0.5f);
        v[1] = glm::vec3(-0.5f,-0.5f,0.5f);
        v[2] = glm::vec3(0.5f,-0.5f,0.5f);
        v[3] = glm::vec3(0.5f,-0.5f,-0.5f);
        v[4] = glm::vec3(0.0f,0.5f,0.0f);
        
        vertices[0].pos = glm::vec3(-0.5f,-0.5f,-0.5f);     vertices[0].tex = glm::vec2(0.0f,0.0f);//Arka
        vertices[1].pos = glm::vec3(0.5f,-0.5f,-0.5f);      vertices[1].tex = glm::vec2(1.0f,0.0f);
        vertices[2].pos = glm::vec3(0.0f,0.5f,0.0f);        vertices[2].tex = glm::vec2(0.5f,1.0f);

        vertices[3].pos = glm::vec3(-0.5f,-0.5f,0.5f);      vertices[3].tex = glm::vec2(0.0f,0.0f);//On
        vertices[4].pos = glm::vec3(0.5f,-0.5f,0.5f);       vertices[4].tex = glm::vec2(1.0f,0.0f);
        vertices[5].pos = glm::vec3(0.0f,0.5f,0.0f);        vertices[5].tex = glm::vec2(0.5f,1.0f);

        vertices[6].pos = glm::vec3(-0.5f,-0.5f,-0.5f);     vertices[6].tex = glm::vec2(0.0f,0.0f);//sol
        vertices[7].pos = glm::vec3(-0.5f,-0.5f,0.5f);      vertices[7].tex = glm::vec2(1.0f,0.0f);
        vertices[8].pos = glm::vec3(0.0f,0.5f,0.0f);        vertices[8].tex = glm::vec2(0.5f,1.0f);

        vertices[9].pos = glm::vec3(0.5f,-0.5f,-0.5f);      vertices[9].tex = glm::vec2(0.0f,0.0f);//sag
        vertices[10].pos = glm::vec3(0.5f,-0.5f,0.5f);      vertices[10].tex = glm::vec2(1.0f,0.0f);
        vertices[11].pos = glm::vec3(0.0f,0.5f,0.0f);       vertices[11].tex = glm::vec2(0.5f,1.0f);

        vertices[12].pos = glm::vec3(-0.5f,-0.5f,-0.5f);    vertices[12].tex = glm::vec2(0.0f,1.0f);
        vertices[13].pos = glm::vec3(-0.5f,-0.5f,0.5f);     vertices[13].tex = glm::vec2(0.0f,0.0f);
        vertices[14].pos = glm::vec3(0.5f,-0.5f,0.5f);      vertices[14].tex = glm::vec2(1.0f,0.0f);
        vertices[15].pos = glm::vec3(0.5f,-0.5f,-0.5f);     vertices[15].tex = glm::vec2(1.0f,1.0f);

        indices[0] = 0;     indices[1] = 1;     indices[2] = 2;
        indices[3] = 3;     indices[4] = 4;     indices[5] = 5;
        indices[6] = 6;     indices[7] = 7;     indices[8] = 8;
        indices[9] = 9;     indices[10] = 10;     indices[11] = 11;
        indices[12] = 12;     indices[13] = 13;     indices[14] = 14;
        indices[15] = 12;     indices[16] = 14;     indices[17] = 15;
        
        vao = createTextureBuffers(vertices,indices);
        vaoMap["pyramid"] = vao;
    }
    else
    {
        vao = vaoMap["pyramid"];
    }
    Mesh3D *mesh= new Mesh3D;
    mesh->vertexArrayObject = vao;

    return mesh;
}
Mesh3D* MeshManager::createCylinder()
{
    VertexArrayObject vao;
    if(!vaoMap.count("cylinder"))
    {
        
        int circlevertexCount = 360/3.6f;
        int vertexCount= circlevertexCount*4;
        float angle = 3.6f;
        float halfRadius = 0.5f;

        TexturedVertexList vertices(vertexCount);
        IndexList   indices; 
        for(int i=0;i<circlevertexCount;i++)
        {
            TexturedVertex vertex;
            float nextAngle = glm::radians(i*angle);
            vertex.pos.x = glm::cos(nextAngle)*halfRadius;
            vertex.pos.y = glm::sin(nextAngle)*halfRadius;
            vertex.pos.z = 0.5f;

            vertex.tex.x = glm::cos(nextAngle)*0.5f+0.5f;
            vertex.tex.y = glm::sin(nextAngle)*0.5f+0.5f;   
            vertices[i]= vertex;

            vertex.tex.x = i/100.0f;
            vertex.tex.y = 0.0f;
            vertices[i+circlevertexCount*2] = vertex;

            //Alt Taraf
            vertex.pos.z = -0.5f;
            vertex.tex.x = glm::cos(nextAngle)*0.5f+0.5f;
            vertex.tex.y = glm::sin(nextAngle)*0.5f+0.5f;
            vertices[i+circlevertexCount] = vertex;

            vertex.tex.x = i/100.0f;
            vertex.tex.y = 1.0f;
            vertices[i+circlevertexCount*3] = vertex;
        }
        for(int i=0;i<circlevertexCount-2;i++)
        {   
            //Ön Yüz 
            indices.push_back(0);
            indices.push_back(i+1);
            indices.push_back(i+2);
            //Arka yüz
            indices.push_back(circlevertexCount);
            indices.push_back(circlevertexCount+i+1);
            indices.push_back(circlevertexCount+i+2);

        }
        int startIndex = circlevertexCount*2;
        int currentIndex = startIndex;
        for(int i=0;i<circlevertexCount-1;i++)
        {
            indices.push_back(currentIndex);
        indices.push_back(currentIndex+circlevertexCount);
        indices.push_back(currentIndex+circlevertexCount+1);

        indices.push_back(currentIndex);
        indices.push_back(currentIndex+circlevertexCount+1);
        indices.push_back(currentIndex+1);

         currentIndex++;
        }
        indices.push_back(currentIndex);
    indices.push_back(currentIndex+circlevertexCount);
    indices.push_back(currentIndex+1);

    indices.push_back(currentIndex);
    indices.push_back(currentIndex+1);
    indices.push_back(startIndex);    
        vao = createTextureBuffers(vertices,indices);
        vaoMap["cylinder"] = vao;
    }
    else
    {
        vao = vaoMap["cylinder"];
    }
    Mesh3D *mesh= new Mesh3D;
    mesh->vertexArrayObject = vao;

    return mesh;
}
VertexArrayObject MeshManager::createTextureBuffers(TexturedVertexList& vertices,IndexList& indices)
{
    unsigned int vertexBufferId;
    unsigned int vertexArrayObjectId;
    unsigned int indexBufferId;

    glGenVertexArrays(1,&vertexArrayObjectId);
    glBindVertexArray(vertexArrayObjectId);

    glGenBuffers(1,&vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER,sizeof(TexturedVertex)*vertices.size(),&vertices[0],GL_STATIC_DRAW);

    glGenBuffers(1,&indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*indices.size(),&indices[0],GL_STATIC_DRAW);


    glVertexAttribPointer(0,3,GL_FLOAT,false,sizeof(TexturedVertex),0);
    glVertexAttribPointer(1,2,GL_FLOAT,false,sizeof(TexturedVertex),(const void*)(sizeof(float)*3));
    glEnableVertexAttribArray(0);  
    glEnableVertexAttribArray(1); 


    VertexArrayObject vao;
    vao.indexCount = indices.size();
    vao.id= vertexArrayObjectId;
    return vao;
}