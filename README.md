# Coalition-Race
the SPLand president decided to change the method of forming a coalition by letting multiple "agents" from different parties try their best to create a 61 coalition as fast as possible. this is a C++ program that simulates the "Coalition Race" and report the first coalition formed (or failure).

Additional information about implementation:

The simulator should be based on a graph that contains:

● Parties as vertices

● Collaborations as edges (2 parties that agree to cooperate)

● “Similarity score” as edge weight, for every 2 connected parties

Here is an example for a graph at the beginning of the simulation. The colors represent the state of the parties (will be explained later).

![image](https://user-images.githubusercontent.com/104310099/235743344-3a83e78f-b7b9-42c3-8841-1b97833fcd8f.png)

The program will receive a config file (JSON) as input, which includes the parties' details (id, name, number of mandates, join policy), the graph, and the list of agents (id, party id, selection policy). “Join policy” and “Selection policy” will be explained later. Each agent belongs to a party. In every step, the agent offers an adjacent party to join. When a party has decided to join a coalition, it should clone the agent who made the offer to the newly joined party (so the joined party can now help the coalition). To clarify:

● Coalition is a set of connected parties (in SPLand, connectivity is enough).

● In each party, there is a single agent if the party belongs to a coalition (state Joined).

● The total number of agents in the simulation equals the number of parties in the graph belonging to some coalition (state Joined).

Example

Suppose an agent from party#0 offered party#1 to join its coalition. If party#1 accepts the offer, it adds itself to the coalition and adds a clone of the agent to the vector of agents (as well as updating the id and party id).

![image](https://user-images.githubusercontent.com/104310099/235743393-4f370849-28f2-4d0e-aadb-022c3dc84002.png)

3.1 Classes

Parser – This is a class with static methods only, that is responsible for parsing from JSON to object of class Simulation and the other way around.

Simulation - This class is responsible for managing the simulation resources and making simulation steps (described in The program flow). This object is created by Parser using the initial values from the JSON configuration file. The Simulation object contains

● Graph

● Vector of Agents

Graph – This class is represented by an adjacency matrix (edges) and parties vector (vertices). Since the graph is undirected, you may assume that the matrix is symmetric. Note that an edge exists if and only if the weight is greater than 0.

Party – A vertex in the graph. Each party has an id, name, number of mandates, join policy and party state. The states are:

Waiting - the party is not a part of any coalition yet, and also didn’t get offers yet.
CollectingOffers - after receiving the first offer, the party changes its state and starts collecting offers from Agents for joining coalitions. The party has a “cooldown” - a timer of exactly 3 iterations, until moving to the next state by joining some coalition. Note, if a party got the first offer at the end of iteration 𝑖, it will join some coalition at the beginning of iteration 𝑖 + 3. Note - the iteration is counted even if the party did not get an offer in that iteration.
Joined - after 3 iterations, the party uses JoinPolicy::join(...) method for deciding which offer to accept. After joining a coalition, the party’s state won’t change anymore and it cannot join any other coalitions.
Agent – This class has agentId, partyId (each agent associated with a single party), and selection policy. In each step, an agent is trying to select a neighboring party (in the graph) using SelectionPolicy::select(...) and offers the party to join its coalition.

SelectionPolicy - an abstract class that represents a strategy algorithm for selecting the next party to offer. It has the abstract method SelectionPolicy::select(...) that will be implemented in the derived classes:

● MandatesSelectionPolicy - Selects the neighboring party with the most mandates.

● EdgeWeightSelectionPolicy - Selects the neighboring party with the highest edge weight.

If the maximum mandates/edge weight is not unique, take the first party (with the lower id).

JoinPolicy - an abstract class that represents a strategy algorithm for choosing which offer to accept and which coalition to join. It has JoinPolicy::join(...) abstract method that will be implemented in the derived classes:

● MandatesJoinPolicy - Selects the coalition with the largest number of mandates. Note that this refers to the number of mandates in the iteration when the offer is accepted. If the number of mandates is not unique, join the coalition that offered first.

● LastOfferJoinPolicy - Selects the coalition that made the last offer.

3.2 The program flow

It is recommended to follow the main.cpp implementation we supplied while reading this section. The program receives the config file's path as the first command line argument. Once the program starts, it parses the config file and creates a “Simulation” object. The format of the file is JSON, which is a very common format for object representation. The main function checks every iteration if the termination conditions are satisfied (described in Termination conditions). Until they are satisfied, the main function calls the Simulation::step() method and saves the state of the simulation as JSON. At the end of the simulation, the results list will be written to an output file (this is how we can grade your solution). All the file-handling methods are implemented for you in the supplied code. The flow of Simulation::step() is applying Party::step(Simulation& s) for each party (from graph) and then applying Agent::step(Simulation& s) for each agent (keep the original order). The flow of Party::step(Simulation& s) is to check if the status is CollectingOffers and update the timer if so. Once the timer of 3 iterations is done - join some coalition (using the JoinPolicy). When joining, the party’s state should be changed to Joined and the agent must be cloned. The flow of Agent::step(Simulation& s) is to select a party using SelectionPolicy::select(...) and then offer the party to join the coalition (in which the agent is a member). The selection of the party is from the set of parties that satisfy the conditions:

The party is a neighbor of the party to which the agent belongs.
The party is in Waiting or in CollectingOffers state.
The party did not already receive an offer from any agent from the coalition to which the agent belongs. That is, if an agent from a coalition offers a party to join, other agents from the same coalition should not select the party (this might be a waste of an offer). When there are no parties to select from, the agent is idle.
3.3 Configuration file format

The configuration file is given in a JSON format, and it contains a dictionary (hash map) with the following entries:

● parties - list of objects with name, mandates, join_policy.

● graph - a 2D list that represents the adjacency matrix.

● agents - list of objects with party_id, selection_policy.

The agentId and the partyId members are based on the index of the object in the list. When you clone an agent, make sure to change those fields in the cloned object. You may assume that the config file is valid, i.e. it is a JSON file that contains the mentioned dictionary, the adjacency matrix is a symmetric 𝑁 × 𝑁 matrix (when 𝑁 is the number of parties), and the number of mandates sums to 120. Parsing of JSON is easy in C++ using Niels Lohman's JSON for Modern C++ - an open-source project. If you want, you can learn how to use this package, and see examples here.

3.4 Termination Conditions

The program terminates when one of the coalitions reaches at least 61 mandates or when all the parties have already joined a coalition (all parties are in state Joined). You may assume that any given input leads to one of these conditions.

3.5 Output

The program creates a “.out” file in JSON format (which is a bit different from the input JSON). The parser is doing this part for you, but you will have to implement the methods marked with “TODO” in the skeleton files.

3.6 Full Example

Now we will follow a full simulation example based on the “01.json” config file we supplied to you. Take a look at it.

At the beginning of the simulation, it initialized with 4 parties, 2 agents, and 2 coalitions ({party#0}, {party#3}).
At Iteration#0:
No parties in CollectingOffers state - pass.
Agent#0 selects from the set {party#2} using EdgeSelectionPolicy and offers party#2.
Agent#1 selects from the set {party#1, party#2} using EdgeSelectionPolicy and offers party#2.
![image](https://user-images.githubusercontent.com/104310099/235743499-58df958f-a369-4b84-9d6f-b68eb2d0f36c.png)

At Iteration#1:
Party#2 in CollectingOffers state but the timer is not done - pass.
Agent#0 has no parties to select from - pass.
Agent#1 selects from the set {party#1} using EdgeSelectionPolicy and offers party#1.
At Iteration#2:
Party#1 and Party#2 in CollectingOffers state but both timers are not done - pass.
Agents have no parties to select from - pass.
![image](https://user-images.githubusercontent.com/104310099/235743533-bb8cdd57-f6d0-4b6b-89fb-14da022dff8b.png)

At Iteration#3:
Party#1 in CollectingOffers state but timer not done - pass.
Party#2 in CollectingOffers state and timer is done - joining using LastOfferJoinPolicy to coalition#1 and clone agent#1.
Agents have no parties to select from - pass
At Iteration#4:
Party#1 in CollectingOffers state and timer is done - joining using MandatesJoinPolicy to coalition#1 and clone agent#1.
Agents have no parties to select from - pass.
![image](https://user-images.githubusercontent.com/104310099/235743572-2f81c437-4a38-423b-b921-1ea7d89f7f5d.png)
