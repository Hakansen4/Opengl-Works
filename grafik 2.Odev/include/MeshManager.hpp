#ifndef MeshManager_hpp
#define MeshManager_hpp
#include<map>
#include<string>
#include "VertexTypes.hpp"
#include "VertexArrayObject.hpp"
class Mesh2D;
class Mesh3D;
class VertexArrayObject;



class MeshManager
{
public:
    Mesh3D* createPyramid();
    Mesh3D* createCube();
    Mesh3D* createCylinder();
private:
    VertexArrayObject createTextureBuffers(TexturedVertexList& vertices,IndexList& indices);
    std::map<std::string,VertexArrayObject> vaoMap;
};


#endif