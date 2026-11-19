def bubble_sort(nums: list[int], descending: bool = False, show_steps: bool = False) -> None:
    """Sort nums in place: swap neighbouring values until nothing is out of order."""

    size = len(nums)

    for outer in range(size - 1):

        if show_steps:
            print(f"pass {outer}: unsorted part is {nums[:size - outer]}")

        for inner in range(0, size - 1 - outer):

            if descending:
                out_of_order = nums[inner] < nums[inner + 1]
            else:
                out_of_order = nums[inner] > nums[inner + 1]

            if out_of_order == True:
                nums[inner], nums[inner + 1] = nums[inner + 1], nums[inner]

                if show_steps:
                    print(f"  swap a[{inner}] and a[{inner + 1}] -> {nums}")

        if show_steps:
            print(f"  pass {outer} done -> {nums}, sorted tail {nums[size - 1 - outer:]}")
            print()


if __name__ == "__main__":
    a_list = [5, 3, 8, 1, 9, 2]
    print("start:", a_list)
    print()

    bubble_sort(a_list, show_steps=True)
    print("asc  :", a_list)

    b_list = [5, 3, 8, 1, 9, 2]
    bubble_sort(b_list, descending=True)
    print("desc :", b_list)

    c_list = [4, 4, 1, 3]
    bubble_sort(c_list)
    print("dupes:", c_list)

    d_list = []
    bubble_sort(d_list)
    print("empty:", d_list)
