def bucket_sort(nums: list[int], descending: bool = False, show_steps: bool = False) -> None:
    """Sort nums in place by spreading values into buckets, sorting each, then reading them back."""

    if len(nums) <= 1:
        return

    low = min(nums)
    high = max(nums)

    bucket_width = (high - low + 1 + len(nums) - 1) // len(nums)
    bucket_count = (high - low + 1 + bucket_width - 1) // bucket_width
    buckets = [[] for _ in range(bucket_count)]

    # sort into buckets
    for index in range(len(nums)):
        bucket_index = (nums[index] - low) // bucket_width
        buckets[bucket_index].append(nums[index])

    if show_steps:
        print(f"  range {low}..{high}, {bucket_count} buckets of width {bucket_width}")
        print(f"  filled: {buckets}")


    # sort each bucket
    for bucket in buckets:

        # some sorting algorithm that sorts each bucket
        bucket.sort(reverse=descending)


    # merge results
    nums_index = 0

    if descending:
        order = range(len(buckets) - 1, -1, -1)
    else:
        order = range(len(buckets))

    for bucket_index in order:
        for num in buckets[bucket_index]:
            nums[nums_index] = num
            nums_index += 1

    if show_steps:
        print(f"  after merging: {nums}")


if __name__ == "__main__":
    a_list = [5, 3, 8, 1, 9, 2]
    print("start:", a_list)
    print()

    bucket_sort(a_list, show_steps=True)
    print("asc  :", a_list)

    b_list = [5, 3, 8, 1, 9, 2]
    bucket_sort(b_list, descending=True)
    print("desc :", b_list)

    c_list = [4, 4, 1, 3]
    bucket_sort(c_list)
    print("dupes:", c_list)

    d_list = [7, 7, 7]
    bucket_sort(d_list)
    print("all equal:", d_list)

    e_list = []
    bucket_sort(e_list)
    print("empty:", e_list)
