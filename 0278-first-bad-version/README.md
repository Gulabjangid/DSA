# 0278-first-bad-version

## 📋 Problem Description
You are a product manager overseeing the development of a new product. Unfortunately, a recent version of the product has introduced a bug, causing it to fail quality checks. Due to the nature of development, where each new version is built upon the previous one, all versions released *after* a bad version are also considered bad.

You are given `n` versions, numbered from `1` to `n`. Your task is to find the *first* version that is bad. You have access to an API function `bool isBadVersion(version)` which takes a version number as input and returns `true` if that version is bad, and `false` otherwise.

Your goal is to implement a function `firstBadVersion(n)` that returns the integer representing the first bad version. You should strive to minimize the number of calls made to the `isBadVersion` API.

## 🔍 Examples
```
Input: n = 5, bad = 4
Output: 4
Explanation:
isBadVersion(3) -> false (Version 3 is good)
isBadVersion(5) -> true  (Version 5 is bad)
isBadVersion(4) -> true  (Version 4 is bad)
Since version 3 is good and version 4 is bad, version 4 is the first bad version.
```

```
Input: n = 1, bad = 1
Output: 1
Explanation:
isBadVersion