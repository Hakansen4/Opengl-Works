#include "GuiControl.hpp"
#include<imgui/imgui.h>
#include<imgui/imgui_impl_glfw.h>
#include<imgui/imgui_impl_opengl3.h>
#include<glm/glm.hpp>
#include<iostream>

GuiControl::GuiControl()
{
    isDeleted = false;
}
void GuiControl::init(GLFWwindow* window)
{
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsClassic();
}
void GuiControl::createFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GuiControl::setAngle(float *angle)
{
    this->angle = angle;
}
void GuiControl::setPos(glm::vec2* pos)
{
    this->vecPos = pos;
}
void GuiControl::setScale(glm::vec2* scale)
{    
    this->Scale = scale;
}
void GuiControl::setColor(glm::vec4* color)
{
    this->color = color;
}
void GuiControl::setColorActive(bool active)
{
    colorActive = active;
}
bool GuiControl::getColorActive()
{
    return colorActive;
}
void GuiControl::setDeleted(bool isDeleted)
{
    this->isDeleted = isDeleted;
}
bool GuiControl::getDeleted()
{
    return isDeleted;
}
void GuiControl::createFrameItems()
{
    ImGui::Begin("imgui penceresi");
    ImGui::SliderFloat("dondurme",angle,0,360);
    ImGui::SliderFloat2("hareket",(float*)vecPos,-1.0f,1.0f);
    ImGui::SliderFloat2("Scale",(float*)Scale,-1.0f,2.0f);
    ImGui::ColorEdit3("Color",(float*)color);
    if(ImGui::Button("Kaplama"))
    {
        setColorActive(false);
    }
    ImGui::SameLine();
    if(ImGui::Button("Renk"))
    {
        setColorActive(true);
    }
    ImGui::SameLine();
    if(ImGui::Button("Sil"))
    {
        setDeleted(true);
    }
    ImGui::RadioButton("Kare",&secilenSekil,0);ImGui::SameLine();
    ImGui::RadioButton("Daire",&secilenSekil,1);ImGui::SameLine();
    ImGui::RadioButton("Altigen",&secilenSekil,2);ImGui::SameLine();
    ImGui::RadioButton("Ucgen",&secilenSekil,3); 

    if(ImGui::Button("Uret"))
    {
        tiklaSekilOlustur((SHAPETYPE)secilenSekil);
    }
    ImGui::End();
}
void GuiControl::draw()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
