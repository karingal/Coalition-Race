#include "SelectionPolicy.h"
#include "Simulation.h"
#include <vector>
#include <algorithm>

using std::vector;

SelectionPolicy* EdgeWeightSelectionPolicy::clone()
{
     return new EdgeWeightSelectionPolicy(*this);
}

int EdgeWeightSelectionPolicy::select(int partyId, vector<int> &candidates, Graph &graph)
{
    int numOfParties = graph.getNumVertices();
    vector<int> weightPerParty(numOfParties, -1);
    for (int candidate: candidates) {
        int edgeWeight = graph.getEdgeWeight(partyId, candidate);
        weightPerParty[candidate] = edgeWeight;
    }
    vector<int>::iterator maxValueIt;
    maxValueIt = max_element(weightPerParty.begin(), weightPerParty.end());
    int maxParty = distance(weightPerParty.begin(), maxValueIt);
    return maxParty;
}