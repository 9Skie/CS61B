class Stack:
    """Fixed-capacity stack backed by an array; top_pointer == -1 means empty."""

    def __init__(self, values: list[int], capacity: int) -> None:
        """values[0] sits at the bottom, values[-1] on top."""

        assert capacity >= len(values)

        self._stack = [0] * capacity
        self.top_pointer = len(values) - 1   # -1 when there are no values
        self.capacity = capacity

        for i in range(len(values)):
            self._stack[i] = values[i]


    def push(self, value: int) -> None:
        """Put value on top. Raises AssertionError when the stack is full."""

        assert self.top_pointer + 1 <= self.capacity - 1

        self.top_pointer += 1
        self._stack[self.top_pointer] = value


    def pop(self) -> int:
        """Remove and return the top value. Raises AssertionError when empty."""

        assert self.top_pointer >= 0

        value = self._stack[self.top_pointer]
        self.top_pointer -= 1
        return value


    def size(self) -> int:
        """Number of elements currently on the stack."""

        return self.top_pointer + 1


    def __str__(self) -> str:
        """Format bottom-to-top, e.g. "bottom -> 1 -> 2 -> 3 -> top", or "(empty)"."""

        if self.top_pointer < 0:
            return "(empty)"

        parts = []
        for i in range(self.top_pointer + 1):
            parts.append(str(self._stack[i]))
        return "bottom -> " + " -> ".join(parts) + " -> top"


if __name__ == "__main__":
    s = Stack([1, 2, 3], 5)
    print("start   :", s)

    s.push(4)
    print("push 4  :", s)

    print("pop     :", s.pop(), "-> size", s.size())

    s.push(9)
    print("push 9  :", s)

    print("raw     :", s._stack)
