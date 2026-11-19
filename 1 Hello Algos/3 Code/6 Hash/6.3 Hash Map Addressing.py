class HashMapAddressing:
    """A hash map that handles collisions by linear probing, one pair per slot."""


    class Pair:
        """One key-value entry; deleted marks a tombstone that probing must walk past."""

        def __init__(self, key: int, value: int):
            self.key = key
            self.value = value
            self.deleted = False


    def __init__(self, values: dict[int, int], capacity: int):
        """Fill the table by putting every key-value pair of values."""

        self.hashmapaddressing: list[HashMapAddressing.Pair | None] = [None] * capacity
        self.capacity = capacity
        self.size = 0


        for key, value in values.items():
            self.put(key, value)


    # this is an extremeley simple hash function for demonstration
    def hash(self, key: int) -> int:
        """Map a key to a slot index with the demo hash formula."""

        index = ((31 * key + 7) % 101) % self.capacity
        assert 0 <= index < len(self.hashmapaddressing), "Index out of range"
        return index


    def __str__(self) -> str:
        """Format every slot in order: "key:value" live, "key:DEL" tombstone, "." empty."""

        parts = []
        for index, node in enumerate(self.hashmapaddressing):
            if node == None:
                parts.append(f"[{index}] .")
            elif node.deleted == True:
                parts.append(f"[{index}] {node.key}:DEL")
            else:
                parts.append(f"[{index}] {node.key}:{node.value}")
        return " ".join(parts)


    # linear probing
    def put(self, key: int, value: int) -> None:
        """Insert or update key, reusing the first tombstone passed if one is found."""

        index = self.hash(key)
        start = index
        node = self.hashmapaddressing[index]
        deleted_existed = False
        first_deleted_index = index

        while node != None:
            if node.key == key and node.deleted == False:
                node.value = value
                return

            if deleted_existed == False and node.deleted == True:
                first_deleted_index = index
                deleted_existed = True

            index = (index + 1) % self.capacity

            if index == start:
                if deleted_existed:
                        break
                raise OverflowError("Hash map is full")

            node = self.hashmapaddressing[index]


        if deleted_existed == True:
            self.hashmapaddressing[first_deleted_index] = self.Pair(key, value)
        else:
            self.hashmapaddressing[index] = self.Pair(key, value)

        self.size += 1


    def get(self, key: int) -> int | None:
        """Return the value under key, or None: probing stops at a None slot, not a tombstone."""

        index = self.hash(key)
        start = index
        node = self.hashmapaddressing[index]

        if node == None:
            return None

        while node.key != key or node.deleted == True:
            index = (index + 1) % self.capacity

            if index == start:
                return None

            node = self.hashmapaddressing[index]

            if node == None:
                return None


        if node.deleted == False:
            return node.value


    def delete(self, key: int) -> None:
        """Mark key's slot as a tombstone instead of clearing it, so probing still works."""

        index = self.hash(key)
        start = index
        node = self.hashmapaddressing[index]

        if node == None:
            return None


        while node.key != key or node.deleted == True:
            index = (index + 1) % self.capacity

            if index == start:
                return None

            node = self.hashmapaddressing[index]

            if node == None:
                return None

        node.deleted = True
        self.size -= 1


if __name__ == "__main__":
    h = HashMapAddressing({10: 1000, 9: 900}, 7)
    print("start    :", h, "-> size", h.size)

    print("get 9    :", h.get(9), "(hash(9)=0, slot 0 taken by 10, so it probed to 1)")

    h.delete(10)
    print("delete 10:", h, "-> size", h.size)

    print("get 9    :", h.get(9), "(probes PAST the tombstone at slot 0)")

    h.put(2, 20)
    print("put 2    :", h, "-> size", h.size)

    h.delete(99)
    print("delete 99:", h, "-> size", h.size, "(absent key changes nothing)")

    h.put(9, 999)
    print("put 9,999:", h, "-> size", h.size, "(updates in place)")
