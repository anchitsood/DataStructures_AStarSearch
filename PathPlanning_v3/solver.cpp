//#include "grid.h"
#include "solver.h"
#include <stdio.h>
#include <math.h>


//class Solver
//{
//private:
//	// private resources
//	int x_len, y_len;
//	int num_gridpoints;
//	int num_obstacles;
//	int start_index, goal_index;
//	int* open_f_values;
//	int* parent_tracker;
//	Point* points;
//	// Grid grid;
//
//protected:
//	// protected resources
//
//public:
//	// public resources
//	Solver(Grid grid);
//	~Solver();
//	
//	int getXLength();
//	void setXLength(int);
//	int getYLength();
//	void setYLength(int);
//
//	int getNumGridPoints();
//	void setNumGridPoints(int);
//
//	int getNumObstacles();
//	void setNumObstacles(int);
//
//	bool isValidIndex(int);
//
//	int getStart();
//	void setStart(int);
//	int getGoal();
//	void setGoal(int);
//
//	int* getOpenSet();
//	void setOpenSet(int*);
//	int* getClosedSet();
//	void setClosedSet(int*);
//
//	Point* getPoints();
//	void setPoints(Point*);
//
//};


Solver::Solver(Grid grid)
{
	setXLength(grid.getXLength());
	setYLength(grid.getYLength());

	setNumGridPoints(grid.getNumGridPoints());
	setNumObstacles(grid.getNumObstacles());

	Point* points_in = new Point[getNumGridPoints()];
	parent_tracker = new int[getNumGridPoints()];
	open_f_values = new int[getNumGridPoints()];
	closed_set = new int[getNumGridPoints()];
	open_g_values = new int[getNumGridPoints()];

	for (int i = 0; i < getNumGridPoints(); i++)
	{
		points_in[i] = grid.getPoints()[i];
		parent_tracker[i] = -1;
		open_f_values[i] = -1;
		closed_set[i] = -1;
		open_g_values[i] = -1;
	}
	setPoints(points_in);
	points_in = nullptr;

	setStart(grid.getStart());
	setGoal(grid.getGoal());

	//initialize(grid);
}

Solver::Solver(const Solver &incoming)
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
		open_f_values = new int[num_gridpoints];
		parent_tracker = new int[num_gridpoints];
		closed_set = new int[num_gridpoints];
		open_g_values = new int[num_gridpoints];

		for (int i = 0; i < num_gridpoints; i++)
		{
			points[i] = incoming.points[i];
			open_f_values[i] = incoming.open_f_values[i];
			parent_tracker[i] = incoming.parent_tracker[i];
			closed_set[i] = incoming.closed_set[i];
			open_g_values[i] = incoming.open_g_values[i];
		}
	}
}
Solver &Solver::operator=(const Solver &incoming)
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
		open_f_values = new int[num_gridpoints];
		parent_tracker = new int[num_gridpoints];
		closed_set = new int[num_gridpoints];
		open_g_values = new int[num_gridpoints];

		for (int i = 0; i < num_gridpoints; i++)
		{
			points[i] = incoming.points[i];
			open_f_values[i] = incoming.open_f_values[i];
			parent_tracker[i] = incoming.parent_tracker[i];
			closed_set[i] = incoming.closed_set[i];
			open_g_values[i] = incoming.open_g_values[i];
		}
	}
	return *this;
}

Solver::~Solver()
{
	cleanUp();
}


void Solver::cleanUp()
{
	if (points != nullptr)
	{
		delete[] points;
		points = nullptr;
	}

	if (open_f_values != nullptr)
	{
		delete[] open_f_values;
		open_f_values = nullptr;
	}

	if (parent_tracker != nullptr)
	{
		delete[] parent_tracker;
		parent_tracker = nullptr;
	}

	if (open_g_values != nullptr)
	{
		delete[] open_g_values;
		open_g_values = nullptr;
	}

	if (closed_set != nullptr)
	{
		delete[] closed_set;
		closed_set = nullptr;
	}
}
void Solver::initialize(Grid grid)
{
	setXLength(grid.getXLength());
	setYLength(grid.getYLength());

	setNumGridPoints(grid.getNumGridPoints());
	setNumObstacles(grid.getNumObstacles());

	Point* points_in = new Point[getNumGridPoints()];
	parent_tracker = new int[getNumGridPoints()];
	open_f_values = new int[getNumGridPoints()];

	for (int i = 0; i < getNumGridPoints(); i++)
	{
		points_in[i] = grid.getPoints()[i];
		parent_tracker[i] = -1;
		open_f_values[i] = -1;
	}
	setPoints(points_in);
	points_in = nullptr;

	setStart(grid.getStart());
	setGoal(grid.getGoal());

}


void Solver::dynamicReinitialize(Grid grid)
{
	cleanUp();

	Point* points_in = new Point[getNumGridPoints()];
	parent_tracker = new int[getNumGridPoints()];
	open_f_values = new int[getNumGridPoints()];
	closed_set = new int[getNumGridPoints()];
	open_g_values = new int[getNumGridPoints()];

	for (int i = 0; i < getNumGridPoints(); i++)
	{
		points_in[i] = grid.getPoints()[i];
		parent_tracker[i] = -1;
		open_f_values[i] = -1;
		closed_set[i] = -1;
		open_g_values[i] = -1;
	}
	setPoints(points_in);
	points_in = nullptr;

	setStart(grid.getStart());
	setGoal(grid.getGoal());

}

int Solver::getXLength()
{
	return x_len;
}
void Solver::setXLength(int xlen_in)
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
int Solver::getYLength()
{
	return y_len;
}
void Solver::setYLength(int ylen_in)
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


int Solver::getNumGridPoints()
{
	return num_gridpoints;
}
void Solver::setNumGridPoints(int numgridpoints_in)
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


int Solver::getNumObstacles()
{
	return num_obstacles;
}
void Solver::setNumObstacles(int numobstacles_in)
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


bool Solver::isWall(int index_in)
{
	return (isVerticalWall(index_in) || isHorizontalWall(index_in));
}
bool Solver::isHorizontalWall(int index_in)
{
	return (isTopWall(index_in) || isBottomWall(index_in));
}
bool Solver::isVerticalWall(int index_in)
{
	return (isLeftWall(index_in) || isRightWall(index_in));
}
bool Solver::isTopWall(int index_in)
{
	return (index_in <= getXLength());
}
bool Solver::isBottomWall(int index_in)
{
	return (index_in < getNumGridPoints() && index_in >= (getNumGridPoints() - getXLength() - 1));
}
bool Solver::isLeftWall(int index_in)
{
	return (index_in % (getXLength() + 1) == 0);
}
bool Solver::isRightWall(int index_in)
{
	return ((index_in - getXLength()) % (getXLength() + 1) == 0);
}


bool Solver::isValidIndex(int index_in)
{
	return ((index_in >= 0) && (index_in < getNumGridPoints()));
}


int Solver::getStart()
{
	return start_index;
}
void Solver::setStart(int startidx_in)
{
	if (!isWall(startidx_in) && isValidIndex(startidx_in))
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
int Solver::getGoal()
{
	return goal_index;
}
void Solver::setGoal(int goalindex_in)
{
	if (!isWall(goalindex_in) && isValidIndex(goalindex_in))
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


Point* Solver::getPoints()
{
	return points;
}
void Solver::setPoints(Point* points_in)
{
	points = points_in;
}



int Solver::idxToX(int idx_in, int xlen_in, int ylen_in)
{
	return (idx_in % (xlen_in + 1));
}
int Solver::idxToY(int idx_in, int xlen_in, int ylen_in)
{
	return (idx_in / (xlen_in + 1));
}
int Solver::XYtoIdx(int x_in, int y_in, int xlen_in, int ylen_in)
{
	return ((y_in * (xlen_in + 1)) + x_in);
}




int Solver::heuristicManhattan(int index1, int index2)
{
	if (isValidIndex(index1) && isValidIndex(index2))
	{
		return 10*(abs(idxToX(index1, x_len, y_len) - idxToX(index2, x_len, y_len)) + abs(idxToY(index1, x_len, y_len) - idxToY(index2, x_len, y_len)));
	}
	else
	{
		// invalid inputs
		return -1;
	}
}


int Solver::heuristicQuickCostlyManhattan(int index1, int index2, int scale_factor)
{
	if (isValidIndex(index1) && isValidIndex(index2))
	{
		return scale_factor * 10 * (abs(idxToX(index1, x_len, y_len) - idxToX(index2, x_len, y_len)) + abs(idxToY(index1, x_len, y_len) - idxToY(index2, x_len, y_len)));
	}
	else
	{
		// invalid inputs
		return -1;
	}
}


int* Solver::getFreeNeighborIndices(int index)
{
	int neighbors[] = { -1, -1, -1, -1, -1, -1, -1, -1 };
	
	if (isValidIndex(index) && !isWall(index))	
	{
		// east
		if (!points[index + 1].isObstacle() && closed_set[index + 1] == -1)
		{
			neighbors[0] = index + 1;
		}

		// northeast
		if (!points[index - x_len].isObstacle() && closed_set[index - x_len] == -1)
		{
			neighbors[1] = index - x_len;
		}

		//north
		if (!points[index - (x_len + 1)].isObstacle() && closed_set[index - (x_len + 1)] == -1)
		{
			neighbors[2] = index - (x_len + 1);
		}

		// northwest
		if (!points[index - (x_len + 2)].isObstacle() && closed_set[index - (x_len + 2)] == -1)
		{
			neighbors[3] = index - (x_len + 2);
		}

		// west
		if (!points[index - 1].isObstacle() && closed_set[index - 1] == -1)
		{
			neighbors[4] = index - 1;
		}

		// southwest
		if (!points[index + x_len].isObstacle() && closed_set[index + x_len] == -1)
		{
			neighbors[5] = index + x_len;
		}

		// south
		if (!points[index + x_len + 1].isObstacle() && closed_set[index + x_len + 1] == -1)
		{
			neighbors[6] = index + x_len + 1;
		}

		// southeast
		if (!points[index + x_len + 2].isObstacle() && closed_set[index + x_len + 2] == -1)
		{
			neighbors[7] = index + x_len + 2;
		}
	}
	
	return neighbors;
}

int* Solver::getNeighborInitWeights()
{
	int generic_weights[] = { 10, 14, 10, 14, 10, 14, 10, 14 };
	return generic_weights;
}




int Solver::solveAstar(int penalty, int heuristic_scaleup)
{
	int direction_penalty = penalty;
	int cur_direction = 0;

	int ret_value = 0;

	int lowest_f_index = start_index;
	// int lowest_f = 0;	// not really needed, the closed_f_values is keeping this value saved at each step

	int temp_lowest_f_index = start_index;

	// this is the only point whose parent is the point itself, so add this.
	parent_tracker[temp_lowest_f_index] = lowest_f_index;

	// add cumulative f value to corresponding index in open set.
	open_f_values[start_index] = 0;


	// keep track of final f values assigned to each point in closed set, this will help calculate total final cost
	//int* closed_f_values = new int[num_gridpoints];
	//for (int i = 0; i < num_gridpoints; i++)
	//{
	//	closed_f_values[i] = -1;
	//}
	//closed_f_values[lowest_f_index] = 0;

	closed_set[lowest_f_index] = 0;
	open_g_values[lowest_f_index] = 0;

	int initweights[] = { 10, 14, 10, 14, 10, 14, 10, 14 };

	while (true)
	{
		// repeat till either a solution is reached, or if no solution is found

		// contrary to conventional setup, here the closed set has a dual purpose of keeping track of parents, as well as keeping track of the current path.
		// meaning, don't just add the lowest_f_value square to the parent_tracker.
		// instead, add all children to closed set, but only remove the lowest_f_value square from open_f_values.



		// outside the search for the next best neighbor to go to, switch the lowest_f_value square from open to closed set.
		// parent_tracker[temp_lowest_f_index] = lowest_f_index;
		
		// check
		closed_set[temp_lowest_f_index] = open_g_values[temp_lowest_f_index];
		
		
		// setting open_f_values value to -2 means removed from open set.
		open_f_values[temp_lowest_f_index] = -2;
		// now reset the lowest_f_index to its new value, so temp_lowest_f_value can go search for the next square.
		lowest_f_index = temp_lowest_f_index;

		
		int min_f = -1;
		bool found_a_neighbor = false;
		int new_direction = 0;

		for (int i = 0; i < 8; i++)
		{

			// first valid run thru, to find a valid neighbor
			if ((getFreeNeighborIndices(lowest_f_index)[i] != -1) && (!found_a_neighbor))
			{
				found_a_neighbor = true;



				// existing g + increment to g due to one step taken + h
				// this is because the open_g_value for this square doesn't yet exist, because its the first valid neighbor visited
				min_f = closed_set[lowest_f_index] + initweights[i] + heuristicQuickCostlyManhattan(getFreeNeighborIndices(lowest_f_index)[i], goal_index, heuristic_scaleup);
				// min_f += ((abs(new_direction - cur_direction)) / 45) * direction_penalty;
				
				temp_lowest_f_index = getFreeNeighborIndices(lowest_f_index)[i];
				i--;
			}

			// once a traversable neighbor has been found, a min benchmark f has been set.
			// continue with the next traversable neighbor, and compare its f value to the benchmark set above, change it if necessary.
			else if ((getFreeNeighborIndices(lowest_f_index)[i] != -1) && (found_a_neighbor))
			{
				// calculating the minimum f value out of the 8 traversable neighbors. right now, assign it a placeholder starter value.
				int new_f = min_f;

				new_direction = getFreeNeighborIndices(lowest_f_index)[i] - lowest_f_index;
				new_direction = convertDirToAngle(new_direction);

				// difference in directions
				int direction_difference = abs(new_direction - cur_direction);

				// absorb the difference in turning clockwise and anticlockwise
				if (direction_difference > 180)
				{
					direction_difference = direction_difference - 180;
				}

				// normalize directional differences
				direction_difference = direction_difference / 45;


				// at the same time, if it isn't on the open set, add it. also update its parent to the current node
				// parent_tracker[child] = parent
				if (open_f_values[getFreeNeighborIndices(lowest_f_index)[i]] == -1)
				{
					// parent_tracker fulfiing its secondary purpose of keeping track of parents here. no switching from open_f_values happens here.
					parent_tracker[getFreeNeighborIndices(lowest_f_index)[i]] = lowest_f_index;
					// parent_tracker[child] = parent;
					
					// calculate g value.
					open_g_values[getFreeNeighborIndices(lowest_f_index)[i]] = initweights[i] + closed_set[lowest_f_index];
					
					
					// calculate the f_value, and add it to the open_f_values
					new_f = open_g_values[getFreeNeighborIndices(lowest_f_index)[i]] + heuristicQuickCostlyManhattan(getFreeNeighborIndices(lowest_f_index)[i], goal_index, heuristic_scaleup);
					
					// penalize change in direction
					new_f += direction_difference * direction_penalty;

					open_f_values[getFreeNeighborIndices(lowest_f_index)[i]] = new_f;
				}



				// but if it's already there, update its f value if there's been an improvement. also update its parent to its grandparent.
				// parent_tracker[child] = parent, but parent_tracker[parent] = grandparent
				// we need to set parent_tracker[child] = grandparent
				// therefore, parent_tracker[parent_tracker[child]] = grandparent
				// and so, we need to set parent_tracker[child] = parent_tracker[parent_tracker[child]]
				// check correctness of this
				else if (open_f_values[getFreeNeighborIndices(lowest_f_index)[i]] >= 0)
				{
					// check for improvement by testing its existing g value with the new one being assigned.
					// there's no improvement if the new value is more than the existing one.
					if (open_g_values[getFreeNeighborIndices(lowest_f_index)[i]] <= closed_set[lowest_f_index] + initweights[i])
					{
						// so we backtrack one level, and thus, we do not update the g value.
						// this means that the point retains its old, better, g value, and no further calculation is needed.
						
						// since it has now ben visited twice, and still no improvement was seen, we've made the best possible use of this square.
						// so commit its g value to memory.
						closed_set[getFreeNeighborIndices(lowest_f_index)[i]] = open_g_values[getFreeNeighborIndices(lowest_f_index)[i]];						
					}

					// newer g value is better. trivial set of steps for a new square discovered. except its parent and open_g_value is already assigned.
					else
					{
						// assign current point as parent
						parent_tracker[getFreeNeighborIndices(lowest_f_index)[i]] = lowest_f_index;
						
						// recalculate g value.
						open_g_values[getFreeNeighborIndices(lowest_f_index)[i]] = initweights[i] + closed_set[lowest_f_index];

						// recalculate f value.
						new_f = open_g_values[getFreeNeighborIndices(lowest_f_index)[i]] + heuristicManhattan(getFreeNeighborIndices(lowest_f_index)[i], goal_index);
						
						// penalize change in direction
						new_f += direction_difference * direction_penalty;

						open_f_values[getFreeNeighborIndices(lowest_f_index)[i]] = new_f;

						// visiting this point this time caused an improvement, so don't commit its g value yet. this point might be improved further.
					}
				}

				// at this point, we now have the most updated open set f values for the next iteration of the overall while loop, where the next step will be calculated.
				// further, we have all the parents for all the points on the open_f_values (make sure this is true! parent is needed!)
				// we now select the minimum of the 8 f values to continue the search
				if (new_f < min_f)
				{
					min_f = new_f;
					temp_lowest_f_index = getFreeNeighborIndices(lowest_f_index)[i];
					cur_direction = temp_lowest_f_index - lowest_f_index;
					cur_direction = convertDirToAngle(cur_direction);
					// min_g = initweights[i];
				}
			}


			// no traversable neighbors found!!!
			// careful with this one. this means that the current point is fully surrounded by walls or, by points from the closed set.
			// what to do here?
			else
			{
				// in this case, it turns out that there is no way to go, and we're boxed in (or boxed out, really)
				// by design, f_min will be -1 if this case is true, and this will eventually cause loop termination with output of a failure
			}
		}
		// end of traversing all traversable neighbors



		// now do some checking to see if the goal has been reached, or if we're boxed in
		// after each step, check if the last addition to the closed set was the goal state. if yes, we reached the solution
		if (lowest_f_index == goal_index)
		{
			// solution found!
			ret_value = 1;
			break;
		}

		// however, if at any state, the min_f value drops below zero (more like, doesn't change from -1), this means that there are no other points left to search.
		// return no solution
		// check this
		else if (min_f < 0)
		{
			// no solution found
			ret_value = -1;
			break;
		}


		// if neither of the above cases, then keep looking!
		// use the temp_lowest_f_index to restart the search. this is handled at the starting of the loop.
		else
		{
			continue;
		}
	}

	return ret_value;
}




bool Solver::isPath(int index)
{
	bool flag = false;
	int iter = goal_index;

	while (parent_tracker[iter] != iter)
	{
		if (parent_tracker[iter] != index)
		{
			iter = parent_tracker[iter];
		}
		else
		{
			flag = true;
			break;
		}
	}
	return flag;
}


void Solver::setPath(int index)
{
	if (isPath(index))
	{
		points[index].setSolutionPath(true);
	}
}


int Solver::pathCost()
{
	return closed_set[goal_index];
}


void Solver::printBackPath()
{
	int next = goal_index;
	
	printf("Backtracked path is:\n");
	while (true)
	{
		if (parent_tracker[next] != next)
		{
			printf("%d ", next);
			next = parent_tracker[next];
		}
		else
		{
			break;
		}
	}
	printf("\n\n");
}


void Solver::consoleSolutionDraw()
{
	int gridpoints_in = getNumGridPoints();

	//printf("\n");
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
		else if (isPath(i))
		{
			printf("*");
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
	
	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	printf("\n\n\n\n");
}



int Solver::convertDirToAngle(int direction)
{
	if (direction == 1)
	{
		return 0;
	}
	else if (direction == -1)
	{
		return 180;
	}
	else if (direction == getXLength() + 1)
	{
		return -90;
	}
	else if (direction == -(getXLength() + 1))
	{
		return 90;
	}
	else if (direction == -getXLength())
	{
		return 45;
	}
	else if (direction == -(getXLength() + 2))
	{
		return 135;
	}
	else if (direction == getXLength() + 2)
	{
		return -45;
	}
	else if (direction == getXLength())
	{
		return -135;
	}
}