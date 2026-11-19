#hmm... let me see

#we need to define a node class, a node class will have 3 attributes, the element it stores, it's left and right child

#Insert, this should be recursive in comparing the inserted value with the current node's value, 
#if tree empty, value becomes root node, if not, the value gets compared and compared unitl it reaches a leaf node, where it becomes a leaf node

#Delete... make it 3 scenarios, delete from a leaf, just remove it's parent's pointer to it, but we have to trace back to it's parent, guess we need a parent pointer
#the second scenario, we delete a node with 1 children, in this case we just make the node's parent's point point to it's children and make the node's current pointer a null
#the third scenario, we find the node's first in order successor, the smallest node in the right subtree, and replace the element in the node with that element
#then we just delete the first in order successor from it's original position in the tree

#ISearch, we start at the root node and compare the search value to the current value, move to the left child if it's smaller, move to the right child if it's larger...
#Either we find a node with our desired value, or reach a leaf node and conclude that the tree doens't contain the value

#Min/Max, just keep going left or keep going right till we reach a leaf...

#Traversal... this is basically for printing out the tree, same goal can be achieved by depth first or breadth first




#just saying... I dunno if this implementation can handle repeated elements, cuz we search indexes by elements, and repeats... I dunno man

from collections import deque


class Binary_Search_Tree:

    class Node:
        def __init__(self, element=None, left_child=None, right_child=None, parent=None, tree=None):
            self.element = element
            self.left_child = left_child
            self.right_child = right_child
            self.parent = parent
            self.tree = tree

        def __str__(self):

            #I would be more glad if this can return the depth as well, but, from here we cannot call the search function from the Binary Search Tree, so we can't know it's depth
            return (f"element stored {self.element}")


    def __init__(self, root=None):
        self.root = root

    #do a traversal and print stuff out... but how do you print it good? This part is by ChatGPT cuz I'm lazy
    def __str__(self):
        if self.root is None:
            return ""

        queue = deque()
        queue.append((self.root, None))
        level = 0
        result = ""

        while len(queue) != 0:
            level_size = len(queue)
            result += f"Level {level}: "

            for _ in range(level_size):
                node, parent = queue.popleft()
                result += f"{node.element}("

                if parent is not None:
                    result += f"{parent.element}"

                result += ") "

                if node.left_child is not None:
                    queue.append((node.left_child, node))

                if node.right_child is not None:
                    queue.append((node.right_child, node))

            result += "\n"
            level += 1

        return result


    def is_empty(self):
        if self.root == None:
            return True
        else:
            return False

    def maximum(self, node=None):
        if node is None:
            node = self.root

        while node.right_child is not None:
            node = node.right_child
        return node
    
    def minimum(self, node=None):
        if node is None:
            node = self.root

        while node.left_child is not None:
            node = node.left_child
        return node


    #iterative, not recursive
    def search(self, value, current_node=None):

        depth = 0
        
        if current_node == None:
            current_node = self.root

        while True:
            if current_node == None or current_node.element == value:
                return current_node, depth
            elif value > current_node.element:
                current_node = current_node.right_child
                depth += 1
            elif value < current_node.element:
                current_node = current_node.left_child
                depth += 1

    #this actually does the job of Node class's str method lol
    def print_search(self, value, current_node=None):
        node, depth = self.search(value, current_node)
        print(f"{node}, depth is {depth}")
    
    
    #iterative, not recursive
    def insert(self, element):
        current_node = self.root
        new_node = self.Node(element)

        if self.root == None:
            self.root = new_node
        else:
            if type(current_node.element) == type(new_node.element):

                while True:

                    #right children stuff
                    if element > current_node.element:
                        if current_node.right_child == None:
                            current_node.right_child = new_node
                            new_node.parent = current_node
                            break
                        else:
                            current_node = current_node.right_child
                        
                    #left children stuff
                    elif element <= current_node.element:
                        if current_node.left_child == None:
                            current_node.left_child = new_node
                            new_node.parent = current_node
                            break
                        else:
                            current_node = current_node.left_child

            else:
                print("New node has a different data type than the root node.")
                return


    def delete(self, element):
        node_to_delete, depth = self.search(element)

        if node_to_delete == None:
            print("The node was not found in in the Binary Search Tree")
            return
        else:
            parent_of_bygone = node_to_delete.parent


            #when node_to_delete has no children
            if node_to_delete.left_child == None and node_to_delete.right_child == None:

                #is node_to_delete a left or right children of parent_of_bygone?
                if parent_of_bygone == None:
                    self.root = None

                elif parent_of_bygone.left_child == node_to_delete:
                    parent_of_bygone.left_child = None

                elif parent_of_bygone.right_child == node_to_delete:
                    parent_of_bygone.right_child = None

                node_to_delete.parent = None


            #when node_to_delete has 1 children
            elif node_to_delete.left_child == None or node_to_delete.right_child == None:

                #when we want to delete the root node
                if parent_of_bygone == None:
                    if node_to_delete.left_child != None:
                        self.root = node_to_delete.left_child
                    else:
                        self.root = node_to_delete.right_child


                elif parent_of_bygone.right_child == node_to_delete:

                    #case 1, node_to_delete is parent_of_bygone's right child, and node_to_delete has only a right child
                    if node_to_delete.right_child != None:
                        parent_of_bygone.right_child = node_to_delete.right_child
                        node_to_delete.right_child.parent = parent_of_bygone

                    #case 2, node_to_delete is parent_of_bygone's right child, and node_to_delete has only a left child
                    else:
                        parent_of_bygone.right_child = node_to_delete.left_child
                        node_to_delete.left_child.parent = parent_of_bygone
                    
                    
                elif parent_of_bygone.left_child == node_to_delete:

                    #case 3, node_to_delete is parent_of_bygone's left child, and node_to_delete has only a right child
                    if node_to_delete.right_child != None:
                        parent_of_bygone.left_child = node_to_delete.right_child
                        node_to_delete.right_child.parent = parent_of_bygone
            

                    #case 4, node_to_delete is parent_of_bygone's left child, and node_to_delete has only a left child
                    else:
                        parent_of_bygone.left_child = node_to_delete.left_child
                        node_to_delete.left_child.parent = parent_of_bygone
            
                node_to_delete.parent = None


            #when node_to_delete has 2 children
            elif node_to_delete.left_child != None and node_to_delete.right_child != None:
                smallest_in_right_subtree = self.minimum(node_to_delete.right_child)
                self.delete(smallest_in_right_subtree.element)
                node_to_delete.element = smallest_in_right_subtree.element



#creating binary search tree
numbers = Binary_Search_Tree()
numbers.insert(5)
numbers.insert(2)
numbers.insert(7)
numbers.insert(1)
numbers.insert(8)
numbers.insert(3)
numbers.insert(6)
numbers.insert(4)
numbers.insert(9)


#testing implementation
print(numbers)
numbers.delete(8)
print(numbers)
numbers.delete(7)
print(numbers)
numbers.insert(13)
print(numbers)
numbers.print_search(13)
print(numbers.minimum())