#pretty much the same operations, but we can only perform any action to the "Top" element

#so stack needs to define an element to be "Top", but the rest can mostly be the same as a list

#Peek, should just return the current top element

#Push, increment top by 1 in the list, and insert at top's index

#Pop, decrement top by 1 in the list

#Is_Empty, returns true or false based on if Top is assigned a value (or just use list length)


#Stack as List
class List_Stack:
    def __init__(self):
        self.items = list()
        self.top = -1

    def __str__(self):
        return str(self.items) + (f" Top is {self.items[self.top]}")

    def is_empty(self):
        if self.top == -1:
            return True
        else:
            return False
        
    def length(self):
        return len(self.items)

    def peek(self):
        if self.is_empty() == True:
            print("Top is not yet declared")
        else:
            print(f"Top is at index {self.top}, element stored {self.items[self.top]}")
    
    def push(self, element):
        self.items.append(element)
        self.top += 1
    
    def pop(self):
        if self.is_empty() == True:
            raise IndexError("Can't pop from an empty stack")
        else:
            self.items.pop(self.top)
            self.top -= 1



#creating Stack
fruits = List_Stack()
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
fruits.peek()
fruits.pop()
print(fruits)
fruits.peek()




    