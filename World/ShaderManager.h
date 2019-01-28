#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <GL/glew.h>
#include <map>
#include <string>

// TODO: Locks / mutex

class ShaderManager
{
	static ShaderManager* _instance;
	static const char* SHADER_DIR;
public:
	typedef std::pair<std::string, GLuint> ProgramEntry_t;
public:
	ShaderManager();
	~ShaderManager();
	GLuint loadShader(const std::string& filePath, GLuint gl_type)const;
	GLuint loadProgram(const std::string& programName);
	bool registerProgram(const std::string& name, GLuint program);
	bool deleteProgram(const std::string& name);
	GLuint getProgram(const std::string& name)const;
	bool bindProgram(const std::string& name);
	bool bindProgram(GLuint program);
	GLuint getCurrentProgram()const;


	static ShaderManager* instance();
	static void destroy();

private:
	std::map<std::string, GLuint> m_loadedProgramMap;
	GLuint m_currentProgram;

};

#endif