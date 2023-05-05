

#include<iostream>
#include <conio.h>
#include <cstdlib>
#include<string>
#include <crtdbg.h>
#include"animation.h"

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW
#define FRAME_RATE				1.0f/60.0f   // Controls the frame rate of the animation
#define Radiant_conversion		180
#define Pie					    3.1415926535 
#define MAX_ANGLE 360
const int Width = 800; // Window width.
const int Height = 600; // Window height.

int main()
{
	{
		double current_time = 0, previous_time = 0; // Variables that are responsible to control the frame rate 
		WindowGenerator my_window(Width, Height, 0.4f);  // Create a 800x600 window
		while (!my_window.shouldClose())
		{
			current_time = glfwGetTime();
			if (current_time - previous_time >= FRAME_RATE)
			{
				previous_time = current_time;
				my_window.spin_cube_in_x_direction((1.f / Radiant_conversion) * Pie); // performing the spin itself
				my_window.spin_cube_in_y_direction((1.f / Radiant_conversion) * Pie);
				my_window.spin_cube_in_z_direction((1.f / Radiant_conversion) * Pie);
				my_window.Isometric_projection();		// Using Isometric projection to convert 2d to 3d.
				my_window.draw_animation();
				my_window.refresh();
				my_window.processEvents();  // Process events (if any)
			}
		}





	}
	std::cout << std::endl;
	std::cout << "Leaks: " << _CrtDumpMemoryLeaks() << std::endl;
	return 0;

}

// Things we need to do for next time: 
//  Double check the formulas.    
//	Import the graphics library.   ( Done)
//  Import all the functions from the mini cubes 2 file.    (Done)
//  Create a main window throgh main that operates at 60 FPS   (Done) 