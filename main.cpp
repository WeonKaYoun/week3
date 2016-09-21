#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"

const int width = 740;
const int height = 580;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}

void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	if (i0 == i1)
	{
		for (int k = j0; k < j1; k++)
			drawPixel(i0, k, 0.0f, 0.0f, 0.0f);
		return;
	}
	else
	{
		for (int i = i0; i <= i1; i++)
		{
			const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

			drawPixel(i, j, red, green, blue);
		}
	}
}

void drawOnPixelBuffer()
{
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background


	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

	//squre
	drawLine(100, 450, 200, 450, 0.0f, 0.0f, 0.0f);
	drawLine(100, 500, 200, 500, 0.0f, 0.0f, 0.0f); 
	drawLine(100, 450, 100, 500, 0.0f, 0.0f, 0.0f);
	drawLine(200, 450, 200, 500, 0.0f, 0.0f, 0.0f);

	//thicker line
	for (int x = 1; x < 8; x++) 
	{
	drawLine(300, 450+x, 400, 500+x, 0.0f, 0.0f, 0.0f);
	}

	//square filled with a non-white color
	for (int m = 450; m < 500;m++)
		drawLine(500, m, 600, m, 1.0f, 0.0f, 1.0f);

	//triangle
	drawLine(100, 200, 200, 200, 0.0f, 0.0f, 0.0f);
	for (int n = 0; n < 3; n++)
	{
		drawLine(100, 200+n, 150, 300+n, 0.0f, 0.0f, 0.0f);
		drawLine(150, 300+n, 200, 200+n, 0.0f, 0.0f, 0.0f);
	}

	//pentagon
	drawLine(295, 200, 405, 200, 0.0f, 0.0f, 0.0f);
	for (int k = 0; k < 2; k++)
	{
		drawLine(270, 290 +k, 350, 350 + k, 0.0f, 0.0f, 0.0f);
		drawLine(350, 350 + k, 430, 290 + k, 0.0f, 0.0f, 0.0f);
	}
	for (int l = 0; l < 4; l++)
	{
		drawLine(270, 288 + l, 295, 200 + l, 0.0f, 0.0f, 0.0f);
		drawLine(405, 200 + l, 430, 288 + l, 0.0f, 0.0f, 0.0f);
	}

	//circle



}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(1, 1, 1, 1); // while background

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		drawOnPixelBuffer();

		//TODO: RGB struct
		//Make a pixel drawing function
		//Make a line drawing function

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}

