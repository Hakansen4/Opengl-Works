#ifndef GuiControl_hpp
#define GuiControl_hpp
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <functional>
class GLFWwindow;

enum SHAPETYPE
{
    SHAPE_SQUARE=0,
    SHAPE_CIRCLE=1,
    SHAPE_HEXAGON=2,
    SHAPE_TRIANGLE=3    
};

typedef std::function<void(SHAPETYPE)>  SekilOlusturFonksiyonu;
class GuiControl
{
public:
    GuiControl();
    void init(GLFWwindow* window);
    void createFrame();
    void createFrameItems();
    void draw();
    void setPos(glm::vec2* pos);
    void setAngle(float *angle);
    void setScale(glm::vec2* scale);
    void setColor(glm::vec4* color);
    void setColorActive(bool active);
    bool getColorActive();
    void setDeleted(bool isDeleted);
    bool getDeleted();
    SekilOlusturFonksiyonu tiklaSekilOlustur;
private:
    int secilenSekil;
    glm::vec2* vecPos;
    glm::vec2* Scale;
    glm::vec4* color;
    float*  angle;
    bool colorActive;
    bool isDeleted;
};

#endif