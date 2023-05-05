#include "animation.h"
#include<math.h>

WindowGenerator::WindowGenerator(const int& width, const int& height, const float& size)
{
	//Define all the parameters
	m_width = width;
	m_height = height;
	m_size = size;


	// Point A (0,0,0)
	cube_matrix[0][0] = 0;
	cube_matrix[0][1] = 0;
	cube_matrix[0][2] = 0;
	cube_matrix[0][3] = 1.0;

	// Point B (0,0,0)
	cube_matrix[1][0] = 0;
	cube_matrix[1][1] = m_size;
	cube_matrix[1][2] = 0;
	cube_matrix[1][3] = 1.0;

	// Point C (0,0,0)
	cube_matrix[2][0] = m_size;
	cube_matrix[2][1] = m_size;
	cube_matrix[2][2] = 0;
	cube_matrix[2][3] = 1.0;

	// Point D (0,0,0)
	cube_matrix[3][0] = m_size;
	cube_matrix[3][1] = 0;
	cube_matrix[3][2] = 0;
	cube_matrix[3][3] = 1.0;

	// Point E (0,0,0)
	cube_matrix[4][0] = 0;
	cube_matrix[4][1] = 0;
	cube_matrix[4][2] = m_size;
	cube_matrix[4][3] = 1.0;

	// Point F (0,0,0)
	cube_matrix[5][0] = 0;
	cube_matrix[5][1] = m_size;
	cube_matrix[5][2] = m_size;
	cube_matrix[5][3] = 1.0;

	// Point G (0,0,0)
	cube_matrix[6][0] = m_size;
	cube_matrix[6][1] = m_size;
	cube_matrix[6][2] = m_size;
	cube_matrix[6][3] = 1.0;

	// Point H (0,0,0)
	cube_matrix[7][0] = m_size;
	cube_matrix[7][1] = 0;
	cube_matrix[7][2] = m_size;
	cube_matrix[7][3] = 1.0;


	for (int i = 0; i < num_corners; i++)  // Transfering data to the temp cube matrix
	{
		for (int j = 0; j < vector_length; j++)
		{
			temp_cube_matrix[i][j] = cube_matrix[i][j];
		}
	}

	Isometric_projection(); // converts 3d to 2d

	// Initialize GLFW library
	glfwInit();

	// Create a window
	m_window = glfwCreateWindow(m_width, m_height, "Window Generator", NULL, NULL);

	// Set the window as the current OpenGL context
	glfwMakeContextCurrent(m_window);

	// Set the viewport to the entire window
	glViewport(0, 0, m_width, m_height);

	// Set the clear color to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);




}

WindowGenerator::~WindowGenerator()
{
	// Destroy the window and terminate GLFW
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool WindowGenerator::shouldClose()
{
	// Check if the window should close (e.g. user clicked the close button)
	return glfwWindowShouldClose(m_window);
}

void WindowGenerator::processEvents()
{
	// Poll for and process events (e.g. window resize, key presses)
	glfwPollEvents();
}

void WindowGenerator::refresh()
{
	// Swap the front and back buffers (double buffering)
	glfwSwapBuffers(m_window);
}

void WindowGenerator::spin_cube_in_x_direction(const float& angle)
{
	for (int i = 0; i < num_corners; i++) // go over all the corners and transfer the data to the temporary vector matrix
	{
		temp_cube_matrix[i][0] = cube_matrix[i][0]; // x itself stays the same			// 0 --> x  , 1 --> y , 2--> z , w --> 3 (stays the same)
		temp_cube_matrix[i][1] = cube_matrix[i][1]*cos(angle)-sin(angle)*cube_matrix[i][2];
		temp_cube_matrix[i][2] = cube_matrix[i][1] * sin(angle) + cos(angle) * cube_matrix[i][2];
	}
	for (int i = 0; i < num_corners; i++)  // Transfering updated data back to the original cube matrix
	{
		for (int j = 0; j < vector_length - 1; j++)
		{
			cube_matrix[i][j] = temp_cube_matrix[i][j];
		}
	}
}

void WindowGenerator::spin_cube_in_y_direction(const float& angle)
{
	for (int i = 0; i < num_corners; i++) // go over all the corners and transfer the data to the temporary vector matrix
	{
		temp_cube_matrix[i][0] = cube_matrix[i][0] * cos(angle) + sin(angle) * cube_matrix[i][2];
		temp_cube_matrix[i][1] = cube_matrix[i][1]; // y itself stays the same
		temp_cube_matrix[i][2]= -sin(angle)*cube_matrix[i][0]+cos(angle)*cube_matrix[i][2];
	}


	for (int i = 0; i < num_corners; i++)  // Transfering updated data back to the original cube matrix
	{
		for (int j = 0; j < vector_length - 1; j++)
		{
			cube_matrix[i][j] = temp_cube_matrix[i][j];
		}
	}
}

void WindowGenerator::spin_cube_in_z_direction(const float& angle)
{
	for (int i = 0; i < num_corners; i++) // go over all the corners and transfer the data to the temporary vector matrix
	{
		temp_cube_matrix[i][0] = cube_matrix[i][0] * cos(angle) - sin(angle) * cube_matrix[i][1];
		temp_cube_matrix[i][1]= cube_matrix[i][0]*sin(angle)+cos(angle)*cube_matrix[i][1];
		temp_cube_matrix[i][2]=cube_matrix[i][2];
	}

	for (int i = 0; i < num_corners; i++)  // Transfering updated data back to the original cube matrix
	{
		for (int j = 0; j < vector_length - 1; j++)
		{
			cube_matrix[i][j] = temp_cube_matrix[i][j];
		}
	}
}

void WindowGenerator::Isometric_projection()
{
	//Isometric projection: 
	//This involves projecting the 3D object onto a plane that is oriented at a fixed angle with respect to each of the three axes.
	//The formula for isometric projection is:
	//x' = (sqrt(3)/2) * x - (sqrt(3)/2) * z
	//y' = (1/2) * x + (1/2) * y + (1/2) * z

	for (int i = 0; i < num_corners; i++)
	{
		two_dimensional_data[i][0] = (sqrt(3.0f) / 2.0f) * cube_matrix[i][0] - (sqrt(3.0f) / 2.0f) * cube_matrix[i][2];
		two_dimensional_data[i][1] = 0.5f * (cube_matrix[i][0] + cube_matrix[i][1] + cube_matrix[i][2]);
	}

}

void WindowGenerator::draw_animation()
{
	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// Set the colors
	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw 
	glBegin(GL_LINE_LOOP);
	glVertex2f(two_dimensional_data[0][0], two_dimensional_data[0][1]);
	glVertex2f(two_dimensional_data[1][0], two_dimensional_data[1][1]);
	glVertex2f(two_dimensional_data[5][0], two_dimensional_data[5][1]);
	glVertex2f(two_dimensional_data[4][0], two_dimensional_data[4][1]);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(two_dimensional_data[0][0], two_dimensional_data[0][1]);
	glVertex2f(two_dimensional_data[3][0], two_dimensional_data[3][1]);
	glVertex2f(two_dimensional_data[7][0], two_dimensional_data[7][1]);
	glVertex2f(two_dimensional_data[4][0], two_dimensional_data[4][1]);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(two_dimensional_data[3][0], two_dimensional_data[3][1]);
	glVertex2f(two_dimensional_data[2][0], two_dimensional_data[2][1]);
	glVertex2f(two_dimensional_data[6][0], two_dimensional_data[6][1]);
	glVertex2f(two_dimensional_data[7][0], two_dimensional_data[7][1]);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2f(two_dimensional_data[1][0], two_dimensional_data[1][1]);
	glVertex2f(two_dimensional_data[2][0], two_dimensional_data[2][1]);
	glVertex2f(two_dimensional_data[6][0], two_dimensional_data[6][1]);
	glVertex2f(two_dimensional_data[5][0], two_dimensional_data[5][1]);
	glEnd();

}
