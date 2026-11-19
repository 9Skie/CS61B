def BinarySearch(a_list: list[int], search_value: int, show_steps: bool = False) -> int | None:
    """Return the index of search_value in the sorted a_list, or None if it is absent."""

    top = len(a_list) - 1
    bot = 0

    while top >= bot:

        mid = (top + bot)//2

        if show_steps:
            print(f"  bot={bot} top={top} mid={mid} a_list[mid]={a_list[mid]}")

        if a_list[mid] == search_value:
            return mid
        elif a_list[mid] < search_value:
            bot = mid + 1
        elif a_list[mid] > search_value:
            top = mid - 1

    return None


if __name__ == "__main__":
    a_list = [1, 3, 5, 7, 9, 11, 13, 15]
    print("list      :", a_list, "-> length", len(a_list))
    print()

    for search_value in (7, 1, 15, 8):
        print("search for", search_value, ":")
        index = BinarySearch(a_list, search_value, show_steps=True)

        if index == None:
            print("  not found -> None")
        else:
            print("  found at index", index)

        print()
