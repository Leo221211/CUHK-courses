# Usage:
#   python src/main.py <first_string> <second_string>
#
#   Example: python src/main.py "hello" "world"
#   Output:
#     String 1: hello
#     String 2: world
#     Longest Common Substring Length: 1
#     Longest Common Prefix Length: 0
#     Longest Common Suffix Length: 0


import argparse

from asgn_4_package.lib_raw import StringAnalysis


def main():
    # Parse command line arguments
    parser = argparse.ArgumentParser(
        description="Program to analyze string relationships"
    )
    parser.add_argument("first_string", help="First string")
    parser.add_argument("second_string", help="Second string")
    args = parser.parse_args()

    # Analyse the given strings
    string_analysis = StringAnalysis(args.first_string, args.second_string)
    result = string_analysis.analyze()

    print("Analysis result: ")
    print(f"  String 1: {result['String 1']}")
    print(f"  String 2: {result['String 2']}")
    print(
        f"  Longest Common Substring Length: {result['Longest Common Substring Length']}"
    )
    print(f"  Longest Common Prefix Length: {result['Longest Common Prefix Length']}")
    print(f"  Longest Common Suffix Length: {result['Longest Common Suffix Length']}")
    print()


if __name__ == "__main__":
    main()
