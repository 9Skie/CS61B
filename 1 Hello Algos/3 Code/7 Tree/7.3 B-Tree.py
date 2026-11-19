class BTree:
    """A B-tree: nodes hold many sorted keys and children, kept balanced by splitting."""

    class Node:
        """One node: sorted keys, child pointers, and a leaf flag."""

        def __init__(self, leaf: bool):
            self.keys: list[int] = []
            self.children: list[BTree.Node] = []
            self.leaf = leaf


    def __init__(self, order: int, values: list[int], b_size: int):
        """Set the branching order, then insert every value."""
        pass


    def __str__(self) -> str:
        """Print the tree level by level, e.g. "[10] -> [3, 7] [12, 20]"."""
        pass


    def search(self, value: int) -> bool:
        """Return True if value is anywhere in the tree."""
        pass


    def insert(self, value: int) -> None:
        """Add value, splitting any full node on the way down."""
        pass


    def remove(self, value: int) -> None:
        """Delete value, borrowing or merging a sibling when a node would underflow."""
        pass


    def split_child(self, parent: BTree.Node, index: int) -> None:
        """Split the overfull child at parent.children[index] and lift its middle key."""
        pass
