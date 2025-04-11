#version 330 core
in vec2 f_tex;
in vec3 f_col;

uniform sampler2D image;
uniform int type;

out vec4 o_color;

#define u_buffer 0.5
#define u_gamma  1.0/32.0

void main() {
    if(type == 1){
        o_color = vec4(f_col,1.0);
    }else if(type == 2){
        o_color = texture(image,f_tex);
    }else if(type == 3){
        float dist = texture(image,f_tex).r;
        float alpha = smoothstep(u_buffer - u_gamma, u_buffer + u_gamma, dist);
        o_color = vec4(f_col,alpha);
    }else{
        discard;
    }
}
