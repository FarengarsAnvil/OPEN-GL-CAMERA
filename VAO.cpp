#include"VAO.h"

VAO::VAO() {

	// Constructor that generates a VAO ID
		glGenVertexArrays(1, &ID);
	}

	 // Links a VBO and it's attribute to the VAO using a certain layout
    //  Layout specifies the What attribute u are bounding from the Vertices array, be it Colour or texture to the VAO.
   //   Number of Componenents, or argument 3 is dependent on the Vector type of the attribute. a vec 3 = 3 numComponents and etc
  //    Stride is the same for all Attributes/ Layouts. Calculate stride by counting number of items in a row * sizeof(float)
 //     Offset is calculated by sizeof(float) * number of items before the start of the Particular attribute for the Layout. Eg: for texture it is 6, for Color it is 3.

void VAO::linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {

    VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();

}

// Binds the VAO
void VAO::Bind()
{
	glBindVertexArray(ID);
}

// Unbinds the VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}