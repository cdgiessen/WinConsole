#ifndef WINCONSOLE_H
#define WINCONSOLE_H

#include <iostream>

#include <string>
#include <chrono>
#include <vector>
#include <ctime>
#include <cmath>

#ifdef _WIN32         // WINDOWS MACHINES
#include <Windows.h>
#include <conio.h>
#endif

#define KEYS_LENGTH    512

namespace wc {
	
	/*
	 *  Function to convert 2D point to a linear spot in array (y * width + x).
	 *  Param 1: X pos
	 *  Param 2: Y pos
	 *  Param 3: Width
	 *  Returns: Linear index
	 */
	short toLinearInd(short, short, short);

	/*
	 *  Vector 3, holds three floats.
	 */
	struct Vec3 {
		float x;
		float y;
		float z;
		
		/*
		 *  Constructor. Sets all values to zero.
		 *  No parameters.
		 *  No return value.
		 */
		Vec3();
		
		/*
	 	 *  Constructor. Sets values correspondingly.
	 	 *  Param 1: X value
	 	 *  Param 2: Y value
	 	 *  Param 3: Z Value
	 	 *  No return value
	 	 */
		Vec3(float, float, float);
		
		/*
		 *  Adds a vector to itself and returns it. Will not modify the vector itself (this).
		 *  Param 1: Vector to add
		 *  Returns: Result
		 */
		Vec3 add(Vec3);

		/*
		 *  Subtracts a vector to itself and returns it. Will not modify the vector itself (this).
		 *  Param 1: Vector to subtract
		 *  Returns: Result
		 */
		Vec3 sub(Vec3);
		
		/*
		 *  Multiplies a vector to itself and returns it. Will not modify the vector itself (this).
		 *  Param 1: Vector to multiply
		 *  Returns: Result
		 */
		Vec3 mult(Vec3);
		
		/*
		 *  Divides a vector to itself and returns it. Will not modify the vector itself (this).
		 *  Param 1: Vector to divide by
		 *  Returns: Result
		 */
		Vec3 div(Vec3);
		
		/*
		 *  Gets corresponding values as if accessed by array. X = index 0, y = index 1, z = index 2
		 *  Param 1: Index
		 *  Returns: Corresponding value
		 */
		float getIndex(short);

		/*
		 *  Sets corresponding values as if modified as an array. X = index 0, y = index 1, z = index 2
		 *  Param 1: Index
		 *  Param 2: New value
		 *  No return value.
		 */
		void setIndex(float, short);
		
		/*  
		 *  Returns itself but with all of the values floored to represent an integer.
		 *  No parameters.
		 *  Returns: Floored version of self
		 */
		Vec3 integer();
	};
	
	/*
	 *  Matrix 3x3
	 */
	struct Mat3 {
		static const short MAT_SIZE = 3;
		float dat[MAT_SIZE][MAT_SIZE];

		/*
		 *  Constructor. Sets all values to zero.
		 *  No parameters.
		 *  No return value.
		 */
		Mat3();

		/*
		 *  Constructor. Initializes as an identity matrix with the diagnal being the parameter.
		 *  Param 1: Diagnal value
		 *  No return value.
		 */
		Mat3(float);

		/*
		 *  Destructor.
		 */
		~Mat3();

		/*
		 *  Adds a matrix to itself and returns it. Will not modify the vector itself (this).
		 *  Param 1: Matrix to add
		 *  Returns: Result
		 */
		Mat3 add(Mat3);

		/*
		 *  Subtracts a matrix to itself and returns it. Will not modify the vector itself (this).
		 *  Param 1: Matrix to subtract
		 *  Returns: Result
		 */
		Mat3 sub(Mat3);
		
		/*
		 *  Multiplies a matrix to itself and returns it. Will not modify the vector itself (this).
		 *  Param 1: Matrix to multiply
		 *  Returns: Result
		 */
		Mat3 mult(Mat3);

		/*  
		 *  Returns itself but with all of the values floored to represent an integer.
		 *  No parameters.
		 *  Returns: Floored version of self
		 */
		Mat3 integer();
	};
	
	/* 
	 *  Multiplies a vector3 by a matrix3x3 from left to right.
	 *  Param 1: Vector to multiply
	 *  Param 2: Matrix to multiply
	 *  Returns: Result of multiplication
	 */
	Vec3 VecTimesMat(Vec3, Mat3);

	/* 
	 *  Multiplies a vector3 by a matrix3x3 from right to left.
	 *  Param 1: Matrix to multiply
	 *  Param 2:Vector to multiply
	 *  Returns: Result of multiplication
	 */
	Vec3 VecTimesMat(Mat3, Vec3);
	
	/* 
	 *  Prints a vector3.
	 *  Param 1: Vector to print
	 *  No return value.
	 */
	void printVec(Vec3);

	/* 
	 *  Prints a matrix3x3.
	 *  Param 1: Matrix to print
	 *  No return value.
	 */
	void printMat(Mat3);
	
	/*
	 *  Sets all the values in the vector to a random number between the specified ranges.
	 *  Param 1: Vector to override
	 *  Param 2: Minimum random value
	 *  Param 3: Maximum random value
	 *  No return value.
	 */
	void overrideAsRandom(Vec3 &, float, float);

	/*
	 *  Sets all the values in the vector to a random number between the specified ranges.
	 *  Param 1: Vector to override
	 *  Param 2: Minimum random value
	 *  Param 3: Maximum random value
	 *  No return value.
	 */
	void overrideAsRandom(Mat3 &, float, float);
	
	/*
	 *  Similar to a sprite, but made of chars instead of pixels.
	 */
	struct Map {
		short width;
		short height;
		std::vector<char *> dat;
		
		/*
		 *  Constructor. Sets the map to a 7x7 square filled with empty spaces.
		 *  No parameters.
		 *  No return value.
		 */
		Map();

		/*
		 *  Constructor. Sets the size of the map with all the values being empty spaces.
		 *  Param 1: Width
		 *  Param 2: Height
		 *  No return value.
		 */
		Map(short, short);
		
		/*
		 *  Constructor. Sets the size and actual data of the map.
		 *  Param 1: Width
		 *  Param 2: Height
		 *  Param 3: std::vector<char *> of data.
		 *  No return value.
		 */
		Map(short, short, std::vector<char *>);
		~Map();
	};
	
	/*
	 *  Modifies console to output to the console faster than printf or std::cout, sets up some drawing functions,
	 *  and also sets up an initialization function with a game and render loop.
	 */
	class WinConsole {
		private:
			#ifdef _WIN32       // WINDOWS MACHINES.
			HANDLE hConsole;
			DWORD junk;
			SMALL_RECT winsize;
			#endif
		
			short width;
			short height;
			short fontw;
			short fonth;
			bool alive;
			float elapsed;
			
			char *buffer;
			bool *keys;
			
			Mat3 translation;
			Mat3 rotation;
			Mat3 scalar;
			Mat3 transform;
			
		public:
			
			/*
			 *  Destructor.
			 */
			~WinConsole();
			
		public:
			/* 
			 *  Sets up the variables and executes the WinConsole::systemSetup function.
			 *  Param 1: Console width (in characters)
			 *  Param 2: Console height (in characters)
			 *  Param 3: Console font width
			 *  Param 4: Console font height
			 *	No return value.
			 */
			bool build(short, short, short, short);
			
			/*
			 *  Starts up and sets up the console correctly with the corresponding OS.
			 *  TODO: IMPLEMENT LINUX
			 *  TODO: IMPLEMENT MAC (PROLLY NOT, MAC CAN KISS MY ASS)
			 *  No parameters.
			 *  No return value.
			 */
			bool systemSetup();
			
			/*
			 *  Starts executes the WinConsole::init function, if successful will then continue to execture
			 *  the WinConsole::tick and WinConsole::render functions as long as they return true (should also be overriden). 
			 *  Will account for different machine speeds with an elapsed time variable. See: WinConsole::tick(float).
			 *  Is not threaded, so the program will literally be stuck in a while loop located in this function.
			 *  No parameters.
			 *  Returns: Whether exit was a successful and planned termination.
			 */
			bool start();
			
			/*
			 *  To be overriden. Superclass default returns 'false'. Used to set up the user's console app.
			 *  No parameters.
			 *  Returns: Whether execution was successful.
			 */
			virtual bool init();

			/*
			 *  To be overriden. Superclass default returns 'false'. Used to execute the main program calculations.
			 *  Param 1: Amount of time elapsed since last call.
			 *  Returns: Whether execution was successful.
			 */
			virtual bool tick(float elapsed);
			
			/*
			 *  To be overriden. Superclass default returns 'false'. Used to draw the characters to the console.
			 *  No return value.
			 *  Returns: Whether execution was successful.
			 */
			virtual bool render();
			
		public:
			/*
			 *  Note: all drawing functions that handle actually drawing to the screen buffer will take in
			 *  account the current transformations. To update or reset transforms, use WinConsole::updateTransforms
			 *  after adding new transformations, and WinConsole::resetTransform to reset all matrices to an
			 *  empty identity matrix. Otherwise, you can get a pointer to the buffer array of chars using
			 *  WinConsole::getBuffer.
			 */
			 
			/*
			 *  Puts a new char in the specified spot.
			 *  Param 1: X pos
			 *  Param 2: Y pos
			 *  Param 3: Char to set
			 *  No return value.
			 */
			void putChar(short, short, char);
			
			/*
			 *  Draws a string overwriting what ever is in the text's way using sprintf.
			 *  Param 1: Starting x pos
			 *  Param 2: Starting y pos
			 *  Param 3: String to draw
			 *  No return value.
			 */
			void stringAt(short, short, std::string);
			
			/*
			 *  Draws an outlined rectangle with the specified char.
			 *  Param 1: X pos
			 *  Param 2: Y pos
			 *  Param 3: Width
			 *  Param 4: Height
			 *  Param 5: Char to set
			 *  No return value.
			 */
			void drawRect(short, short, short, short, char);
			
			/*
			 *  Draws a filled rectangle with the specified char.
			 *  Param 1: X pos
			 *  Param 2: Y pos
			 *  Param 3: Width
			 *  Param 4: Height
			 *  Param 5: Char to set
			 *  No return value.
			 */
			void fillRect(short, short, short, short, char);
			
			/*
			 *  Draws a map (which is similar to a sprite) at the specified x and y position from the top left corner.
			 *  Param 1: X pos
			 *  Param 2: Y pos
			 *  Param 3: Map to draw
			 *  Param 4: Don't draw spaces? (See through like a window)
			 *  No return value.
			 */
			void drawMap(short, short, Map map, bool);
			
			/*
			 *  Multiplies current translation matrix by a new specified translation matrix.
			 *  Transform will not change until WinConsole::updateTransform is called.
			 *  | 1   0   0 |  X = Translation X
			 *  | 0   1   0 |  Y = Translation Y
			 *  | X   Y   1 |
			 *  Param 1: Translation X
			 *  Param 2: Translation Y
			 *  No return value.
			 */
			void translate(float, float);

			/*
			 *  Multiplies current rotation matrix by a new specified rotation matrix.
			 *  Transform will not change until WinConsole::updateTransform is called.
			 *  | C  -S   0 |  C = cos(theta)
			 *  | S   C   0 |  S = sin(theta)
			 *  | 0   0   1 |
			 *  Param 1: Rotation in radians (theta)
			 *  No return value.
			 */
			void rotate(float);
			
			/*
			 *  Multiplies current scale matrix by a new specified scale matrix.
			 *  Transform will not change until WinConsole::updateTransform is called.
			 *  | X   0   0 |  X = X scalar
			 *  | 0   Y   0 |  Y = Y scalar
			 *  | 0   0   1 |
			 *  Param 1: Y scalar
			 *  Param 2: Y scalar
			 *  No return value.
			 */
			void scale(float, float);
			
			/*
			 *  Updates transform by setting the current transform to Scale * Rotation * Translation. Call this function
			 *  after setting the transforms you want (WinConsole::translate, WinConsole::rotate, WinConsole::scale).
			 *  I made it this way so that way the transform matrix will not be changed every single time a transformation function
			 *  is called, in case multiple ones are used. Most commonly translation + rotation combo.
			 *  No parameters.
			 *  No return value.
			 */
			void updateTransform();
			
			/*
			 *  Sets all the transform matrices (translate, rotate, scale) and the current transform matrix back to
			 *  an empty identity matrix.
			 *  No parameters.
			 *  No return value.
			 */
			void resetTransform();
			
			/*
			 *  Checks if a specified point is within the screen buffer. This function DOES NOT take in account the current matrix,
			 *  this function is mainly for my other drawing functions to not draw characters where they shouldn't be.
			 *  Param 1: Point to check
			 *  Returns: Is it in bounds? (x >= 0 && y >= 0 && x < width && y < height && y * width + x < width * height)
			 */
			bool pointInBounds(Vec3);
			
		public:
			/*
			 *  Sets width of console in characters.
			 *  TODO: RESIZE CONSOLE WINDOW. CURRENTLY, RESIZING ISN't IMPLEMENTED SO IT DOES NOT WORK. DO NOT USE YET.
			 *  Param 1: New width
			 *  No return value.
			 */
			void setWidth(short);

			/*
			 *  Sets height of console in characters.
			 *  TODO: RESIZE CONSOLE WINDOW. CURRENTLY, RESIZING ISN'T IMPLEMENTED SO IT DOES NOT WORK. DO NOT USE YET.
			 *  Param 1: New height
			 *  No return value.
			 */
			void setHeight(short);

			/*
			 *  Sets console font width.
			 *  TODO: RESIZE FONT WIDTH. CURRENTLY, RESIZING FONT WIDTH IS NOT IMPLEMENTED SO IT DOES NOT WORK. DO NOT USE YET.
			 *  Param 1: New font width
			 *  No return value.
			 */
			void setFontWidth(short);

			/*
			 *  Sets console font height.
			 *  TODO: RESIZE FONT HEIGHT. CURRENTLY, RESIZING FONT HEIGHT IS NOT IMPLEMENTED SO IT DOES NOT WORK. DO NOT USE YET.
			 *  Param 1: New font width
			 *  No return value.
			 */
			void setFontHeight(short);

		public:
			
			/*
			 *  Gets the screen buffer array. Is a pointer, so any changes made to it will modify the reference, beware.
			 *  Usually used for any specific changes needed that the default functions supplied with the class can't accomplish.
			 *  No parameters.
			 *  Returns: Screen buffer array.
			 */
			char *getBuffer();

			/*
			 *  Gets the screen width as characters.
			 *  No parameters.
			 *  Returns: Width.
			 */
			short getWidth();

			/*
			 *  Gets the screen height as characters.
			 *  No parameters.
			 *  Returns: Height.
			 */
			short getHeight();

			/*
			 *  Gets the font width.
			 *  No parameters.
			 *  Returns: Font width.
			 */
			short getFontWidth();

			/*
			 *  Gets the font height.
			 *  No parameters.
			 *  Returns: Font width.
			 */
			short getFontHeight();

			/*
			 *  Gets the elapsed time of the last execution of the tick/render loop.
			 *  Usually used if the render function or an object outside of this file needs access
			 *  to the elapsed time for some reason.
			 *  No parameters.
			 *  Returns: Elapsed time.
			 */
			float getElapsed();

			/*
			 *  Gets the current translation matrix.
			 *  No parameters.
			 *  Returns: Current translation
			 */
			Mat3 &getTranslation();

			/*
			 *  Gets the current rotation matrix.
			 *  No parameters.
			 *  Returns: Current rotation
			 */
			Mat3 &getRotation();

			/*
			 *  Gets the current scale matrix.
			 *  No parameters.
			 *  Returns: Current scale
			 */
			Mat3 &getScalar();

			/*
			 *  Gets the current transform matrix.
			 *  No parameters.
			 *  Returns: Current transform
			 */
			Mat3 &getTransform();

			/*
			 *  Checks if a key of the provided keycode is active.
			 *  Example use: if(this->getKey(65) { std::cout << "The 'A' key is pressed.\n"; }
			 *  Example use: if(this->getKey((unsigned short)('A')) { std::cout << "The 'A' key is pressed.\n"; }
			 *  Param 1: Keycode to check
			 *  Returns: Whether the key is pressed down
			 */
			bool getKey(unsigned short);

			/*
			 *  Checks if a key of the provided char is active. Will cast the char to an unsigned short, so you don't have to
			 *  cast it yourself in the other WinConsole::getKey function.
			 *  Example use: if(this->getKey('A') { std::cout << "The 'A' key is pressed.\n"; }
			 *  Param 1: Char to check.
			 *  Returns: Whether the key is pressed down
			 */
			bool getKey(char);
	};
	
}

#endif
