class Heap:

    def __init__(self, values: list[int], min_heap: bool) -> None:
        self.values = []
        self.min_heap = min_heap

        for value in values:
            self.insert(value)


    def __str__(self) -> str:
        """Format the underlying array, e.g. "[1, 3, 2, 5]"; empty gives "[]"."""

        return "[" + ", ".join(str(v) for v in self.values) + "]"


    # these are just definitions of a heap's indexes when using an array... nothing special
    def left(self, i: int) -> int:
        """Get index of left child node"""
        return 2 * i + 1

    def right(self, i: int) -> int:
        """Get index of right child node"""
        return 2 * i + 2

    def parent(self, i: int) -> int:
        """Get index of parent node"""
        return (i - 1) // 2  # Floor division


    def insert(self, value: int):
        self.values.append(value)
        self.heapify_up(len(self.values)-1)


    def heapify_up(self, index: int):
        while index > 0:

            parent = self.parent(index)

            if self.min_heap:
                if self.values[parent] <= self.values[index]:
                    break # min_heap property already achieved
            else:
                if self.values[parent] >= self.values[index]:
                    break # max_heap property already achieved

            # heapify
            temp = self.values[parent]
            self.values[parent] = self.values[index]
            self.values[index] = temp

            index = parent


    def remove(self):
        value = self.values[0]
        last = self.values.pop()

        if len(self.values) > 0:
            self.values[0] = last
            self.heapify_down(0)

        return value


    def heapify_down(self, index: int):

        while self.left(index) < len(self.values):
            left = self.left(index)
            right = self.right(index)
            child = left

            if right < len(self.values):
                if self.values[left] == self.values[right]:
                    child = left

                if self.min_heap == True:
                    if self.values[right] < self.values[left]:
                        child = right
                    elif self.values[right] > self.values[left]:
                        child = left

                elif self.min_heap == False:
                    if self.values[right] > self.values[left]:
                        child = right
                    elif self.values[right] < self.values[left]:
                        child = left

            if self.min_heap:
                if self.values[index] <= self.values[child]:
                    break
            else:
                if self.values[index] >= self.values[child]:
                    break

            temp = self.values[index]
            self.values[index] = self.values[child]
            self.values[child] = temp

            index = child


if __name__ == "__main__":
    h = Heap([5, 3, 8, 1, 9, 2], True)
    print("min-heap :", h)

    h.insert(0)
    print("insert 0 :", h)

    print("remove   :", h.remove(), "-> ", h)

    m = Heap([5, 3, 8, 1, 9, 2], False)
    print("max-heap :", m)

    m.insert(10)
    print("insert 10:", m)

    print("remove   :", m.remove(), "-> ", m)
