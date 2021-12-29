#include "Mesh2D.hpp"
#include "ShaderProgram.hpp"

#include <glm/gtx/matrix_transform_2d.hpp>
#include<glm/mat3x3.hpp>
Mesh2D::Mesh2D()
{
    position=glm::vec2(0.0f,0.0f);
    scale = glm::vec2(1.0f,1.0f);
    angle= 0.0f;
    isDeleted = false;
    colorActive = false;
    update();
}
bool Mesh2D::getColorActive()
{
    return colorActive;
}
void Mesh2D::setColorActive(bool active)
{
    colorActive = active;
}
void Mesh2D::setColor(const glm::vec4& color)
{
    this->color = color;
}
void Mesh2D::setPosition(const glm::vec2& pos)
{
    this->position = pos;
    update();
}
void Mesh2D::setScale(const glm::vec2& scale)
{
    this->scale = scale;
     update();
}
void Mesh2D::setAngle(float angle)
{
    this->angle = angle;
     update();
}
void Mesh2D::setDeleted(bool isDeleted)
{
    this->isDeleted = isDeleted;
}
bool Mesh2D::checkCollision(glm::vec2 mouse)
{
    if(this->scale.x>0 && this->scale.y>0)
    {
        bool collisionX = this->position.x + this->scale.x/2 >= mouse.x ;
        bool collisionY = this->position.y + this->scale.y/2 >= mouse.y ;
    
        bool collisionX1 = this->position.x - this->scale.x/2 <= mouse.x ;
        bool collisionY1 = this->position.y - this->scale.y/2 <= mouse.y ;

        return collisionX && collisionY &&  collisionY1 && collisionX1;
    }
    if(this->scale.x<0  &&  this->scale.y<0)
    {
        bool collisionX = this->position.x + this->scale.x/2 <= mouse.x ;
        bool collisionY = this->position.y + this->scale.y/2 <= mouse.y ;
    
        bool collisionX1 = this->position.x - this->scale.x/2 >= mouse.x ;
        bool collisionY1 = this->position.y - this->scale.y/2 >= mouse.y ;

        return collisionX && collisionY &&  collisionY1 && collisionX1;
    }
    if(this->scale.x<0  &&  this->scale.y>0)
    {
        bool collisionX = this->position.x + this->scale.x/2 <= mouse.x ;
        bool collisionY = this->position.y + this->scale.y/2 >= mouse.y ;
    
        bool collisionX1 = this->position.x - this->scale.x/2 >= mouse.x ;
        bool collisionY1 = this->position.y - this->scale.y/2 <= mouse.y ;

        return collisionX && collisionY &&  collisionY1 && collisionX1;
    }
    if(this->scale.x>0  &&  this->scale.y<0)
    {
        bool collisionX = this->position.x + this->scale.x/2 >= mouse.x ;
        bool collisionY = this->position.y + this->scale.y/2 <= mouse.y ;
    
        bool collisionX1 = this->position.x - this->scale.x/2 <= mouse.x ;
        bool collisionY1 = this->position.y - this->scale.y/2 >= mouse.y ;

        return collisionX && collisionY &&  collisionY1 && collisionX1;
    }
}
void Mesh2D::update()
{
    glm::mat3 mtxRotate = glm::rotate(glm::mat3(1),glm::radians(angle));
    glm::mat3 mtxTranslate = glm::translate(glm::mat3(1),position);
    glm::mat3 mtxScale = glm::scale(glm::mat3(1),scale);
    mtxWorld = mtxTranslate*mtxRotate*mtxScale;
}
void Mesh2D::rotate(float angle)
{
    if(this->angle>360)
    {
        this->angle=360-this->angle;
    }
    this->angle=angle;
    update();
}
void Mesh2D::draw(ShaderProgram& program)
{
    program.setMat3("uMtxTransform",mtxWorld);
    program.setVec4("uColor",color);
    vertexArrayObject.use();
    if(!isDeleted)
        vertexArrayObject.draw();
    vertexArrayObject.unuse();
}