class HashMap:
    """A fixed-capacity hash map with one pair per slot."""

    class Pair:
        """A single key-value entry."""

        def __init__(self, key: int, value: int):
            """Store a key and its value."""

            self.key = key
            self.value = value


    def __init__(self, values: dict[int, int], capacity: int):
        """Build the map from pre-made pairs by reusing put()."""

        assert len(values) <= capacity, "more pairs than slots"

        self.hashmap: list[HashMap.Pair | None] = [None] * capacity
        self.capacity = capacity
        self.size = 0

        for key, value in values.items():
            self.put(key, value)


    def __str__(self) -> str:
        """Format as "key -> value" pairs in slot order, e.g. "{1 -> 10, 3 -> 30}"."""

        parts = []
        for pair in self.hashmap:
            if pair is not None:
                parts.append(f"{pair.key} -> {pair.value}")
        return "{" + ", ".join(parts) + "}"


    # this is an extremeley simple hash function for demonstration
    def hash(self, key: int) -> int:
        """Map a key to a slot index with the demo hash formula."""

        index = ((31 * key + 7) % 101) % self.capacity
        assert 0 <= index < len(self.hashmap), "Index out of range"
        return index


    # this does not solve hash collision
    def put(self, key: int, value: int) -> None:
        """Store value under key, overwriting whatever is in that slot."""

        pair = self.Pair(key, value)
        index = self.hash(key)

        if self.hashmap[index] is None:
            self.size += 1

        self.hashmap[index] = pair


    def get(self, key: int) -> int | None:
        """Return the value under key, or None if key is not in the map."""

        index = self.hash(key)
        pair = self.hashmap[index]

        if pair == None or pair.key != key:
            return None

        return pair.value


    def remove(self, key: int) -> None:
        """Clear the slot for key, but only if key is really sitting there."""

        index = self.hash(key)
        pair = self.hashmap[index]

        if pair is not None and pair.key == key:
            self.hashmap[index] = None
            self.size -= 1


    def contains(self, key: int) -> bool:
        """Return True if key is in the map, else False."""

        index = self.hash(key)
        pair = self.hashmap[index]

        if pair is not None and pair.key == key:
            return True

        return False


if __name__ == "__main__":
    h = HashMap({1: 10, 2: 20, 3: 30}, 5)
    print("start   :", h)

    h.put(4, 40)
    print("put 4   :", h)

    print("get 2   :", h.get(2), "-> size", h.size)

    h.remove(1)
    print("remove 1:", h)

    h.put(4, 99)
    print("put 4,99:", h, "-> size", h.size)

    print("contains:", h.contains(3), h.contains(9))

    print("raw     :", [(i, p.key if p else None) for i, p in enumerate(h.hashmap)])

    c = HashMap({3: 30, 0: 100}, 4)
    print("collide :", c, "-> size", c.size)
