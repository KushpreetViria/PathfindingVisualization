
#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragPath) {
    //------------FIRST GET THE SHADERS SOURCE CODE FROM THE FILES-------------//
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(get_current_dir().append(vertexPath));
        fShaderFile.open(get_current_dir().append(fragPath));
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cerr << "ERROR: SHADER SOURCE CODE - FILE_NOT_SUCCESFULLY_READ" << std::endl;
        exit(EXIT_FAILURE);
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    //-----------COMPILE AND LINK SHADERS-------------//
    GLuint vertex, fragment;

    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    compileCheck(vertex, "VERTEX");


    // Fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    compileCheck(fragment, "FRAGMENT");

    // shader Program
    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertex);
    glAttachShader(this->ID, fragment);
    glLinkProgram(this->ID);
    compileCheck(this->ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    std::cout << "Finished shader" << std::endl;
}

void Shader::use(){
    glUseProgram(this->ID);
}
void Shader::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()),(int)value);
}
void Shader::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}
void Shader::setMat4(const std::string& name, glm::mat4 mat4) const{
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat4));
}
void Shader::setVec3f(const std::string& name, glm::vec3 vec3) const{
    glUniform3f(glGetUniformLocation(this->ID, name.c_str()),vec3.x, vec3.y, vec3.z);
}

Shader::~Shader()
{
}

void Shader::compileCheck(GLuint shader, std::string type) {
    int success;
    char infoLog[512];
    
    (type!="PROGRAM") ? glGetShaderiv(shader, GL_COMPILE_STATUS, &success) : glGetProgramiv(shader, GL_LINK_STATUS, &success);

    if (!success){
        (type == "PROGRAM") ? glGetShaderInfoLog(shader, 512, NULL, infoLog) : glGetProgramInfoLog(shader, 512, NULL, infoLog);
        std::string str = "ERROR::SHADER::";
        str.append(type).append("::COMPILATION_FAILED\n").append(infoLog).append("\n");
        std::cerr << "ERROR::SHADER::" << type << "COMPILATION_FAILED\n" << infoLog << std::endl;
    };
}