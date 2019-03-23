#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 groupMatrix;

void main() {
    vec4 initialPosition = vec4(aPos, 1.0);
    vec4 transformedPosition = projectionMatrix * viewMatrix * groupMatrix * modelMatrix * initialPosition;

    gl_Position = transformedPosition;
    ourColor = aColor;
}
