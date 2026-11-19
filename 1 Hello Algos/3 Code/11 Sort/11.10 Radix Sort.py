def radix_sort(nums: list[int], descending: bool = False, show_steps: bool = False) -> None:
    """Sort non-negative nums in place, one decimal digit at a time, least significant first."""

    if len(nums) <= 1:
        return

    # get a digit
    def get_digit(value: int, place: int) -> int:
        return (value // place) % 10


    # sort based on a digit, which basically could be any sorting algorithm
    # we will use counting sort here, since it's fixed 0-9 per digit
    def digit_sort(place: int) -> None:

        buckets = [[] for _ in range(10)]

        # drop each value into the bucket for its current digit
        for value in nums:
            buckets[get_digit(value, place)].append(value)

        if show_steps:
            print(f"  digit place {place}: buckets {[b for b in buckets if b]}")

        # put back the values in digit order
        nums_index = 0

        for bucket in buckets:
            for value in bucket:
                nums[nums_index] = value
                nums_index += 1

        if show_steps:
            print(f"    -> {nums}")


    largest = max(nums)
    place = 1

    while largest // place > 0:

        digit_sort(place)
        place *= 10

    # each pass builds ascending order, so reversing gives descending
    if descending:
        nums.reverse()


if __name__ == "__main__":
    a_list = [5, 3, 80, 1, 9, 2]
    print("start:", a_list)
    print()

    radix_sort(a_list, show_steps=True)
    print("asc  :", a_list)

    b_list = [5, 3, 80, 1, 9, 2]
    radix_sort(b_list, descending=True)
    print("desc :", b_list)

    c_list = [4, 4, 1, 3]
    radix_sort(c_list)
    print("dupes:", c_list)

    d_list = [0, 0, 0]
    radix_sort(d_list)
    print("zeros:", d_list)

    e_list = []
    radix_sort(e_list)
    print("empty:", e_list)
