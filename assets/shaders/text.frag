#version 330 core
in vec2 f_tex;

uniform sampler2D u_image;

out vec4 o_color;

void main() {
    o_color = vec4(1,1,1,texture(u_image, f_tex).r);
}
