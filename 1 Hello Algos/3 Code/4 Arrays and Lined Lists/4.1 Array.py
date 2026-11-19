import random


class ArrayList:
    """
    Dynamic array that grows automatically when full.
    """

    def __init__(self, values: list[int], capacity: int):

        self.capacity = capacity
        self.size = len(values)
        self.data = [0] * capacity

        for i in range(self.size):
            self.data[i] = values[i]

    def __str__(self) -> str:
        return f"ArrayList({self.data[:self.size]}, size={self.size}, capacity={self.capacity})"


    def random_access(self) -> int:
        """
        Return a randomly chosen element.
        """

        index = random.randint(0, self.size - 1)
        return self.data[index]


    def access(self, index: int) -> int:
        """
        Return the element at index.
        """

        return self.data[index]


    def search(self, value: int) -> int:
        """
        Linear search. Returns the index, or -1 if absent.
        """

        for i in range(self.size):
            if self.data[i] == value:
                return i
        return -1


    def traverse(self) -> None:
        """
        Visit every valid element, in order.
        """

        line = ""
        for i in range(self.size):
            line += str(self.data[i]) + " "
        print(line.strip())


    def insert(self, value: int, index: int) -> None:
        """
        Insert value at index, shifting everything after it right.
        If the array is full, grow it before inserting.
        """

        if self.size == self.capacity:
            self.extend(max(1, self.capacity))  # Double capacity; handle zero.

        self.size += 1
        for i in range(self.size - 1, index, -1):
            self.data[i] = self.data[i - 1]
        self.data[index] = value


    def remove(self, index: int) -> None:
        """
        Remove the element at index, shifting everything after it left.
        """

        for i in range(index, self.size - 1):
            self.data[i] = self.data[i + 1]
        self.size -= 1


    def extend(self, amount: int) -> None:
        """
        Grow the array by `amount` slots.
        """

        new_data = [0] * (self.capacity + amount)
        for i in range(self.size):
            new_data[i] = self.data[i]
        self.data = new_data
        self.capacity += amount



if __name__ == "__main__":
    nums = ArrayList([1, 3, 2, 5, 4], capacity=5)
    print("start      :", nums)

    print("access[2]  :", nums.access(2))
    print("search 3   :", nums.search(3))
    print("search 99  :", nums.search(99))
    print("random     :", nums.random_access())
    nums.insert(6, 3)
    print("insert 6@3 :", nums)
    nums.remove(2)
    print("remove @2  :", nums)
    print("traverse   : ", end="")
    nums.traverse()
    nums.extend(3)
    print("extend 3   :", nums)
