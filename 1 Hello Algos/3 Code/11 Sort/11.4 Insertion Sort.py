def insertion_sort(nums: list[int], descending: bool = False, show_steps: bool = False) -> None:
    """Sort nums in place: slide bigger elements right and drop each new value into the gap."""

    for unsorted_index in range(1, len(nums)):

        unsorted_value = nums[unsorted_index]
        fill_index = unsorted_index

        if show_steps:
            print(f"take a[{unsorted_index}]={unsorted_value} from {nums}")

        while fill_index > 0:

            if descending:
                should_shift = nums[fill_index - 1] < unsorted_value
            else:
                should_shift = nums[fill_index - 1] > unsorted_value

            if should_shift == False:
                break

            if show_steps:
                print(f"  a[{fill_index - 1}]={nums[fill_index - 1]} moves right")

            nums[fill_index] = nums[fill_index - 1]
            fill_index -= 1

        nums[fill_index] = unsorted_value

        if show_steps:
            print(f"  {unsorted_value} lands at index {fill_index} -> {nums}")
            print()


if __name__ == "__main__":
    a_list = [5, 3, 8, 1, 9, 2]
    print("start:", a_list)
    print()

    insertion_sort(a_list, show_steps=True)
    print("asc  :", a_list)

    b_list = [5, 3, 8, 1, 9, 2]
    insertion_sort(b_list, descending=True)
    print("desc :", b_list)

    c_list = [4, 4, 1, 3]
    insertion_sort(c_list)
    print("dupes:", c_list)

    d_list = []
    insertion_sort(d_list)
    print("empty:", d_list)
