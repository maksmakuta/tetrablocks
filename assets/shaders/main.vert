#version 330 core

layout(location = 0) in uint pos_type;
layout(location = 1) in uint col;
layout(location = 2) in uint tex;

uniform mat4 u_mat;

flat out uint f_type;
out vec4 f_col;
out vec2 f_tex;

void main() {
    f_type = (pos_type >> 30u) & 0x3u;
    vec2 pos = vec2(
        int((pos_type >> 15u) & 0x7FFFu) - (1 << 14),
        int(pos_type & 0x7FFFu) - (1 << 14)
    );

    f_col = vec4(
        float((col >> 16u) & 0xFFu) / 255.0,
        float((col >> 8u)  & 0xFFu) / 255.0,
        float((col >> 0u)  & 0xFFu) / 255.0,
        float((col >> 24u) & 0xFFu) / 255.0
    );

    f_tex = vec2(
        float((tex >> 16u) & 0xFFFFu) / float(0xFFFFu),
        float((tex >> 0u)  & 0xFFFFu) / float(0xFFFFu)
    );

    gl_Position = u_mat * vec4(pos, 0.0, 1.0);
}
