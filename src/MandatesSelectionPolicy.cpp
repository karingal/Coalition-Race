#include "SelectionPolicy.h"
#include "Simulation.h"
#include <vector>
#include <string>
#include <algorithm>

using std::vector;
using std::string;

SelectionPolicy* MandatesSelectionPolicy::clone()
{
     return new MandatesSelectionPolicy(*this);
}

int MandatesSelectionPolicy::select(int partyId, vector<int> &candidates, Graph &graph)
{
    int numOfParties = graph.getNumVertices();
    vector<int> mandatesPerParty(numOfParties, -1);
    for (int candidate: candidates) {
        Party party = graph.getParty(candidate);
        int mandates = party.getMandates();
        mandatesPerParty[candidate] = mandates;
    }
    vector<int>::iterator maxValueIt;
    maxValueIt = max_element(mandatesPerParty.begin(), mandatesPerParty.end());
    int maxParty = distance(mandatesPerParty.begin(), maxValueIt);
    return maxParty;
}
