#version 330 core
out vec4 fragColor;
in vec2 texCoords;
uniform sampler2D ourTexture;
uniform vec4 uColor;
uniform bool uChoose;
void main()
{
    if(uChoose)
    {
        fragColor = uColor;
    }
    else
    {
        fragColor = texture(ourTexture,texCoords);
    }
}