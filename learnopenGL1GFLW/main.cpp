//#include <iostream>
//#include <stdlib.h> 
//#include <time.h>
//// GLEW and GLFW
//#define GLEW_STATIC
//#include <glew.h>
//#include <glfw3.h>
//
//// Other Libs
//#include <SOIL.h>
//// GLM Mathematics
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtx/vector_angle.hpp>
//
//// Other includes
//#include "teapot.h"
//#include "Entity.h"
//#include "Shader.h"
//#include "Camera.h"
//#include "Bullet.h"
////#include "Container.h"
//#include "Model.h"
//
////#include "Game.h"
//
////TODO
///*
//Toy tanks!!!!!
//Create room, like bathroom, kitchen, bedroom. Blender scenes? Scale by 20?
//Create multiple rooms if i have time.
//
//
//*/
//
//using namespace std;
//
//// Function prototypes////////////////////////////////
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void doMovement(GLFWwindow* window);
//void drawTeapot(GLint VAO, Shader shader, Entity entity);
//
//// Camera
//Camera camera1(glm::vec3(-10.0f, 0.0f, 0.0f));
//bool keys[1024];
//GLfloat lastX = 400, lastY = 300;
//bool firstMouse = true;
//
//bool cameraFollow = false;
//bool isMoving = false;
//bool firing = false;
//
//Entity tank;
//
//GLfloat deltaTime = 0.0f;
//GLfloat lastFrame = 0.0f;
//
//GLfloat bulletDeltaTime = 0.0f;
//GLfloat bulletLastFire = 0.0f;
//
//GLuint teapot_vao = 0;
//
//vector<Bullet> bullets;
//
//// Window dimensions
//const GLuint WIDTH = 800, HEIGHT = 600;
//
//
//int main() {
//	// Init GLFW
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//	glfwWindowHint(GLFW_SAMPLES, 4);
//
//	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr); // Windowed
//	glfwMakeContextCurrent(window);
//
//	// Set the required callback functions
//	glfwSetKeyCallback(window, key_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//
//	// Initialize GLEW to setup the OpenGL Function pointers
//	glewExperimental = GL_TRUE;
//	
//	glewInit();
//
//	srand(time(NULL));
//
//	//map1 = ContainerMap(1, 1, 1.0f);
//
//	Model tankModel("tank.obj");
//	Model level("level1.dae");
//	
//	/*for (int i = 0; i < level.meshes[0].vertices.size(); i++) {
//		/*float s = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//		float t = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//		level.meshes[0].vertices[i].TexCoords.s = s;
//		level.meshes[0].vertices[i].TexCoords.t = t;*/
//		//cout << "Vertex " + to_string(i) + " " << level.meshes[0].vertices[i].TexCoords.s << " " << level.meshes[0].vertices[i].TexCoords.t << endl;
//	//}
//
//	// Define the viewport dimensions
//	glViewport(0, 0, WIDTH, HEIGHT);
//
//	// Setup some OpenGL options
//	glEnable(GL_DEPTH_TEST); // enable depth-testing
//	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
//
//	//bullets = vector<Bullet>;
//	Shader containerShader("vertexCon.shader", "fragCon.shader");
//
//	// Setup and compile our shaders
//	Shader teapotShader("vertex.shader", "frag.shader");
//
//	Shader tankShader("tankvertex.shader", "tankfrag.shader");
//
//	Shader lampShader("lamp.vs", "lamp.frag");
//
//	GLuint VBO, VBO2, VAO;
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &VBO2);
//	// Bind our Vertex Array Object first, then bind and set our buffers and pointers.
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, teapot_vertex_count * 3 * sizeof(GLfloat), teapot_vertex_points, GL_STATIC_DRAW);
//
//	// Position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//
//	//normals here
//	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
//	glBufferData(GL_ARRAY_BUFFER, teapot_vertex_count * 3 * sizeof(GLfloat), teapot_normals, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(1);
//
//	glBindVertexArray(0); // Unbind VAO
//
//	GLuint containerVAO, containerVBO;
//	glGenVertexArrays(1, &containerVAO);
//	glGenBuffers(1, &containerVBO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, containerVBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glBindVertexArray(containerVAO);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//	glBindVertexArray(0);
//
//
//	// Then, we set the light's VAO (VBO stays the same. After all, the vertices are the same for the light object (also a 3D cube))
//	GLuint lightVAO;
//	glGenVertexArrays(1, &lightVAO);
//	glBindVertexArray(lightVAO);
//	// We only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need.
//	glBindBuffer(GL_ARRAY_BUFFER, containerVBO);
//	// Set the vertex attributes (only position data for the lamp))
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0); // Note that we skip over the other data in our buffer object (we don't need the normals/textures, only positions).
//	glEnableVertexAttribArray(0);
//	glBindVertexArray(0);
//
//	// Load textures
//	GLuint diffuseMap, specularMap, emissionMap;
//	glGenTextures(1, &diffuseMap);
//	glGenTextures(1, &specularMap);
//	glGenTextures(1, &emissionMap);
//	int width, height;
//	unsigned char* image;
//	// Diffuse map
//	image = SOIL_load_image("container2.png", &width, &height, 0, SOIL_LOAD_RGB);
//	glBindTexture(GL_TEXTURE_2D, diffuseMap);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	SOIL_free_image_data(image);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//	// Specular map
//	image = SOIL_load_image("container2_specular.png", &width, &height, 0, SOIL_LOAD_RGB);
//	glBindTexture(GL_TEXTURE_2D, specularMap);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	SOIL_free_image_data(image);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	// Set texture units
//	containerShader.use();
//	glUniform1i(glGetUniformLocation(containerShader.Program, "material.diffuse"), 0);
//	glUniform1i(glGetUniformLocation(containerShader.Program, "material.specular"), 1);
//
//	// Positions of the point lights
//	glm::vec3 pointLightPositions[] = {
//		glm::vec3(0.7f, -130.0f, 2.0f),
//		glm::vec3(-200.0f, 30.0f, -4.0f),
//		glm::vec3(-4.0f, 150.0f, -12.0f),
//		glm::vec3(0.0f, 30.0f, 220.0f)
//	};
//
//	GLfloat bodyScale = 0.1f;
//	GLfloat tankScale = 3.0f;
//	GLfloat wheelAngle = 0.0f;
//
//	// Game loop
//	while (!glfwWindowShouldClose(window)) {
//		// Set frame time
//		GLfloat currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		/*
//		Game.cpp!
//
//		game.processInput(deltaTime);
//		game.update(deltaTime);
//		game.render();
//		
//		*/
//
//		// Check and call events
//		glfwPollEvents();
//		doMovement(window);
//
//		// Clear the colorbuffer
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		GLint modelLoc;
//		GLint viewLoc;
//		GLint projLoc;
//		//glm::vec3 subVec = tank.headFront;
//		//subVec.y -= 10.0f;
//		glm::vec3 camPosition = tank.pos - 30.0f * (tank.headFront);
//		// TODO this doesnt work when tank goes up and down for obvious reasons.
//		camPosition.y += 10.0f;
//		glm::mat4 view = glm::lookAt(camPosition, tank.pos + 10.0f * tank.headFront , glm::vec3(0.0f, 1.0f, 0.0f));
//		//view = glm::lookAt(camPosition, tank.pos, glm::vec3(0.0f, 1.0f, 0.0f));
//		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//		/*Top down view could be cool or base whole game on it? glm::vec3 camPosition = tank.pos;
//		camPosition.y += 10.0f;
//		glm::mat4 view = glm::lookAt(camPosition, tank.pos + tank.headFront, glm::vec3(0.0f, 1.0f, 0.0f));
//		*/
//		glm::mat4 projection = glm::perspective(glm::radians(camera1.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);
//
//		tankShader.use();
//		modelLoc = glGetUniformLocation(tankShader.Program, "model");
//		viewLoc = glGetUniformLocation(tankShader.Program, "view");
//		projLoc = glGetUniformLocation(tankShader.Program, "projection");
//
//		GLint viewPosLoc = glGetUniformLocation(tankShader.Program, "viewPos");
//		glUniform3f(viewPosLoc, camera1.Position.x, camera1.Position.y, camera1.Position.z);
//		// Set material properties
//		//glUniform1f(glGetUniformLocation(tankShader.Program, "material.shininess"), 32.0f);
//
//		// Directional light
//		glUniform3f(glGetUniformLocation(tankShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
//		glUniform3f(glGetUniformLocation(tankShader.Program, "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
//		glUniform3f(glGetUniformLocation(tankShader.Program, "dirLight.diffuse"), 0.2f, 0.2f, 0.2f);
//		glUniform3f(glGetUniformLocation(tankShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
//		// Point light 1
//		glUniform3f(glGetUniformLocation(tankShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
//		glUniform3f(glGetUniformLocation(tankShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
//		glUniform3f(glGetUniformLocation(tankShader.Program, "pointLights[0].diffuse"), 0.8f, 0.8f, 0.8f);
//		glUniform3f(glGetUniformLocation(tankShader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
//		glUniform1f(glGetUniformLocation(tankShader.Program, "pointLights[0].constant"), 1.0f);
//		glUniform1f(glGetUniformLocation(tankShader.Program, "pointLights[0].linear"), 0.022);
//		glUniform1f(glGetUniformLocation(tankShader.Program, "pointLights[0].quadratic"), 0.0019);
//		// Point light 2
//		glUniform3f(glGetUniformLocation(tankShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
//		glUniform3f(glGetUniformLocation(tankShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
//		glUniform3f(glGetUniformLocation(tankShader.Program, "pointLights[1].diffuse"), 0.8f, 0.8f, 0.8f);
//		glUniform3f(glGetUniformLocation(tankShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
//		glUniform1f(glGetUniformLocation(tankShader.Program, "pointLights[1].constant"), 1.0f);
//		glUniform1f(glGetUniformLocation(tankShader.Program, "pointLights[1].linear"), 0.022);
//		glUniform1f(glGetUniformLocation(tankShader.Program, "pointLights[1].quadratic"), 0.0019);
//		// Point light 3
//		glUniform3f(glGetUniformLocation(tankShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
//		glUniform3f(glGetUniformLocation(tankShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
//		glUniform3f(glGetUniformLocation(tankShader.Program, "pointLights[2].diffuse"), 0.8f, 0.8f, 0.8f);
//		glUniform3f(glGetUniformLocation(tankShader.Program, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
//		glUniform1f(glGetUniformLocation(tankShader.Program, "pointLights[2].constant"), 1.0f);
//		glUniform1f(glGetUniformLocation(tankShader.Program, "pointLights[2].linear"), 0.022);
//		glUniform1f(glGetUniformLocation(tankShader.Program, "pointLights[2].quadratic"), 0.0019);
//		// Point light 4
//		glUniform3f(glGetUniformLocation(tankShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
//		glUniform3f(glGetUniformLocation(tankShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
//		glUniform3f(glGetUniformLocation(tankShader.Program, "pointLights[3].diffuse"), 0.8f, 0.8f, 0.8f);
//		glUniform3f(glGetUniformLocation(tankShader.Program, "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
//		glUniform1f(glGetUniformLocation(tankShader.Program, "pointLights[3].constant"), 1.0f);
//		glUniform1f(glGetUniformLocation(tankShader.Program, "pointLights[3].linear"), 0.022);
//		glUniform1f(glGetUniformLocation(tankShader.Program, "pointLights[3].quadratic"), 0.0019);
//
//		glm::mat4 tankGlobalBody;
//		tankGlobalBody = glm::translate(tankGlobalBody, glm::vec3(tank.pos.x, tank.pos.y, tank.pos.z));
//		tankGlobalBody = glm::rotate(tankGlobalBody, glm::radians(-tank.baseYaw), tank.baseUp);
//		tankGlobalBody = glm::rotate(tankGlobalBody, glm::radians(tank.basePitch), tank.baseRight);
//		tankGlobalBody = glm::scale(tankGlobalBody, glm::vec3(tankScale, tankScale, tankScale));
//		tankGlobalBody = glm::translate(tankGlobalBody, glm::vec3(0.0f, 0.0f, 0.0f));
//		// Pass the matrices to the shader	
//		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(tankGlobalBody));
//		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
//
//		// TANK TURRET HEAD
//		glm::mat4 headLocal;
//		headLocal = glm::translate(headLocal, glm::vec3(-1.29f, 0.0f, 0.0f));
//		headLocal = glm::rotate(headLocal, glm::radians(-tank.headYaw), tank.baseUp);
//		headLocal = glm::translate(headLocal, glm::vec3(1.29f, 0.0f, 0.0f));
//		headLocal = tankGlobalBody * headLocal;
//
//		tankModel.Draw(tankShader, tankGlobalBody, headLocal, true);
//
//	
//
//		//SOME FACTS:
//		//1. CAMERA WILL ALWAYS FACE DIRECTION TURRET IS FACING
//		//2. IF BASE ROTATES SO WILL HEAD, THEREFORE CHANGING LOOK DIRECTION
//		//3. TURRET HEAD WILL ALWAYS HAVE ANGLE/YAW/ROTATION RELATIVE TO THE FRONT OF THE BASE. (FIRST ANGLE BELOW IF RELATIVE TO BASE!!!!!)
//
//		//ATTEMPT 1 good. Perfect for not moving and W and S. AHHHHHH ROTATION IS RELATIVE AND PERFECT BUT CAMERA DOESN'T FOLLOW!!!!
//		//headYaw is relative to baseYaw which is absolute yaw. However the camera doesn't know about relative yaw and treats all yaws like absolute.
//		// Therefore find absolute turret yaw by summing both yaws?
//		//--------------------------------------------------------*/
//
//		
//
//
//		// BULLET CODE
//		teapotShader.use();
//		glBindVertexArray(VAO);
//		modelLoc = glGetUniformLocation(teapotShader.Program, "model");
//		viewLoc = glGetUniformLocation(teapotShader.Program, "view");
//		projLoc = glGetUniformLocation(teapotShader.Program, "projection");
//		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
//		bulletDeltaTime += deltaTime;
//		//cout << "Delta time:" << deltaTime << " Bullet delta Time: " << bulletDeltaTime << endl;
//		if (firing && bulletDeltaTime > 0.07f) {
//			bulletDeltaTime = 0.0f;
//			bullets.push_back(Bullet(tank.pos + 7.0f * tank.headFront * tankScale, tank.headFront));
//			//cout << "No. of bullets: " << bullets.size() << endl;
//		}
//
//		for (int i = 0; i < bullets.size(); i++) {
//			if (!bullets[i].update()) {
//				bullets.erase(bullets.begin() + i);
//			}
//			else {
//				glm::mat4 local = glm::mat4();
//				local = glm::translate(local, bullets[i].pos);
//				GLfloat bulletScale = 0.38f;
//				local = glm::scale(local, glm::vec3(bulletScale, bulletScale, bulletScale));
//				glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(local));
//				glDrawArrays(GL_TRIANGLES, 0, teapot_vertex_count);
//			}
//		}
//
//		//set up teapot drawing
//		teapotShader.use();
//		glBindVertexArray(VAO);
//		modelLoc = glGetUniformLocation(teapotShader.Program, "model");
//		viewLoc = glGetUniformLocation(teapotShader.Program, "view");
//		projLoc = glGetUniformLocation(teapotShader.Program, "projection");
//		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
//
//
//		for (int i = 0; i < bullets.size(); i++) {
//			glm::mat4 local = glm::mat4();
//			local = glm::translate(local, bullets[i].pos);
//			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(local));
//			glDrawArrays(GL_TRIANGLES, 0, teapot_vertex_count);
//		}
//
//		glBindVertexArray(0);
//
//		// TEAPOT WHEELS
//		/*legAngleXaxis = sin(glfwGetTime() * 4.0f);
//		headAngle = sin(glfwGetTime() * 1.0f);
//		if (isMoving) wheelAngle += 4.0f;
//		teapotShader.use();
//		glBindVertexArray(VAO);
//
//		// RIGHT SIDE LEGS -----------------------------------
//		for (int i = 0; i < 3; i++) {
//			glm::mat4 local;
//			local = glm::translate(local, glm::vec3(firstLegXPos - i * legPadding, -7.5f, zAxisDistFromBody));
//
//			local = glm::rotate(local, glm::radians(wheelAngle), glm::vec3(0.0f, 0.0f, -1.0f));
//			local = glm::rotate(local, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//			local = glm::scale(local, glm::vec3(legScale, legScale, legScale));
//
//			glm::mat4 legModel = tankGlobalBody * local;
//			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(legModel));
//			glDrawArrays(GL_TRIANGLES, 0, teapot_vertex_count);
//		}
//
//		// LEFT SIDE LEGS -----------------------------------
//		for (int i = 0; i < 3; i++) {
//			glm::mat4 local;
//			local = glm::translate(local, glm::vec3(firstLegXPos - i * legPadding, -7.5f, -zAxisDistFromBody));
//			local = glm::rotate(local, glm::radians(wheelAngle), glm::vec3(0.0f, 0.0f, -1.0f));
//			local = glm::rotate(local, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
//			local = glm::scale(local, glm::vec3(legScale, legScale, legScale));
//			glm::mat4 legModel = tankGlobalBody * local;
//			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(legModel));
//			glDrawArrays(GL_TRIANGLES, 0, teapot_vertex_count);
//		}
//
//		// Draw the loaded model
//		/*glm::mat4 model;
//		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
//		model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));	// It's a bit too big for our scene, so scale it down
//		glUniformMatrix4fv(glGetUniformLocation(teapotShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
//		ourModel.Draw(teapotShader);*/
//
//
//
//		containerShader.use();	
//
//		viewPosLoc = glGetUniformLocation(containerShader.Program, "viewPos");
//		glUniform3f(viewPosLoc, camera1.Position.x, camera1.Position.y, camera1.Position.z);
//		// Set material properties
//		glUniform1f(glGetUniformLocation(containerShader.Program, "material.shininess"), 32.0f);
//
//		// Directional light
//		glUniform3f(glGetUniformLocation(containerShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
//		glUniform3f(glGetUniformLocation(containerShader.Program, "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
//		glUniform3f(glGetUniformLocation(containerShader.Program, "dirLight.diffuse"), 0.2f, 0.2f, 0.2f);
//		glUniform3f(glGetUniformLocation(containerShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
//		// Point light 1
//		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
//		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
//		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[0].diffuse"), 0.8f, 0.8f, 0.8f);
//		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
//		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[0].constant"), 1.0f);
//		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[0].linear"), 0.022);
//		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[0].quadratic"), 0.0019);
//		// Point light 2
//		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
//		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
//		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[1].diffuse"), 0.8f, 0.8f, 0.8f);
//		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
//		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[1].constant"), 1.0f);
//		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[1].linear"), 0.022);
//		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[1].quadratic"), 0.0019);
//		// Point light 3
//		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
//		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
//		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[2].diffuse"), 0.8f, 0.8f, 0.8f);
//		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
//		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[2].constant"), 1.0f);
//		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[2].linear"), 0.022);
//		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[2].quadratic"), 0.0019);
//		// Point light 4
//		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
//		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
//		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[3].diffuse"), 0.8f, 0.8f, 0.8f);
//		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
//		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[3].constant"), 1.0f);
//		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[3].linear"), 0.022);
//		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[3].quadratic"), 0.0019);
//		// SpotLight
//		glUniform3f(glGetUniformLocation(containerShader.Program, "spotLight.position"), tank.pos.x, tank.pos.y, tank.pos.z);
//		glUniform3f(glGetUniformLocation(containerShader.Program, "spotLight.direction"), tank.headFront.x, tank.headFront.y, tank.headFront.z);
//		glUniform3f(glGetUniformLocation(containerShader.Program, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
//		glUniform3f(glGetUniformLocation(containerShader.Program, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
//		glUniform3f(glGetUniformLocation(containerShader.Program, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
//		glUniform1f(glGetUniformLocation(containerShader.Program, "spotLight.constant"), 1.0f);
//		glUniform1f(glGetUniformLocation(containerShader.Program, "spotLight.linear"), 0.09);
//		glUniform1f(glGetUniformLocation(containerShader.Program, "spotLight.quadratic"), 0.032);
//		glUniform1f(glGetUniformLocation(containerShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(8.0f)));
//		glUniform1f(glGetUniformLocation(containerShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));
//
//		glBindVertexArray(containerVAO);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, diffuseMap);
//		glUniform1i(glGetUniformLocation(containerShader.Program, "diffuse"), 0);
//		modelLoc = glGetUniformLocation(containerShader.Program, "model");
//		viewLoc = glGetUniformLocation(containerShader.Program, "view");
//		projLoc = glGetUniformLocation(containerShader.Program, "projection");
//		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
//	
//		glm::mat4 model;
//		GLfloat levelScale = 500.0f;
//		model = glm::translate(model, glm::vec3(0.0f, 0.2f * levelScale, 0.0f)); // Translate it down a bit so it's at the center of the scene
//		
//		model = glm::scale(model, glm::vec3(levelScale, levelScale, levelScale));	// It's a bit too big for our scene, so scale it down
//		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		
//		//level.Draw(containerShader, model, glm::mat4(), false);
//
//		glBindVertexArray(0);
//
//		// Also draw the lamp object, again binding the appropriate shader
//		lampShader.use();
//		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
//		modelLoc = glGetUniformLocation(lampShader.Program, "model");
//		viewLoc = glGetUniformLocation(lampShader.Program, "view");
//		projLoc = glGetUniformLocation(lampShader.Program, "projection");
//		GLint lampColourLoc = glGetUniformLocation(lampShader.Program, "lampColor");
//		// Set matrices
//		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
//
//		glm::vec3 lampColour = glm::vec3(1.0f, 1.0f, 1.0f);
//
//		// We now draw as many light bulbs as we have point lights.
//		glBindVertexArray(lightVAO);
//		for (GLuint i = 0; i < 4; i++) {
//			model = glm::mat4();
//			model = glm::translate(model, pointLightPositions[i]);
//			model = glm::scale(model, glm::vec3(2.0f)); // Make it a smaller cube
//			glUniform3f(lampColourLoc, lampColour.x, lampColour.y, lampColour.z);
//			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//		glBindVertexArray(0);
//
//		//map1.draw(containerShader, view, projection);
//
//		// Swap the buffers
//		glfwSwapBuffers(window);
//	}
//	// Properly de-allocate all resources once they've outlived their purpose
//	/*glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);*/
//	glfwTerminate();
//	return 0;
//}
//
//void doMovement(GLFWwindow* window) {
//	// Camera controls
//	GLfloat tankSpeed = 0.3f;
//	GLfloat angleSpeed = 1.0f;
//	if (keys[GLFW_KEY_W]) {
//		tank.pos += tank.baseFront * tankSpeed;
//	}
//
//	if (keys[GLFW_KEY_S]) {
//		tank.pos -= tank.baseFront * tankSpeed;
//	}
//
//	if (keys[GLFW_KEY_A]) {
//		tank.baseYaw -= angleSpeed;
//		//tank.headYaw -= angleSpeed;
//	}
//
//	if (keys[GLFW_KEY_D]) {
//		tank.baseYaw += angleSpeed;
//		//tank.headYaw += angleSpeed;
//	}
//	if (keys[GLFW_KEY_SPACE]) {
//		tank.basePitch += angleSpeed * 0.3f;
//	}
//	if (keys[GLFW_KEY_LEFT_CONTROL]) {
//		tank.basePitch -= angleSpeed * 0.3f;
//	}
//
//	if (tank.basePitch > 89.0f) tank.basePitch = 89.0f;
//	else if (tank.basePitch < -89.0f) tank.basePitch = -89.0f;
//
//	tank.updateBaseVectors();
//	tank.updateHeadVectors();
//}
//
//// Is called whenever a key is pressed/released via GLFW
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	if (key >= 0 && key < 1024) {
//		if (action == GLFW_PRESS) {
//			keys[key] = true;
//			if (key == GLFW_KEY_S || key == GLFW_KEY_W) isMoving = true;
//			if (key == GLFW_KEY_F) firing = true;
//		}
//		else if (action == GLFW_RELEASE) {
//			keys[key] = false;
//			if (!keys[GLFW_KEY_S] && !keys[GLFW_KEY_W]) isMoving = false;
//			if (key == GLFW_KEY_F) firing = false;
//		}
//
//	}
//	if (key == GLFW_KEY_C && action == GLFW_RELEASE) cameraFollow = !cameraFollow;
//}
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
//	if (firstMouse) {
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	GLfloat xoffset = xpos - lastX;
//	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left
//
//	lastX = xpos;
//	lastY = ypos;
//
//	xoffset *= camera1.MouseSensitivity;
//	yoffset *= camera1.MouseSensitivity;
//
//	tank.headYaw += xoffset;
//	tank.headPitch += yoffset;
//
//	tank.updateHeadVectors();
//}
