from collections import deque


class BinarySearchTree:

    class Node:

        def __init__(self, value: int):
            """Store a value with no children yet."""

            self.value = value
            self.left: BinarySearchTree.Node | None = None
            self.right: BinarySearchTree.Node | None = None


    def __init__(self, values: list[int]):
        """Insert every value in order, starting from an empty tree."""

        self.root: BinarySearchTree.Node | None = None
        self.size = 0

        for value in values:
            self.insert(value)


    def __str__(self) -> str:
        """Format values in sorted order, e.g. "[5, 10, 20, 30]"; empty gives "[]"."""

        out = []

        def walk(node: BinarySearchTree.Node | None) -> None:
            if node == None:
                return
            walk(node.left)
            out.append(node.value)
            walk(node.right)

        walk(self.root)
        return "[" + ", ".join(str(v) for v in out) + "]"


    def insert(self, value: int):
        """Hang value on the first empty child slot the comparison walk reaches; duplicates ignored."""

        if self.size == 0:
            self.root = self.Node(value)
            self.size += 1
            return

        node = self.root
        while node != None:

            if value == node.value:
                return

            elif value < node.value:

                if node.left == None:
                    node.left = self.Node(value)
                    self.size += 1
                    return
                node = node.left

            elif value > node.value:
                if node.right == None:
                    node.right = self.Node(value)
                    self.size += 1
                    return
                node = node.right



    # binary search (sorta)
    def contains(self, value: int):
        """Go left when value is smaller and right when bigger; False once the walk falls off."""

        node = self.root
        while node != None:

            if node.value == value:
                return True

            if node.value < value:
                node = node.right

            elif node.value > value:
                node = node.left

        return False


    def remove(self, value: int):
        """Find the node holding value, then rewire for one of the three cases; absent is a no-op."""

        node = self.root
        prev = None

        while node != None and node.value != value:

            prev = node

            if node.value < value:
                node = node.right

            elif node.value > value:
                node = node.left


        if node == None:
            return


        # the 3 cases

        # case 1: no children
        if node.left == None and node.right == None:

            if prev == None:
                self.root = None

            elif prev.left == node:
                prev.left = None

            elif prev.right == node:
                prev.right = None

            self.size -= 1
            return


        # case 2: 1 children (left/right)
        elif node.left == None or node.right == None:

            if node.left != None:
                child = node.left
            else: #node.right != None
                child = node.right

            if prev == None:
                self.root = child

            elif prev.left == node:
                prev.left = child

            elif prev.right == node:
                prev.right = child

            self.size -= 1
            return


        # case 3: 2 children (left&right)
        elif node.left != None and node.right != None:

            # we are doing smallest value in the right subtree (inorder successor)
            # you can also do the largest value in the left subtree (inorder predecessor)

            # go right once, then keep going left
            successor = node.right

            while successor.left is not None:
                successor = successor.left

            self.remove(successor.value)
            node.value = successor.value

            return


    def min(self) -> int | None:
        """Leftmost value, or None when the tree is empty."""

        if self.root == None:
            return None

        node = self.root
        while node.left != None:
            node = node.left

        return node.value


    def max(self) -> int | None:
        """Rightmost value, or None when the tree is empty."""

        if self.root == None:
            return None

        node = self.root
        while node.right != None:
            node = node.right

        return node.value


    def height(self) -> int:
        """Number of levels: an empty tree is 0 and a single node is 1."""

        def walk(node: BinarySearchTree.Node | None) -> int:
            if node == None:
                return 0
            return 1 + max(walk(node.left), walk(node.right))

        return walk(self.root)


    # the 4 traversals
    def level_order_traversal(self) -> list[int]:

        # not gonna make a queue myself here, using collections
        queue = deque()
        queue.append(self.root)

        node_values = []

        while len(queue) > 0:

            node = queue.popleft()
            node_values.append(node.value)

            if node.left != None:
                queue.append(node.left)

            if node.right != None:
                queue.append(node.right)

        return node_values


    def pre_order_traversal(self):
        # visit node, traverse left, traverse right

        node_values = []

        def pre_order(node: BinarySearchTree.Node | None):
            if node is None:
                return

            node_values.append(node.value)
            pre_order(node.left)
            pre_order(node.right)

        pre_order(self.root)

        return node_values


    def in_order_traversal(self):
        # traverse left, visit node, traverse right

        node_values = []

        def in_order(node: BinarySearchTree.Node | None):
            if node is None:
                return

            in_order(node.left)
            node_values.append(node.value)
            in_order(node.right)

        in_order(self.root)

        return node_values


    def post_order_traversal(self):
        # traverse left, traverse right, visit node

        node_values = []

        def post_order(node: BinarySearchTree.Node | None):
            if node is None:
                return

            post_order(node.left)
            post_order(node.right)
            node_values.append(node.value)

        post_order(self.root)

        return node_values



if __name__ == "__main__":
    t = BinarySearchTree([20, 10, 30, 5, 15, 25, 40, 22])
    print("start    :", t, "-> size", t.size, "height", t.height())
    print("min/max  :", t.min(), t.max())
    print("contains :", t.contains(22), t.contains(99))

    t.insert(35)
    print("insert 35:", t, "-> size", t.size, "height", t.height())

    t.remove(20)
    print("remove 20:", t, "-> size", t.size, "| root value", t.root.value)

    t.remove(5)
    print("remove 5 :", t, "-> size", t.size)

    t.remove(10)
    print("remove 10:", t, "-> size", t.size, "height", t.height())
