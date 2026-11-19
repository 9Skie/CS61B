class HashMapChain:
    """A hash map that handles collisions by chaining: each slot holds a linked list."""


    class Pair:
        """One key-value entry, linked to the next entry in the same slot."""

        def __init__(self, key: int, value: int):
            self.key = key
            self.value = value
            self.next: HashMapChain.Pair | None = None


    def __init__(self, values: dict[int, int], capacity: int):
        """Fill the table by putting every key-value pair of values."""

        self.hashmapchain: list[HashMapChain.Pair | None] = [None] * capacity
        self.capacity = capacity
        self.size = 0

        for key, value in values.items():
            self.put(key, value)


    def __str__(self) -> str:
        """Format each used slot as its chain: "key:value" per node, "->" between nodes."""

        parts = []
        for index, node in enumerate(self.hashmapchain):
            chain = []
            while node is not None:
                chain.append(f"{node.key}:{node.value}")
                node = node.next
            if chain:
                parts.append(f"[{index}] " + " -> ".join(chain))
        return "{" + ", ".join(parts) + "}"


    # this is an extremeley simple hash function for demonstration
    def hash(self, key: int) -> int:
        """Map a key to a slot index with the demo hash formula."""

        index = ((31 * key + 7) % 101) % self.capacity
        assert 0 <= index < len(self.hashmapchain), "Index out of range"
        return index


    def put(self, key: int, value: int) -> None:
        """Store value under key: overwrite if the key exists, else append to its chain."""

        index = self.hash(key)
        pair = self.Pair(key, value)
        node = self.hashmapchain[index]

        if node == None:
            self.hashmapchain[index] = pair
            self.size += 1
        else:
            while node.next != None:

                # key already exist, overwrite value
                if node.key == key:
                    node.value = value
                    return

                node = node.next

            if node.key == key:
                node.value = value
                return

            node.next = pair
            self.size += 1


    def get(self, key: int) -> int | None:
        """Return the value under key, or None if key is not in the map."""

        index = self.hash(key)
        node = self.hashmapchain[index]

        if node == None:
            return None

        elif node.key == key:
            return node.value

        else:
            while node.next != None:

                if node.key == key:
                    return node.value

                node = node.next

        if node.key == key:
            return node.value

        return None


    def remove(self, key: int) -> None:
        """Unlink the node holding key, if it exists."""

        index = self.hash(key)
        node = self.hashmapchain[index]

        if node == None:
            return

        elif node.key == key:
            self.hashmapchain[index] = node.next
            self.size -= 1
            return

        prev = node
        node = node.next

        while node != None:

            if node.key == key:
                prev.next = node.next
                node.next = None
                self.size -= 1
                return

            prev = node
            node = node.next


    def contains(self, key: int) -> bool:
        """Return True if key is in the map, else False."""

        index = self.hash(key)
        node = self.hashmapchain[index]

        if node == None:
            return False

        elif node.key == key:
            return True

        node = node.next

        while node != None:
            if node.key == key:
                return True
            node = node.next

        return False


if __name__ == "__main__":
    h = HashMapChain({3: 30, 0: 100, 16: 1600, 28: 2800}, 4)
    print("start    :", h, "-> size", h.size)

    print("get 16   :", h.get(16), "-> size", h.size)

    h.put(0, 999)
    print("put 0,999:", h, "-> size", h.size)

    h.put(1, 10)
    print("put 1    :", h, "-> size", h.size)

    h.remove(16)
    print("remove 16:", h, "-> size", h.size)

    print("contains :", h.contains(28), h.contains(7))

    print("raw      :", [(i, p.key if p else None) for i, p in enumerate(h.hashmapchain)])
