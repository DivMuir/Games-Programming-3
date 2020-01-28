#pragma once


#include "GameConstants.h"

class LightManager
{
public:
	LightManager();
	LightManager(GLenum lightID, lightColour4 ambient, lightColour4 diffuse, lightColour4 specular, vec4 position, vec3 spotDirection, GLfloat  spotExponent, GLfloat  spotCutoff, GLfloat  constantAttenuation, GLfloat  linearAttenuation, GLfloat  quadraticAttenuation);
	void LightOn();
	void LightOff();

	lightColour4 m_Ambient;
	lightColour4 m_Diffuse;
	lightColour4 m_Specular;

	vec4 LightPosition;
	vec3 LightSpotDirection;
private:

	GLenum m_LightID;
	GLfloat  m_SpotExponent;
	GLfloat  m_SpotCutoff;
	GLfloat  m_ConstantAttenuation;
	GLfloat  m_LinearAttenuation;
	GLfloat  m_QuadraticAttenuation;
};
