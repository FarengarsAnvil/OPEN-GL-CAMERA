
#version 330 core

//Outputs Color
out vec4 FragColor;  

in vec3 color;
in vec2 texCoord;


//This uniform gens the first Texture
uniform  sampler2D tex0;

  
void main()
{
    //Outputs the Texture from the FragColor variable.
    FragColor = texture(tex0,texCoord);
 
}