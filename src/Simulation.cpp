#include "Simulation.h"
#include <vector>

using std::vector;

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents), mNumOfCoalitions(mAgents.size()), mPartiesByCoalitions()
{
    for (int i = 0; i<mNumOfCoalitions; i++) {
        vector<int> temp;
        temp.push_back(mAgents[i].getPartyId());
        mPartiesByCoalitions.push_back(temp);
    }
}

void Simulation::step()
{
    for (int partyId = 0; partyId<mGraph.getNumVertices(); partyId++) {
        Party &party = mGraph.getPartyNew(partyId);
        party.step(*this);
    }
    for (Agent &agent: mAgents) {
        agent.step(*this);
    }
}

bool Simulation::shouldTerminate() const
{
    vector<vector<int>> coalitions = getPartiesByCoalitions();
    for (vector<int> &coalition: coalitions) {
        int sumMandates = 0;
        for (int partyId: coalition) {
            const Party &party = mGraph.getParty(partyId);
            sumMandates += party.getMandates();
            if (sumMandates >= 61) {
                return true;
            }
        }
    }
    for (int partyId = 0; partyId<mGraph.getNumVertices(); partyId++) {
        if (mGraph.getParty(partyId).getState() != State::Joined) {
            return false;
        }
    }
    return true;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

Graph &Simulation::getGraphNew()
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

void Simulation::addAgent(Agent newAgent) {
    mAgents.push_back(newAgent);
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    return mPartiesByCoalitions;
}

int Simulation::getNumOfCoalitions() 
{
    return mNumOfCoalitions;
}

void Simulation::addPartyToCoalition(int coalitionId, int partyId) 
{
    vector<int> &coalition = mPartiesByCoalitions[coalitionId];
    coalition.push_back(partyId);
}