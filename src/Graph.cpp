#include "Graph.h"

Graph::Graph(vector<Party> vertices, vector<vector<int>> edges) : mVertices(vertices), mEdges(edges) 
{
    // You can change the implementation of the constructor, but not the signature!
}

int Graph::getMandates(int partyId) const
{
    return mVertices[partyId].getMandates();
}

int Graph::getEdgeWeight(int v1, int v2) const
{
    return mEdges[v1][v2];
}

int Graph::getNumVertices() const
{
    return mVertices.size();
}

const Party &Graph::getParty(int partyId) const
{
    return mVertices[partyId];
}

Party &Graph::getPartyNew(int partyId)
{
    return mVertices[partyId];
}

 vector<int> Graph::getNeighbors(int partyId) const
 {
     int numOfVertices = getNumVertices();
     vector<int> neighbors;
     for (int v2 = 0; v2<numOfVertices; v2++) {
         if (getEdgeWeight(partyId,v2) != 0) {
             neighbors.push_back(v2);
         }
     }
     return neighbors;
 }