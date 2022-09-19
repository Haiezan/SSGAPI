#pragma once

#include "../../Lib/gl/include/GL/glew.h"
#include "../../Lib/gl/include/GL/wglew.h"
#include <string>
#include "HeadDefine.h"
char *ReadTxtFile(const std::string &filename);

enum SHADER_TYPE
{
	SHADERTYPE_SMOOTH=0,
};

class _SSG_OPENGLDLL CShader
{
public:
	CShader(void);
	~CShader(void);

	BOOL bSupportShader;

	GLuint m_glslProgram;
	GLuint m_fragmentShader;
	GLuint m_vertexShader;

	//����GLSL����
	BOOL Init(SHADER_TYPE shader_type);
	void Use(void);
	void Delete(void);
	BOOL IsUsable() {return m_glslProgram!=0;}
	//���¼��س���
	void Reload(SHADER_TYPE shader_type);

	void SetAttrib(const char *szName,float fVal);
	void SetUniform(const char *szName,float fVal);
};

