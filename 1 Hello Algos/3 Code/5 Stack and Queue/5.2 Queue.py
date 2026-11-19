class Queue:
    """Fixed-capacity circular queue; front is the oldest, rear the newest."""

    def __init__(self, values: list[int], capacity: int):
        """rear is the index of the LAST element, so an empty queue starts at capacity - 1."""

        assert capacity >= len(values)

        self._queue = [0] * capacity
        self.capacity = capacity
        self.size = len(values)
        self.front = 0
        self.rear = (len(values) - 1) % capacity

        for i in range(len(values)):
            self._queue[i] = values[i]


    def push(self, value: int) -> None:
        """Add value at the back. Raises IndexError when full."""

        if self.size == self.capacity:
            raise IndexError("Queue is full")

        self.rear = (self.rear + 1) % self.capacity
        self._queue[self.rear] = value
        self.size += 1


    def pop(self) -> int:
        """Remove and return the front value. Raises IndexError when empty."""

        if self.size == 0:
            raise IndexError("Queue is empty")

        value = self._queue[self.front]
        self.front = (self.front + 1) % self.capacity
        self.size -= 1
        return value


    def __str__(self) -> str:
        """Format front-to-back, e.g. "front -> 1 -> 2 -> 3 -> back", or "(empty)"."""

        if self.size == 0:
            return "(empty)"

        parts = []
        for i in range(self.size):
            parts.append(str(self._queue[(self.front + i) % self.capacity]))
        return "front -> " + " -> ".join(parts) + " -> back"


if __name__ == "__main__":
    q = Queue([1, 2, 3], 5)
    print("start  :", q)

    q.push(4)
    print("push 4 :", q)

    print("pop    :", q.pop(), "-> size", q.size)

    q.push(9)
    print("push 9 :", q)

    print("raw    :", q._queue)
