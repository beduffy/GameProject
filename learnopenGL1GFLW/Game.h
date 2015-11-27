#ifndef GAME_H
#define GAME_H

// C++ libraries
#include <iostream>
#include <stdlib.h> 
#include <time.h>
#include <vector>

// GLEW and GLFW
#define GLEW_STATIC
#include <glew.h>
#include <glfw3.h>

// Other Libs
#include <SOIL.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

// My files
//#include "teapot.h"
#include "Entity.h"
#include "Shader.h"
#include "Camera.h"
//#include "Bullet.h"
#include "Model.h"
#include "Tank.h"
#include "LightManager.h"

using namespace std;

// Represents the current state of the game
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game {
public: // Game Main Variables
	// Game state
	GameState  state;
	GLboolean  keys[1024];
	GLuint	   width, height;


public: // Game Object Variables
	Camera camera;
	glm::mat4 view;
	glm::mat4 projection;
	LightManager lightManager;
public: // Game public functions
	// Constructor/Destructor
	Game(GLuint width, GLuint height);
	~Game();
	// Initialize game state (load all shaders/textures/levels)
	void init();
	// GameLoop
	void processPollingInput(GLfloat dt);
	void processMouseInput(GLfloat xoffset, GLfloat yoffset);
	void update(GLfloat dt);
	void render();

private: // Game Object Variables
	Tank playerTank;
//	vector<Bullet> bullets;
	glm::vec3 pointLightPositions[4]; // Keep, easier to manage positions in one place.
	//Tank tank;
private: 
};

#endif