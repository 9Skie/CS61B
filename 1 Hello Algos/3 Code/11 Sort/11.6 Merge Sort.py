def merge_sort(nums: list[int], descending: bool = False, show_steps: bool = False) -> None:
    """Sort nums in place with merge sort, using one scratch array of the same size."""

    if len(nums) <= 1:
        return

    # one scratch array reused by every merge, so total extra space is O(n)
    scratch = [0] * len(nums)


    def sort_range(low: int, high: int) -> None:
        """Sort nums[low..high] in place."""

        # terminal case
        if low >= high:
            return

        mid = (low + high) // 2

        sort_range(low, mid)
        sort_range(mid + 1, high)

        if show_steps:
            print(f"  merge a[{low}..{mid}]={nums[low:mid + 1]} with a[{mid + 1}..{high}]={nums[mid + 1:high + 1]}")

        # copy this range into scratch, then merge the two halves back into nums
        for i in range(low, high + 1):
            scratch[i] = nums[i]

        left_index = low
        right_index = mid + 1
        nums_insertion_index = low

        # comparing and inserting from both halves
        while left_index <= mid and right_index <= high:

            if descending:
                takes_left = scratch[left_index] >= scratch[right_index]
            else:
                takes_left = scratch[left_index] <= scratch[right_index]

            if takes_left:
                nums[nums_insertion_index] = scratch[left_index]
                left_index += 1
            else:
                nums[nums_insertion_index] = scratch[right_index]
                right_index += 1

            nums_insertion_index += 1


        # draining whichever half still has elements
        while left_index <= mid:
            nums[nums_insertion_index] = scratch[left_index]
            left_index += 1
            nums_insertion_index += 1

        while right_index <= high:
            nums[nums_insertion_index] = scratch[right_index]
            right_index += 1
            nums_insertion_index += 1

        if show_steps:
            print(f"    -> {nums}")


    sort_range(0, len(nums) - 1)


if __name__ == "__main__":
    a_list = [5, 3, 8, 1, 9, 2]
    print("start:", a_list)
    print()

    merge_sort(a_list, show_steps=True)
    print("asc  :", a_list)

    b_list = [5, 3, 8, 1, 9, 2]
    merge_sort(b_list, descending=True)
    print("desc :", b_list)

    c_list = [4, 4, 1, 3, 4, 0]
    merge_sort(c_list)
    print("dupes:", c_list)

    d_list = list(range(10))
    merge_sort(d_list)
    print("already sorted:", d_list)

    e_list = []
    merge_sort(e_list)
    print("empty:", e_list)
