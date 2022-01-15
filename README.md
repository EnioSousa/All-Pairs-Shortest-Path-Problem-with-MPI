# Goal
Allow students to acquire sensibility and practical experience with parallel programming for distributed memory environments using the MPI framework.

# Description
The problem to be solved consists in determining all shortest paths between pairs of nodes in a given graph. This is the well known all-pairs shortest path problem.
The idea is simple: given a directed graph G = (V,E) in which V is the set of nodes (or vertices) and E is the set of links (or edges) between nodes, the goal is to determine 
for each pair of nodes (vi,vj) the size of the shortest path that begins in vi and ends in vj. A path is simply a sequence of links in which the end node and start node of 
two consecutive links are the same. One link can be seen as a tuple of the form <vi, vj, t> where vi is the origin node, vj is the destination node and t is the
size of the link between the nodes. The sum of the sizes of the links is the size of the path between vi and vj.

# How to run


## Host file
In the host file you can specify which computers you want to run the program. 

```
<Computer name 1> slots=<maximum number of threads>
<Computer name 2> slots=<maximum number of threads>
```

The following command runs each example available, in the data folder, on you local machine 
```
make runTestHome
```
The following command runs each example available. For each example, the next command executes in distributed mode, i.e. each node shares a bit of the work
```
make runTestLab
```

To run by hand, do:
```
make run < <file path>
```
