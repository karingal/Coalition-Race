#include "Agent.h"
#include "Simulation.h"
#include "SelectionPolicy.h"
#include <string>
// #include <typeinfo>
// #include <iostream>

using namespace std;


Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy), mCoalitionId(mAgentId)
{
    
}

//copy-constructor
Agent::Agent(const Agent& other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy->clone()), mCoalitionId(other.mCoalitionId)
{

}

// copy assignment operator
Agent &Agent::operator=(const Agent &other)
{
    if (&other != this) {
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        mCoalitionId = other.mCoalitionId;
        mSelectionPolicy = other.mSelectionPolicy->clone();
        delete mSelectionPolicy;
    }
    return *this;
}

//destructor
Agent::~Agent() 
{
    if (mSelectionPolicy) delete mSelectionPolicy;
} 

// move assignment operator
Agent &Agent::operator=(Agent &&other)
{
    if (&other != this) {
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        mCoalitionId = other.mCoalitionId;
        if (mSelectionPolicy) delete mSelectionPolicy;
        mSelectionPolicy = other.mSelectionPolicy;
        other.mSelectionPolicy = nullptr;
    }   
    return *this;
}

//move constructor
Agent::Agent(Agent &&other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy), mCoalitionId(other.mCoalitionId)
{
    other.mSelectionPolicy = nullptr;
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::step(Simulation &sim)
{
    vector<int> candidates;
    Graph &g1 = sim.getGraphNew();
    const vector<int> neighbors = g1.getNeighbors(mPartyId);
    for (int neighbor: neighbors) {
        Party &party = g1.getPartyNew(neighbor);
        if (party.getState() != State::Joined) {
            const vector<int> &offers = party.getOffers();
            if (!isCoalitionExists(offers,mCoalitionId, sim)) {
                candidates.push_back(neighbor);
            }
        }
    }
    if (!candidates.empty()){
        int selectedPartyId = mSelectionPolicy->select(mPartyId, candidates, g1);
        Party &party = g1.getPartyNew(selectedPartyId);
        party.addOffer(mAgentId);
        party.setState(State::CollectingOffers);
    }
}

const int Agent::getCoalition() const
{
    return mCoalitionId;
}

void Agent::setCoalition(int coalitionId)
{
    mCoalitionId = coalitionId;
}

bool Agent::isCoalitionExists(vector<int> offers, int offerToSearch, Simulation &s)
{
    for (int agentId: offers) {
        const vector<Agent> &agents = s.getAgents();
        const Agent &currAgent = agents[agentId];
        if (currAgent.getCoalition() == offerToSearch) {
            return true;
        }
    }
    return false;
}

void Agent::cloneAgent(int partyId,  Simulation &sim) const
{
    int size = sim.getAgents().size();
    int newAgentId = size;
    Agent newAgent(*this);
    newAgent.setId(newAgentId);
    newAgent.setPartyId(partyId);
    sim.addAgent(newAgent);
}

void Agent::setId(int agentId)
{
    mAgentId = agentId;
}

void Agent::setPartyId(int partyId)
{
    mPartyId = partyId;
}


