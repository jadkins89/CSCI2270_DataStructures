#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>

Graph::Graph() {}


Graph::~Graph() {}


void Graph::addEdge(std::string v1, std::string v2, int weight) {
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                }
            }
        }
    }
}


void Graph::addVertex(std::string name) {
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == name){
            found = true;
            std::cout << vertices[i].name << " found." << std::endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = name;
        v.districtID = -1;
        v.visited = false;
        v.parent = nullptr;
        vertices.push_back(v);
    }
}


void Graph::displayEdges() {
    //loop through all vertices and adjacent vertices
    for(int i = 0; i < vertices.size(); i++){
        std::cout << vertices[i].districtID << ":" << vertices[i].name << "-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            if (j == vertices[i].adj.size() - 1){
                std::cout << vertices[i].adj[j].v->name;
            }
            else {
                std::cout << vertices[i].adj[j].v->name << "***";
            }
        }
        std::cout << std::endl;
    }
}


void Graph::assignDistricts() {
	int dIDNum = 1;
	for (int i = 0; i < vertices.size(); i++) {
		if (!vertices[i].visited) {
			DFSLabel(vertices[i].name, dIDNum);
			dIDNum++;
		}
	}
}


void Graph::shortestPath(std::string startingCity, std::string endingCity) {
	vertex* startVert = findVertex(startingCity);
	vertex* endVert = findVertex(endingCity);

	if (startVert == nullptr || endVert == nullptr) {
		std::cout << "One or more cities doesn't exist" << std::endl;
		return;
	}
	if (startVert->districtID != endVert->districtID) {
		std::cout << "No safe path between cities" << std::endl;
		return;
	}
	if (startVert->districtID == -1) {
		std::cout << "Please identify the districts before checking distances" << std::endl;
		return;
	}
	bool pathComplete = false;

	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].visited = false;
		vertices[i].unweightedDistance = std::numeric_limits<int>::max();
	}
 
	startVert->visited = true;
	startVert->unweightedDistance = 0;
	startVert->parent = nullptr;
	std::queue<vertex*> vertexQ;
	vertexQ.push(startVert);
	while (!vertexQ.empty() && !pathComplete) {
		vertex* curV = vertexQ.front();
		vertexQ.pop();
		for (int i = 0; i < curV->adj.size(); i++) {
			if (!curV->adj[i].v->visited) {
				curV->adj[i].v->unweightedDistance = curV->unweightedDistance + 1;
				curV->adj[i].v->parent = curV;
				curV->adj[i].v->visited = true;
				vertexQ.push(curV->adj[i].v);
			}
		}
	}
	int hopCount = 0;
	vertex* curParent = endVert;
	std::stack<std::string> pathCities;
	pathCities.push(curParent->name);
	curParent = curParent->parent;
	while (curParent != nullptr) {
		pathCities.push(curParent->name);
		hopCount++;
		curParent = curParent->parent;
	}
	std::cout << hopCount;
	while (!pathCities.empty()) {
		std::cout << ", " << pathCities.top();
		pathCities.pop();
	}
	std::cout << std::endl;
}


void Graph::shortestWeightedPath(std::string startingCity, std::string endingCity) {
	vertex* startVert = findVertex(startingCity);
	vertex* endVert = findVertex(endingCity);

	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].visited = false;
		vertices[i].parent = nullptr;
		vertices[i].weightedDistance = std::numeric_limits<int>::max();
	}

	int curDist;
	int minDistance;
	vertex* solvedVertex;
	vertex* curV;
	vertex* curParent;
	if (startVert == nullptr || endVert == nullptr) {
		std::cout << "One or more cities doesn't exist" << std::endl;
		return;
	}
	if (startVert->districtID != endVert->districtID) {
		std::cout << "No safe path between cities" << std::endl;
		return;
	}
	if (startVert->districtID == -1) {
		std::cout << "Please identify the districts before checking distances" << std::endl;
		return;
	}

	startVert->visited = true;
	startVert->weightedDistance = 0;
	std::vector<vertex*> solvedVertices;
	solvedVertices.push_back(startVert);
	while (!endVert->visited) {
		minDistance = INT_MAX;
		for (int i = 0; i < solvedVertices.size(); i++) {
			curV = solvedVertices[i];
			for (int j = 0; j < curV->adj.size(); j++) {
				if (!curV->adj[j].v->visited) {
					curDist = curV->weightedDistance + curV->adj[j].weight;
					if (curDist < minDistance) {
						solvedVertex = curV->adj[j].v;
						minDistance = curDist;
						curParent = curV;
					}
				}
			}
		}
		solvedVertex->weightedDistance = minDistance;
		solvedVertex->parent = curParent;
		solvedVertex->visited = true;
		solvedVertices.push_back(solvedVertex);
	}

	curParent = endVert;
	std::stack<std::string> pathCities;
	pathCities.push(curParent->name);
	std::cout << curParent->weightedDistance;
	curParent = curParent->parent;
	while (curParent != nullptr) {
		pathCities.push(curParent->name);
		curParent = curParent->parent;
	}
	while (!pathCities.empty()) {
		std::cout << ", " << pathCities.top();
		pathCities.pop();
	}
	std::cout << std::endl;
}


vertex* Graph::findVertex(std::string name) {
	int i = 0;
	while (i < vertices.size()) {
		if (vertices[i].name == name) {
			return &vertices[i];
		}
		i++;
	}
	return nullptr;
}


void Graph::DFSLabel(std::string startingCity, int distID) {
	vertex* currentVert = findVertex(startingCity);
	if (currentVert != nullptr) {
		currentVert->visited = true;
		currentVert->districtID = distID;
		std::stack<vertex*> vertStack;
		vertStack.push(currentVert);
		while (!vertStack.empty()) {
			vertex* curV = vertStack.top();
			vertStack.pop();
			for (int i = 0; i < curV->adj.size(); i++) {
				if (!curV->adj[i].v->visited) {
					curV->adj[i].v->visited = true;
					vertStack.push(curV->adj[i].v);
				}
				curV->adj[i].v->districtID = distID;
			}
		}
	}
}
