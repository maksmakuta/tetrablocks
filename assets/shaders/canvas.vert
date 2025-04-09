#version 330 core

layout(location = 0) in vec2 pos;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec3 col;

uniform mat4 u_mat;

out vec2 f_tex;
out vec3 f_col;

void main() {
    f_tex = tex;
    f_col = col;
    gl_Position = u_mat * vec4(pos,0.0, 1.0);
}
