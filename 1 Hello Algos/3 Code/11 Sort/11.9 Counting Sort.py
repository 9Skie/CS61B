def counting_sort(nums: list[int], descending: bool = False, show_steps: bool = False) -> None:
    """Sort nums in place by counting each value, then writing them back in value order."""

    if len(nums) <= 1:
        return

    low = min(nums)
    high = max(nums)

    counts = [0] * (high - low + 1)

    # add count into count list
    for value in nums:
        index = value - low
        counts[index] += 1

    if show_steps:
        print(f"  values {low}..{high}, counts = {counts}")

    # put back the counted values into list
    nums_index = 0

    if descending:
        order = range(len(counts) - 1, -1, -1)
    else:
        order = range(len(counts))

    for index in order:
        value = index + low

        for _ in range(counts[index]):
            nums[nums_index] = value
            nums_index += 1

    if show_steps:
        print(f"  after writing back: {nums}")


if __name__ == "__main__":
    a_list = [5, 3, 8, 1, 9, 2]
    print("start:", a_list)
    print()

    counting_sort(a_list, show_steps=True)
    print("asc  :", a_list)

    b_list = [5, 3, 8, 1, 9, 2]
    counting_sort(b_list, descending=True)
    print("desc :", b_list)

    c_list = [4, 4, 1, 3]
    counting_sort(c_list)
    print("dupes:", c_list)

    d_list = []
    counting_sort(d_list)
    print("empty:", d_list)
