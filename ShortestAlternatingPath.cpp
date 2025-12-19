

//Leetcode 1129


/*

You are given an integer n, the number of nodes in a directed graph where the nodes are labeled from 0 to n - 1. Each edge is red or blue in this graph, and there could be self-edges and parallel edges.

You are given two arrays redEdges and blueEdges where:

redEdges[i] = [ai, bi] indicates that there is a directed red edge from node ai to node bi in the graph, and
blueEdges[j] = [uj, vj] indicates that there is a directed blue edge from node uj to node vj in the graph.
Return an array answer of length n, where each answer[x] is the length of the shortest path from node 0 to node x such that the edge colors alternate along the path, or -1 if such a path does not exist.

 

Example 1:

Input: n = 3, redEdges = [[0,1],[1,2]], blueEdges = []
Output: [0,1,-1]
Example 2:

Input: n = 3, redEdges = [[0,1]], blueEdges = [[2,1]]
Output: [0,1,-1]



*/
#include <iostream>
#include <vector>
#include <queue>



using namespace std; 

class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        
        vector<vector<pair<int,int>>> adj(n);
        for(auto& edge: redEdges) adj[edge[0]].push_back({edge[1], 0});
        for(auto& edge: blueEdges) adj[edge[0]].push_back({edge[1], 1});

        
        vector<vector<int>> dist(n, vector<int>(2, -1));

        queue<pair<int,int>> q;

        q.push({0, 0}); 
        q.push({0, 1});
        dist[0][0] = 0;
        dist[0][1] = 0;

        while(!q.empty()) {
           
            auto [currNode, prevColor] = q.front();
            q.pop();

            for(auto& [neighbor, edgeColor] : adj[currNode]) {
                
                if(prevColor == edgeColor) continue;

               
                if(dist[neighbor][edgeColor] == -1) {
                    dist[neighbor][edgeColor] = dist[currNode][prevColor] + 1;
                    q.push({neighbor, edgeColor}); 
                }
            }
        }

        
        vector<int> res(n);
        for(int i = 0; i < n; i++) {
            int d1 = dist[i][0];
            int d2 = dist[i][1];
            
            if (d1 == -1 && d2 == -1) res[i] = -1;
            else if (d1 == -1) res[i] = d2;
            else if (d2 == -1) res[i] = d1;
            else res[i] = min(d1, d2);
        }
        
        return res;
    }
};