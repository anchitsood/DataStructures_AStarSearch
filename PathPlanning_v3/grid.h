class Point
{
private:
	// private resources
	int x, y;
	int idx;
	bool obstacle;
	bool solution_path;

protected:
	// protected resources

public:
	// public resources
	int getX();
	void setX(int);

	int getY();
	void setY(int);

	int getIndex();
	void setIndex(int);

	bool isObstacle();
	void setObstacle(bool);

	bool isSolutionPath();
	void setSolutionPath(bool);

	void printPoint();

	Point();
	Point(int, int, int, bool, bool);
	~Point();

};






class Grid
{
private:
	// private resources
	int x_len, y_len;
	int num_gridpoints;
	int num_obstacles;
	Point* points;
	int start_index, goal_index;
	// Point startpoint, goalpoint;

protected:
	// protected resources
	void setXLength(int);
	void setYLength(int);
	void setNumGridPoints(int);
	void setNumObstacles(int);
	void setPoints(Point*);
	void cleanUp();
	void initialize();

public:
	// public resources
	int getXLength();
	int getYLength();
	int getNumGridPoints();
	int getNumObstacles();
	Point* getPoints();
	
	void setObstacle(int);
	void clearObstacle(int);
	bool isObstacle(int);

	void setObstacle(int, int);
	void clearObstacle(int, int);
	bool isObstacle(int, int);

	void setObstacles(int*, int*);
	void clearObstacles(int*, int*);

	int idxToX(int, int, int);
	int idxToY(int, int, int);
	int XYtoIdx(int, int, int, int);

	bool isWall(int);
	bool isHorizontalWall(int);
	bool isVerticalWall(int);
	bool isTopWall(int);
	bool isBottomWall(int);
	bool isLeftWall(int);
	bool isRightWall(int);

	void printPoints();

	void consoleDraw();
	void showAll();

	Grid();
	Grid(int, int);
	Grid(int, int, bool);
	Grid(const Grid &incoming);
	Grid &operator=(const Grid &incoming);
	~Grid();

	bool isValidIndex(int);

	int getStart();
	void setStart(int);
	int getGoal();
	void setGoal(int);

	void swapStates();

	void setLineObstacle(int, int, bool);
	void setLineObstacle(int, int, int, bool);

	void setInterleavedObstacle(int, int, bool);
};
