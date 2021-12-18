import sys
import time

def replace_chars(formula: str, chars_to_value: dict[str, int]) -> str:
    replaced_formula = formula

    for char in chars_to_value:
        replaced_formula = replaced_formula.replace(char, str(chars_to_value[char]))

    return replaced_formula

# Replace every char in every part with the value
def is_valid(parts: list[str], chars_to_value: dict[str, int]) -> bool:
    value = None

    for part in parts:
        try:
            part_str = replace_chars(part, chars_to_value)

            for fragment in part_str.split(" "):
                if len(fragment) > 1 and fragment[0] == "0":
                    return False

            part_value = eval(part_str)

            if value is None:
                value = part_value
            elif part_value != value:
                return False
        except:
            # Invalid operation, or 0 as first character
            return False

    return True

def solve(parts: list[str], remaining_chars: set[str], remaining_numbers: set[int], chars_to_value: dict[str, int]) -> list[dict[str, int]]:
    solutions = []
    current_char = remaining_chars.pop()

    for i in set(remaining_numbers):

        new_chars_to_value = chars_to_value.copy()
        new_chars_to_value[current_char] = i

        if not remaining_chars:
            if is_valid(parts, new_chars_to_value):
                solutions.append(new_chars_to_value)
        else:
            remaining_numbers.discard(i)
            solutions += solve(parts, remaining_chars, remaining_numbers, new_chars_to_value)
            remaining_numbers.add(i)
        

    remaining_chars.add(current_char)
    return solutions

def format_solutions(formula: str, solutions: list[dict[str, int]]) -> str:
    solutions_str = [replace_chars(formula, solution) for solution in solutions]
    return ";".join(sorted(solutions_str))

def main():
    total_start = time.time()

    cases = int(input())

    for i in range(cases):
        case_start = time.time()
        
        formula = input()
        parts = formula.split("=")

        # Save every char of the formula in a set
        remaining_chars = set(formula)
        remaining_numbers = set(range(10))
        
        for remaining_char in remaining_chars:
            if remaining_char in "0123456789":
                remaining_numbers.discard(int(remaining_char))
        
        for discarded_char in " =+-*/0123456789":
            remaining_chars.discard(discarded_char)

        solutions = solve(parts, remaining_chars, remaining_numbers, {})

        if not solutions:
            print("Case #", i + 1, ": IMPOSSIBLE", sep="")
        else:
            print("Case #", i + 1, ": ", format_solutions(formula, solutions), sep="")

        case_end = time.time()
        print("Case #", i + 1, ", Chars: ", len(remaining_chars), " time: ", round((case_end - case_start)*1000), "ms", sep="", file=sys.stderr)

    total_end = time.time()
    print("Total time: ", round((total_end - total_start)*1000), "ms", sep="", file=sys.stderr)

main()