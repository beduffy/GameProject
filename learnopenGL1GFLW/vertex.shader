#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 n_eye;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main() {
	n_eye = (view * vec4 (normal, 0.0)).xyz;
	gl_Position =  projection * view * model * vec4 (position, 1.0);
}