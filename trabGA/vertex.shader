#version 330 core

layout (location = 0) in vec3 vPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 model_times_vertex = model * vec4(vPosition, 1.0);
	
	gl_Position = projection * view * model_times_vertex;
}