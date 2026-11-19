#define linked lists class, it should just be a head attribute that stores a pointer to the first element in the linked list, default set to null,
#and we can use is_empty to see if the linked list is empty based on if the head is pointing to something or not

#create Node class, a node needs a stored element and a pointer to the next node

#is_empty, should return true or false based on looking at the head node

#access_node, should access the given nodes element (based on it's index in the linked list)

#insert element, should insert at given index by traversing first to the existing node at that index, change the previous node's pointer to the new node we want to insert,
#and have our new node's pointer to the original node at that index

#delete element, should delete at given index by traversing first to the existing node at that index, change the pointer to the node to the next node, and make this node's pointer null

#search element, should traverse through the entire linked list (linear search) until we either run into the value we search for or that we didn't find it in the linked list

#return (f"element stored \"{self.element}\", next node {self.next_node}"), this is somehow recursive


class Linked_List:

    class Node:
        def __init__(self, element=None, next_node=None):
            self.element = element
            self.next_node = next_node
        
        def __str__(self):
            return str(self.element)


    def __init__(self):
        self.head = None
        self.tail = None


    def __str__(self):
        current_node = self.head
        result = []
        separator =  " -> "

        while current_node != None:
            result.append(current_node.element)
            current_node = current_node.next_node
        return separator.join(map(str, result))
        

    def is_empty(self):
        if self.head == None:
            return True
        else:
            return False
        

    def length(self):
        current_node = self.head
        list_length = 0

        while current_node != None:
            current_node = current_node.next_node
            list_length += 1

        return list_length
    

    def access(self, index):
        current_node = self.head
        current_index = 0

        if index <= self.length() - 1:
            while current_index != index:
                current_node = current_node.next_node
                current_index += 1
            return current_node
        else:
            raise IndexError


    def insert(self, element, index):

        if self.is_empty() and index == 0:
            self.head = self.Node(element)
            self.tail = self.Node(element)
       
        if index <= self.length() - 1:
            if index == 0:
                current_head_node = self.head
                new_node = self.Node(element)

                new_node.next_node = current_head_node
                self.head = new_node 
                
            elif index == self.length() - 1:
                self.append(element)

            else:
                #this is the previous node to, the current node at the index
                previous_node = self.access(index - 1)
                new_node = self.Node(element)

                new_node.next_node = previous_node.next_node
                previous_node.next_node = new_node
        else:
            raise ValueError


    def delete(self, index):
        if index <= self.length() - 1:
           if index == 0:
               current_head_node = self.head
               self.head = current_head_node.next_node
               current_head_node.next_node = None
           else:
               current_node = self.access(index)
               previous_node = self.access(index - 1)
               previous_node.next_node = current_node.next_node
               current_node.next_node = None
        else:
            raise ValueError


    def append(self, element):
        new_node = self.Node(element)

        if self.is_empty() == True:
            self.head = new_node
            self.tail = new_node
        else:
            current_tail_node = self.tail
            current_tail_node.next_node = new_node
            self.tail = new_node


    def search(self, value):
        current_node = self.head
        current_index = 0

        while current_index <= self.length() - 1:
            if current_node.element == value:
                return current_index
            else:
                current_node = current_node.next_node
                current_index += 1
        raise ValueError
        
        
        
#create linked lists and nodes, and create pointers
names = Linked_List()
names.append("jamie")
names.append("drake")
names.append("olivia")
names.append("bob")
names.append("sarah")


#test implementation
print(names)
names.append("fiona")
print(names)
names.insert("raffaella", 3)
print(names)
names.delete(4)
print(names)
print(names.access(3))