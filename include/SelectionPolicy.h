#pragma once
#include <vector>
#include <string>

using std::vector;
using std::string;
class Graph;

class SelectionPolicy {
public:
    virtual ~SelectionPolicy() = default;
    virtual int select(int partyId, vector<int> &candidates, Graph &graph) = 0;
    virtual SelectionPolicy* clone()=0;
};


class MandatesSelectionPolicy: public SelectionPolicy {
public:
    int select(int partyId, vector<int> &candidates, Graph &graph) override;
    SelectionPolicy* clone();
};

class EdgeWeightSelectionPolicy: public SelectionPolicy {
public:
    int select(int partyId, vector<int> &candidates, Graph &graph) override;
    SelectionPolicy* clone();
};