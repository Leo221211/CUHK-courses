import pytest
from asgn_4_package.lib_raw import  longest_common_substr

@pytest.mark.parametrize(
    "s1, s2, expected",
    [
        ("abcdef", "zcdemf", "cde"),  # Common substring is "cde"
        ("hello", "yellow", "ello"),  # Common substring is "ello"
        ("abc", "def", ""),  # No common substring
        ("abc", "b", "b"),  # The first is longer than the second
        ("b", "abc", "b"),  # The second is longer than the first
        ("", "abc", ""),  # One string is empty
        ("abc", "", ""),  # Other string is empty
        ("", "", ""),  # Both strings are empty
        ("abc", "abc", "abc"),  # Both strings are identical
        ("abcde", "abxyz1", "ab"),  # Common substring is at the start
        ("xyzabc", "1defabc", "abc"),  # Common substring is at the end
        ("ABC", "abc", ""),  # Case-sensitive, no match
        ("abc", "ABC", ""),  # Case-sensitive, no match
        ("a" * 1000 + "b", "a" * 1000 + "c", "a" * 1000),  # Long common substring
    ],
)
def test_longest_common_substr(s1, s2, expected):
    assert longest_common_substr(s1, s2) == len(expected)
