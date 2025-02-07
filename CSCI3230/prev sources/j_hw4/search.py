# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
# 
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).

# If you have any question, ask in Piazza or email me (mxchen21@cse.cuhk.edu.hk)
# DO NOT copy the answer from any website. You can refer to tutorial slides, but try it by yourself first! 


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

from sys import path
import util

class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions
    s = Directions.SOUTH
    w = Directions.WEST
    return  [s, s, w, s, w, w, s, w]

def depthFirstSearch(problem):
    """ 
    Question 1: Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print("Start:", problem.getStartState())
    print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    print("Start's successors:", problem.getSuccessors(problem.getStartState()))

    You only need to submit this file. Do not change other files!
    If you finish this function, you almost finish all the questions!
    Read util.py to find suitable data structure!
    All you need is pass all the code in commands.txt
    """

    # SOLUTION 1 iterative function
    "*** YOUR CODE HERE ***"
    def iterativeDFS():
        # Initialize the frontier stack with the start state
        # Stack elements are tuples: (state, actions to reach state)
        frontier = util.Stack()
        frontier.push((problem.getStartState(), []))

        # Set to keep track of visited states
        explored = set()

        while not frontier.isEmpty():
            state, actions = frontier.pop()

            # Skip if we've already visited this state
            if state in explored:
                continue

            # Check if we've reached the goal
            if problem.isGoalState(state):
                return actions

            # Mark state as explored
            explored.add(state)

            # Add successors to frontier
            for nextState, action, cost in problem.getSuccessors(state):
                if nextState not in explored:
                    frontier.push((nextState, actions + [action]))

        return []  # No solution found


    # SOLUTION 2 recursive function
    "*** YOUR CODE HERE ***"
    def recursiveDFS():
        explored = set()

        def dfs_helper(state):
            # Base case: goal reached
            if problem.isGoalState(state):
                return []

            # Mark current state as explored
            explored.add(state)

            # Recursively explore successors
            for nextState, action, cost in problem.getSuccessors(state):
                if nextState not in explored:
                    result = dfs_helper(nextState)
                    if result is not None:  # If path found
                        return [action] + result

            return None  # No path found

        return dfs_helper(problem.getStartState()) or []

    return iterativeDFS()


def breadthFirstSearch(problem):
    """Question 2: Search the shallowest nodes in the search tree first."""

    "*** YOUR CODE HERE ***"
    frontier = util.Queue()
    frontier.push((problem.getStartState(), []))

    # Set to keep track of explored states
    explored = set()

    while not frontier.isEmpty():
        state, actions = frontier.pop()

        # Check if we've reached the goal
        if problem.isGoalState(state):
            return actions

        # Skip if we've already explored this state
        if state in explored:
            continue

        # Mark state as explored
        explored.add(state)

        # Add successors to frontier
        for nextState, action, cost in problem.getSuccessors(state):
            if nextState not in explored:
                frontier.push((nextState, actions + [action]))

    return []  # No solution found


def uniformCostSearch(problem):
    """Question 3: Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"
    # Initialize priority queue with start state, empty action list, and zero cost
    # Queue elements are: (state, actions, cumulative cost)
    frontier = util.PriorityQueue()
    frontier.push((problem.getStartState(), [], 0), 0)

    # Dictionary to keep track of explored states and their costs
    explored = {}  # state -> cost

    while not frontier.isEmpty():
        state, actions, currentCost = frontier.pop()

        # Check if we've reached the goal
        if problem.isGoalState(state):
            return actions

        # Skip if we've already found a cheaper path to this state
        if state in explored and explored[state] <= currentCost:
            continue

        # Mark state as explored with its cost
        explored[state] = currentCost

        # Add successors to frontier
        for nextState, action, stepCost in problem.getSuccessors(state):
            newCost = currentCost + stepCost
            if nextState not in explored or newCost < explored[nextState]:
                frontier.push((nextState, actions + [action], newCost), newCost)

    return []  # No solution found


def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):
    """Question 4: Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"
    # Initialize priority queue with start state
    # Queue elements are: (state, actions, g_cost)
    # Priority is f_cost = g_cost + h_cost
    frontier = util.PriorityQueue()
    startState = problem.getStartState()
    frontier.push((startState, [], 0), heuristic(startState, problem))

    # Dictionary to keep track of explored states and their g_costs
    explored = {}  # state -> g_cost

    while not frontier.isEmpty():
        state, actions, g_cost = frontier.pop()

        # Check if we've reached the goal
        if problem.isGoalState(state):
            return actions

        # Skip if we've already found a cheaper path to this state
        if state in explored and explored[state] <= g_cost:
            continue

        # Mark state as explored with its g_cost
        explored[state] = g_cost

        # Add successors to frontier
        for nextState, action, stepCost in problem.getSuccessors(state):
            new_g_cost = g_cost + stepCost
            if nextState not in explored or new_g_cost < explored[nextState]:
                # f_cost = g_cost + h_cost
                f_cost = new_g_cost + heuristic(nextState, problem)
                frontier.push((nextState, actions + [action], new_g_cost), f_cost)

    return []  # No solution found



# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
