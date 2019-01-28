#include "ShaderManager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <filesystem>

const char* ShaderManager::SHADER_DIR = "../shaders/";
ShaderManager* ShaderManager::_instance = 0;

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
	bindProgram(0);
	for(auto& entry: m_loadedProgramMap)
	{
		glDeleteProgram(entry.second);
		entry.second = 0;
	}
	m_loadedProgramMap.erase(m_loadedProgramMap.begin(), m_loadedProgramMap.end());
}

GLuint ShaderManager::loadShader(const std::string& filePath, GLuint gl_type) const
{
	const GLuint shader = glCreateShader(gl_type);

	std::string source;
	std::ifstream stream(filePath, std::ios::in);
	if(stream.is_open())
	{
		std::stringstream ss;
		ss << stream.rdbuf();
		source = ss.str();
		stream.close();

	}else
	{
		std::cout << "failed to create shader from sourcepath: " << filePath << std::endl;
		return 0;
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	std::cout << "Compiling shader : " <<  filePath << std::endl;
	char const * sourcePointer = source.c_str();
	glShaderSource(shader, 1, &sourcePointer, NULL);
	glCompileShader(shader);

	// Check Vertex Shader
	glGetShaderiv(shader, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(shader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		std::cout << VertexShaderErrorMessage.data() << std::endl;
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

GLuint ShaderManager::loadProgram(const std::string& programName)
{
	GLuint programID = glCreateProgram();
	//	For file in ./shaders/programName do:
	//		determine type based on file ext
	//		loadShader(file, type)
	//	create program from shaders
	std::stringstream ss;
	ss << ShaderManager::SHADER_DIR << programName;

	std::vector<GLuint> attachedShaders;

	for(const auto& entry: std::filesystem::directory_iterator(ss.str()))
	{
		std::cout << "\tLoading file: " << entry.path() << std::endl;
		GLuint shaderType = 0;

		if(entry.path().extension().string() == ".vert")
		{
			shaderType = GL_VERTEX_SHADER_ARB;
		}else if (entry.path().extension().string() == ".frag")
		{
			shaderType = GL_FRAGMENT_SHADER_ARB;
		}else if (entry.path().extension().string() == ".geom")
		{
			shaderType = GL_GEOMETRY_SHADER_ARB;
		}else if (entry.path().extension().string() == ".tevl")
		{
			shaderType = GL_TESS_EVALUATION_SHADER;
		}
		else if (entry.path().extension().string() == ".tctl")
		{
			shaderType = GL_TESS_CONTROL_SHADER;
		}

		if(shaderType)
		{
			GLuint shader = loadShader(entry.path().string(), shaderType);
			if(shader)
			{
				glAttachShader(programID, shader);
				attachedShaders.push_back(shader);
			}
		}else
		{
			std::cout << "\t\t Ignoring (unknown type): " << entry.path() << std::endl;
		}
		
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	glLinkProgramARB(programID);
	glGetProgramiv(programID, GL_LINK_STATUS, &Result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cout << ProgramErrorMessage.data() << std::endl;
	}

	for(const GLuint shader: attachedShaders)
	{
		glDetachShader(programID, shader);
		glDeleteShader(shader);
	}

	if (Result == GL_TRUE) {
		registerProgram(programName, programID);
	}

	return programID;
}

bool ShaderManager::registerProgram(const std::string& name, GLuint program)
{
	m_loadedProgramMap[name] = program;
	return true;
}

bool ShaderManager::deleteProgram(const std::string& name)
{
	auto match = m_loadedProgramMap.find(name);
	if(match != m_loadedProgramMap.end())
	{
		if (m_currentProgram == match->second) {
			glUseProgram(0);
		}
		glDeleteProgram(match->second);
		m_loadedProgramMap.erase(match);
	}
	return true;
}

GLuint ShaderManager::getProgram(const std::string& name) const
{
	auto match = m_loadedProgramMap.find(name);
	if (match != m_loadedProgramMap.end())
	{
		return match->second;
	}
	return 0;
}

bool ShaderManager::bindProgram(const std::string& name)
{
	const GLuint program = getProgram(name);
	if(program)
	{
		return bindProgram(program);
	}
	return false;
}

bool ShaderManager::bindProgram(GLuint program)
{
	glUseProgram(program);
	m_currentProgram = program;
	return true;
}

GLuint ShaderManager::getCurrentProgram() const
{
	return m_currentProgram;
}


ShaderManager* ShaderManager::instance()
{
	if(nullptr == ShaderManager::_instance)
	{
		ShaderManager::_instance = new ShaderManager();
	}
	return ShaderManager::_instance;
}

void ShaderManager::destroy()
{
	delete ShaderManager::_instance;
}
