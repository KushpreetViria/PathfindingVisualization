#pragma once

#include "pch.h"

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "../getDir.h"

//a class to compile and use shader program
class Shader{
	public:
		GLuint ID;
		Shader(const char* vertexPath, const char* fragPath);
		void use();
		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string& name, float value) const;
		void setMat4(const std::string& name, glm::mat4) const;
		void setVec3f(const std::string& name, glm::vec3) const;

		~Shader();
	private:
		void compileCheck(GLuint shader, std::string);

};
