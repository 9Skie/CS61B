from random import randint


def quick_sort(nums: list[int], left: int, right: int, descending: bool = False, show_steps: bool = False) -> None:
    """Sort nums in place: partition around a random pivot, then sort both sides."""

    def partition(nums: list[int], left: int, right: int):

        start = left
        end = right

        # the selection of pivot is herustic
        pivot = randint(left, right)
        pivot_value = nums[pivot]

        if show_steps:
            print(f"  partition a[{start}..{end}] = {nums[start:end + 1]}, pivot = {pivot_value}")

        # swapping values so everything smaller ends up left of pivot_value and larger to its right, if descending
        while left <= right:

            if descending:
                while left <= right and nums[left] > pivot_value:
                    left += 1

                while left <= right and nums[right] < pivot_value:
                    right -= 1
            else:
                while left <= right and nums[left] < pivot_value:
                    left += 1

                while left <= right and nums[right] > pivot_value:
                    right -= 1

            if left <= right:
                nums[left], nums[right] = nums[right], nums[left]
                left += 1
                right -= 1

        if show_steps:
            print(f"    -> {nums}")

        return left, right


    # terminal case
    if left >= right:
        return

    next_left, next_right = partition(nums, left, right)

    quick_sort(nums, left, next_right, descending, show_steps)
    quick_sort(nums, next_left, right, descending, show_steps)


if __name__ == "__main__":
    a_list = [5, 3, 8, 1, 9, 2]
    print("start:", a_list)
    print()

    quick_sort(a_list, 0, len(a_list) - 1, show_steps=True)
    print("asc  :", a_list)

    b_list = [5, 3, 8, 1, 9, 2]
    quick_sort(b_list, 0, len(b_list) - 1, descending=True)
    print("desc :", b_list)

    c_list = [4, 4, 1, 3, 4, 0]
    quick_sort(c_list, 0, len(c_list) - 1)
    print("dupes:", c_list)

    d_list = list(range(10))
    quick_sort(d_list, 0, len(d_list) - 1)
    print("already sorted:", d_list)

    e_list = []
    quick_sort(e_list, 0, len(e_list) - 1)
    print("empty:", e_list)
