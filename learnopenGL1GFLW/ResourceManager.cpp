/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <SOIL.h>

// Instantiate static variables
std::map<std::string, Texture2D>    ResourceManager::textures;
std::map<std::string, Shader>       ResourceManager::shaders;
std::map<std::string, Model>       ResourceManager::models;

Shader ResourceManager::loadShader(const std::string vShaderFile, const std::string fShaderFile, std::string name) {
	shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile);
	return shaders[name];
}

Shader ResourceManager::getShader(std::string name) {
	return shaders[name];
}

Texture2D ResourceManager::loadTexture(const std::string file, GLboolean alpha, std::string name, std::string directory) {
	textures[name] = loadTextureFromFile(file, alpha, directory);
	return textures[name];
}

Texture2D ResourceManager::getTexture(std::string name) {
	return textures[name];
}

Model ResourceManager::loadModel(GLchar* file, std::string name) {
	models[name] = loadModelFromFile(file);
	return models[name];
}

Model ResourceManager::getModel(std::string name) {
	return models[name];
}

void ResourceManager::clear() {
	// (Properly) delete all shaders	
	for (auto iter : shaders)
		glDeleteProgram(iter.second.ID);
	// (Properly) delete all textures
	for (auto iter : textures)
		glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const std::string vShaderFile, const std::string fShaderFile) {
	// 1. Retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	try {
		// Open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::exception e) {
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const std::string vShaderCode = vertexCode.c_str();
	const std::string fShaderCode = fragmentCode.c_str();
	// 2. Now create shader object from source code
	Shader shader(vShaderCode, fShaderCode);
	return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const std::string file, GLboolean alpha, std::string directory) {
	std::string filename;
	if (directory.size() > 0) filename = directory + '/' + filename;
	else filename = file;

	// Create Texture object
	Texture2D texture;
	if (alpha) {
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}
	// Load image
	int width, height;
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
	// Now generate texture
	texture.generate(width, height, image);
	// And finally free image data
	SOIL_free_image_data(image);
	return texture;
}

Model ResourceManager::loadModelFromFile(GLchar* file) {
	return Model(file);
}