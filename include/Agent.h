#pragma once

#include <vector>
#include "Graph.h"

class SelectionPolicy;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    Agent(const Agent &other);
    Agent& operator=(const Agent &other);
    ~Agent();
    Agent(Agent &&other);
    Agent& operator=(Agent &&other);

    int getPartyId() const;
    int getId() const;
    void step(Simulation &);
    void setCoalition(int coalitionId);
    const int getCoalition() const;
    void cloneAgent(int partyId, Simulation &sim) const;
    void setId(int agentId);
    void setPartyId(int partyId);    

private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    int mCoalitionId;
    bool isCoalitionExists(vector<int> offers, int offerToSearch, Simulation &s);
};
