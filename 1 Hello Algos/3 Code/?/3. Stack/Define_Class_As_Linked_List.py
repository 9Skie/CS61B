#Top = Head here, since both pretty much do the same job by pointing to the first node in the linked list



class Linked_List_Stack:
    class Node:
        def __init__(self, element=None, next_node=None):
            self.element = element
            self.next_node = next_node
        
        def __str__(self):
            return (f"Top element stored {self.element}")

    
    def __init__(self):
        self.head = None


    def __str__(self):
        #same function as linked list
        current_node = self.head
        result = []
        separator =  " -> "

        while current_node != None:
            result.append(current_node.element)
            current_node = current_node.next_node
        return separator.join(map(str, result)) + (f" | Top element stored {self.head.element}")
    

    def is_empty(self):
        if self.head == None:
            return True
        else:
            return False


    def length(self):
        #same function as linked list
        current_node = self.head
        list_length = 0

        while current_node != None:
            current_node = current_node.next_node
            list_length += 1

        return list_length
        

    def peek(self):
        #almost same function as list_stack
        if self.is_empty() == True:
            print("Top Node is not yet declared")
        else:
            return self.head
    

    def push(self, element):
        #same function as linked list
        new_node = self.Node(element)

        if self.is_empty() == True:
            self.head = new_node
        else:
            current_head_node = self.head
            new_node.next_node = current_head_node
            self.head = new_node 


    def pop(self):
        #same function as linked list
        if self.is_empty() == True:
            print("Can't pop from an empty stack")
        else:
            current_head_node = self.head
            self.head = current_head_node.next_node
            current_head_node.next_node = None



#creating Stack
fruits = Linked_List_Stack()
fruits.push("apple")
fruits.push("banana")
fruits.push("cherry")
fruits.push("fig")
fruits.push("grape")
fruits.push("honeydew")
fruits.push("jackfruit")


#test implementation
print(f"The stack currently has {fruits.length()} elements stored")
print(fruits)
print(fruits.peek())
fruits.pop()
print(fruits)
print(fruits.peek())