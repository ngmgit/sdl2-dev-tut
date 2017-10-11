#version 130

in vec2 vertexPosition;

void main() {
    gl_Position.xy = vertexPosition;
    gl_Position.z = 0.0;
    gl_Position.w = 1.0;
}