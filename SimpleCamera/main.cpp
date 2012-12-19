#include <GL\glew.h>
#include <GL\freeglut.h>

#include "camera.h"

#include <iostream>

int g_windowWidth = 800;
int g_windowHeight = 600;
const char * g_windowTitle = "Simple Camera";

float vertices[] = {
     0.0f,  0.5f, 
     0.5f, -0.5f, 
    -0.5f, -0.5f
};
GLuint g_vbo;

Camera g_mainCamera;
void renderFunction();
void idleFunction();

extern const char * g_vertexShaderSource;
extern const char * g_fragmentShaderSource;

GLuint g_vertexShader;
GLuint g_fragmentShader;
GLuint g_shaderProgram;

void checkShaderStatus(const char * info, GLuint shader);

int main(int argc, char * argv [])
{
	glutInit(&argc, argv);
	glutInitWindowSize(g_windowWidth, g_windowHeight);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow(g_windowTitle);

	glutDisplayFunc(renderFunction);
	glutIdleFunc(idleFunction);
	
	glewInit();

	// Inittilize all data here
	// Generate vertex buffer and load vertices
	glGenBuffers( 1, &g_vbo );
	glBindBuffer( GL_ARRAY_BUFFER, g_vbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

	// Load and compile vertex shader from source
	g_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(g_vertexShader, 1, &g_vertexShaderSource, NULL);
	glCompileShader(g_vertexShader);
	checkShaderStatus("Vertex Shader", g_vertexShader);

	// Load and compile fragment shader from source
	GLuint g_fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( g_fragmentShader, 1, &g_fragmentShaderSource, NULL );
	glCompileShader( g_fragmentShader );
	checkShaderStatus("Fragment Shader", g_fragmentShader);

	// Create shader program
	GLuint g_shaderProgram = glCreateProgram();
	glAttachShader( g_shaderProgram, g_vertexShader );
	glAttachShader( g_shaderProgram, g_fragmentShader );

	// Specify output buffer
	glBindFragDataLocation( g_shaderProgram, 0, "outColor" );

	glLinkProgram(g_shaderProgram);
	glUseProgram(g_shaderProgram);

	GLint posAttrib = glGetAttribLocation( g_shaderProgram, "position" );
	glVertexAttribPointer( posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0 );
	glEnableVertexAttribArray( posAttrib );

	glutMainLoop();

	return 0;
}

void renderFunction()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Do rendering here
	glDrawArrays( GL_TRIANGLES, 0, 3 );

	glutSwapBuffers();
}

void idleFunction()
{
	glutPostRedisplay();
}

void checkShaderStatus(const char * info, GLuint shader)
{
	
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status );

	if(status == GL_TRUE)
	{
		std::cout << info << std::endl;
		std::cout << "OK" << std::endl;
	}
	else
	{
		char buffer [512];
		glGetShaderInfoLog(shader, 512, NULL, buffer );
		std::cout << info << std::endl;
		std::cout << buffer << std::endl;
	}
}
