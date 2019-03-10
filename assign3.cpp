#include <iostream>
#include "Drawing.h"
#include "Drawable.h"
#include <string>
#include <stdlib.h>
#include <forward_list>
using namespace std;

COLOUR getRGB(char* x, char* y, char* z)
{
	unsigned int red = atoi(x);
	unsigned int green = atoi(y);
	unsigned int blue = atoi(z);
	COLOUR colour{ static_cast<unsigned>(red), static_cast<unsigned>(green), static_cast<unsigned>(blue)};
	return colour;
}

COORD getCoord(char* x, char* y)
{
	int coord1 = atoi(x);
	int coord2 = atoi(y);
	return {coord1, coord2};
}

int main(int argc, char *argv[])
{
	//Convert rbg values into integers that will be used for colours
	COLOUR colour = getRGB(argv[4], argv[5], argv[6]);
	//Create drawing
	Drawing drawing(atoi(argv[2]), atoi(argv[3]), colour);

	//Create list containing all DrawObjects
	forward_list<DrawObject*> listOfObj;

	//Counter used to traverse the list
	int k = 7;
	//Go through the argument list, create and add shapes to the DrawObject list
	while (argv[k] != nullptr)
	{
		if (*argv[k] == 'P')
		{
			//Once P is found look for the next size arguments to create point
			//Convert command line arguments to colours
			COLOUR colour = getRGB(argv[k + 1], argv[k + 2], argv[k + 3]);
			//Convert command line arguments to coordinate
			COORD coordinate = getCoord(argv[k + 4], argv[k + 5]);
			//Create point
			Point *point = new Point(colour, coordinate);
			//Add point to the forward list
			listOfObj.push_front(point);
		}

		else if (*argv[k] == 'L')
		{
			//Once L is found look for the next size arguments to create line
			//Convert command line arguments to colours
			COLOUR colour = getRGB(argv[k + 1], argv[k + 2], argv[k + 3]);
			//Convert command line arguments to coordinates
			COORD coord1 = getCoord(argv[k + 4], argv[k + 5]);
			//Convert command line arguments to coordinates
			COORD coord2 = getCoord(argv[k + 6], argv[k + 7]);
			//Create line object
			Line *line = new Line(colour, coord1, coord2);
			listOfObj.push_front(line);
		}

		else if (*argv[k] == 'S')
		{
			//Convert command line arguments to colours
			COLOUR colour = getRGB(argv[k + 1], argv[k + 2], argv[k + 3]);
			//Create Shape object
			Shape *shape = new Shape(colour);
			//Number of row/col pairs that follow
			int numCoord = atoi(argv[k + 4]);
			numCoord *= 2;
			int start = k + 5;
			//Go through list to get points
			for (int i = 0; i < numCoord; i+=2)
			{
				shape->addCoord(getCoord(argv[start +i], argv[start + i + 1]));
			}
			//Add shape to the list
			listOfObj.push_front(shape);
		}
		k++;
	}
	//Print out the number of shapes that were created
	cout << "Number of Shapes: " << Shape::getNumShapes() << endl;

	//Draw each object in the forward list and remove it from the list when done
	while (!listOfObj.empty())
	{
		//Draw the object
		listOfObj.front()->draw(drawing);
		delete listOfObj.front();
		listOfObj.pop_front();
	}


	//If the file is saved and the object list is empty then print success else print fail
	if (drawing.saveBMP(argv[1]) && listOfObj.empty())
	{
		cout << argv[1] << " saved successfully" << endl;
	}
	else
	{
		cout << argv[1] << " saved unsuccessfully" << endl;
	}

	//Output number of shapes
	cout << "Number of Shapes: " << Shape::getNumShapes() << endl;

	//Get user input
	char c;
	cin >> c;

}
