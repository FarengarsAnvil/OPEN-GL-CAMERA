#include"Mesh.h"


Mesh::Mesh(std::vector <Vertex>& vertices, std::vector<GLuint>& indices, std::vector <Texture>& textures) {

	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;


	//Instantiate Vertex Array Objects for the Vertex Buffer Object
	VAO.Bind();

	//Instantiate Vertex Buffer Objects which binds all the Vertex Data to it.
	VBO VBO(vertices);

	//Instantiate EBO Objects

	EBO EBO(indices);


	//Links VAO to Vertex Buffer Object. Layout 0 = Co-ordinates rendering.
	VAO.linkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	//layout 1 = Colour rendering of Vertices.
	VAO.linkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	//Layout 2 = Texture Linking to VAO
	VAO.linkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));


	//Unbinds everything to prevent them from being bound to something else.
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();


};

//Draws
void Mesh::Draw(Shader& shader, Camera& camera) {

	shader.Activate();
	VAO.Bind();


	//Lighting for texture 
	unsigned int diffuse = 0;
	unsigned int specular = 0;

	//Iterate through textures vector
	for (int i = 0; i < textures.size(); i++) {

		std::string num;
		std::string type = textures[i].type;

		textures[i].texUnit(shader)




	}



}


