#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include"shaderClass.h"

//Purpose of header file is to Declare the Objects fields and Methods which can then be defined in a .cpp file.

class Camera {

public:

	//Declare Object fields
	glm::vec3 position;
	glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up =      glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);


	int width;
	int height;

	//Camera Attribute declaration
	float sensitivity = 25.0f;
	float speed;
	float deltaTime;
	float previousFrame;
	float currentFrame;
	bool firstMovement = true;


	// Constructor: Camera objects take a height, width and a vec3 initial Position.
	Camera(int width, int height, glm::vec3 position);

	//Method Declarations

	//Sets the View and Projection (and Model??) Matrices
	void updateMatrix(GLFWwindow* window, float fovDegree, float farPlane, float nearPlane);

	void Matrix(Shader& shaderProgram, const char* uniform);

	//Allows camera Movement in x and Y directions via moving the mouse. Allows moving Camera position via Keyboard
	void mouseInput(GLFWwindow* window);




};


#endif
