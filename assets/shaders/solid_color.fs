#version 330 core

// uniform mat4 model;
// uniform mat4 view;
// uniform mat4 projection;

uniform vec3 color = vec3(1.0f);

out vec4 fragColor;

void main() {
    fragColor = vec4(color, 1.0);
}
