#include "GuiControl.hpp"
#include<imgui/imgui.h>
#include<imgui/imgui_impl_glfw.h>
#include<imgui/imgui_impl_opengl3.h>
#include<iostream>

GuiControl::GuiControl()
{

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

void GuiControl::setAngle(glm::vec3* angles)
{
    this->vecAngles = angles;
  
}
void GuiControl::setPos(glm::vec3* pos)
{
    this->vecPos = pos;
}
void GuiControl::createFrameItems()
{
    ImGui::Begin("imgui penceresi");
    ImGui::SliderFloat3("dondurme",(float*)vecAngles,0,360);
    ImGui::SliderFloat3("hareket",(float*)vecPos,-1.0f,1.0f);

    ImGui::RadioButton("CUBE",&secilenSekil,0);ImGui::SameLine();
    ImGui::RadioButton("PYRAMID",&secilenSekil,1);ImGui::SameLine();
    ImGui::RadioButton("CYLINDER",&secilenSekil,2);

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
