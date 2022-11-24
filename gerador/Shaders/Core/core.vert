#version 330 core

layout (location = 0) in vec3 values;
out vec3 VertColor;

uniform mat4 projection;

void main() {
	VertColor = vec3(0.0, 0.0, values.z);
    gl_Position = projection * vec4(values.x, values.y, 0.0, 1.0);
}
