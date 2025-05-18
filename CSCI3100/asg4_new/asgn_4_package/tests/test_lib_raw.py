import pytest
from asgn_4_package.lib_raw import longest_common_substr

@pytest.mark.parametrize("s1, s2, expected", [
    ("", "", 0),
    ("", "ABC", 0),
    ("XYZ", "", 0),

    ("ABC", "DEF", 0),
    ("AAAA", "BBBB", 0),

    ("ABCDEFG", "ZABCFGH", 3),   
    ("12345", "45123", 3),       
    ("foobar", "barfoo", 3),    

    ("hello", "ohelloworld", 5),
    ("longerstring", "string", 6),

    ("AAAAA", "AAA", 3),

    ("ABCABC", "BCABCA", 5),
])

def test_longest_common_substr(s1, s2, expected):
    assert longest_common_substr(s1, s2) == expected
