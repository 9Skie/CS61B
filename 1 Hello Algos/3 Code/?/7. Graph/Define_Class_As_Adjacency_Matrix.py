#graphs... huh... this is gonna take a while

#in an adjacency matrix, the connection of every node to every node is stored, this is good for very dense graphs, not good for light graphs

#we need a class for the matrix, and operations on the matrix, and another list to store the elements of each vertex
#another class should be vertex, and edges

#this seems far more complex than the other data strucutres that we've encountered so far... so let's think this carefully

#this is not going to be weighted, nor directed (actually thinking about it directed might be easier because we don't have to make the matrix symmetrical)


#for the matrix

#init method... we should create an emtpy 2d list, and that's all

#str method... printing out a graph can be challenging... maybe we just print out all of the 2d matrix?


#for the nodes, and edges

#insert new node, should create a new column and a new node for the matrix, as well as know it's element, oh yeah we should add a new element in the list as well

#delete node, should remove the node's row and column, as well as deleting it from the list keeping it's stored value

#insert new edge, should just update a connection in the adjacent matrix, to True, by giving in the 2 nodes we want to make a connection to

#delete edge, should update the connection in the adjacent matrix to False, give the 2 nodes

#finding all adjacent nodes to a node, hmm... iterate through the row of the node, make a list, and add nodes which store the connection "True" in them

#finding if 2 vertices are connected, we just travel to graph[a][b] and see if the stored value is True or False, and return something based on that

#finding if a node exisits (like how? by iterating through the node list?), search by element is better, we'd dp a breadth first search with a queue and whatever

#shortest path between two nodes... oh wait this isn't weighted lol


#just saying... I dunno if this implementation can handle repeated elements, cuz we search indexes by elements, and repeats... I dunno man

class Adjacency_Matrix_Graph:

    def __init__(self):
        self.matrix = []
        self.nodes = []
    
    def __str__(self):
        # Create a string to hold the adjacency matrix and nodes
        graph_str = ""
    
        # Get the size of the graph
        size = len(self.nodes)
    
        # Print new line
        graph_str += "\n"
    
        # Print small space indent
        graph_str += "  "
    
        # Print out 1 2 3 4... all the way up to however big size is
        for j in range(size):
            graph_str += f"{j} "
    
        # Print new line
        graph_str += "\n"
    
        for i in range(size):
            # Print out 1 2 3 4... all the way up to however big size is, but vertically
            graph_str += f"{i} "
    
            # Actually prints out the rows of the board 1 by 1
            for j in range(size):
                if self.matrix[i][j] == True:
                    graph_str += "Y "
                elif self.matrix[i][j] == False:
                    graph_str += "N "
    
            # Print new line
            graph_str += "\n"

        # Add the list of nodes to the string
        graph_str += "Nodes " + str(self.nodes)

        # Print new line
        graph_str += "\n"
    
        # Return the string representation of the graph
        return graph_str


    def find_node(self, element):
        try:
            node_index = self.nodes.index(element)
            return node_index
        except ValueError:
            print(f"Node with element {element} not found")
            return None
        
        
    def find_edge(self, node1, node2):
        node1_index = self.find_node(node1)
        node2_index = self.find_node(node2)
        
        if node1_index == None or node2_index == None:
            pass
        else:
            return self.matrix[node1_index][node2_index]


    def insert_node(self, element):
        self.nodes.append(element)
        self.matrix.append([])

        new_size = len(self.nodes)

        for _ in range(new_size):
            self.matrix[new_size - 1].append(False)

        for index in range(new_size - 1):
            self.matrix[index].append(False)
        
        self.matrix[new_size - 1][new_size - 1] = True


    def delete_node(self, element):
        delete_index = self.find_node(element)

        if delete_index == None:
            pass
        else:
            self.matrix.pop(delete_index)
            self.nodes.pop(delete_index)

            new_size = len(self.nodes)

            for index in range(new_size):
                self.matrix[index].pop(delete_index)


    def insert_edge(self, node1, node2):
        node1_index = self.find_node(node1)
        node2_index = self.find_node(node2)
        
        if node1_index == None or node2_index == None:
            pass
        else:
            #Because we are a symmetrical matrix, so we have to update both (b,a) and (a,b)
            self.matrix[node1_index][node2_index] = True
            self.matrix[node2_index][node1_index] = True


    def delete_edge(self, node1, node2):
        node1_index = self.find_node(node1)
        node2_index = self.find_node(node2)
        
        if node1_index == None or node2_index == None:
            pass
        elif self.matrix[node1_index][node2_index] == False:
            print(f"Edge between {node1} and {node2} does not exist")
        else:
            #Because we are a symmetrical matrix, so we have to update both (b,a) and (a,b)
            self.matrix[node1_index][node2_index] = False
            self.matrix[node2_index][node1_index] = False


    def adjacent_nodes(self, node):
        node_index = self.find_node(node)
        adjacent_nodes = []

        if node_index == None:
            pass
        else:
            for another_node_index in range(len(self.nodes) - 1):
                if self.matrix[node_index][another_node_index] == True:
                    adjacent_nodes.append((another_node_index, self.nodes[another_node_index]))

        return adjacent_nodes

    

# Create an empty graph
cities = Adjacency_Matrix_Graph()

# Insert nodes
cities.insert_node("A")
print(cities)
cities.insert_node("B")
print(cities)
cities.insert_node("C")
print(cities)
cities.insert_node("D")
print(cities)

#Insert edges
cities.insert_edge("A", "B")
print(cities)
cities.insert_edge("B", "C")
print(cities)
cities.insert_edge("C", "D")
print(cities)


#trying other functions
cities.delete_node("B")
print(cities)
cities.delete_edge("C", "D")
print(cities)
cities.insert_node("G")
print(cities)
cities.insert_edge("G", "A")
cities.insert_edge("G", "C")
print(cities.adjacent_nodes("G"))
print(cities.find_node("A"))
print(cities.find_edge("G", "A"))
