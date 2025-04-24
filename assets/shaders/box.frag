#version 330 core
in vec2 f_tex;

uniform sampler2D u_image;
uniform vec4 u_color;
uniform int u_type;

out vec4 f_color;

void main() {
    if(u_type == 1){
        f_color = u_color;
    }else if(u_type == 2){
        f_color = texture(u_image,f_tex);
    }else if(u_type == 3){
        f_color = vec4(u_color.xyz, u_color.w * texture(u_image,f_tex).r);
    }else{
        discard;
    }
}
