#pragma once
#include <string>
#include <vector>

using std::vector;
using std::string;

class JoinPolicy;
class Simulation;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *);
    Party(const Party &other);
    ~Party();
    Party& operator=(const Party &other);
    Party(Party &&other);
    Party& operator=(Party &&other);

    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;
    const vector<int> &getOffers() const; 
    const void addOffer(int agentId);

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int mTimer;
    vector<int> mOffers; // vector of agentIds!
};
