#version 120

uniform sampler2D diffuse;

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D diffuseSampler;
uniform vec3 lightDirection = vec3(-1,0,0);

void main()
{
	float lightModifier = clamp(dot(-lightDirection, normal0), 0.1, 1.0);
	gl_FragColor = texture2D(diffuse, texCoord0) * lightModifier;
}
