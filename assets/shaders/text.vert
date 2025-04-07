#version 330 core

layout(location = 0) in uint pos;
layout(location = 1) in uint tex;

uniform mat4 proj;

out vec2 f_tex;

void main() {
    float x = float(pos & 0xFFFFu);
    float y = float((pos >> 16) & 0xFFFFu);

    float s = float(tex & 0xFFFFu) / 65565.0f;
    float t = float((tex >> 16) & 0xFFFFu) / 65565.0f;

    gl_Position = proj * vec4(x, y, 0.0, 1.0);
    f_tex = vec2(s,t);
}
