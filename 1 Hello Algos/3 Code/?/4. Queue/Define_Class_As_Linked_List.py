
#This actually would not work if we enqueue at front and dequeue at end, 
#that would require a doubly linked list so that dequeue can actually know the node in front of the last node to update the rear pointer
#I'm too lazt lol



class Linked_List_Queue:
    class Node:
        def __init__(self, element=None, next_node=None):
            self.element = element
            self.next_node = next_node
        
        def __str__(self):
            return (f"element stored {self.element}")

    
    def __init__(self):
        self.front = None
        self.rear = None
    
    def __str__(self):
        #same function as linked list
        current_node = self.front
        result = []
        separator =  " -> "

        while current_node != None:
            result.append(current_node.element)
            current_node = current_node.next_node
        return separator.join(map(str, result)) + (f" | Front element stored {self.front.element}, Rear element stored {self.rear.element}")
    
    def is_empty(self):
        if self.front == None and self.rear == None:
            return True
        else:
            return False
        
    def length(self):
        #same function as linked list
        current_node = self.front
        list_length = 0

        while current_node != None:
            current_node = current_node.next_node
            list_length += 1

        return list_length
    
    def see_front(self):
        if self.is_empty() == True:
            print("Front is not yet declared")
        else:
            return ("Front ") + str(self.front) 
        
    def see_rear(self):
        if self.is_empty() == True:
            print("Rear is not yet declared")
        else:
            return ("Rear ") + str(self.rear)
        
    #Enqueue at last element
    def enqueue(self, element):
        new_node = self.Node(element)

        if self.is_empty() == True:
            self.front = new_node
            self.rear = new_node
        else:
            current_rear_node = self.rear
            current_rear_node.next_node = new_node
            self.rear = new_node

    #Dequeue at first element
    def dequeue(self):
        if self.is_empty() == True:
            raise IndexError("Can't dequeue from an empty queue")
        else:
            current_front_node = self.front
            self.front = current_front_node.next_node
            current_front_node.next_node = None


#creating queue
us_states = Linked_List_Queue()
us_states.enqueue("Alabama")
us_states.enqueue("Alaska")
us_states.enqueue("Arizona")
us_states.enqueue("Arkansas")
us_states.enqueue("California")
us_states.enqueue("Colorado")


#testing implementation
print(us_states)
us_states.dequeue()
print(us_states)
print(us_states.see_front())
print(us_states.see_rear())

        
    
