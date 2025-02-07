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
    Search the deepest nodes in the search tree first.

    Your search algorithm needs to return a list of actions that reaches the
    goal. Make sure to implement a graph search algorithm.

    To get started, you might want to try some of these simple commands to
    understand the search problem that is being passed in:

    print("Start:", problem.getStartState())
    print("Is the start a goal?", problem.isGoalState(problem.getStartState()))
    print("Start's successors:", problem.getSuccessors(problem.getStartState()))
    """
    "*** YOUR CODE HERE ***"
    
    # SOLUTION 1 iterative function
    # initialization
    fringe = util.Stack()
    visitedList = []

    #push the starting point into stack
    fringe.push((problem.getStartState(),[],0))
    #pop out the point
    (state,toDirection,toCost) = fringe.pop()
    #add the point to visited list
    visitedList.append(state)

    while not problem.isGoalState(state): #while we do not find the goal point
        successors = problem.getSuccessors(state) #get the point's successors
        for son in successors:
            if son[0] not in visitedList: # if the successor has not been visited,push it into stack
                fringe.push((son[0],toDirection + [son[1]],toCost + son[2])) 
                visitedList.append(son[0]) # add this point to visited list
        (state,toDirection,toCost) = fringe.pop()
    return toDirection

    # SOLUTION 1 recursive function
    # StartState = problem.getStartState()
    # visitedList = []

    # def dfs_recursive(CurrentState):
    #     visitedList.append(CurrentState[0])
    #     if not problem.isGoalState(CurrentState[0]):
    #         successors = problem.getSuccessors(CurrentState[0])
    #     else:
    #         return CurrentState[1]

    #     for son in successors:
    #         if son[0] not in visitedList: # if the successor has not been visited, do a DFS on it
    #             Path = dfs_recursive((son[0],CurrentState[1] + [son[1]],CurrentState[2] + son[2]))
    #             if Path:
    #                 return Path
    #     return False
    # StartState = (StartState,[],0)
    
    # return dfs_recursive(StartState)


def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""

    "*** YOUR CODE HERE ***"

    fringe = util.Queue()
    visitedList = []

    #push the starting point into stack
    fringe.push((problem.getStartState(),[],0))
    #pop out the point
    (state,toDirection,toCost) = fringe.pop()
    #add the point to visited list

    while not problem.isGoalState(state): #while we do not find the goal point
        if state not in visitedList:
            visitedList.append(state) # add this point to visited list
            successors = problem.getSuccessors(state) #get the point's successors
            for son in successors:
                if son[0] not in visitedList: # if the successor has not been visited,push it into queue
                    fringe.push((son[0],toDirection + [son[1]],toCost + son[2])) 
        (state,toDirection,toCost) = fringe.pop()
    return toDirection


def uniformCostSearch(problem):
    """Search the node of least total cost first."""
    "*** YOUR CODE HERE ***"

    fringe = util.PriorityQueue()
    visitedList = []

    #push the starting point into stack
    fringe.push((problem.getStartState(),[],0),0)
    #pop out the point
    (state,toDirection,toCost) = fringe.pop()

    while not problem.isGoalState(state): #while we do not find the goal point
        if state not in visitedList:
            visitedList.append(state) # add this point to visited list
            successors = problem.getSuccessors(state) #get the point's successors
            for son in successors:
                if son[0] not in visitedList: # if the successor has not been visited,push it into stack
                    fringe.push((son[0],toDirection + [son[1]],toCost + son[2]),toCost + son[2]) 
        (state,toDirection,toCost) = fringe.pop()
    return toDirection 

def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0

def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    "*** YOUR CODE HERE ***"

    fringe = util.PriorityQueue()
    visitedList = []

    #push the starting point into stack
    fringe.push((problem.getStartState(),[],0),0 + heuristic(problem.getStartState(), problem))
    #pop out the point
    (state,toDirection,toCost) = fringe.pop()

    while not problem.isGoalState(state): #while we do not find the goal point
        if state not in visitedList:
            visitedList.append(state) # add this point to visited list
            successors = problem.getSuccessors(state) #get the point's successors
            for son in successors:
                if son[0] not in visitedList: # if the successor has not been visited,push it into stack
                    fringe.push((son[0],toDirection + [son[1]],toCost + son[2]),toCost + son[2] + heuristic(son[0], problem)) 
        (state,toDirection,toCost) = fringe.pop()
    return toDirection 


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
