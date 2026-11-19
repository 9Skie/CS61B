class AVLTree:
    """A self-balancing binary search tree: every node keeps left - right height within 1."""

    class Node:
        """One tree node: value, children, plus cached height and balance."""

        def __init__(self, value: int):
            """Store a value as a fresh leaf: height 1, balance 0."""

            self.value = value
            self.left: AVLTree.Node | None = None
            self.right: AVLTree.Node | None = None
            self.height = 1
            self.balance = 0


    def __init__(self, values: list[int]):
        """Insert every value in order, starting from an empty tree."""

        self.root: AVLTree.Node | None = None
        self.size = 0

        for value in values:
            self.insert(value)


    def __str__(self) -> str:
        """Format values in sorted order, e.g. "[5, 10, 20, 30]"; empty gives "[]"."""

        out = []

        def walk(node: AVLTree.Node | None) -> None:
            if node == None:
                return
            walk(node.left)
            out.append(node.value)
            walk(node.right)

        walk(self.root)
        return "[" + ", ".join(str(v) for v in out) + "]"


    def update_height_and_balance(self, node: "AVLTree.Node"):
        """Recompute both cached fields from the children, treating a missing child as height 0."""

        if node.left != None:
            left_height = node.left.height
        else:
            left_height = 0

        if node.right != None:
            right_height = node.right.height
        else:
            right_height = 0

        node.height = 1 + max(left_height, right_height)
        node.balance = left_height - right_height


    def rebalance(self, parents: list[AVLTree.Node], stop_after_rotation: bool):
        """Walk parents leaf-to-root, refreshing heights and rotating; insert stops after one rotation, delete keeps going."""

        for i in range(len(parents) - 1, -1, -1):

            parent = parents[i]
            self.update_height_and_balance(parent)

            if parent.balance > 1 or parent.balance < -1:
                new_root = self.rotate(parent)

                if i == 0:
                    self.root = new_root
                elif parents[i-1].left is parent:
                    parents[i-1].left = new_root
                else:
                    parents[i-1].right = new_root

                if stop_after_rotation == True:
                    break


    def insert(self, value: int):
        """BST insert by comparison, then rebalance back up the path; duplicates ignored."""

        if self.size == 0:
            self.root = self.Node(value)
            self.size += 1
            return

        parents = []
        node = self.root

        while node != None:
            parents.append(node)

            if value == node.value:
                return

            elif value > node.value:

                if node.right == None:
                    node.right = self.Node(value)
                    self.size += 1
                    break
                node = node.right

            elif value < node.value:

                if node.left == None:
                    node.left = self.Node(value)
                    self.size += 1
                    break
                node = node.left

        # up to here is just BST insertion

        # one rotation fixes the path on insert
        self.rebalance(parents, True)



    def right_rotation(self, node: AVLTree.Node):
        """Pivot the left child up over node (fixes balance > 1); returns the new subtree root."""

        child = node.left
        assert child is not None, "Right rotation requires a left child"

        grand_child = child.right
        child.right = node
        node.left = grand_child

        self.update_height_and_balance(node)
        self.update_height_and_balance(child)

        # child becomes new root of subtree, needs to re-attach
        return child


    def left_rotation(self, node: AVLTree.Node):
        """Pivot the right child up over node (fixes balance < -1); returns the new subtree root."""

        child = node.right
        assert child is not None, "Left rotation requires a left child"

        grand_child = child.left
        child.left = node
        node.right = grand_child

        self.update_height_and_balance(node)
        self.update_height_and_balance(child)

        # child becomes new root of subtree, needs to re-attach
        return child


    def rotate(self, node: AVLTree.Node):
        """Pick single or double rotation from node and its child balances; returns the new subtree root."""

        # 4 cases

        # case 1: parent balance > 1, left child balance >= 0
        # rotate parent right
        if node.balance > 1 and node.left.balance >= 0:
            return self.right_rotation(node)

        # case 2: parent balance > 1, left child balance < 0
        # rotate left child left, parent right
        if node.balance > 1 and node.left.balance < 0:
            node.left = self.left_rotation(node.left)
            return self.right_rotation(node)

        # case 3: parent balance < -1, right child balance <= 0
        # rotate parent left
        if node.balance < -1 and node.right.balance <= 0:
            return self.left_rotation(node)

        # case 4: parent balance < -1, right child balance > 0
        # rotate right child right, parent left
        if node.balance < -1 and node.right.balance > 0:
            node.right = self.right_rotation(node.right)
            return self.left_rotation(node)

        # if we don't need rotations
        return node


    def remove(self, value: int):
        """Find the node, splice it for the leaf / one-child / two-child case, then rebalance the whole path."""

        node = self.root
        parents = []
        prev = None

        while node != None and node.value != value:

            prev = node
            parents.append(node)

            if node.value < value:
                node = node.right

            elif node.value > value:
                node = node.left


        if node == None:
            return


        # 3 cases

        # case 1: no children
        if node.left == None and node.right == None:

            if prev == None:
                 self.root = None

            elif prev.left == node:
                prev.left = None

            elif prev.right == node:
                prev.right = None

            self.size -= 1


        # case 2: 1 child (left/right)
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


        # case 3: 2 child (left&right)
        elif node.left != None and node.right != None:

            # we are doing smallest value in the right subtree (inorder successor)
            # you can also do the largest value in the left subtree (inorder predecessor)

            # go right once, then keep going left
            successor = node.right

            while successor.left is not None:
                successor = successor.left

            self.remove(successor.value)
            node.value = successor.value

            # node survives, so it belongs in the walk back up too
            parents.append(node)

        # delete can unbalance several ancestors, so no early stop
        self.rebalance(parents, False)


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


if __name__ == "__main__":
    t = AVLTree([1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
    print("start    :", t, "-> size", t.size, "height", t.root.height)

    print("root     :", t.root.value, "balance", t.root.balance)
    print("children :", t.root.left.value, t.root.right.value)

    t.insert(11)
    print("insert 11:", t, "-> height", t.root.height)

    t.remove(4)
    print("remove 4 :", t, "-> size", t.size, "height", t.root.height)

    t.remove(99)
    print("remove 99:", t, "-> size", t.size, "(absent, nothing changes)")

    u = AVLTree([10, 9, 8, 7])
    print("10..7    :", u, "-> root", u.root.value, "height", u.root.height)
