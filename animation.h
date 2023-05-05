#pragma once
#include <GLFW/glfw3.h>

#define vector_length 4
#define num_corners 8
 

// Note: the 'i' in this story just controls the current corner 
// while the 'j' is the actual (x,y,z,w).


class WindowGenerator {
	
public:
	WindowGenerator(const int& width, const int& height, const float& size);
	~WindowGenerator();

	bool shouldClose();  //Window related functions.
	void processEvents();
	void refresh();

	void spin_cube_in_x_direction(const float& angle);						// Spins the cube on the X axis
	void spin_cube_in_y_direction(const float& angle);						// Spins the cube on the Y axis
	void spin_cube_in_z_direction(const float& angle);						// Spins the cube on the Z axis

	void Isometric_projection();											// Simple function that converts the 3d cube data into 2d cube data using Isometric projection.

	void draw_animation();													// Draws the cube animation.

protected:

	GLFWwindow* m_window;		// Window object itself
	int m_width, m_height;		// Window width and height
	float m_size;				// Size of each side of the spinning cube.





	float cube_matrix[num_corners][vector_length];							// contains the current position of each corner of the cube
	float temp_cube_matrix[num_corners][vector_length];						// contains the temporary current position of each corner of the cube
	float two_dimensional_data[num_corners][2];								// contains the 2d version of the cube, will be displayed on the actual screen.

};



