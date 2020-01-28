#include "ShaderManager.h"

ShaderManager::ShaderManager()     //Class Constructor
{

}

ShaderManager::ShaderManager(const std::string& fileName)            //Class Constructor
{
	ShaderProgram = glCreateProgram();                                                 //Creates the Shader Program

	Shaders[0] = CreateShader(LoadShader(fileName + ".vert"), GL_VERTEX_SHADER);       //Loads the Shader from File
	Shaders[1] = CreateShader(LoadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);     //Loads the Shader from File

	for (unsigned int i = 0; i < NUM_SHADER; i++)         //For Each Shader
	{
		glAttachShader(ShaderProgram, Shaders[i]);        //Attach the Shader
	}
	AttachAttribs();
	SetUniforms();
}

void ShaderManager::SetUniforms()          //Method to assign Uniforms
{
	Uniforms[TRANSFORM_U] = glGetUniformLocation(ShaderProgram, "transform");
	Uniforms[LPOS_U] = glGetUniformLocation(ShaderProgram, "lightPos");
	Uniforms[SPOTDIR_U] = glGetUniformLocation(ShaderProgram, "spotDirection");
}

void ShaderManager::AttachAttribs()
{
	glBindAttribLocation(ShaderProgram, 0, "position");    //Binds the Position Attributes
	glBindAttribLocation(ShaderProgram, 1, "texCoord");    //Binds the Texture Co-Ordinates Attributes
	glBindAttribLocation(ShaderProgram, 2, "normal");      //Binds the Normal Attributes

	//Check for errors in the program
	glLinkProgram(ShaderProgram);                                                                     //Links the Shader Program
	CheckShaderError(ShaderProgram, GL_LINK_STATUS, true, "Error: Shader failed to link: ");          //Checks for that the Shader has properly Linked, If not Then an Error Message is displayed

	glValidateProgram(ShaderProgram);                                                                 //Validates the Shader Program
	CheckShaderError(ShaderProgram, GL_VALIDATE_STATUS, true, "Error: Shader unvalidated: ");         //Checks that the Shader Program has been Validated, If not then an error message is displayed
}

ShaderManager::~ShaderManager()                              //Class Destructor
{
	for (unsigned int i = 0; i < NUM_SHADER; i++)      //For each Shader 
	{
		glDetachShader(ShaderProgram, Shaders[i]);     //Detach the Shader
		glDeleteShader(Shaders[i]);                    //Deletes the Shaders
	}
	glDeleteProgram(ShaderProgram);                    //Deletes the Shader Programs
}


void ShaderManager::BindShader()    //Binds the Shaders
{
	glUseProgram(ShaderProgram);    //Binds the Shader to the Program
}

//updates transform, light pos and spot direction
void ShaderManager::Update(const TransformManager& transform, const CameraManager& camera, const LightManager& light)               //Updates the the Transform, Light Position and Light Direction
{
	glm::mat4 model = camera.GetViewProjectionMatrix() * transform.GetModel();                

	glUniformMatrix4fv(Uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	glUniform3f(Uniforms[LPOS_U], light.LightPosition.x, light.LightPosition.y, light.LightPosition.z);
	glUniform3f(Uniforms[SPOTDIR_U], light.LightSpotDirection.x, light.LightSpotDirection.y, light.LightSpotDirection.z);
}
void ShaderManager::Update(const TransformManager& transform, const CameraManager& camera)
{
	glm::mat4 model = camera.GetViewProjectionMatrix() * transform.GetModel();

	glUniformMatrix4fv(Uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	//glUniform3f(m_uniforms[CAMDIR_UNIF], camera.GetForwardV().x, camera.GetForwardV().y, camera.GetForwardV().z);
}

GLuint ShaderManager::CreateShader(const std::string& text, GLenum shaderType)  //Creates the Shader
{
	GLuint shader = glCreateShader(shaderType);                        //Creates the Shader

	if (shader == 0)                                                    //If Shader is Equal to 0 
	{
		std::cerr << "Error:Shader creation failed" << std::endl;       //Display and error message
	}

	
	const GLchar* shaderSourceStrings[1];                               //Creates an Array to Hold Strings
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);        //Sends the Shader Data to OpenGl
	glCompileShader(shader);                                                          //Compiles the Shader

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error:Shader could not compile");   //Checks for Errors

	return shader;        //Returns the Created Shader
}


std::string ShaderManager::LoadShader(const std::string& fileName)    //Method to load the Shader from File
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())                          //If the Shader file is opened
	{
		while (file.good())                      //If the File can be read
		{
			getline(file, line);                 //Reads the Current line
			output.append(line + "\n");
		}
	}
	else
	{	
		std::cerr << "Unable to load the shader correctly: " << fileName << std::endl;    //Otherwise Display an Error Message
	}
	return output;	//Returns the Shader
}




void ShaderManager::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)    //Method to check the Shaders for Errors
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)                              //If there is a Program
	{
		glGetProgramiv(shader, flag, &success); //Find the Programs Info
	}
	else                                        //Otherwise
	{
		glGetShaderiv(shader, flag, &success);  //Find the Shader Info
	}
	if (success == GL_FALSE)         //If success is False
	{
		if (isProgram)               //And if there is a Program
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);      //It finds the Info log for the Program
		}
		else                                                              //Otherwise
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);       //It Finds the Info Log for the Shader
		}

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;  //Display the Error Message
	}
}