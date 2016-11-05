#ifndef _CUBE_H_
#define _CUBE_H_

#include <SFML\OpenGL.hpp>

class Cube
{
public:
	Cube(GLuint textureID);

	float _verticalAngle;

	void Update(float dt, int direction, bool isRotating);
	void Draw(GLenum mode);

private:
	float _horizontalAngle;
	GLuint _textureID;

	float _textureOffset;
	int direction;
	bool isRotating;
};

#endif //_CUBE_H_