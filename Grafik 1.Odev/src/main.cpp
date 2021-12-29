
#define STB_IMAGE_IMPLEMENTATION
#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <vector>
#include <string>
#include <stb/stb_image.h>
#include "Timer.hpp"
#include "FileLoader.hpp"
#include "ShaderProgram.hpp"
#include "GuiControl.hpp"
#include "glm/gtx/matrix_transform_2d.hpp"
#include "VertexTypes.hpp"
#include "MeshManager.hpp"
#include "Mesh2D.hpp"
using namespace std;
ShaderProgram program;
GuiControl imguiWindow;
unsigned int textureId;
Timer timer;

MeshManager meshManager;
Mesh2D *c[100];
unsigned int objectCount = 0;
unsigned int activeIndex=0;
unsigned int silinIndexler[100];
unsigned int silinenCounter=0;

glm::vec2 vectorMove[100];
glm::vec2 Scale[100];
float Angle[100];
glm::vec4 color[100];
bool colorActive[100];
bool isActive=false;
void sekilOlustur(SHAPETYPE type)
{
    if(type==SHAPE_CIRCLE)
    {
        c[objectCount] = meshManager.createCircle();
        activeIndex = objectCount;
        objectCount++;
    }
    if(type==SHAPE_SQUARE)
    {
        c[objectCount] = meshManager.createSquare();
        activeIndex = objectCount;
        objectCount++;
    }
    if(type==SHAPE_TRIANGLE)
    {
        c[objectCount] = meshManager.createTriangle();
        activeIndex = objectCount;
        objectCount++;
    }    
    if(type == SHAPE_HEXAGON)
    {
        c[objectCount] = meshManager.createHexagon();
        activeIndex = objectCount;
        objectCount++;
    }
}
unsigned int loadTexture(std::string fileName)
{
    unsigned int id;
    glGenTextures(1,&id);
    glBindTexture(GL_TEXTURE_2D,id);
    int width,height,nrChannels;
    auto data = stbi_load(fileName.c_str(),&width,&height,&nrChannels,0);
  
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(data);
    return id;
}
void initScene(GLFWwindow* window)
{
    program.attachShader("./shaders/vertex.glsl",GL_VERTEX_SHADER);
    program.attachShader("./shaders/fragment.glsl",GL_FRAGMENT_SHADER);
    program.link();
    program.addUniform("uMtxTransform");
    program.addUniform("uColor");
    program.addUniform("uChoose");

    
    //c1= meshManager.createCircle();

    textureId =loadTexture("images/brick.jpg");

    imguiWindow.init(window);

    timer.start();
      
}
void acitvateObject(unsigned int index)
{
    imguiWindow.setPos(&vectorMove[index]);
    imguiWindow.setAngle(&Angle[index]);
    imguiWindow.setScale(&Scale[index]);
    imguiWindow.setColor(&color[index]);
    if(imguiWindow.getDeleted())
    {
        c[index]->setDeleted(true);
        imguiWindow.setDeleted(false);
    }
    colorActive[index] = imguiWindow.getColorActive();
    imguiWindow.tiklaSekilOlustur= sekilOlustur;
}
void draw()
{   
    double elapsedTime = timer.elapsedSeconds();
    if(elapsedTime<0.016)
    {
        unsigned int miliseconds = (0.016-elapsedTime)*1000;

        timer.sleep(miliseconds);
    }
    glClearColor(0.3,0.4,0.3,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    program.use();   
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,textureId);  
    for(int i=0;i<objectCount;i++)
    {
        c[i]->rotate(Angle[i]);
        c[i]->setPosition(vectorMove[i]);
        c[i]->setScale(Scale[i]);
        c[i]->setColor(color[i]);
        c[i]->setColorActive(colorActive[i]);
        program.setBool("uChoose",c[i]->getColorActive());
        c[i]->draw(program);
    }  
}
void MouseClick(GLFWwindow* window)
{
    GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
    glfwSetCursor(window, cursor);
    double xpos,ypos;
    glfwGetCursorPos(window,&xpos,&ypos);
    xpos = (xpos/250)-1;
    ypos = (ypos/-250)+1;
    glm::vec2 mouse(xpos,ypos);
    int state = glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT);
    if(state == GLFW_PRESS)
    {
        if(objectCount > 0)
        {
            for(int i= objectCount-1;i>=0;i--)
            {
                if(c[i]->checkCollision(mouse))
                {
                    activeIndex = i;
                    break;
                }    
            }
        }
    }

}
int main()
{
    if(!glfwInit())    return -1;

    GLFWwindow* window = glfwCreateWindow(500,500,"ilk program",0,0);
    if(window==nullptr)
    {
        std::cout<<"pencere olusmadi"<<std::endl;
        glfwTerminate();
        return -1;        
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout<<"glad yukleme hatasi"<<std::endl;
    }
    
    initScene(window); 
   
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        MouseClick(window);
        acitvateObject(activeIndex);
        draw();
        imguiWindow.createFrame();
        imguiWindow.createFrameItems();
        imguiWindow.draw();
        glfwSwapBuffers(window);
    }




    
}