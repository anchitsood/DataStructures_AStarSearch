#include "solver.h"
#include <stdio.h>


Solver iterateOverPenalties(Grid grid, int penalty_limits, int heuristic_scaleup);
// initializes a solver object, that uses a weighted heuistic for faster search, plus it penalizes any change in direction.
// it runs the search iteratively from -penalty_limits to penalty_limits, and settles on the least costly path that it gets


int main()
{
	
	// test grid 0
	Grid grid0 = Grid(10, 7, false);
	grid0.setLineObstacle(27, 2, true);
//	grid0.setLineObstacle(39, 200, true);

	grid0.setStart(36);
	grid0.setGoal(40);

	grid0.consoleDraw();
	Solver solver0 = iterateOverPenalties(grid0, 20, 1);

	grid0.swapStates();
	solver0 = iterateOverPenalties(grid0, 20, 1);

		




	// test grid A
	Grid gridA = Grid(10, 7, false);
	gridA.setLineObstacle(15, 4, true);
	gridA.setLineObstacle(39, 200, true);
	
	gridA.setStart(-1);
	gridA.setGoal(-1);
	
	gridA.consoleDraw();

	Solver solverA = iterateOverPenalties(gridA, 20, 1);


	//Solver solverA = Solver(gridA);
	//solverA.solveAstar(15, 1);
	//solverA.consoleSolutionDraw();
	





	// test grid B
	Grid gridB = Grid(10, 7, false);
	gridB.setLineObstacle(15, 4, true);
	gridB.setLineObstacle(39, 200, true);

	gridB.setStart(75);
	gridB.setGoal(12);

	gridB.consoleDraw();

	Solver solverB = iterateOverPenalties(gridB, 20, 1);






	Grid gridC = Grid(75, 50, false);
	gridC.setLineObstacle(90, 50, true);

	//gridC.setInterleavedObstacle(390, 5, true);
	
	gridC.consoleDraw();

	Solver solverC = iterateOverPenalties(gridC, 10, 10);





	Grid gridD = Grid(75, 50, false);
	gridD.setLineObstacle(1000, 47, false);
	gridD.setLineObstacle(1048, 25, true);
	//gridD.setInterleavedObstacle(390, 30, true);

	gridD.setStart(2600);
	gridD.setGoal(600);

	//gridD.swapStates();
	gridD.consoleDraw();

	Solver solverD = iterateOverPenalties(gridD, 30, 5);




}




Solver iterateOverPenalties(Grid grid, int penalty_limits, int heuristic_scaleup)
{
	Solver solver = Solver(grid);
	int solution = -1;
	int min_cost = 14 * grid.getNumGridPoints();
	int opt_penalty = -penalty_limits;

	for (int i = -penalty_limits; i <= penalty_limits; i++)
	{
		int this_cost = 14 * grid.getNumGridPoints();

		solution = solver.solveAstar(i, heuristic_scaleup);
		if (solution == 1)
		{
			this_cost = solver.pathCost();
			if (this_cost < min_cost)
			{
				min_cost = this_cost;
				opt_penalty = i;
			}
		}
		solver.dynamicReinitialize(grid);
	}

	if (min_cost < 14 * grid.getNumGridPoints())
	{
		solution = solver.solveAstar(opt_penalty, heuristic_scaleup);
		printf("Solution exists!\n");
		printf("Path cost: %d\n", min_cost);
		printf("Penalty function = %d\n", opt_penalty);
		solver.printBackPath();
		solver.consoleSolutionDraw();
	}
	else
	{
		printf("No solution exists within a penalty range of -%d to %d!\n", penalty_limits, penalty_limits);
	}

	return solver;
}