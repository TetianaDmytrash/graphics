#version 330 core

out vec4 FragColor;
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  

uniform float time;
uniform vec3 rgb;

void main()
{
    float hue = ((cos(time*2)+3)/4);

    vec4 color = vec4(1,0,0,1);
    FragColor = vertexColor*hue;
} 