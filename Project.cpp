//////////////////////////////////////////////////////////////////////////////
//
//  Triangles.cpp
//
//////////////////////////////////////////////////////////////////////////////
using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GLFW/glfw3.h"
#include "LoadShaders.h"
#include <glm/glm.hpp> //includes GLM
#include "glm/ext/vector_float3.hpp"
#include "glm/fwd.hpp"
#include <glm/ext/matrix_transform.hpp> // GLM: translate, rotate
using glm::vec4;
using glm::mat4;
using glm::vec4;
using glm::mat3;
#include <glm/ext/matrix_clip_space.hpp> // GLM: perspective and ortho 
#include <glm/gtc/type_ptr.hpp> // GLM: access to the value_ptr
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>
#include<vector>

#include "Project.h"
//3D object create by Liam Thomas using code examble from comp3016 to help setting this up



	

// to use this example you will need to download the header files for GLM put them into a folder which you will reference in
// properties -> VC++ Directories -> libraries

enum VAO_IDs { Triangles, Indices, Colours, Tex, NumVAOs = 2 };
enum Buffer_IDs { ArrayBuffer, NumBuffers = 4 };
enum Attrib_IDs { vPosition = 0, cPosition = 1, tPosition = 2 };

GLuint  VAOs[NumVAOs];
GLuint  Buffers[NumBuffers];
GLuint texture1;
const GLuint  NumVertices = 36;
// this is the array i set up 
const int testcount = 1200;
string test[testcount];
int NUMBERFROMFILE[testcount];
bool wireison = true;// bool is here to turn on or off the wire frame 
//----------------------------------------------------------------------------
//
// init
//
#define BUFFER_OFFSET(a) ((void*)(a))

//void Project::initSecence() {
//
//}

void
init(void)
{
	ShaderInfo  shaders[] =
	{
		{ GL_VERTEX_SHADER, "media/triangles.vert" },
		{ GL_FRAGMENT_SHADER, "media/triangles.frag" },
		{ GL_NONE, NULL }
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[0]);

	

	GLfloat vertices[][3] = {
		{0.5f,  0.5f, -0.5f},  //0 top right
		{0.5f, -0.5f, -0.5f},  //1 bottom right
		{-0.5f, -0.5f, -0.5f}, //2 bottom left
		{-0.5f,  0.5f, -0.5f},  //3 top left

		{0.5f,  0.5f, 0.5f},  //4 top right
		{0.5f, -0.5f, 0.5f},  //5 bottom right
		{-0.5f, -0.5f, 0.5f}, //6 bottom left
		{-0.5f,  0.5f, 0.5f}  //7 top left 
	};
	GLuint indices[][3] = {  // note that we start from 0!
		{0, 3, 1},  // first Triangle front
		{3, 2, 1},   // second Triangle
		
		{4, 7, 0 },
		{7, 3, 0 },
		
		{1, 2, 5 },
		{2, 6, 5 },
		
		{5, 4, 0 },
		{0, 1, 5 },
		
		{2, 3, 7 },
		{7, 6, 2 },
		
		{4, 5, 7 },  // first Triangle back
		{7, 5, 6 }   // second Triangle
	};

	GLfloat  colours[][4] = {
		{ 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f },  
		{ 1.0f, 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f, 1.0f }, { 0.0f, 1.0f, 0.0f, 1.0f }, 
		{ 0.0f, 0.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 0.0f, 1.0f }, 
	};
	GLfloat  texture_coords[] = {
		 1.0f, 1.0f,
		 1.0f, 0.0f,
		 0.0f, 0.0f,
		 0.0f, 1.0f,

		 0.0f, 1.0f,
	     0.0f, 0.0f,
		 1.0f, 0.0f,
		 1.0f, 1.0f,

		
	
	};



	glGenBuffers(NumBuffers, Buffers);
	
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[Triangles]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[Indices]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	

	glVertexAttribPointer(vPosition, 3, GL_FLOAT,
		GL_FALSE, 0, BUFFER_OFFSET(0));
	
	//Colour Binding
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[Colours]);
	glBufferStorage(GL_ARRAY_BUFFER, sizeof(colours), colours, 0);


	glVertexAttribPointer(cPosition, 4, GL_FLOAT,
		GL_FALSE, 0, BUFFER_OFFSET(0));

	//Texture Binding
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[Tex]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texture_coords), texture_coords, GL_STATIC_DRAW);
	glVertexAttribPointer(tPosition, 2, GL_FLOAT,
		GL_FALSE, 0, BUFFER_OFFSET(0));

	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(cPosition);
	glEnableVertexAttribArray(tPosition);

	glBindVertexArray(VAOs[1]);


	glGenBuffers(NumBuffers, Buffers);

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[Triangles]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[Indices]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



	glVertexAttribPointer(vPosition, 3, GL_FLOAT,
		GL_FALSE, 0, BUFFER_OFFSET(0));

	//Colour Binding
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[Colours]);
	glBufferStorage(GL_ARRAY_BUFFER, sizeof(colours), colours, 0);


	glVertexAttribPointer(cPosition, 4, GL_FLOAT,
		GL_FALSE, 0, BUFFER_OFFSET(0));

	//Texture Binding
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[Tex]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texture_coords), texture_coords, GL_STATIC_DRAW);
	glVertexAttribPointer(tPosition, 2, GL_FLOAT,
		GL_FALSE, 0, BUFFER_OFFSET(0));


	loadTexture(texture1, "media/textures/awesomeface.png");
	glUniform1i(glGetUniformLocation(program, "texture1"), 0);



	// creating the model matrix
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	model = glm::rotate(model, glm::radians(-40.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));

	// creating the view matrix
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -2.0f));

	// creating the projection matrix
	glm::mat4 projection = glm::perspective(45.0f, 4.0f / 3, 0.1f, 20.0f);

	// Adding all matrices up to create combined matrix
	glm::mat4 mvp = projection * view * model;


	//adding the Uniform to the shader
	int mvpLoc = glGetUniformLocation(program, "mvp");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(cPosition);
	glEnableVertexAttribArray(tPosition);
}

void loadTexture(GLuint &texture, std::string texturepath)
{
	// load and create a texture 
// -------------------------

// texture 1
// ---------
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	GLint width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* data = stbi_load(texturepath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

//liam code using 
Project::Project() { // input code is find using https://cplusplus.com/doc/tutorial/files/

};

void maintest() { // crete by Liam 
	string line;
	int arrayline = 0;
	ifstream myfile("data/simple3.ply");
	if (myfile.is_open()) {
		while (getline(myfile, line))
		{
			cout << line;
			myfile >> test[arrayline] ; // this get infomation but need to get number into int value 
			arrayline++;
			
		}
		myfile.close();
	}
	else cout << "file is unable to open file";

}

void skybox() { // https://learnopengl.com/Advanced-OpenGL/Cubemaps
	vector<std::string> faces;
	vector<std::string> Textures_faces;
	unsigned int SkyBoxTextrueID;
	glGenTextures(1, &SkyBoxTextrueID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, SkyBoxTextrueID);
	int width, hight, nrChannels;
	unsigned char* date;
	for (unsigned int i = 0; i < Textures_faces.size(); i++) {
		date = stbi_load(Textures_faces[i].c_str(), &width, &hight,&nrChannels, 0);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0, GL_RGB, width, hight, 0, GL_RGB, GL_UNSIGNED_BYTE, date);
        } // here we have a vectro due to time limte i am droping skybox  and making the light works 
	
}
void Light() { //this is using comp3015 for the base Create by Marius Varga. link here https://dle.plymouth.ac.uk/pluginfile.php/2497682/mod_resource/content/0/Lab3%20-%20Lighting%20and%20shading.pdf

}








//----------------------------------------------------------------------------
//
// display
//

void
display(void)
{
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	glClearBufferfv(GL_COLOR, 0, black);
	glClear(GL_COLOR_BUFFER_BIT);
	// bind textures on corresponding texture units
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);


	//modify position using mv & p
	glBindVertexArray(VAOs[0]);
	glBindTexture(GL_TEXTURE_2D, texture1);
	
	glDrawElements(GL_TRIANGLES, NumVertices, GL_UNSIGNED_INT, 0);



	//modify position using mv & p
	glBindVertexArray(VAOs[1]);
	glBindTexture(GL_TEXTURE_2D, texture1);
glDrawElements(GL_TRIANGLES, NumVertices, GL_UNSIGNED_INT, 0);
	
}


int runTests(std::string value)
{
	doctest::Context ctx;
	if (value.compare("adv") == 0)
	{
		ctx.addFilter("test-case-exclude", "STD");
	}
	else
	{
		ctx.addFilter("test-case-exclude", "ADV");
	}
	ctx.setOption("abort-after", 10);  // default - stop after 5 failed asserts
	ctx.setOption("no-breaks", true); // override - don't break in the debugger
	int res = ctx.run();              // run test cases unless with --no-run
	if (ctx.shouldExit())              // query flags (and --exit) rely on this
		return res;                   // propagate the result of the tests
	// your actual program execution goes here - only if we haven't exited
	return res; // + your_program_res
}
void Wireison() { //create by Liam thomas
	std::string ONorOFF;
	cout << "do you want to using wireFrame?\n";
	cout << "type Yes for WireFrame or type No for not be on wireframe\n";
	cin >> ONorOFF;
	if (ONorOFF == "Yes" || ONorOFF =="yes") {
		wireison = true;
	}
	else if (ONorOFF =="No" || ONorOFF =="no")
	{
		wireison = false;
	}

}
//----------------------------------------------------------------------------
//
// main
//
int
main(int argc, char** argv)
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(800, 600, "Light and wire Frame", NULL, NULL);
	Wireison(); // new void to allow me to ask the user for wire frame
	glfwMakeContextCurrent(window);
	glewInit();
	maintest();
	init();

	while (!glfwWindowShouldClose(window))
	{
	
		if (wireison == true) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			display();
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		else if (wireison == false);
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
}

