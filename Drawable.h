#pragma once
#include <vector>
#include"Drawing.h"
using namespace std;
class DrawObject {
public:
	DrawObject(COLOUR col) { colour = col; }
	COLOUR getColour() { return colour; }
	virtual void draw(Drawing &object)= 0;
	virtual ~DrawObject() { ; }
private:
	COLOUR colour;
protected:
	vector<COORD> coordinates;
};

class Point : public DrawObject {
public:
	Point(COLOUR col, COORD coord):DrawObject(col)
	{
		//Set the coordinates
		coordinates.push_back(coord);
		
	}
	~Point() { ; }
	 virtual void draw(Drawing &object)
	{
		//Set the pixel at the first coord to the colour of the base class
		object.setPixel(coordinates[0], getColour());
		coordinates.clear();
	}
};

class Line : public DrawObject {
public:
	Line(COLOUR col, COORD start, COORD end):DrawObject(col)
	{
		//Set the start and end coordinates
		coordinates.push_back(start);
		coordinates.push_back(end);
	}
	~Line() { ; }
	 virtual void draw(Drawing &object)
	{
		//Draw a line from the first coordinate to the second coordinate with the base class's colour
		object.drawLine(coordinates[0], coordinates[1], getColour());
		//Remove coordinates from the coordinates list
		coordinates.clear();
	}
};

class Shape : public DrawObject {
	static int numShapes;
public:
	Shape(COLOUR col):DrawObject(col)
	{
		//Increase the number of shapes
		numShapes++;
	}

	 virtual void draw(Drawing &object)
	{
		for (unsigned int i = 0; i < coordinates.size()-1; i++)
		{
			//Draw line which connects each coordinate
			object.drawLine(coordinates[i], coordinates[i+1], getColour());
		}

		//Connect the last point to the first
		object.drawLine(coordinates.back(), coordinates.front(), getColour());
		//Remove coordinates from the coordinates list
		coordinates.clear();
	}

	void addCoord(COORD coord)
	{
		//Add the coordinate to the vector
		coordinates.push_back(coord);
	}

	static int getNumShapes()
	{
		return numShapes;
	}
	~Shape(){numShapes--;}	
};
int Shape::numShapes = 0;