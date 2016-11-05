#include <SFML/Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include "Cube.h"


int main(int argc, char* argv)
{
	sf::RenderWindow window1(sf::VideoMode(400, 400), "GL_TRANSFORMS", sf::Style::Titlebar | sf::Style::Close);

	sf::Image silverImage;
	silverImage.loadFromFile("res/silver.jpg");

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glFrontFace(GL_CW);
	GLuint silverTextureID;
	glGenTextures(1, &silverTextureID);

	//bind texture to active texture space
	glBindTexture(GL_TEXTURE_2D, silverTextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, silverImage.getSize().x, silverImage.getSize().y,
		0, GL_RGBA, GL_UNSIGNED_BYTE, silverImage.getPixelsPtr());


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	/* Telling OpenGL how we want to represent our texture when we try to draw past its bounds. */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	float positionZ = 0.5f;
	float angle = 0.0f;

	/*Triangle*/
	GLenum mode = GL_TRIANGLES;

	int direction = 1;
	bool isRotating = false;
	Cube cube = Cube(silverTextureID);
	sf::Event event;
	sf::Clock appTimer;

	int keySelection = 1;

	/*	while (window1.isOpen() || window2.isOpen() || window3.isOpen() || window4.isOpen()) { */
	while (window1.isOpen()) {
		float deltaTime = appTimer.restart().asSeconds();

		/*		while (window1.pollEvent(event) || window2.pollEvent(event) || window3.pollEvent(event) || window4.pollEvent(event)) { */
		while (window1.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window1.close();
			}

			/*	if (window1.pollEvent(event)) {

			if (event.type == sf::Event::Closed)window1.close();

			}

			if (window2.pollEvent(event)) {

			if (event.type == sf::Event::Closed)window2.close();

			}

			if (window2.isOpen()) {
			window2.display();
			}

			if (window3.pollEvent(event)) {

			if (event.type == sf::Event::Closed)window3.close();

			}
			if (window3.isOpen()) {
			window3.display();
			}

			if (window4.pollEvent(event)) {

			if (event.type == sf::Event::Closed)window4.close();

			}
			if (window4.isOpen()) {
			window4.display();
			} */
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Num1) {
					mode = GL_TRIANGLES;
				}
				else if (event.key.code == sf::Keyboard::Num2) {
					mode = GL_TRIANGLE_STRIP;
				}
				else if (event.key.code == sf::Keyboard::Num3) {
					mode = GL_QUADS;
				}
				else if (event.key.code == sf::Keyboard::Num4) {
					mode = GL_QUAD_STRIP;
				}
				else if (event.key.code == sf::Keyboard::Right) {
					isRotating = true;
					direction = -2;
				}
				else if (event.key.code == sf::Keyboard::Left) {
					isRotating = true;
				}
			}
			/*to allow to stop on one face of the cube*/
			else if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left) {
					isRotating = false;
				}
			}
		} //end second while

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLenum error = glGetError();

		float offset = 0.25f;
		angle += 90.0f * deltaTime;

		//draw with different methods
		GLfloat position[] = { positionZ, -0.1, positionZ, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, position);


		glPushMatrix();
		glRotatef(angle, 1.0f, 0.0f, 0.0f); // rotate at 90 degrees/second on the X axis. 
		glRotatef(20.0f, 0.0f, 1.0f, 0.0f); //rotate 20 degrees on the Y axis

		
		cube.Update(deltaTime, direction, isRotating);
		cube.Draw(mode);

		glPopMatrix();
		window1.display();
	}
	return 0;
}