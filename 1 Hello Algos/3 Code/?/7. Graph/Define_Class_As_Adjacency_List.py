#a list of lists that contains connections between nodes, that's it lol, we don't have as many redundent connections stored as inside matrix

#this one will be a little more complex, as we will now care for a directed graph (is it directed?)



class Adjacency_List_Graph:

    class Edge:

        def __init__(self, start, end):
            self.start = start
            self.end = end

        def __str__(self):
            pass


    def __init__(self):
        self.list_of_lists = []
        self.nodes = []

    def __str__(self):
        list_str = ""

        for index, nodes_list in enumerate(self.list_of_lists):
            list_str += self.nodes[index] + " | "
            for edges in nodes_list:
                list_str += edges.end + " "
            list_str += "\n"

        return list_str


    def find_node(self, element):
        try:
            node_index = self.nodes.index(element)
            return node_index
        except ValueError:
            print(f"Node with element {element} not found")
            return None


    def find_edge(self, begin_node_index, end_node):
        for index, edge in enumerate(self.list_of_lists[begin_node_index]):
            if edge.end == end_node:
                return index
        begin_node = self.nodes[begin_node_index]
        print(f"Edge with starting node {begin_node} and ending node {end_node} not found")
        return None


    def insert_node(self, element):
        self.nodes.append(element)
        self.list_of_lists.append([])

    def delete_node(self, element):
        delete_index = self.find_node(element)

        if delete_index == None:
            pass
        else:
            self.nodes.pop(delete_index)
            self.list_of_lists.pop(delete_index)


    #This doenss't have a faulty check, as in we can insert infinite many edges between two nodes (yes meow)
    def insert_edge(self, begin_node, end_node):

        begin_node_index = self.find_node(begin_node)
        end_node_index = self.find_node(end_node)

        if begin_node_index == None or end_node_index == None:
            pass
        else:
            new_edge = self.Edge(begin_node, end_node)
            self.list_of_lists[begin_node_index].append(new_edge)


    #This should iterate through the entire list at the starting node's index, linearly, to check if there is a edge between them
    def delete_edge(self, begin_node, end_node):

        begin_node_index = self.find_node(begin_node)
        end_node_index = self.find_node(end_node)

        #making sure both node's exist
        if begin_node_index == None or end_node_index == None:
            pass
        else:

            #making sure the edge exists
            edge_index = self.find_edge(begin_node_index, end_node)
            if edge_index == None:
                pass
            else:
                self.list_of_lists[begin_node_index].pop(edge_index)


    def adjacent_nodes(self, node):
        node_index = self.find_node(node)

        if node_index == None:
            pass
        else:
            print(self.list_of_lists[node_index])


stars = Adjacency_List_Graph()
stars.insert_node("A")
stars.insert_node("B")
stars.insert_node("C")
stars.insert_node("D")
stars.insert_node("E")

stars.insert_edge("A", "C")
stars.insert_edge("A", "D")
stars.insert_edge("B", "C")
stars.insert_edge("B", "E")
stars.insert_edge("C", "E")
stars.insert_edge("D", "C")
stars.insert_edge("D", "B")
stars.insert_edge("E", "A")
stars.insert_edge("E", "B")
print(stars)


stars.delete_edge("C", "E")
print(stars)


#huh... this is actually a very big problem that I dunno an answer to, because it's weighted,
#so in deleteing a node, the edges to the node are contained in the list connections of other nodes, and those are not deleted properly
#I mean, deleting it's index in the list and it's row in the 2d list is a good start, but every time that we delete a node we have to traverse through the entire 2d list? that's dumb

#stars.delete_node("C")
#print(stars)
