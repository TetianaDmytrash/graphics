#version 330 core

layout (location = 0) in vec3 aPos; // the position variable has attribute position 0

out vec4 vertexColor; // specify a color output to the fragment shader

uniform float time;
uniform vec3 RGB;
uniform mat4 modelView;
uniform mat4 modelProj;

const float PI = 3.1415926535897932384626433832795;

void main()
{
    gl_Position = modelProj*modelView*vec4(aPos.x*cos(time),aPos.y*cos(time),aPos.z*cos(time), 1.0); // see how we directly give a vec3 to vec4's constructor
    if(gl_VertexID % 2 == 0){
        vertexColor = vec4((sin(time)+1)/2, (cos(time)+1)/2, (cos(time)+1)/2, 1.0); // set the output variable to a dark-red color
    }
    else{
        vertexColor = vec4(RGB/2, 1.0); // set the output variable to a dark-red color
    }
}