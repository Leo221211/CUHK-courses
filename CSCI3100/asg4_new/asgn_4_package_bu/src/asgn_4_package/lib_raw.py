# orig
# def longest_common_substr(s1: str, s2: str) -> int:
#     """
#     Computes the length of the longest common substring between two strings s1 and s2

#     Example:
#         Given s1 = "abcdefg" and s2 = "abcfgh", the longest common substring is "abc"
#         and the function will return 3
#     """
#     m = len(s1)
#     # n = len(s1)
#     n = len(s2)

#     prev = []
#     for i in range(0, n + 2):
#         prev.append(0)

#     res = 0
#     for i in range(1, m + 1):

#         # A temp array to store the curent row's results
#         cur = []
#         for j in range(0, n + 2):
#             cur.append(0)
#         for j in range(1, n + 1):
#             if s1[i - 1] == s2[j - 1]:
#                 cur[j] = prev[j - 1] + 1
#                 res = max(res, cur[j])
#             else:
#                 cur[j] = 0
#         prev = cur

#     return res

# New
def longest_common_substr(s1: str, s2: str) -> int:
    """
    Computes the length of the longest common substring between two strings s1 and s2.

    Example:
        Given s1 = "abcdefg" and s2 = "abcfgh", the longest common substring is "abc"
        and the function will return 3
    """
    m, n = len(s1), len(s2)

    if m == 0 or n == 0:
        return 0

    # generate at once
    prev = [0] * (n + 1)
    res = 0

    for ch1 in s1:
        cur = [0] * (n + 1)
        # Compare against each character in s2
        for j, ch2 in enumerate(s2, start=1):
            if ch1 == ch2:
                val = prev[j - 1] + 1
                cur[j] = val

                if val > res:
                    res = val

        prev = cur

    return res




def longest_common_prefix(s1: str, s2: str) -> int:
    """
    Computes the length of the longest common prefix between two strings s1 and s2.
    """
    min_length = min(len(s1), len(s2))
    for i in range(min_length):
        if s1[i] != s2[i]:
            return i
    return min_length


def longest_common_suffix(s1: str, s2: str) -> int:
    """
    Computes the length of the longest common suffix between two strings s1 and s2.
    """
    min_length = min(len(s1), len(s2))
    for i in range(1, min_length + 1):
        if s1[-i] != s2[-i]:
            return i - 1
    return min_length


class StringAnalysis:
    """
    A class to analyze relationships between two strings, including their
    longest common substring, prefix, and suffix.
    """

    def __init__(self, s1: str, s2: str):
        self.s1 = s1
        self.s2 = s2

    def analyze(self):
        lcs_length = longest_common_substr(self.s1, self.s2)
        lcpre_length = longest_common_prefix(self.s1, self.s2)
        lcsuf_length = longest_common_suffix(self.s1, self.s2)

        return {
            "String 1": self.s1,
            "String 2": self.s2,
            "Longest Common Substring Length": lcs_length,
            "Longest Common Prefix Length": lcpre_length,
            "Longest Common Suffix Length": lcsuf_length,
        }
