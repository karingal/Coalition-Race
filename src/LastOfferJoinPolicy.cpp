#include "JoinPolicy.h"
#include "Agent.h"
#include "Simulation.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

JoinPolicy* LastOfferJoinPolicy::clone()
{
     return new LastOfferJoinPolicy(*this);
}


int LastOfferJoinPolicy::join(vector<int> &offers, Simulation &s)
{
    int n = offers.size();
    int selectedAgentId = offers[n-1];
    const vector<Agent> &agents = s.getAgents();
    const Agent &currAgent = agents[selectedAgentId];
    int selectedCoalition = currAgent.getCoalition();
    return selectedCoalition;
}