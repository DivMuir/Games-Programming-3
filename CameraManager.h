#pragma once

#include "GameConstants.h"

class CameraManager
{

private:
	mat4 CameraPerspectiveMatrix;	     //The Camera's Perspective Matrix
	vec3 CameraPosition;	             //The Camera's Position
	vec3 CameraForwardVec;               //The Camera's Forward Vector
	vec3 CameraUpVec;	                 //The Camera's Up Vector

public:
	CameraManager()   //Camera Managers Constructor
	{

	}

	CameraManager(const vec3& CameraPos, float CameraFov, float CameraAspect, float NearClip, float FarClip)    //Constructor that Initialises the Camera
	{
		
		CameraPerspectiveMatrix = perspective(CameraFov, CameraAspect, NearClip, FarClip);       //Sets up the Camera's Perspective Matrix
		CameraPosition = CameraPos;                                                              //Sets up the Camera's Position
		CameraForwardVec = vec3(0, -1, 0);                                                       //Sets up the Forward Vector
		CameraUpVec = vec3(1, 0, 0);                                                             //Sets up the Upward Vector

		SetView();                                                                               //Sets up the Camera View
	}

	mat4 ViewMatrix;



	void ChangeCameraSettingsTo3rd()                //Changes the Camera Vectors to get a Third person View
	{
		CameraForwardVec = vec3(0, 0, 1);
		CameraUpVec = vec3(0, 1, 0);
	}

	void ChangeCameraSettingsToTop()                //Changes the Camera Vectors to get a Top Down View
	{
		CameraForwardVec = vec3(0, -1, 0);
		CameraUpVec = vec3(1, 0, 0);
	}

	vec3 GetForwardVector() const        //Finds the Camera's Forward Vector
	{
		return CameraForwardVec;
	}

	vec3 GetUpVector() const             //Finds the Camera's Up Vector
	{
		return CameraUpVec;
	}

	inline mat4 GetView()                //Get's the Camera's View
	{
		ViewMatrix = lookAt(CameraPosition, CameraPosition + CameraForwardVec, CameraUpVec);
		return ViewMatrix;
	}

	inline mat4 GetViewProjectionMatrix() const         // Finds the View Projection Matrix
	{
		return CameraPerspectiveMatrix *lookAt(CameraPosition, CameraPosition + CameraForwardVec, CameraUpVec);

	}

	void SetView()        //Sets the View for the Camera
	{
		ViewMatrix = lookAt(CameraPosition, CameraPosition + CameraForwardVec, CameraUpVec);
	}



};
