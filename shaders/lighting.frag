#version 330 core

#define MAX_LIGHTS 64

in vec2 texCoord;
in vec3 FragPos;

out vec4 FragColor;

struct Light {
	int enabled;
	vec2 pos;
	vec4 color;
};

uniform sampler2D tex0;
uniform Light lights[MAX_LIGHTS];

void main()
{
    vec4 texColor = texture(tex0, texCoord);

    float constant = 1.0;
    float linear = 0.09;
    float quadratic = 0.0032;

	vec3 ambient = vec3(0.1f);

	vec3 color = vec3(0);

	for (int i=0; i<lights.length(); i++)
	{
		float distance = length(lights[i].pos - FragPos.xy);

		float attenuation = 3.0 / (constant + linear * distance + quadratic * (distance * distance));

		color += (lights[i].color.rgb * attenuation) * texColor.rgb;
	}

	color += ambient*texColor.rgb;

	FragColor = vec4(clamp(color,0.0,0.9), texColor.a);
}