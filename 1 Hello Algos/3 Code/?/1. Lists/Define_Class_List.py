#create list
fruits = ["apple", "banana", "orange", "strawberry", "orange"]
print(fruits)

#insert at end of list
fruits.append("watermelon")
print(fruits)

#inserts element at index
fruits.insert(3, "grapes")
print(fruits)

#delete element by index
fruits.pop(1)
print(fruits)

#delete the first occurance of this element by name
fruits.remove("orange")
print(fruits)

#yeah... just give the index inside of range
a_fruit = fruits[2]

#searches index of first occurance of this element by name
print(fruits.index("orange"))

#This is by default Ascending, we can make it descending by saying reverse=True, or even sort by our own function "key="
fruits.sort()
print(fruits)

#counts times of occurance of element
print(fruits.count("apple"))

#makes a copy of the list
fruits2 = fruits.copy()

#turn list empty
fruits.clear()
print(fruits2)
