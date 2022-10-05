#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"shaderClass.h"
#include"EBO.h"
#include"VAO.h"
#include"VBO.h"
#include"texture.h"
#include"Camera.h"


const unsigned int width =  800;
const unsigned int height = 800;
const float fov = 60.0f;


int main() {

	//Initialises GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	// Vertices coordinates
	GLfloat vertices[] =

	{ //     COORDINATES     /        COLORS      /   TexCoord  //     
		-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
		 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
		 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f

	};



	// Indices for  rendering vertices in a given order.
	GLuint indices[] =
	{

    0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4,

	0,1,2,
	0,3,4,
	0,4,3,
	1,2,4


	};

	GLuint* pointer;
	pointer = indices;

	//Initialise Window Object with glfwCreateWindow Constructor
	GLFWwindow* window = glfwCreateWindow(width,height,"GL",NULL,NULL);

	//Ensures that the Window has been instantiated
	if (window == NULL) {
		std::cout << "Window not initialised. ERROR";
		glfwTerminate();
		return -1;
	}

 
	//Sets Current Window
	glfwMakeContextCurrent(window);
	//Loads Open Gl
	gladLoadGL();
	//Sets the Viewport, First 2 parameters are StartX, and StartY of the Window. 
	glViewport(0, 0, width, height);


	//Instantiates Shader object from shaderClass.h. pass two txt files as Params.
	Shader shaderProgram("default.vert", "default.frag");

	//Instantiate Vertex Array Objects for the Vertex Buffer Object
	VAO VAO1;
	VAO1.Bind();

	//Instantiate Vertex Buffer Objects which binds all the Vertex Data to it.
	VBO VBO1(vertices, sizeof(vertices));
	
	//Instantiate EBO Objects

	EBO EBO1(indices, sizeof(indices));
	EBO1.Bind();

	
	//Links VAO to Vertex Buffer Object. Layout 0 = Co-ordinates rendering.
	VAO1.linkAttrib(VBO1, 0, 3, GL_FLOAT, 8*sizeof(float), (void*)0);
	//layout 1 = Colour rendering of Vertices.
	VAO1.linkAttrib(VBO1, 1, 3, GL_FLOAT, 8*sizeof(float), (void*)(3*sizeof(float)));
	//Layout 2 = Texture Linking to VAO
	VAO1.linkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));


	//Unbinds everything to prevent them from being bound to something else.
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	//First texture of Brick. 
	Texture imgTexture("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE );
	imgTexture.texUnit(shaderProgram, "tex0", 0);


	//Enabling Depth buffer corrects  texture Glitch.
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//Initialise Camera Object
	Camera Camera1(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	//Stores time since Compile in variable.
	double time = glfwGetTime();


    //Main Loop for the rendering of Window.
	while (!glfwWindowShouldClose(window)) {
		//Clears Color Buffer, and sets Window colour.
		glClearColor(0.15f,0.2f,0.4f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Activates Shader, enables Camera and Camera Keyboard inputs.
		shaderProgram.Activate();

		//Calls Input and Matrix projection functions.
		Camera1.updateMatrix(window, fov, 1.0f, 100.0f);
		Camera1.Matrix(shaderProgram,"cameraMatrix");

		Camera1.mouseInput(window);


		//Bind texture
		imgTexture.Bind();

		VAO1.Bind();
		//Draws Index Buffer
		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Free Memory and Pipeline by deleting buffers, textures and shaders.

    imgTexture.Delete();
	shaderProgram.Delete();
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();

	//Closes Window and ends main func.
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
};