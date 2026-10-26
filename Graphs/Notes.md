# Graphs

> A central collection of graph concepts, algorithms, properties, and comparisons. Algorithm implementations are maintained separately in `.cpp` template files.

## Table of Contents

- [1. Graph Fundamentals](#1-graph-fundamentals)
  - [1.1 Basic Terminology](#11-basic-terminology)
  - [1.2 Directed and Undirected Graphs](#12-directed-and-undirected-graphs)
  - [1.3 Complete Graph](#13-complete-graph)
  - [1.4 Bipartite Graph](#14-bipartite-graph)
  - [1.5 Cyclic Graphs and DAGs](#15-cyclic-graphs-and-dags)
  - [1.6 Trees](#16-trees)
  - [1.7 Connected Components](#17-connected-components)
- [2. Graph Traversal Overview](#2-graph-traversal-overview)
- [3. Depth-First Search (DFS)](#3-depth-first-search-dfs)
  - [3.1 Applications](#31-applications)
  - [3.2 Parent Tracking and Path Reconstruction](#32-parent-tracking-and-path-reconstruction)
  - [3.3 Entry and Exit Times](#33-entry-and-exit-times)
  - [3.4 Ancestor Checking](#34-ancestor-checking)
  - [3.5 Depth and Subtree Size](#35-depth-and-subtree-size)
  - [3.6 Cycle Detection](#36-cycle-detection)
- [4. Breadth-First Search (BFS)](#4-breadth-first-search-bfs)
  - [4.1 Applications and Properties](#41-applications-and-properties)
  - [4.2 Shortest Paths](#42-shortest-paths)
  - [4.3 Connected Components](#43-connected-components)
  - [4.4 Bipartite Checking](#44-bipartite-checking)
  - [4.5 Multi-Source BFS](#45-multi-source-bfs)
  - [4.6 Grid BFS](#46-grid-bfs)
  - [4.7 Tree Diameter](#47-tree-diameter)
- [5. Topological Sorting](#5-topological-sorting)
  - [5.1 DFS using Pointer](#51-dfs-using-pointer)
  - [5.2 DFS using Vector](#52-dfs-using-vector)
  - [5.3 Kahn's Algorithm](#53-kahns-algorithm)
  - [5.4 Kahn's Algorithm — Level by Level](#54-kahns-algorithm--level-by-level)
  - [5.5 DFS Cycle Detection](#55-dfs-cycle-detection)
  - [5.6 Topological Sort Template — DFS](#56-topological-sort-template--dfs)
  - [5.7 Topological Sort Template — Kahn](#57-topological-sort-template--kahn)
  - [5.8 Choosing Between Them](#58-choosing-between-them)
- [6. Dijkstra's Algorithm](#6-dijkstras-algorithm)
  - [6.1 Properties and Complexity](#61-properties-and-complexity)
  - [6.2 Shortest Distance](#62-shortest-distance)
  - [6.3 Parent Tracking and Path Reconstruction](#63-parent-tracking-and-path-reconstruction)
  - [6.4 Counting Shortest Paths](#64-counting-shortest-paths)
  - [6.5 Minimum and Maximum Number of Edges](#65-minimum-and-maximum-number-of-edges)
  - [6.6 Important Conditions](#66-important-conditions)
- [7. DFS vs. BFS vs. Dijkstra](#7-dfs-vs-bfs-vs-dijkstra)
- [8. Quick Decision Guide](#8-quick-decision-guide)
- [9. Future Notes](#9-future-notes)

---

# 1. Graph Fundamentals

## 1.1 Basic Terminology

- **Vertex (Node):** An individual element of a graph.
- **Edge:** A connection between two vertices.
- **Degree:** The number of edges incident to a vertex in an undirected graph.
- **Path:** A sequence of vertices connected by edges.
- **Cycle:** A path that returns to its starting vertex without repeating other vertices, except that start/end vertex.
- **Weight:** A value assigned to an edge representing a cost, distance, time, or another quantity.
- **Neighbor:** A vertex directly connected to another vertex by an edge.
- **Reachability:** A vertex `v` is reachable from `u` if a path exists from `u` to `v`.

Notation:

- `n` = number of vertices.
- `m` = number of edges.
- `adj[u]` = adjacency list of vertex `u`.

For an undirected graph, each edge is usually stored in both endpoints' adjacency lists. For a directed graph, an edge `u -> v` is stored in `adj[u]`.

## 1.2 Directed and Undirected Graphs

### Undirected Graph

Edges have no direction.

If an edge connects `u` and `v`, we can travel in either direction:

`u — v`

### Directed Graph (Digraph)

Every edge has a direction:

`u -> v`

An edge from `u` to `v` does not necessarily allow travel from `v` to `u`.

## 1.3 Complete Graph

A **complete graph** is a simple graph in which every pair of distinct vertices is connected directly.

For an undirected complete graph with `n` vertices:

- Every vertex has degree `n - 1`.
- Number of edges: `n * (n - 1) / 2`.

For a directed complete graph with no self-loops and an edge in each direction between every pair:

- Every vertex has `n - 1` outgoing edges and `n - 1` incoming edges.
- Number of directed edges: `n * (n - 1)`.

## 1.4 Bipartite Graph

A graph is **bipartite** if its vertices can be divided into two disjoint sets such that every edge connects vertices belonging to different sets.

Properties:

- No edge connects two vertices in the same set.
- A bipartite graph can be colored using two colors so that adjacent vertices always have different colors.
- An undirected graph is bipartite if and only if it contains no odd-length cycle.

**How to check it:**

Use DFS or BFS to assign one of two colors to each vertex. If an edge connects two vertices with the same color, the graph is not bipartite.

For a disconnected graph, start a traversal from every unvisited vertex.

**Time complexity:** `O(n + m)`.

## 1.5 Cyclic Graphs and DAGs

### Directed Cyclic Graph

A directed graph containing at least one directed cycle.

A directed cycle allows us to follow the edge directions and eventually return to the starting vertex.

### Directed Acyclic Graph (DAG)

A **DAG** is a directed graph that contains no directed cycles.

Properties:

- Every edge has a direction.
- It is impossible to follow directed edges and return to the starting vertex.
- A DAG always has at least one topological ordering.

Common applications:

- Task scheduling and dependencies.
- Course prerequisites.
- Build systems.
- Topological sorting.
- Dynamic programming on directed acyclic graphs.

## 1.6 Trees

A **tree** is a connected, undirected graph with no cycles.

For a tree with `n` vertices:

- Number of edges: `n - 1`.
- There is exactly one simple path between every pair of vertices.
- Removing any edge disconnects the tree.
- Adding an edge between two existing vertices creates a cycle.

A graph is a tree if and only if it is connected and has no cycles.

An equivalent test for an undirected graph is:

```cpp
(m == n - 1) && (num_of_connected_components == 1)
```

This test assumes a valid undirected graph.

### Rooted Tree

A rooted tree has one designated vertex called the **root**.

- **Parent:** The vertex directly above a vertex in the rooted tree.
- **Child:** A vertex directly below its parent.
- **Ancestor:** A vertex on the path from the root to another vertex.
- **Descendant:** A vertex whose path from the root passes through another vertex.
- **Depth:** The number of edges from the root to a vertex.
- **Subtree:** A vertex and all its descendants.
- **Height of a vertex:** The maximum number of edges from that vertex to a descendant leaf.

## 1.7 Connected Components

A **connected component** of an undirected graph is a maximal set of vertices in which every pair of vertices is connected by a path.

To count connected components:

1. Iterate over every vertex.
2. Whenever an unvisited vertex is found, start DFS or BFS from it.
3. Increase the component count.
4. Continue until every vertex has been visited.

Each new traversal discovers exactly one connected component.

**Time complexity:** `O(n + m)`.

For directed graphs, connectivity has different meanings, including *weakly connected* and *strongly connected* components.

---

# 2. Graph Traversal Overview

Graph traversal algorithms visit vertices by exploring the graph's edges.

The two fundamental traversal algorithms are:

- **DFS (Depth-First Search):** Explores as deeply as possible before backtracking.
- **BFS (Breadth-First Search):** Explores vertices level by level using a queue.

Both have `O(n + m)` time complexity when traversing the entire graph with an adjacency list.

## DFS vs. BFS: Basic Comparison

| Feature | DFS | BFS |
|---|---|---|
| Main data structure | Recursion / stack | Queue |
| Traversal order | Deep before backtracking | Level by level |
| Shortest path in an unweighted graph | Not guaranteed | Yes |
| Connected components | Yes | Yes |
| Bipartite checking | Yes | Yes |
| Undirected cycle detection | Yes | Yes |
| Directed cycle detection | Yes, using states | Requires other techniques for general cases |
| Entry and exit times | Natural fit | Not a standard application |
| Ancestor checking | Yes, using timestamps | Not directly |
| Subtree size | Yes, using DFS tree structure | Not a standard application |
| Tree diameter | Yes | Yes |
| Time complexity | `O(n + m)` | `O(n + m)` |
| Auxiliary space | `O(n)` | `O(n)` |

## Shared Applications

Both DFS and BFS can be used for:

- Graph traversal and reachability.
- Parent tracking and path reconstruction.
- Connected components in undirected graphs.
- Bipartite checking.
- Cycle detection in undirected graphs.
- Tree diameter.

The choice depends on the information required by the problem, not only on whether the graph can be traversed.

---

# 3. Depth-First Search (DFS)

DFS explores one branch as deeply as possible before returning to explore another branch.

It can be implemented recursively or iteratively using a stack.

## 3.1 Applications

DFS is particularly useful for:

- Graph traversal and reachability.
- Parent tracking and path reconstruction.
- Entry and exit times (`in`, `out`).
- Ancestor checking.
- Depth calculation in a DFS tree.
- Subtree size calculation.
- Cycle detection in directed graphs.
- Cycle detection in undirected graphs.
- Topological sorting.
- Recursive tree DP and backtracking.

**Time complexity:** `O(n + m)` for a full traversal.

## 3.2 Parent Tracking and Path Reconstruction

During DFS, store the vertex from which each vertex was first visited:

```cpp
par[u] = v;
```

Here, `v` is the parent of `u` in the DFS tree.

To reconstruct a path, start at the destination and repeatedly follow parent pointers until reaching the source or a designated sentinel value.

```cpp
vector<int> path;

while (src != -1) {
    path.push_back(src);
    src = par[src];
}

reverse(path.begin(), path.end());
```

The sentinel value must match the initialization used by the implementation. For example, if the source parent is `-2`, the stopping condition must use `-2` instead of `-1`.

**Important:** DFS finds a path, but it does not generally guarantee the shortest path in an unweighted graph.

## 3.3 Entry and Exit Times

DFS can record when each vertex is entered and when its exploration finishes.

```cpp
in[v] = timer++;
// Explore children.
out[v] = timer++;
```

- `in[v]`: Entry time of vertex `v`.
- `out[v]`: Exit time of vertex `v`.

These timestamps describe the nesting structure of the DFS traversal.

They are useful for:

- Ancestor checking.
- Identifying nested DFS subtrees.
- Reasoning about DFS traversal order.
- Some tree and directed-graph algorithms.

## 3.4 Ancestor Checking

A vertex `u` is an ancestor of vertex `v` in a rooted tree if `u` lies on the path from the root to `v`.

The direct parent is the immediate ancestor.

Using DFS entry and exit times, `u` is an ancestor of `v` if:

```cpp
in[u] <= in[v] && out[v] <= out[u]
```

This condition includes the case where `u == v`. If only *proper ancestors* should count, additionally require `u != v`.

Why it works:

- DFS enters an ancestor before entering its descendants.
- DFS finishes every descendant before finishing the ancestor.
- Therefore, the descendant's interval lies inside the ancestor's interval.

## 3.5 Depth and Subtree Size

### Depth

When DFS moves from a vertex to an unvisited child:

```cpp
depth[u] = depth[v] + 1;
```

`depth[v]` represents the number of edges from the DFS root to `v` in the DFS tree.

**Important:** In a general graph, DFS depth is not necessarily the shortest distance from the source.

### Subtree Size

For a rooted tree, the subtree size of a vertex includes the vertex itself and every descendant.

Initialize each vertex's subtree size to `1`, then add the subtree sizes of its children after visiting them:

```cpp
subtree[v] += subtree[u];
```

Conceptually:

`subtree[v] = 1 + sum(subtree[u])` over all children `u` of `v`.

This is commonly used in tree DP, subtree queries, and rerooting techniques.

## 3.6 Cycle Detection

### Undirected Graph

In DFS, track the parent of the current vertex.

If an already-visited neighbor is found and it is not the current vertex's parent, a cycle exists in a simple undirected graph.

```cpp
if (u != par[v])
    return true;
```

For multigraphs containing parallel edges, parent-vertex checking alone is insufficient; track parent edge IDs instead.

### Directed Graph

Use three DFS states:

| State | Meaning |
|---|---|
| `0` | Not visited |
| `1` | Currently in the DFS recursion stack |
| `2` | Finished exploring |

If DFS encounters an edge to a vertex in state `1`, a directed cycle exists.

An edge to a vertex in state `2` does not, by itself, indicate a cycle.

## 3.7 Tree Diameter Using DFS

The **diameter of a tree** is the length of the longest shortest path between any two vertices, measured in edges for an unweighted tree.

A standard two-traversal method:

1. Start DFS from any vertex.
2. Find a farthest vertex `x`.
3. Start another traversal from `x`.
4. The maximum distance found in the second traversal is the diameter.

DFS can calculate distances using depth values or return subtree heights.

This method works for trees because there is exactly one simple path between every pair of vertices.

---

# 4. Breadth-First Search (BFS)

BFS explores all vertices at distance `0`, then distance `1`, then distance `2`, and so on from the source.

It uses a queue to process vertices in the order they are discovered.

## 4.1 Applications and Properties

BFS is useful for:

- Graph traversal and reachability.
- Parent tracking and path reconstruction.
- Shortest paths in unweighted graphs.
- Distance and level calculation.
- Connected components.
- Bipartite graph checking.
- Multi-source BFS.
- Grid traversal and shortest paths.
- Tree diameter.

**Time complexity:** `O(n + m)` for a full traversal.

## 4.2 Shortest Paths

BFS finds shortest paths when every edge has the same weight, particularly in unweighted graphs.

For a source vertex `src`:

- `dist[v]` = minimum number of edges from `src` to `v`.
- `par[v]` = parent of `v` in the BFS tree.
- `dist[src] = 0`.
- An unreachable vertex typically retains `dist[v] = -1`.

When an unvisited neighbor `u` is discovered from `v`:

```cpp
dist[u] = dist[v] + 1;
par[u] = v;
```

Because BFS processes vertices in increasing distance order, the first discovery of each vertex gives its shortest distance from the source.

**Remember:**

- DFS → Finds a path, not necessarily the shortest.
- BFS → Finds a shortest path in an unweighted graph.

## 4.3 Connected Components

To find connected components, iterate through all vertices and start BFS whenever an unvisited vertex is found.

Each BFS traversal discovers one component.

To store the actual components, maintain a list of vertices visited during each traversal:

```cpp
vector<vector<int>> components;
```

Each inner vector stores the vertices belonging to one connected component.

**Time complexity:** `O(n + m)`.

## 4.4 Bipartite Checking

BFS can determine whether an undirected graph is bipartite by coloring vertices level by level.

Use two colors, `0` and `1`.

When exploring an edge from `v` to `u`:

- If `u` is unvisited, assign it the opposite color.
- If `u` already has the same color as `v`, the graph is not bipartite.

The opposite color can be computed using XOR:

```cpp
color[u] = color[v] ^ 1;
```

For a disconnected graph, repeat the process from every unvisited vertex.

**Time complexity:** `O(n + m)`.

## 4.5 Multi-Source BFS

Multi-source BFS finds the shortest distance from every reachable vertex to the nearest source in an unweighted graph.

Steps:

1. Insert all source vertices into the queue initially.
2. Set `dist[source] = 0` for every source.
3. Mark all sources as visited.
4. Run normal BFS.

Each vertex's final distance is its minimum number of edges from any source.

Common applications:

- Nearest exit or target.
- Spread simulations.
- Distance to the nearest marked cell in a grid.
- Fire, infection, or propagation problems.

## 4.6 Grid BFS

A grid can be treated as a graph:

- Each valid cell is a vertex.
- An allowed move between adjacent cells represents an edge.
- Blocked cells cannot be entered.

For four-directional movement, the usual directions are up, down, left, and right. Some problems also allow diagonal movement.

BFS is useful for finding the minimum number of moves when each allowed move has equal cost.

**Time complexity:** `O(R * C)` for an `R` by `C` grid when each cell has a constant number of possible moves.

## 4.7 Tree Diameter

BFS can find the diameter of an unweighted tree using two traversals:

1. Start BFS from any vertex.
2. Find a farthest vertex `x`.
3. Start BFS from `x`.
4. The maximum distance found is the tree diameter.

BFS stores distances in `dist`, whereas a recursive DFS implementation may use depth or returned subtree heights.

The two-traversal method works because the input is a tree.

---

# 5. Topological Sorting

> Used for **Directed Acyclic Graphs (DAGs)**.

A **topological ordering** is an ordering of the vertices such that for every directed edge:

```text
u -> v
```

`u` appears before `v`.

### Important

- Topological Sort only exists if the graph has **no directed cycle**.
- A DAG can have **multiple valid topological orders**.
- Time Complexity: **O(n + m)**
- Space Complexity: **O(n + m)**

---

## 5.1 DFS using Pointer

```cpp
const int N = 2e5 + 9;

int topo[N], vis[N], n, m, p;
vector<int> adj[N];

void dfs(int u)
{
    vis[u] = 1;

    for(auto &v : adj[u])
        if(vis[v] == false)
            dfs(v);

    topo[p--] = u;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;

    for(int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        adj[u].emplace_back(v);
    }

    p = n - 1;

    for(int i = 0; i < n; ++i)
        if(vis[i] == false)
            dfs(i);

    for(int i = 0; i < n; ++i)
        cout << topo[i] + 1 << " ";
}
```

### Idea

DFS puts a node into `topo` **after visiting all of its outgoing edges**.

So nodes are added in **postorder**.

Since the last finished node should come first, we fill the array from right to left:

```cpp
topo[p--] = u;
```

---

## 5.2 DFS using Vector

Same idea as above, but instead of filling the answer from right to left, we append nodes and reverse at the end.

```cpp
const int N = 2e5 + 9;

int vis[N], n, m;
vector<int> adj[N];
vector<int> topo;

void dfs(int u)
{
    vis[u] = 1;

    for(auto &v : adj[u])
        if(vis[v] == false)
            dfs(v);

    topo.emplace_back(u);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;

    for(int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        adj[u].emplace_back(v);
    }

    for(int i = 0; i < n; ++i)
        if(vis[i] == false)
            dfs(i);

    reverse(topo.begin(), topo.end());

    for(int i = 0; i < n; ++i)
        cout << topo[i] + 1 << " ";
}
```

### Important

Without:

```cpp
reverse(topo.begin(), topo.end());
```

the result is the **reverse topological order**.

---

## 5.3 Kahn's Algorithm

Kahn's Algorithm uses **BFS + Indegree**.

### Idea

`inDeg[u]` = number of edges going **into** `u`.

Any node with:

```cpp
inDeg[u] == 0
```

can be placed immediately in the topological order.

After taking `u`, remove all edges:

```text
u -> v
```

by decreasing:

```cpp
inDeg[v]--;
```

If:

```cpp
inDeg[v] == 0
```

then `v` is ready to be processed.

```cpp
const int N = 2e5 + 9;

int n, m, inDeg[N];
vector<int> adj[N];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;

    for(int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        adj[u].emplace_back(v);
        inDeg[v]++;
    }

    queue<int> q;

    for(int i = 0; i < n; ++i)
        if(inDeg[i] == 0)
            q.push(i);

    vector<int> topo;

    while(q.size())
    {
        int u = q.front();
        q.pop();

        topo.emplace_back(u);

        for(auto &v : adj[u])
        {
            inDeg[v]--;

            if(inDeg[v] == 0)
                q.push(v);
        }
    }

    for(auto &u : topo)
        cout << u + 1 << " ";
}
```

### Cycle Detection

This is one of the main advantages of Kahn's Algorithm.

If:

```cpp
topo.size() != n
```

then the graph contains a **cycle**.

```cpp
if(topo.size() != n)
    cout << "Cycle exists";
```

Why?

A cycle has no node whose indegree can become `0`, so some nodes will never be added to `topo`.

---

## 5.4 Kahn's Algorithm — Level by Level

Sometimes we need to process all currently available nodes as **one level**.

Instead of processing the queue normally:

```cpp
while(q.size())
{
    int u = q.front();
    q.pop();
    ...
}
```

we save the current queue size:

```cpp
int sz = q.size();
```

and process exactly those nodes.

```cpp
const int N = 2e5 + 9;

int n, m, inDeg[N];
vector<int> adj[N];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;

    for(int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        adj[u].emplace_back(v);
        inDeg[v]++;
    }

    queue<int> q;

    for(int i = 0; i < n; ++i)
        if(inDeg[i] == 0)
            q.push(i);

    vector<int> topo;

    while(q.size())
    {
        int sz = q.size();
        vector<int> V;

        while(sz--)
        {
            int u = q.front();
            q.pop();

            topo.emplace_back(u);

            for(auto &v : adj[u])
            {
                inDeg[v]--;

                if(inDeg[v] == 0)
                    V.emplace_back(v);
            }
        }

        for(auto &u : V)
            q.push(u);
    }

    for(auto &u : topo)
        cout << u + 1 << " ";
}
```

### Why use `V`?

Suppose the queue currently contains:

```text
A B C
```

We want `A B C` to belong to the **same level**.

While processing them, some new nodes become available.

Instead of putting those new nodes directly into `q`, we put them into:

```cpp
vector<int> V;
```

After finishing the current level:

```cpp
for(auto &u : V)
    q.push(u);
```

Now all newly available nodes belong to the **next level**.

---

## 5.5 DFS Cycle Detection

The normal:

```cpp
vis[u] = 1;
```

only tells us whether a node was visited.

For cycle detection in a directed graph, use **3 states**:

```text
0 -> Not visited
1 -> Currently inside DFS
2 -> Completely processed
```

```cpp
int color[N];

bool dfs(int u)
{
    color[u] = 1;

    for(auto &v : adj[u])
    {
        if(color[v] == 1)
            return true;

        if(color[v] == 0 && dfs(v))
            return true;
    }

    color[u] = 2;
    topo.emplace_back(u);

    return false;
}
```

If we find:

```cpp
color[v] == 1
```

then `v` is an ancestor in the current DFS path, meaning we found a **back edge** and therefore a cycle.

---

## 5.6 Topological Sort Template — DFS

Reusable version with cycle detection:

```cpp
const int N = 2e5 + 9;

int n, m, color[N];
vector<int> adj[N], topo;

bool dfs(int u)
{
    color[u] = 1;

    for(auto &v : adj[u])
    {
        if(color[v] == 1)
            return true;

        if(color[v] == 0 && dfs(v))
            return true;
    }

    color[u] = 2;
    topo.emplace_back(u);

    return false;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;

    for(int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        adj[u].emplace_back(v);
    }

    for(int i = 0; i < n; ++i)
        if(color[i] == 0 && dfs(i))
        {
            cout << "Cycle exists";
            return 0;
        }

    reverse(topo.begin(), topo.end());

    for(auto &u : topo)
        cout << u + 1 << " ";
}
```

---

## 5.7 Topological Sort Template — Kahn

Reusable version with cycle detection:

```cpp
const int N = 2e5 + 9;

int n, m, inDeg[N];
vector<int> adj[N];

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> m;

    for(int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        --u;
        --v;

        adj[u].emplace_back(v);
        inDeg[v]++;
    }

    queue<int> q;

    for(int i = 0; i < n; ++i)
        if(inDeg[i] == 0)
            q.push(i);

    vector<int> topo;

    while(q.size())
    {
        int u = q.front();
        q.pop();

        topo.emplace_back(u);

        for(auto &v : adj[u])
        {
            inDeg[v]--;

            if(inDeg[v] == 0)
                q.push(v);
        }
    }

    if(topo.size() != n)
    {
        cout << "Cycle exists";
        return 0;
    }

    for(auto &u : topo)
        cout << u + 1 << " ";
}
```

---

## 5.8 Choosing Between Them

| Method | Main Idea | Cycle Detection | Extra Use |
|---|---|---|---|
| DFS + Pointer | DFS postorder | With 3 states | Simple/flexible |
| DFS + Vector | DFS postorder + reverse | With 3 states | Clean template |
| Kahn | BFS + indegree | `topo.size() != n` | Levels / prerequisites |
| Kahn + Levels | BFS by layers | `topo.size() != n` | Process same-level nodes |

### Remember

```text
DFS:
    visit children
    add node after them
    reverse

Kahn:
    take indegree = 0
    remove its outgoing edges
    newly zero indegree -> queue
```

### Common Applications

- Course prerequisites
- Task scheduling
- Dependency resolution
- Build systems
- Ordering problems
- DAG DP
- Finding whether a directed graph contains a cycle
- Finding the minimum number of rounds/levels for dependent tasks

---

# 6. Dijkstra's Algorithm

Dijkstra's algorithm finds shortest-path distances from one source to all reachable vertices in a weighted graph with non-negative edge weights.

It uses a **min-priority queue** to process the vertex with the smallest currently known distance.

## 6.1 Properties and Complexity

- Finds minimum-cost paths from a single source.
- Supports directed and undirected graphs.
- Requires non-negative edge weights.
- Can track parents to reconstruct one shortest path.
- Can be extended to count shortest paths and track minimum/maximum edge counts under appropriate conditions.

With an adjacency list and a binary heap:

- **Time:** `O((n + m) log n)`.
- **Memory:** `O(n + m)` for the graph and algorithm arrays.

The exact runtime can also be expressed as `O((n + m) log n)` for the usual implementation that inserts improved distance entries into the priority queue and ignores stale entries.

## 6.2 Shortest Distance

Let `dis[v]` be the minimum known cost from the source to vertex `v`.

Initialization:

- `dis[src] = 0`.
- All other distances start at infinity (`OO`).
- An unreachable vertex retains `dis[v] == OO`.

When processing an edge from `v` to `u` with weight `cost`, calculate:

```cpp
if (dis[v] + cost < dis[u]) {
    dis[u] = dis[v] + cost;
}
```

This operation is called **relaxation**.

If a strictly shorter route is discovered, update the distance and push the new `{distance, vertex}` pair into the priority queue.

Stale queue entries can be ignored:

```cpp
if (d != dis[v])
    continue;
```

## 6.3 Parent Tracking and Path Reconstruction

To reconstruct one shortest path, store the predecessor of each vertex whenever a strictly shorter path is found:

```cpp
par[u] = v;
```

If the source parent is initialized to `-2`, that value marks the end of the backward traversal.

Steps:

1. Start at the destination.
2. Follow `par` backwards.
3. Stop when the source sentinel is reached.
4. Reverse the resulting sequence.

If `dis[end] == OO`, the destination is unreachable and no path exists.

**Important:** If multiple shortest paths exist, the parent array stores only one of them.

## 6.4 Counting Shortest Paths

Let `mnPaths[v]` represent the number of shortest paths from the source to vertex `v`, usually modulo `MOD`.

Initialization:

```cpp
mnPaths[src] = 1;
```

When a strictly shorter route to `u` is found through `v`:

```cpp
mnPaths[u] = mnPaths[v];
```

The previous routes are discarded because they were not optimal.

When another route of exactly the same minimum cost is found:

```cpp
mnPaths[u] = (mnPaths[u] + mnPaths[v]) % MOD;
```

The new route contributes additional shortest paths.

**Important conditions:**

- This update pattern works naturally when edge weights are strictly positive.
- Zero-weight edges require additional care because equal-distance dependencies can exist between vertices with the same distance.
- If zero-weight cycles are allowed, the number of shortest walks may be infinite; counting shortest simple paths is a different problem.

## 6.5 Minimum and Maximum Number of Edges

Among all minimum-cost paths from the source to each vertex, a template can track:

- `mn_mx_paths[v].first`: Minimum number of edges.
- `mn_mx_paths[v].second`: Maximum number of edges.

Initialize the source as:

```cpp
mn_mx_paths[src] = {0, 0};
```

When a strictly shorter path to `u` is found through `v`, both values are derived from the predecessor:

```cpp
mn_mx_paths[u].first = mn_mx_paths[v].first + 1;
mn_mx_paths[u].second = mn_mx_paths[v].second + 1;
```

When another path with the same minimum cost is found:

```cpp
mn_mx_paths[u].first =
    min(mn_mx_paths[u].first, mn_mx_paths[v].first + 1);

mn_mx_paths[u].second =
    max(mn_mx_paths[u].second, mn_mx_paths[v].second + 1);
```

These updates aggregate the smallest and largest edge counts among equally optimal paths.

As with shortest-path counting, the straightforward implementation relies on strictly positive weights to ensure shortest-path predecessors have smaller distances and are processed before their successors.

## 6.6 Important Conditions

### Non-Negative Edge Weights

Dijkstra requires non-negative edge weights to guarantee shortest distances.

- Positive weights: Supported.
- Zero weights: Shortest distances are supported, but path counting and edge-count aggregation may need additional handling.
- Negative weights: Use an appropriate alternative, such as Bellman–Ford, when applicable.

### Directed and Undirected Graphs

- `add_edge(u, v, cost)` adds the directed edge `u -> v`.
- `add_edges(u, v, cost)` adds both `u -> v` and `v -> u`.

### BFS vs. Dijkstra

- BFS is preferred when every edge has equal cost.
- Dijkstra is preferred when edge weights are non-negative and can differ.
- Both find shortest paths from a source, but they use different traversal strategies.

---

# 7. DFS vs. BFS vs. Dijkstra

| Feature | DFS | BFS | Dijkstra |
|---|---|---|---|
| Graph type | Directed or undirected | Directed or undirected | Directed or undirected |
| Edge weights | Not used for standard traversal | Equal weights for shortest paths | Non-negative, potentially different |
| Main data structure | Recursion / stack | Queue | Min-priority queue |
| Shortest distance | Not generally guaranteed | Minimum number of edges | Minimum total weight |
| Path reconstruction | Yes | Yes | Yes |
| Connected components | Yes, for undirected graphs | Yes, for undirected graphs | Not its primary purpose |
| Bipartite checking | Yes | Yes | Not its primary purpose |
| Directed cycle detection | Yes, using DFS states | Not the standard approach | No |
| Entry/exit times | Yes | Not standard | Not standard |
| Subtree size | Yes | Not standard | Not standard |
| Multi-source shortest distance | Specialized variants exist | Yes, unweighted graphs | Multi-source initialization is possible |
| Tree diameter | Yes | Yes | Weighted-tree variants require weighted distances |
| Typical complexity | `O(n + m)` | `O(n + m)` | `O((n + m) log n)` |

## Key Takeaway

- **DFS → Structure and relationships:** recursion, entry/exit times, ancestors, subtrees, and backtracking.
- **BFS → Distance and levels:** shortest paths in unweighted graphs, minimum moves, and multi-source distances.
- **Dijkstra → Weighted shortest paths:** minimum-cost routes with non-negative edge weights.

---

# 8. Quick Decision Guide

| Problem Requirement | Preferred Algorithm |
|---|---|
| Traverse a graph | DFS or BFS |
| Determine reachability | DFS or BFS |
| Find a path in a graph | DFS or BFS |
| Find the shortest path in an unweighted graph | BFS |
| Find the minimum number of moves | BFS |
| Find shortest distances from multiple sources in an unweighted graph | Multi-source BFS |
| Find shortest distances with non-negative weighted edges | Dijkstra |
| Count shortest paths in a positive-weight graph | Dijkstra with path counting |
| Find minimum/maximum edge counts among shortest paths | Dijkstra with edge-count tracking |
| Find connected components in an undirected graph | DFS or BFS |
| Check whether a graph is bipartite | DFS or BFS |
| Detect a cycle in an undirected graph | DFS or BFS |
| Detect a cycle in a directed graph | DFS with states |
| Calculate entry and exit times | DFS |
| Check whether a vertex is an ancestor of another | DFS timestamps on a rooted tree |
| Calculate subtree sizes | DFS |
| Perform level-order traversal | BFS |
| Find shortest paths in a grid with equal-cost moves | BFS |
| Find the diameter of an unweighted tree | DFS or BFS |
| Find a topological ordering | DFS or Kahn's algorithm |
| Handle negative-weight shortest paths | Bellman–Ford, when applicable |

---

# 9. Future Notes

Use this section as a placeholder for future graph topics. Add new sections above it and update the Table of Contents when appropriate.

Potential topics to study:

- [ ] Topological Sorting
- [ ] Kahn's Algorithm
- [ ] Strongly Connected Components (SCC)
- [ ] Bridges and Articulation Points
- [ ] Disjoint Set Union (DSU)
- [ ] Minimum Spanning Tree (Kruskal and Prim)
- [ ] Bellman–Ford Algorithm
- [ ] Floyd–Warshall Algorithm
- [ ] 0–1 BFS
- [ ] Lowest Common Ancestor (LCA)
- [ ] Binary Lifting
- [ ] Tree DP
- [ ] Rerooting DP
- [ ] Euler Tour Technique
- [ ] Lowest Common Ancestor with Euler Tour
- [ ] Maximum Flow and Minimum Cut
- [ ] Bipartite Matching

---

**Related template files**

- `DFS.cpp` — Depth-first search and DFS-based applications.
- `BFS.cpp` — Breadth-first search and BFS-based applications.
- `Dijkstra.cpp` — Weighted shortest paths and related information.

Keep implementation-specific details inside their corresponding `.cpp` files and use this Markdown file for concepts, properties, algorithm comparisons, and links between topics.
