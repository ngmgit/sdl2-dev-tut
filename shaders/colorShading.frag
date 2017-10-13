#version 130

in vec2 fragmentPosition;
in vec4 fragmentColor;

out vec4 outColor;

uniform float time;

void main() {
    outColor = vec4(fragmentColor.r * ( 1.0 * (cos(time + fragmentPosition.x) + 1.0) * 0.5),
                    fragmentColor.g * ( 1.0 * (cos(time + fragmentPosition.y) + 1.0) * 0.5),
                    fragmentColor.b * ( 1.0 * (cos(time + fragmentPosition.x * 0.4) + 1.0) * 0.5),
                    0.0);
}
