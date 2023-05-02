#include "JoinPolicy.h"
#include "Agent.h"
#include "Party.h"
#include "Simulation.h"
#include <vector>
#include <algorithm>
#include <string>

using std::vector;
using std::string;

JoinPolicy* MandatesJoinPolicy::clone()
{
     return new MandatesJoinPolicy(*this);
}

int MandatesJoinPolicy::join(vector<int> &offers, Simulation &s)
{
    int numOfCoalitions = s.getNumOfCoalitions();
    vector<int> mandatesPerCoalition(numOfCoalitions, -1);
    for (int agentId: offers) {
        const vector<Agent> &agents = s.getAgents();
        const Agent &currAgent = agents[agentId];
        int coalitionId = currAgent.getCoalition();
        vector<vector<int>> coalitions = s.getPartiesByCoalitions();
        int sumMandates = 0;
        for (int partyId: coalitions[coalitionId]) {
            const Graph &graph = s.getGraph();
            const Party &party = graph.getParty(partyId);
            sumMandates += party.getMandates();
        }
        mandatesPerCoalition[coalitionId] = sumMandates;
    }

    vector<int>::iterator maxValueIt;
    maxValueIt = max_element(mandatesPerCoalition.begin(), mandatesPerCoalition.end());
    int maxCoalition = distance(mandatesPerCoalition.begin(), maxValueIt);
    return maxCoalition;
}