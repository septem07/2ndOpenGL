#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColour;
out vec4 vertexColour;
void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	vertexColour = vec4(aColour.x,aColour.y +0.2,aColour.z, 1.0);
}  