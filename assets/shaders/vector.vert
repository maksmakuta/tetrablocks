#version 330 core

layout(location = 0) in uint pos;
layout(location = 1) in uint col;

uniform mat4 proj;

out vec4 f_col;

void main() {
    float x = float(pos & 0xFFFFu);
    float y = float((pos >> 16) & 0xFFFFu);

    float r = float(col >> 16 & 0xFFu) / 255.f;
    float g = float(col >>  8 & 0xFFu) / 255.f;
    float b = float(col >>  0 & 0xFFu) / 255.f;
    float a = float(col >> 24 & 0xFFu) / 255.f;

    gl_Position = proj * vec4(x, y, 0.0, 1.0);
    f_col = vec4(r,g,b,a);
}
