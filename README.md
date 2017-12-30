# README #

### What is this repository for? ###

This code is used to analyse a phylogenetic tree that resolves the problem of the perfect phylogeny studied in Bioinformatics.

Note: It was requested to have only one file, so all the classes and methods are in SequenceAlignment.cpp.

### Input ###

Compile the source using the G++ command

```
#!command
g++ -o PhylogeneticTree PhylogeneticTree.cpp -Wall -pedantic -ansi
```

Now you're ready to execute the script. You just need to execute in command line
```
#!command
./PhylogeneticTree
If you are using Windows, consider removing the "./"
```

While the program is running you can type as many as matrix you want, then type 0 0 to stop.

Here are an input example:
```
#!command
4 5
0 1 0 1 0
0 0 0 1 0
1 1 0 0 1
1 1 1 1 1
5 6
0 0 0 0 1 0
0 1 0 0 1 0
0 0 1 1 0 0
1 0 1 1 0 0
0 0 1 0 0 1
5 6
0 0 0 1 1 0
1 1 0 0 0 0
0 0 0 1 1 1
1 0 1 0 0 0
0 0 0 1 0 0
0 0
```

Note: If you want you can use the default cmd/terminal operators for files
```
#!command
./PhylogeneticTree < input_file
./PhylogeneticTree < input_file > output_file
```

### Output ###

The output can be a matrix or the message that the perfect phylogeny doesn't exists.

If the perfect phylogeny exists, the matrix will be as below.

The matrix R represents a KxK dimensional tree, where K is the number of nodes. Labeling the nodes from 0 to K-1 (from the root of the tree to it's leafs, from the left to the right side), the value in R[i][j] will be -1 if i isn't j's parent or the value in R[i][j] will be the characteristic number that labels the edge that connects i to j in the tree. If there's an edge connecting the nodes i and j that has no label/characteristic, the value in R[i][j] will be 0.

```
#!command
-1 3 5 -1 -1 -1 -1 -1 -1
-1 -1 -1 4 6 -1 -1 -1 -1
-1 -1 -1 -1 -1 0 2 -1 -1
-1 -1 -1 -1 -1 -1 -1 1 0
-1 -1 -1 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1 -1 -1

-1 1 4 -1 -1 -1 -1 -1 -1
-1 -1 -1 2 3 -1 -1 -1 -1
-1 -1 -1 -1 -1 0 5 -1 -1
-1 -1 -1 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1 0 6
-1 -1 -1 -1 -1 -1 -1 -1 -1
-1 -1 -1 -1 -1 -1 -1 -1 -1
```

The images below represents the two phylogenetic trees above, in a graphical perspective:

![tree1.png](https://bitbucket.org/repo/pp65Ln/images/3711864554-tree1.png)
![tree2.png](https://bitbucket.org/repo/pp65Ln/images/2636162636-tree2.png)

### How To Convert The Output Into Graph? ###

If you want to convert the output of the algorithms to images, as shown above, you can simple compile and run the source "GraphvizTreeGenerator.cpp".

```
#!command
To compile: g++ -o GraphvizTreeGenerator GraphvizTreeGenerator.cpp
To execute: ./GraphvizTreeGenerator < matrix_output_file > graph_output_file
```

With the code generated in graph_output_file, you just need to run the script into Graphviz (<http://www.graphviz.org/>) in Linux or just go to the link <http://sandbox.kidstrythisathome.com/erdos/> and place your script and make your graph.

### Known Issues ###

A known issue in this code is that it only works with binary trees, so if you want to check if a tree with more the two childs has perfect phylogeny, it will not work for now.

### Who do I talk to? ###

Repo owner/admin: Daniel de Faria Godoi (<danielfgodoi@gmail.com>)