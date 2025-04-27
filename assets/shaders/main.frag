#version 330 core

flat in uint f_type;
in vec4 f_col;
in vec2 f_tex;

uniform sampler2D u_image;

out vec4 f_color;

void main() {
    if(f_type == 1u){
        f_color = f_col;
    }else if(f_type == 2u){
        f_color = texture(u_image,f_tex);
    }else if(f_type == 3u){
        f_color = vec4(f_col.rgb, texture(u_image,f_tex).r);
    }else{
        discard;
    }
}
