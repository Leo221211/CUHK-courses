import pytest
from src.asgn_4_package.lib_raw import longest_common_substr

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

def test_random_strings():
    import random, string
    # sanity check: if you pick a random substring of s1 and embed in s2, it must be found
    base = ''.join(random.choices(string.ascii_uppercase, k=100))
    # pick a substring
    i, j = sorted(random.sample(range(len(base)), 2))
    sub = base[i:j]
    # build s2 as random + sub + random
    rnd = lambda n: ''.join(random.choices(string.ascii_uppercase, k=n))
    s2 = rnd(50) + sub + rnd(50)
    assert longest_common_substr(base, s2) == len(sub)
