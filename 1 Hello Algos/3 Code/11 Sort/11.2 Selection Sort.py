def selection_sort(nums: list[int], descending: bool = False, show_steps: bool = False) -> None:
    """Sort nums in place: swap the best leftover candidate to the front of the unsorted part."""

    size = len(nums)

    # the sorted
    for sorted in range(size - 1):

        if show_steps:
            print(f"pass {sorted}: filling index {sorted}, unsorted part is {nums[sorted:]}")

        # the unsorted
        for unsorted in range(sorted + 1, size):

            if descending:
                want_swap = nums[unsorted] > nums[sorted]
            else:
                want_swap = nums[unsorted] < nums[sorted]

            if want_swap:

                if show_steps:
                    print(f"  a[{unsorted}]={nums[unsorted]}, a[{sorted}]={nums[sorted]} -> swap")

                nums[sorted], nums[unsorted] = nums[unsorted], nums[sorted]

                if show_steps:
                    print(f"  now {nums}")

        if show_steps:
            print(f"  pass {sorted} done -> {nums}")
            print()


if __name__ == "__main__":
    a_list = [5, 3, 8, 1, 9, 2]
    print("start:", a_list)
    print()

    selection_sort(a_list, show_steps=True)
    print("asc  :", a_list)

    b_list = [5, 3, 8, 1, 9, 2]
    selection_sort(b_list, descending=True)
    print("desc :", b_list)

    c_list = [4, 4, 1, 3]
    selection_sort(c_list)
    print("dupes:", c_list)
