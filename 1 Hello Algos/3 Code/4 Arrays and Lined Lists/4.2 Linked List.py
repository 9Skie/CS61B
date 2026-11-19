class LinkedList:
    """Singly linked list with a dummy head (sentinel) node."""


    class Node:
        def __init__(self, value) -> None:
            self.value = value
            self.next: LinkedList.Node | None = None

        def __repr__(self) -> str:
            return f"Node({self.value})"


    def __init__(self, values: list[int]) -> None:
        """Build a list holding `values`, in order -- O(n)."""

        self.head = self.Node(None)   # sentinel

        tail = self.head
        for i in range(len(values)):
            node = self.Node(values[i])
            tail.next = node
            tail = node


    def __str__(self) -> str:
        """Format as "1 -> 3 -> 2", or "(empty)" when there is no data."""

        parts = []
        node = self.head.next
        while node is not None:
            parts.append(str(node.value))
            node = node.next
        return " -> ".join(parts) if parts else "(empty)"


    def _access_prev(self, index: int) -> "LinkedList.Node":
        """Return the node just BEFORE `index`, or the sentinel when index is 0 -- O(n)."""

        node = self.head

        for _ in range(index):
            if node == None:
                raise IndexError("index out of range")
            node = node.next

        if node is None:
            raise IndexError("index out of range")

        return node


    def _find_prev(self, value: int) -> "LinkedList.Node":
        """Return the node just BEFORE the first node holding `value` -- O(n)."""

        node = self.head

        while node.next != None:
            if node.next.value == value:
                return node
            node = node.next

        raise ValueError("value not found")


    def insert(self, value: int, index: int) -> None:
        """Insert `value` at `index`; O(n) to walk there, then two pointer writes."""

        prev_node = self._access_prev(index)
        new_node = self.Node(value)

        new_node.next = prev_node.next
        prev_node.next = new_node


    def delete(self, value: int) -> None:
        """Remove the first node holding `value`; O(n) to find, one pointer write."""

        prev_node = self._find_prev(value)

        node = prev_node.next
        assert node is not None

        prev_node.next = node.next
        node.next = None


    def access(self, index: int) -> "LinkedList.Node":
        """Return the node at `index`; O(n) because there is no address arithmetic."""

        node = self.head.next

        for _ in range(index):
            if node == None:
                raise IndexError("index out of range")
            node = node.next

        if node is None:
                raise IndexError("index out of range")

        return node


if __name__ == "__main__":
    nums = LinkedList([1, 3, 9, 5, 4])
    print("start      :", nums)
    print("access[2]  :", nums.access(2))
    nums.insert(6, 3)
    print("insert 6@3 :", nums)
    nums.delete(9)
    print("delete 9   :", nums)
    try:
        nums.delete(99)
        print("delete 99  :", nums)
    except ValueError as e:
        print("delete 99  : ValueError:", e)
