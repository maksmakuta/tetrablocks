#version 330 core
in vec2 f_tex;
in vec3 f_col;

uniform sampler2D u_image;
uniform int u_type;

out vec4 o_color;

#define u_buffer 0.5
#define u_gamma  1.0/32.0

void main() {
    if(u_type == 1){
        o_color = vec4(f_col,1.0);
    }else if(u_type == 2){
        o_color = texture2D(u_image,f_tex);
    }else if(u_type == 3){
        float dist = texture2D(u_image,f_tex).r;
        float alpha = smoothstep(u_buffer - u_gamma, u_buffer + u_gamma, dist);
        o_color = vec4(f_col,alpha);
    }else{
        discard;
    }
}
