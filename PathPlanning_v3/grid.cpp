#include "grid.h"
#include <stdio.h>


//class Point
//{
//private:
//	// private resources
//	int x, y;
//	int idx;
//	bool obstacle;
//
//protected:
//	// protected resources
//
//public:
//	// public resources
//	int getX();
//	void setX(int);
//
//	int getY();
//	void setY(int);
//
//	int getIndex();
//	void setIndex(int);
//
//	bool isObstacle();
//	void setObstacle(bool);
//
//	void printPoint();
//
//	Point();
//	Point(int, int, int, bool);
//	~Point();
//
//};



int Point::getX()
{
	return x;
}
void Point::setX(int x_in)
{
	if (x_in >= 0)
	{
		x = x_in;
	}
	else
	{
		x = 0;
	}
}


int Point::getY()
{
	return y;
}
void Point::setY(int y_in)
{
	if (y_in >= 0)
	{
		y = y_in;
	}
	else
	{
		y = 0;
	}
}


int Point::getIndex()
{
	return idx;
}
void Point::setIndex(int idx_in)
{
	if (idx_in >= 0)
	{
		idx = idx_in;
	}
	else
	{
		idx = 0;
	}
}


bool Point::isObstacle()
{
	return obstacle;
}
void Point::setObstacle(bool flag_in)
{
	obstacle = flag_in;
}


bool Point::isSolutionPath()
{
	return solution_path;
}
void Point::setSolutionPath(bool flag_in)
{
	solution_path = flag_in;
}


void Point::printPoint()
{
	printf("Point %d: x%d y%d idx %d  isObs %d\n", idx + 1, x, y, idx, obstacle);
}


Point::Point()
{
	setX(0);
	setY(0);
	setIndex(0);
	setObstacle(true);
	setSolutionPath(false);
}
Point::Point(int x_in, int y_in, int idx_in, bool obstacle_in, bool solution_in)
{
	setX(x_in);
	setY(y_in);
	setIndex(idx_in);
	setObstacle(obstacle_in);
	setSolutionPath(solution_in);
}
Point::~Point()
{
	// needs definition
}









//class Grid
//{
//private:
//	// private resources
//	int x_len, y_len;
//	int num_gridpoints;
//	int num_obstacles;
//	Point* points;
//	// Point startpoint, goalpoint;
//
//protected:
//	// protected resources
//
//public:
//	// public resources
//	int getXLength();
//	void setXLength(int);
//
//	int getYLength();
//	void setYLength(int);
//
//	int getNumGridPoints();
//	void setNumGridPoints(int);
//
//	int getNumObstacles();
//	void setNumObstacles(int);
//
//	Point* getPoints();
//	void setPoints(Point*);
//
//	void setObstacle(int);
//	void clearObstacle(int);
//	bool isObstacle(int);
//
//	void setObstacle(int, int);
//	void clearObstacle(int, int);
//	bool isObstacle(int, int);
//
//	void setObstacle(int*, int*);
//	void clearObstacle(int*, int*);
//
//	int idxToX(int, int, int);
//	int idxToY(int, int, int);
//	int XYtoIdx(int, int, int, int);
//
//	bool isWall(int);
//
//	void printPoints();
//
//	void cleanUp();
//	void initialize();
//
//	void consoleDraw();
//	void showAll();
//
//	Grid();
//	Grid(int, int);
//	~Grid();
//
//};




int Grid::getXLength()
{
	return x_len;
}
void Grid::setXLength(int xlen_in)
{
	if (xlen_in > 0)
	{
		x_len = xlen_in;
	}
	else
	{
		x_len = 1;
	}
}


int Grid::getYLength()
{
	return y_len;
}
void Grid::setYLength(int ylen_in)
{
	if (ylen_in > 0)
	{
		y_len = ylen_in;
	}
	else
	{
		y_len = 1;
	}
}


int Grid::getNumGridPoints()
{
	return num_gridpoints;
}
void Grid::setNumGridPoints(int numgridpoints_in)
{
	if (numgridpoints_in >= 4)
	{
		num_gridpoints = numgridpoints_in;
	}
	else
	{
		num_gridpoints = 4;
	}
}


int Grid::getNumObstacles()
{
	return num_obstacles;
}
void Grid::setNumObstacles(int numobstacles_in)
{
	if (numobstacles_in >= 0)
	{
		num_obstacles = numobstacles_in;
	}
	else
	{
		num_obstacles = 0;
	}
}


Point* Grid::getPoints()
{
	return points;
}
void Grid::setPoints(Point* points_in)
{
	points = points_in;
}


void Grid::setObstacle(int index_in)
{
	if ((index_in < getNumGridPoints()) && (index_in >= 0))
	{
		if (!points[index_in].isObstacle())
		{
			setNumObstacles(getNumObstacles() + 1);
		}
		points[index_in].setObstacle(true);
	}
}
void Grid::clearObstacle(int index_in)
{
	if ((index_in < getNumGridPoints()) && (index_in >= 0) && !isWall(index_in))
	{
		if (points[index_in].isObstacle())
		{
			setNumObstacles(getNumObstacles() - 1);
		}
		points[index_in].setObstacle(false);
	}
}
bool Grid::isObstacle(int index_in)
{
	if ((index_in < getNumGridPoints()) && (index_in >= 0))
	{
		return points[index_in].isObstacle();
	}
	else
	{
		return false;
	}
}


void Grid::setObstacle(int x_in, int y_in)
{
	setObstacle(XYtoIdx(x_in, y_in, getXLength(), getYLength()));
}
void Grid::clearObstacle(int x_in, int y_in)
{
	clearObstacle(XYtoIdx(x_in, y_in, getXLength(), getYLength()));
}
bool Grid::isObstacle(int x_in, int y_in)
{
	return isObstacle(XYtoIdx(x_in, y_in, getXLength(), getYLength()));
}


int Grid::idxToX(int idx_in, int xlen_in, int ylen_in)
{
	return (idx_in % (xlen_in + 1));
}
int Grid::idxToY(int idx_in, int xlen_in, int ylen_in)
{
	return (idx_in / (xlen_in + 1));
}
int Grid::XYtoIdx(int x_in, int y_in, int xlen_in, int ylen_in)
{
	return ((y_in * (xlen_in + 1)) + x_in);
}


bool Grid::isWall(int index_in)
{
	return (isVerticalWall(index_in) || isHorizontalWall(index_in));
}
bool Grid::isHorizontalWall(int index_in)
{
	return (isTopWall(index_in) || isBottomWall(index_in));
}
bool Grid::isVerticalWall(int index_in)
{
	return (isLeftWall(index_in) || isRightWall(index_in));
}
bool Grid::isTopWall(int index_in)
{
	return (index_in <= getXLength());
}
bool Grid::isBottomWall(int index_in)
{
	return (index_in < getNumGridPoints() && index_in >= (getNumGridPoints() - getXLength() - 1));
}
bool Grid::isLeftWall(int index_in)
{
	return (index_in % (getXLength() + 1) == 0);
}
bool Grid::isRightWall(int index_in)
{
	return ((index_in - getXLength()) % (getXLength() + 1) == 0);
}


void Grid::printPoints()
{
	int gridsize_in = getNumGridPoints();
	Point* points_in = getPoints();

	printf("Now printing all points in grid:\n\n");
	for (int i = 0; i < gridsize_in; i++)
	{
		points_in[i].printPoint();
	}
	printf("\n\n");
}


void Grid::cleanUp()
{
	if (points != nullptr)
	{
		delete[] points;
		points = nullptr;
	}
}
void Grid::initialize()
{
	setXLength(1);
	setYLength(1);
	setNumGridPoints(4);
	setNumObstacles(4);
	setPoints(nullptr);
}


void Grid::consoleDraw()
{
	int gridpoints_in = getNumGridPoints();

	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	for (int i = 0; i < gridpoints_in; i++)
	{
		if (getPoints()[i].isObstacle())
		{
			printf("#");
		}
		else if (i == getStart())
		{
			printf(">");
		}
		else if (i == getGoal())
		{
			printf("<");
		}
		else
		{
			printf(" ");
		}

		if ((i + 1) % (getXLength() + 1) == 0)
		{
			printf("\n");
		}
	}
	printf("\n");
}
void Grid::showAll()
{
	consoleDraw();
	printf("%d points on the grid\n", getNumGridPoints());
	printf("%d obstacles on the grid (including walls)\n", getNumObstacles());
	printf("\n\n");
	printPoints();
}


Grid::Grid()
{
	initialize();

	Point* points_in = new Point[4];
	for (int i = 0; i < 4; i++)
	{
		points_in[i] = Point(0, 0, 0, true, false);
	}

	setPoints(points_in);
}
Grid::Grid(int xlen_in, int ylen_in)
{
	initialize();

	setXLength(xlen_in);
	setYLength(ylen_in);

	int numgridpoints_in = (getXLength() + 1) * (getYLength() + 1);
	int numobstacles_in = (2 * (getXLength() + 1)) + (2 * getYLength()) - 2;

	setNumGridPoints(numgridpoints_in);
	setNumObstacles(numobstacles_in);


	Point* points_in = new Point[getNumGridPoints()];
	for (int i = 0; i < getNumGridPoints(); i++)
	{
		// top bounding line
		if (i <= getXLength())
		{
			points_in[i] = Point(idxToX(i, getXLength(), getYLength()), idxToY(i, getXLength(), getYLength()), i, true, false);

			// obstacleindices_in[wallcount] = i;
		}

		// side bounding lines
		else if (i > getXLength() && i < (numgridpoints_in - getXLength() - 1))
		{
			// left bounding line
			if (i % (getXLength() + 1) == 0)
			{
				points_in[i] = Point(idxToX(i, getXLength(), getYLength()), idxToY(i, getXLength(), getYLength()), i, true, false);
				
				// obstacleindices_in[wallcount] = i;
			}

			// right bounding line
			else if ((i - getXLength()) % (getXLength() + 1) == 0)
			{
				points_in[i] = Point(idxToX(i, getXLength(), getYLength()), idxToY(i, getXLength(), getYLength()), i, true, false);
				
				// obstacleindices_in[wallcount] = i;
			}

			// empty inner grid space
			else
			{
				points_in[i] = Point(idxToX(i, getXLength(), getYLength()), idxToY(i, getXLength(), getYLength()), i, false, false);

			}
		}

		// bottom bounding line
		else
		{
			points_in[i] = Point(idxToX(i, getXLength(), getYLength()), idxToY(i, getXLength(), getYLength()), i, true, false);

			// obstacleindices_in[wallcount] = i;
		}

		// wallcount++;
	}

	setPoints(points_in);

	setStart(-1);
	setGoal(-1);

}
Grid::Grid(int xlen_in, int ylen_in, bool filled)
{
	if (!filled)
	{
		initialize();

		setXLength(xlen_in);
		setYLength(ylen_in);

		int numgridpoints_in = (getXLength() + 1) * (getYLength() + 1);
		int numobstacles_in = (2 * (getXLength() + 1)) + (2 * getYLength()) - 2;

		setNumGridPoints(numgridpoints_in);
		setNumObstacles(numobstacles_in);


		Point* points_in = new Point[getNumGridPoints()];
		for (int i = 0; i < getNumGridPoints(); i++)
		{
			// top bounding line
			if (i <= getXLength())
			{
				points_in[i] = Point(idxToX(i, getXLength(), getYLength()), idxToY(i, getXLength(), getYLength()), i, true, false);

				// obstacleindices_in[wallcount] = i;
			}

			// side bounding lines
			else if (i > getXLength() && i < (numgridpoints_in - getXLength() - 1))
			{
				// left bounding line
				if (i % (getXLength() + 1) == 0)
				{
					points_in[i] = Point(idxToX(i, getXLength(), getYLength()), idxToY(i, getXLength(), getYLength()), i, true, false);

					// obstacleindices_in[wallcount] = i;
				}

				// right bounding line
				else if ((i - getXLength()) % (getXLength() + 1) == 0)
				{
					points_in[i] = Point(idxToX(i, getXLength(), getYLength()), idxToY(i, getXLength(), getYLength()), i, true, false);

					// obstacleindices_in[wallcount] = i;
				}

				// empty inner grid space
				else
				{
					points_in[i] = Point(idxToX(i, getXLength(), getYLength()), idxToY(i, getXLength(), getYLength()), i, false, false);

				}
			}

			// bottom bounding line
			else
			{
				points_in[i] = Point(idxToX(i, getXLength(), getYLength()), idxToY(i, getXLength(), getYLength()), i, true, false);

				// obstacleindices_in[wallcount] = i;
			}

			// wallcount++;
		}

		setPoints(points_in);
		points_in = nullptr;

	}
	else
	{
		initialize();

		setXLength(xlen_in);
		setYLength(ylen_in);

		int numgridpoints_in = (getXLength() + 1) * (getYLength() + 1);
		int numobstacles_in = (getXLength() + 1) * (getYLength() + 1);

		setNumGridPoints(numgridpoints_in);
		setNumObstacles(numobstacles_in);

		Point* points_in = new Point[getNumGridPoints()];
		for (int i = 0; i < getNumGridPoints(); i++)
		{
			points_in[i] = Point(idxToX(i, getXLength(), getYLength()), idxToY(i, getXLength(), getYLength()), i, true, false);
		}
		setPoints(points_in);
		points_in = nullptr;
	}

	setStart(-1);
	setGoal(-1);
}

Grid::Grid(const Grid &incoming)
{
	if (&incoming != this)
	{
		x_len = incoming.x_len;
		y_len = incoming.y_len;
		num_gridpoints = incoming.num_gridpoints;
		num_obstacles = incoming.num_obstacles;
		start_index = incoming.start_index;
		goal_index = incoming.goal_index;

		points = new Point[num_gridpoints];
		for (int i = 0; i < num_gridpoints; i++)
		{
			points[i] = incoming.points[i];
		}
	}
}
Grid &Grid::operator=(const Grid &incoming)
{
	if (&incoming != this)
	{
		x_len = incoming.x_len;
		y_len = incoming.y_len;
		num_gridpoints = incoming.num_gridpoints;
		num_obstacles = incoming.num_obstacles;
		start_index = incoming.start_index;
		goal_index = incoming.goal_index;

		points = new Point[num_gridpoints];
		for (int i = 0; i < num_gridpoints; i++)
		{
			points[i] = incoming.points[i];
		}
	}
	return *this;
}

Grid::~Grid()
{
	cleanUp();
}


bool Grid::isValidIndex(int index_in)
{
	return ((index_in >= 0) && (index_in < getNumGridPoints()));
}


int Grid::getStart()
{
	return start_index;
}
void Grid::setStart(int startidx_in)
{
	if (!points[startidx_in].isObstacle() && isValidIndex(startidx_in))
	{
		start_index = startidx_in;
	}
	else
	{
		start_index = (getXLength() + 2);
	}


	// ensure this point is not an obstacle
	if (getPoints()[getStart()].isObstacle())
	{
		getPoints()[getStart()].setObstacle(false);
	}
}
int Grid::getGoal()
{
	return goal_index;
}
void Grid::setGoal(int goalindex_in)
{
	if (!points[goalindex_in].isObstacle() && isValidIndex(goalindex_in))
	{
		goal_index = goalindex_in;
	}
	else
	{
		goal_index = (getNumGridPoints() - getXLength() - 3);
	}


	// ensure this point is not an obstacle
	if (getPoints()[getGoal()].isObstacle())
	{
		getPoints()[getGoal()].setObstacle(false);
	}
}

void Grid::swapStates()
{
	int temp = getStart();
	setStart(getGoal());
	setGoal(temp);
}

void Grid::setLineObstacle(int startindex_in, int length_in, bool vertical)
{
	if ((startindex_in < getNumGridPoints()) && (startindex_in >= 0) && length_in > 0)
	{
		if (!vertical)
		{
			if (isHorizontalWall(startindex_in))
			{
				// do nothing
				// requested start of obstacle coincides with top or bottom wall
			}
			else
			{
				points[startindex_in].setObstacle(true);
				for (int i = 1; i <= length_in; i++)
				{
					if (isRightWall(startindex_in + i))
					{
						// if a point to the right is a wall
						break;
					}
					else
					{
						if (startindex_in + i == start_index || startindex_in + i == goal_index)
						{
							// don't overwrite start and goal states
							continue;
						}
						else
						{
							points[startindex_in + i].setObstacle(true);
							setNumObstacles(getNumObstacles() + 1);
						}
					}
				}
			}
		}

		else
		{
			if (isVerticalWall(startindex_in))
			{
				// do nothing
				// requested start of obstacle coincides with left or right wall
			}
			else
			{
				points[startindex_in].setObstacle(true);
				for (int i = 1; i <= length_in; i++)
				{
					if (isBottomWall(startindex_in + (i * (getXLength() + 1))))
					{
						// if a point below is a wall
						break;
					}
					else
					{
						if ((startindex_in + (i * (getXLength() + 1))) == start_index || (startindex_in + (i * (getXLength() + 1))) == goal_index)
						{
							// don't overwrite start and goal states
							continue;
						}
						else
						{
							points[startindex_in + (i * (getXLength() + 1))].setObstacle(true);
							setNumObstacles(getNumObstacles() + 1);
						}
					}
				}
			}
		}
	}

	else
	{
		// do nothing
		// index point out of bounds
		
	}
}
void Grid::setLineObstacle(int startx_in, int starty_in, int length_in, bool rotated)
{
	setLineObstacle(XYtoIdx(startx_in, starty_in, getXLength(), getYLength()), length_in, rotated);
}


void Grid::setInterleavedObstacle(int startindex, int gap, bool vertical)
{
	if (isValidIndex(startindex))
	{
		int given_gap = gap;
		if (given_gap < 2)
		{
			given_gap = 2;
		}


		if (vertical)
		{
			int given_start = startindex;
			if (isRightWall(given_start))
			{
				return;
			}

			while (!isTopWall(given_start - getXLength() - 1))
			{
				given_start = given_start - getXLength() - 1;
			}

			int i = given_start;
			bool interleaver = false;

			while (true)
			{
				if (isRightWall(i))
				{
					break;
				}

				if ((i - given_start) % given_gap == 0)
				{
					if (!interleaver)
					{
						interleaver = true;
						setLineObstacle(i, getYLength() - 3, true);
						
					}

					else
					{
						interleaver = false;
						setLineObstacle(i + getXLength() + 1, getYLength() - 3, true);
						
					}
				}
				i++;
			}
		}


		else
		{
			int given_start = startindex;
			if (isBottomWall(given_start))
			{
				return;
			}

			while (!isRightWall(given_start - 1))
			{
				given_start = given_start - 1;
			}

			// got lost in the indexing somewhere, need to add 1 back
			given_start = given_start + 1;



			int i = given_start;
			bool interleaver = false;

			while (true)
			{
				if (isBottomWall(i))
				{
					break;
				}

				if ((i - given_start) % given_gap == 0)
				{
					if (!interleaver)
					{
						interleaver = true;
						setLineObstacle(i, getXLength() - 3, false);
						
					}

					else
					{
						interleaver = false;
						setLineObstacle(i + 1, getXLength() - 3, false);
						
					}
				}
				i = i + getXLength() + 1;
			}
		}
	}
}