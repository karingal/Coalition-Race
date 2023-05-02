#pragma once
#include <vector>
#include <string>

using std::vector;
using std::string;
class Simulation;

class JoinPolicy {
public:
    virtual ~JoinPolicy() = default;
    virtual int join(vector<int> &offers, Simulation &s) = 0;
    virtual JoinPolicy* clone()=0;
};

class MandatesJoinPolicy : public JoinPolicy {
public:
    int join(vector<int> &offers, Simulation &s) override;
    JoinPolicy* clone();
};

class LastOfferJoinPolicy : public JoinPolicy {
public:
    int join(vector<int> &offers, Simulation &s) override; 
    JoinPolicy* clone();
};