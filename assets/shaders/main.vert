#version 460 core

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 tex;

uniform mat4 u_mat;

out vec2 f_tex;

void main() {
    gl_Position = u_mat * vec4(pos, 0.0, 1.0);
    f_tex = tex;
}
