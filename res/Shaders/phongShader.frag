#version 120

uniform sampler2D diffuse;

varying vec2 texCoord0;
varying vec3 normal0;

uniform vec3 lightDirection = vec3(-1,0,0);
uniform vec3 amb = vec3(1,1,1);
uniform vec3 dif = vec3(1,1,1);
uniform vec3 spec = vec3(1,1,1);
uniform float shiny = 0.75f;

uniform vec3 lightPos;
uniform vec3 spotDirection;

void main()
{
	float lightModifier = clamp(dot(-lightDirection, normal0), 0.1, 1.0);
	gl_FragColor = (texture2D(diffuse, texCoord0) * lightModifier);
}
