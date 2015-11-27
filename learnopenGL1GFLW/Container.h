#pragma once

#include <glew.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include "ContainerMap.h"
#include "Shader.h"
// Other Libs
#include <SOIL.h>




/*

class Container {
public:
	Container(GLuint x, GLuint y, GLfloat scale, ContainerMap& map) :
		map(map)
	{
		this->x = x;
		this->y = y;
		this->containerScale = scale;

		// First, set the container's VAO (and VBO)
		glGenVertexArrays(1, &containerVAO);
		glGenBuffers(1, &containerVBO);

		glBindBuffer(GL_ARRAY_BUFFER, containerVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindVertexArray(containerVAO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glBindVertexArray(0);
	}
	void draw(Shader shader) {
		


	}
public:

private:
	GLuint x, y;
	GLuint containerVBO, containerVAO;
	GLfloat containerScale;
//	ContainerMap& map;
};*/