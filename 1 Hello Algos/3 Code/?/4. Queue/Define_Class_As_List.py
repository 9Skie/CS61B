#So about a queue, you need to be able to insert at one end and delete at another, and can you access all elements? I don't think so


#anything between front and rear is considered inside the queue

#Is_Empty, the checkingconditions become if both are -1, because when there is only 1 element the head is the rear

#Front tells me the first element that we insert from, the current front element

#Rear tells me the last element that we delete from, the current rear element

#Enqueue, increment rear by 1, and fill in element at where rear is pointing

#Dequeue, increment front by 1, that's it (hah, no, we don't even have to do anything about it)
#since this is python, by deleting the 1st element in the list, popping it, we don't even have to botyher 

#python apparently has a queue built in itself
import queue
lmao_you_did_useless_work = queue.Queue()


class List_Queue:
    
    def __init__(self):
        self.items = list()
        self.front = -1
        self.rear = -1
    
    def __str__(self) -> str:
        return str(self.items) + (f" Front is {self.items[self.front]}, Rear is {self.items[self.rear]}")
    
    def is_empty(self):
        if self.front == -1 and self.rear == -1:
            return True
        else:
            return False
        

    #Enqueue at end of list    
    def enqueue(self, element):
        if self.is_empty() == True:
            self.items.append(element)
            self.front += 1
            self.rear += 1
        else:
            self.items.append(element)
            self.rear += 1
    
    #This is not constant time, pop moves all elements inside the list so it's O(n) not O(1)
    #Dequeue at front of list    
    def dequeue(self):
        if self.is_empty() == True:
            raise IndexError("Can't dequeue from an empty queue")
        else:
            self.items.pop(self.front)
            self.rear -= 1
            if self.rear == -1:
                self.front = -1
            else:
                pass
        
    def see_front(self):
        if self.is_empty() == True:
            print("Front is not yet declared")
        else:
            print(f"Front is at index {self.front}, element stored {self.items[self.front]}")

    def see_rear(self):
        if self.is_empty() == True:
            print("Rear is not yet declared")
        else:
            print(f"Rear is at index {self.rear}, element stored {self.items[self.rear]}")



#creating queue
us_states = List_Queue()
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
us_states.see_front()
us_states.see_rear()