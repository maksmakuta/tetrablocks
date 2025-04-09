#version 330 core
in vec2 f_tex;
in vec3 f_col;

uniform sampler2D image;
uniform int type;

out vec4 o_color;

void main() {
    if(type == 1){
        o_color = vec4(f_col,1.0);
    }else if(type == 2){
        o_color = texture(image,f_tex);
    }else if(type == 3){
        o_color = vec4(f_col,texture(image,f_tex).r);
    }else{
        discard;
    }
}
