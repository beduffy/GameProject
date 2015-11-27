#include "Game.h"
#include "ResourceManager.h"


Game::Game(GLuint width, GLuint height)
: state(GAME_ACTIVE), keys(), width(width), height(height) {

}

Game::~Game() {

}

void Game::init() {
	srand(time(NULL));

	//Setup all models
	/*Model tankModel("tank.obj");
	Model level("level1.dae");*/

	ResourceManager::loadModel("tank.obj", "tank");

	//TODO replace wtih ResourceManager and put model code into resource manager.

	//Setup and compile Shaders
	/*Shader containerShader("vertexCon.shader", "fragCon.shader");
	Shader teapotShader("vertex.shader", "frag.shader");
	Shader tankShader("tankvertex.shader", "tankfrag.shader");*/
	//TODO replace with ResourceManager::LoadShader and rewrite code
	ResourceManager::loadShader("vertexCon.shader", "fragCon.shader", "containerShader");
	ResourceManager::loadShader("vertex.shader", "frag.shader", "teapotShader");
	ResourceManager::loadShader("tankvertex.shader", "tankfrag.shader", "tankShader");

	

	/*GLuint VBO, VBO2, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBO2);
	// Bind our Vertex Array Object first, then bind and set our buffers and pointers.
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, teapot_vertex_count * 3 * sizeof(GLfloat), teapot_vertex_points, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//normals here
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, teapot_vertex_count * 3 * sizeof(GLfloat), teapot_normals, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO*/

	GLuint containerVAO, containerVBO;
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

	// Load textures
	GLuint diffuseMap, specularMap, emissionMap;
	glGenTextures(1, &diffuseMap);
	glGenTextures(1, &specularMap);
	glGenTextures(1, &emissionMap);
	int width, height;
	unsigned char* image;
	// Diffuse map
	image = SOIL_load_image("container2.png", &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	// Specular map
	image = SOIL_load_image("container2_specular.png", &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, specularMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Set texture units
	//is this copying? Is it faster to get shader each time? but its more ugly.
	Shader containerShader = ResourceManager::getShader("containerShader");
	containerShader.use();
	glUniform1i(glGetUniformLocation(containerShader.ID, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(containerShader.ID, "material.specular"), 1);
	
	//All Light Manager code initialisation
	pointLightPositions[0] = glm::vec3(0.7f, 80.0f, 2.0f);
	pointLightPositions[1] = glm::vec3(2.3f, 30.0f, -4.0f);
	pointLightPositions[2] = glm::vec3(-4.0f, 150.0f, -12.0f);
	pointLightPositions[3] = glm::vec3(0.0f, 80.0f, -3.0f);
	
	//Add all Directional Lights to Light Manager
	lightManager.addDirectionalLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f));

	//Add all Point lights to Light Manager
	glm::vec3 usualAmbPLight = glm::vec3(0.05f, 0.05f, 0.05f);
	glm::vec3 usualDiffPLight = glm::vec3(0.8f, 0.8f, 0.8f);
	glm::vec3 usualSpecPLight = glm::vec3(1.0f, 1.0f, 1.0f);
	GLfloat usualLinCoeffPLight = 0.022f;
	GLfloat usualQuadCoeffPLight = 0.0019f;

	lightManager.addPointLight(glm::vec3(0.7f, 80.0f, 2.0f), usualAmbPLight, usualDiffPLight, usualSpecPLight, usualLinCoeffPLight, usualQuadCoeffPLight);
	lightManager.addPointLight(glm::vec3(2.3f, 30.0f, -4.0f), usualAmbPLight, usualDiffPLight, usualSpecPLight, usualLinCoeffPLight, usualQuadCoeffPLight);
	lightManager.addPointLight(glm::vec3(-4.0f, 150.0f, -12.0f), usualAmbPLight, usualDiffPLight, usualSpecPLight, usualLinCoeffPLight, usualQuadCoeffPLight);
	lightManager.addPointLight(glm::vec3(0.0f, 80.0f, -3.0f), usualAmbPLight, usualDiffPLight, usualSpecPLight, usualLinCoeffPLight, usualQuadCoeffPLight);

	//Add all SpotLights to Light Manager
	// SpotLight
	/*glUniform3f(glGetUniformLocation(containerShader.Program, "spotLight.position"), tank.pos.x, tank.pos.y, tank.pos.z);
	glUniform3f(glGetUniformLocation(containerShader.Program, "spotLight.direction"), tank.headFront.x, tank.headFront.y, tank.headFront.z);
	glUniform3f(glGetUniformLocation(containerShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(containerShader.Program, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(containerShader.Program, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(containerShader.Program, "spotLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(containerShader.Program, "spotLight.linear"), 0.09);
	glUniform1f(glGetUniformLocation(containerShader.Program, "spotLight.quadratic"), 0.032);
	glUniform1f(glGetUniformLocation(containerShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(8.0f)));
	glUniform1f(glGetUniformLocation(containerShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));
	lightManager.addSpotLight(glm::vec3(playerTank.pos));*/
}

void Game::update(GLfloat dt) {
	GLfloat bodyScale = 0.1f;
	GLfloat tankScale = 3.0f;
	GLfloat wheelAngle = 0.0f;


	GLint modelLoc;
	GLint viewLoc;
	GLint projLoc;
	glm::vec3 camPosition = playerTank.pos - 30.0f * (playerTank.headFront);
	// TODO this doesnt work when tank goes up and down for obvious reasons.
	camPosition.y += 10.0f;
	view = glm::lookAt(camPosition, playerTank.pos + 10.0f * playerTank.headFront, glm::vec3(0.0f, 1.0f, 0.0f));

	/*Top down view could be cool or base whole game on it? glm::vec3 camPosition = tank.pos;
	camPosition.y += 10.0f;
	glm::mat4 view = glm::lookAt(camPosition, tank.pos + tank.headFront, glm::vec3(0.0f, 1.0f, 0.0f));
	*/
	projection = glm::perspective(glm::radians(camera.Zoom), (float)width / (float)height, 0.1f, 1000.0f);

	Shader tankShader = ResourceManager::getShader("tankShader");
	tankShader.use();
	modelLoc = glGetUniformLocation(tankShader.ID, "model");
	viewLoc = glGetUniformLocation(tankShader.ID, "view");
	projLoc = glGetUniformLocation(tankShader.ID, "projection");

	GLint viewPosLoc = glGetUniformLocation(tankShader.ID, "viewPos");
	glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);
	// Set material properties glUniform1f(glGetUniformLocation(tankShader.ID, "material.shininess"), 32.0f);

	lightManager.sendAllLightsToShader(tankShader);
	
	glm::mat4 tankGlobalBody;
	tankGlobalBody = glm::translate(tankGlobalBody, glm::vec3(playerTank.pos.x, playerTank.pos.y, playerTank.pos.z));
	tankGlobalBody = glm::rotate(tankGlobalBody, glm::radians(-playerTank.baseYaw), playerTank.baseUp);
	tankGlobalBody = glm::rotate(tankGlobalBody, glm::radians(playerTank.basePitch), playerTank.baseRight);
	tankGlobalBody = glm::scale(tankGlobalBody, glm::vec3(tankScale, tankScale, tankScale));
	tankGlobalBody = glm::translate(tankGlobalBody, glm::vec3(0.0f, 0.0f, 0.0f));
	// Pass the matrices to the shader	
	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tankGlobalBody));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// TANK TURRET HEAD
	glm::mat4 headLocal;
	headLocal = glm::translate(headLocal, glm::vec3(-1.29f, 0.0f, 0.0f));
	headLocal = glm::rotate(headLocal, glm::radians(-playerTank.headYaw), playerTank.baseUp);
	headLocal = glm::translate(headLocal, glm::vec3(1.29f, 0.0f, 0.0f));
	headLocal = tankGlobalBody * headLocal;

	ResourceManager::getModel("tank").Draw(tankShader, tankGlobalBody, headLocal, true);
	
	//SOME FACTS:
	//1. CAMERA WILL ALWAYS FACE DIRECTION TURRET IS FACING
	//2. IF BASE ROTATES SO WILL HEAD, THEREFORE CHANGING LOOK DIRECTION
	//3. TURRET HEAD WILL ALWAYS HAVE ANGLE/YAW/ROTATION RELATIVE TO THE FRONT OF THE BASE. (FIRST ANGLE BELOW IF RELATIVE TO BASE!!!!!)

	//ATTEMPT 1 good. Perfect for not moving and W and S. AHHHHHH ROTATION IS RELATIVE AND PERFECT BUT CAMERA DOESN'T FOLLOW!!!!
	//headYaw is relative to baseYaw which is absolute yaw. However the camera doesn't know about relative yaw and treats all yaws like absolute.
	// Therefore find absolute turret yaw by summing both yaws?
	//--------------------------------------------------------*/

	// BULLET CODE
	/*containerShader.use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, map.diffuseMap);
	glUniform1i(glGetUniformLocation(containerShader.Program, "diffuse"), 0);
	glBindVertexArray(containerVAO);
	modelLoc = glGetUniformLocation(containerShader.Program, "model");
	viewLoc = glGetUniformLocation(containerShader.Program, "view");
	projLoc = glGetUniformLocation(containerShader.Program, "projection");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));*/
/*
	teapotShader.use();

	glBindVertexArray(VAO);
	modelLoc = glGetUniformLocation(teapotShader.Program, "model");
	viewLoc = glGetUniformLocation(teapotShader.Program, "view");
	projLoc = glGetUniformLocation(teapotShader.Program, "projection");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	bulletDeltaTime += deltaTime;
	//cout << "Delta time:" << deltaTime << " Bullet delta Time: " << bulletDeltaTime << endl;
	if (firing && bulletDeltaTime > 0.1f) {
		bulletDeltaTime = 0.0f;
		bullets.push_back(Bullet(tank.pos + 2.0f * tank.headFront * tankScale, tank.headFront));
		//cout << "No. of bullets: " << bullets.size() << endl;
	}

	for (int i = 0; i < bullets.size(); i++) {
		if (!bullets[i].update()) {
			bullets.erase(bullets.begin() + i);
		}
		else {
			glm::mat4 local = glm::mat4();
			local = glm::translate(local, bullets[i].pos);
			GLfloat bulletScale = 0.38f;
			local = glm::scale(local, glm::vec3(bulletScale, bulletScale, bulletScale));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(local));
			glDrawArrays(GL_TRIANGLES, 0, teapot_vertex_count);
		}
	}

	glBindVertexArray(0);

	/*containerShader.use();

	viewPosLoc = glGetUniformLocation(containerShader.Program, "viewPos");
	glUniform3f(viewPosLoc, camera1.Position.x, camera1.Position.y, camera1.Position.z);
	// Set material properties
	glUniform1f(glGetUniformLocation(containerShader.Program, "material.shininess"), 32.0f);

	// Directional light
	glUniform3f(glGetUniformLocation(containerShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
	glUniform3f(glGetUniformLocation(containerShader.Program, "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
	glUniform3f(glGetUniformLocation(containerShader.Program, "dirLight.diffuse"), 0.2f, 0.2f, 0.2f);
	glUniform3f(glGetUniformLocation(containerShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
	// Point light 1
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[0].diffuse"), 0.8f, 0.8f, 0.8f);
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[0].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[0].linear"), 0.022);
	glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[0].quadratic"), 0.0019);
	// Point light 2
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[1].diffuse"), 0.8f, 0.8f, 0.8f);
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[1].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[1].linear"), 0.022);
	glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[1].quadratic"), 0.0019);
	// Point light 3
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[2].diffuse"), 0.8f, 0.8f, 0.8f);
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[2].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[2].linear"), 0.022);
	glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[2].quadratic"), 0.0019);
	// Point light 4
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[3].diffuse"), 0.8f, 0.8f, 0.8f);
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[3].constant"), 1.0f);
	glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[3].linear"), 0.022);
	glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[3].quadratic"), 0.0019);
	// SpotLight
	glUniform3f(glGetUniformLocation(containerShader.Program, "spotLight.position"), tank.pos.x, tank.pos.y, tank.pos.z);
	glUniform3f(glGetUniformLocation(containerShader.Program, "spotLight.direction"), tank.headFront.x, tank.headFront.y, tank.headFront.z);
	glUniform3f(glGetUniformLocation(containerShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(containerShader.Program, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(containerShader.Program, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(containerShader.Program, "spotLight.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(containerShader.Program, "spotLight.linear"), 0.09);
	glUniform1f(glGetUniformLocation(containerShader.Program, "spotLight.quadratic"), 0.032);
	glUniform1f(glGetUniformLocation(containerShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(8.0f)));
	glUniform1f(glGetUniformLocation(containerShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

	glBindVertexArray(containerVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glUniform1i(glGetUniformLocation(containerShader.Program, "diffuse"), 0);
	modelLoc = glGetUniformLocation(containerShader.Program, "model");
	viewLoc = glGetUniformLocation(containerShader.Program, "view");
	projLoc = glGetUniformLocation(containerShader.Program, "projection");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glm::mat4 model;
	GLfloat levelScale = 500.0f;
	model = glm::translate(model, glm::vec3(0.0f, 0.2f * levelScale, 0.0f)); // Translate it down a bit so it's at the center of the scene

	model = glm::scale(model, glm::vec3(levelScale, levelScale, levelScale));	// It's a bit too big for our scene, so scale it down
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);

	//level.Draw(containerShader, model, glm::mat4(), false);

	glBindVertexArray(0);

	//map1.draw(containerShader, view, projection);
	*/
}


void Game::processPollingInput(GLfloat dt) {
	//TODO replace below with or not because this is the only thing you control. tank.processInput(dt, keys);
	// Camera controls
	GLfloat tankSpeed = 0.3f;
	GLfloat angleSpeed = 1.0f;
	if (keys[GLFW_KEY_W]) {
		playerTank.pos += playerTank.baseFront * tankSpeed;
	}
	
	if (keys[GLFW_KEY_S]) {
		playerTank.pos -= playerTank.baseFront * tankSpeed;
	}
	
	if (keys[GLFW_KEY_A]) {
		playerTank.baseYaw -= angleSpeed;
	}
	
	if (keys[GLFW_KEY_D]) {
		playerTank.baseYaw += angleSpeed;
	}
	if (keys[GLFW_KEY_SPACE]) {
		playerTank.basePitch += angleSpeed * 0.3f;
	}
	if (keys[GLFW_KEY_LEFT_CONTROL]) {
		playerTank.basePitch -= angleSpeed * 0.3f;
	}
	
	if (playerTank.basePitch > 89.0f) playerTank.basePitch = 89.0f;
	else if (playerTank.basePitch < -89.0f) playerTank.basePitch = -89.0f;
	
	playerTank.updateBaseVectors();
	playerTank.updateHeadVectors();
}

void Game::processMouseInput(GLfloat xoffset, GLfloat yoffset) {
	playerTank.headYaw += xoffset;
	playerTank.headPitch += yoffset;

	playerTank.updateHeadVectors();
}

void Game::render() {
	//IDEAL single function calls for each object
	/*
	1. Draw level/room.
	2. Draw tank.
	3. Draw enemies.
	4. Draw bullets.
	5. Draw Particles.
	6. Draw other objects.
	7. Draw more objects.
	

	*/
}

