#include "grid.h"


class Solver
{
private:
	// private resources
	int x_len, y_len;
	int num_gridpoints;
	int num_obstacles;
	int start_index, goal_index;
	int* open_f_values;
	int* open_g_values;
	int* parent_tracker;
	int* closed_set;
	Point* points;

protected:
	// protected resources
	void cleanUp();
	void initialize(Grid grid);
	

	int getXLength();
	int getYLength();
	int getNumGridPoints();
	int getNumObstacles();
	bool isWall(int);
	bool isHorizontalWall(int);
	bool isVerticalWall(int);
	bool isTopWall(int);
	bool isBottomWall(int);
	bool isLeftWall(int);
	bool isRightWall(int);
	bool isValidIndex(int);
	int getStart();
	int getGoal();
	Point* getPoints();

	void setXLength(int);
	void setYLength(int);
	void setNumObstacles(int);
	void setNumGridPoints(int);
	void setStart(int);
	void setGoal(int);
	void setPoints(Point*);

	int* getFreeNeighborIndices(int);
	int* getNeighborInitWeights();

	void setPath(int);
	
	int idxToX(int idx_in, int xlen_in, int ylen_in);
	int idxToY(int idx_in, int xlen_in, int ylen_in);
	int XYtoIdx(int x_in, int y_in, int xlen_in, int ylen_in);

public:
	// public resources
	Solver(Grid grid);
	Solver::Solver(const Solver &incoming);
	Solver &Solver::operator=(const Solver &incoming);
	~Solver();
	void dynamicReinitialize(Grid grid);

	int heuristicManhattan(int, int);
	int heuristicQuickCostlyManhattan(int, int, int);

	int solveAstar(int, int);
	bool isPath(int);
	int pathCost();
	void printBackPath();
	void consoleSolutionDraw();
	int convertDirToAngle(int direction);
};