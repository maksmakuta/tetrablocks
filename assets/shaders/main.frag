#version 460 core

flat in uint f_type;
in vec4 f_col;
in vec2 f_tex;

uniform sampler2D u_image;

out vec4 f_color;

void main() {
    if(f_type == 1){
        f_color = f_col;
    }else if(f_type == 2){
        f_color = texture(u_image,f_tex);
    }else if(f_type == 3){
        f_color = vec4(f_col.rgb, f_col.a * texture(u_image,f_tex).r);
    }else{
        discard;
    }
}
