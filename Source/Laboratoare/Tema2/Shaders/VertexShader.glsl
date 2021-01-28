#version 330

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 object_color;
uniform int deformation;

// UNIFORM PROPERTIES
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_color;
layout(location = 2) in vec2 v_texture;
layout(location = 3) in vec3 v_normal;

out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture;
out vec3 frag_color;
 
float noise(float delta){
    return sin(delta + cos(delta * 90) * 100) * 0.5 + 0.5;
}

void main() {
	vec3 position = v_position ;
	frag_color = object_color;

    /* sunt pe un powerup, trebuie sa deformez playerul */
    if (deformation == 1) {
        float sum = 0.0;
	    float size = 1.0;
	    vec3 stp = v_position;
	    for (int i = 0; i < 100; i++) {
		    sum += noise(size * stp.z * stp.y) / size;
		    size *= 2.3;
	    }
	
	    position = v_position * sum;
	    frag_color =  mix(vec3(0.149, 0.141, 0.912), vec3(1.000, 0.833, 0.224), stp.xyz) * 0.7;

    /* culoarea normala a playerului */
    } else if (deformation == 2) {
        frag_color = mix(object_color, v_position, 0.3);

    /* altfel nu este player */
    } else {
	    frag_color = object_color ;
	    frag_position = v_position;
    }
   
    frag_normal = v_normal;
    frag_texture = v_texture;
		gl_Position = Projection * View * Model * vec4(position , 1.0);
		
}