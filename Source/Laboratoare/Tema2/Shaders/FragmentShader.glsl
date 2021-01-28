#version 330

in vec3 frag_position;
in vec3 frag_normal;
in vec3 frag_color;

uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform bool mix_textures; 

in vec2 texcoord;

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_normal;
layout(location = 2) out vec3 out_texture;

void main() {

	out_normal = vec4(frag_normal, 1.f);

	vec4 colour1 = texture2D(texture_1, texcoord);
	vec4 colour2 = texture2D(texture_2, texcoord);

	if (mix_textures == true) {
		
		out_color = mix(colour1, colour2, 0.5f);
	
	} else {
		// out_color = colour1;
	}
		out_color = mix(colour1, vec4(frag_color, 1), 0.2f);

	if (out_color.a < 0.5f)
	{
		discard;
	}

}