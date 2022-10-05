
#include"Camera.h"


//Defines Globals
//Used for the restoring Camera Position in the Camera::Matrix()
glm::mat4 restoreView = glm::mat4(1.0f);
glm::vec3 restorePos = glm::vec3(0.0f,0.0f,2.0f);
glm::vec3 restoreForward = glm::vec3(0.0f, 0.0f, -1.0f);


//Constructor for Camera Obj
//Camera attributes = Those passed into Constructor;
Camera::Camera(int width, int height, glm::vec3 position) {

	//Define Object fields
	Camera::width = width;
	Camera::height = height;
	Camera::position = position;
};

//Method definition
//Methods are Declared in the Header file, and defined in the src.cpp file.

//Responsible for updating the Camera matrices. 
void Camera::updateMatrix(GLFWwindow* window, float fovDegree, float farPlane, float nearPlane) {

	//Initialise view,Projection and Model matrices with a default value of 1.0f for all parameters
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);


	double time = glfwGetTime();
	//This initialises our Camera View.
	view = glm::lookAt(position, position + forward, up);
	restoreView = view;
	//Sets up the Projection of the Object.
	projection = glm::perspective(glm::radians(fovDegree), float(width / height), nearPlane, farPlane);
	cameraMatrix = projection * view;
	//Press R to reset Camera Position, View and Camera Orientation.
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		position = restorePos;
		view = restoreView;
		forward = restoreForward;
	}


};

void Camera::Matrix(Shader& shader, const char* uniform) {

	//Exports Matrix to the Vertex Shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));



}

//Mouse Movement Inputs Control Camera
void Camera::mouseInput(GLFWwindow* window) {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//Corrects weird Camera rotation Jump
	if (firstMovement) {

		glfwSetCursorPos(window, (width / 2), (height / 2));
		firstMovement = false;
	}

	//Declare a y and x Value to retrieve screen co-ordinates of the Cursor to calculate offset.
	double xPos;
	double yPos;
	//Grabs cursor position in x and y.
	glfwGetCursorPos(window, &xPos, &yPos);

	//Calculates the new X and Y co-ordinates by calculating the Offset * Camera Sensitivity
	float newX = sensitivity* (float)(yPos - (height / 2)) / height;
	float newY = sensitivity * (float)(xPos - (width / 2)) / width;


	//rotates the Forward Vector by a Given rotation angle to simulate Camera Movement.
	glm::vec3 newForward = glm::rotate(forward, glm::radians(-newX), glm::normalize(glm::cross(forward, up)));

	//Ensures that newForward and Up vector are Orthogonal, then updates the forward vector of the Camera to newForward vector.
	if (!glm::angle(newForward, up) <= glm::radians(90.0f) or glm::angle(newForward, -up) <= glm::radians(90.0f)) {

		forward = newForward;
	}




	//Bound the Mouse Cursor to Centre, elsewise it Spins uncontrollably.
	glfwSetCursorPos(window, (width / 2), (height / 2));
	//Rotates the Forward(Camera Front) vector Perpendicular to the Y axis, and of a degree of the New x co-ordinate.
	//Allows the camera to look horizontally and diagonally.
	forward = glm::rotate(forward, glm::radians(-newY), up);



	//End of Mouse Input.


	float deltaTime = 0.0f;
	float previousFrame = 0.0f;

	//Current Frame
	float currentFrame = glfwGetTime();
	//Calculates frame Delta 
	deltaTime = currentFrame - previousFrame;
	previousFrame = currentFrame;

	float speed = 0.0f;
	//reduces the camera speed from Sonic on crack, to a value processable by the Human brain.
	speed = 0.1f * deltaTime / 170;

	//End of Speed Config.


	//Below is Code for Keyboard Control of Camera.

	// W moves forward. A moves Left, D moves right, S moves back. Space moves up.
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += speed * forward;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position += speed * -glm::normalize(glm::cross(forward, up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position += speed * -forward;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += speed * glm::normalize(glm::cross(forward, up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		position += speed * up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		position += speed * -up;
	}

};






 
