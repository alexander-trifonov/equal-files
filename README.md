# equal-files

# Task:
To find duplicate files in 2 directories, using C++11/14, any 3rd-party library, with or without GUI.

## Method:
1. Loop recursively through directories and find files with same size
2. Loop through files with same size and find their check-sum (SHA1)
3. Display files with same check-sum

* C++11
* Boost
* Crypto++
* No GUI

## Instructions:
`EqualFilesCL.exe <directory_1> <directory_2>`  
* directory_1, directory_2 - directories paths where search will begin

Running example: 
`EqualFilesCL.exe "D:\Temp\Dir1" "D:\Games\Dir2"`  

Or run without arguments:
1. Generate file, answering 'Y' or use generated file after 'N';  
Input:
```sh
[ Files Generating ]
Generate N text files for a quick test?
Y\N: N
Write paths to directories:
1: D:\Games\Cossacks 3\data\gui\common.inc
2: D:\Games\Cossacks 3\data\gui\common.inc
```
Output:
```sh
[ Hashing ]

[ Found Dublicated Files ]
Done in: 1ms
File size: 17484 bytes
SHA1: 456E3A86D09716752612B6633F6EF33FA9B0B663
        "D:\Games\Cossacks 3\data\gui\common.inc\onmousewheel.inc"
        "D:\Games\Cossacks 3\data\gui\common.inc\onmousewheel.inc"
File size: 3865 bytes
SHA1: 5B6190BCDE1BE321173FD20900B0875D75C77F3B
        "D:\Games\Cossacks 3\data\gui\common.inc\onhint.inc"
        "D:\Games\Cossacks 3\data\gui\common.inc\onhint.inc"
File size: 2213 bytes
SHA1: E8DDE826CAF2DE1D75A9C98189FDCC53720CD69F
        "D:\Games\Cossacks 3\data\gui\common.inc\onmousehook.inc"
        "D:\Games\Cossacks 3\data\gui\common.inc\onmousehook.inc"
Done in: 1ms
```
