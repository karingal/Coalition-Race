#include "Party.h"
#include <vector>
#include "Agent.h"
#include "Simulation.h"
#include "JoinPolicy.h"

using std::vector;

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting), mTimer(0), mOffers()
{

}

//copy-constructor
Party::Party(const Party& other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy->clone()) , mState(other.mState), mTimer(other.mTimer), mOffers(other.mOffers)
{

}

// copy assignment operator
Party &Party::operator=(const Party &other)
{
    if (&other != this) {
        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;
        mState = other.mState;
        mTimer = other.mTimer;
        mOffers = other.mOffers;
        delete mJoinPolicy;
        mJoinPolicy = other.mJoinPolicy->clone();
    }
    return *this;
}

//destructor
Party::~Party()
{
    if (mJoinPolicy) delete mJoinPolicy;
}

// move assignment operator
Party &Party::operator=(Party &&other)
{
    if (&other != this) {
    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;
    mState = other.mState;
    mTimer = other.mTimer;
    mOffers = other.mOffers;
    if (mJoinPolicy) delete mJoinPolicy;
    mJoinPolicy = other.mJoinPolicy;
    other.mJoinPolicy = nullptr;
    }   
    return *this;
}

//move constructor
Party::Party(Party &&other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState), mTimer(other.mTimer), mOffers(other.mOffers) 
{
  other.mJoinPolicy = nullptr;
}

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}

void Party::step(Simulation &s)
{
    if (mState == State::CollectingOffers) {
        mTimer += 1;
        if (mTimer == 3) {
            int agentId = mJoinPolicy->join(mOffers,s);
            const vector<Agent> &agents = s.getAgents();
            const Agent &currAgent = agents[agentId];
            mState = State::Joined;
            currAgent.cloneAgent(mId, s);
            s.addPartyToCoalition(currAgent.getCoalition(),mId);
        }
    }
}

const vector<int> &Party::getOffers() const
{
    return mOffers;
}

const void Party::addOffer(int agentId)
{
    mOffers.push_back(agentId);
}
