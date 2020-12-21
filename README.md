# equal-files
Search for duplicated files in 2 directories

## Task:
To find duplicated files in 2 directories

* C++11
* Boost
* Crypto++
* No GUI

## Method:
1. Loop through directories and map file's size to file's path
2. Loop though files with equal sizes and calculate check-sum (SHA1)
3. Display files with same check-sum

## Ways to improve:
1. Bottlenck is Disk Reading Speed. Find why Crypto++'s SHA1 hashing use much more DRS than required
  * Researches showed: Disk Reading Speed ~50MB/s, File size 5MB, time to hash ~= 1sec, but 0.1s expected.
2. GUI

## Instructions:
`EqualFiles.exe <directory_1> <directory_2>`
* directory_1, directory_2 - paths where search will proceed

Running example:
`EqualFiles.exe "D:\Games\Battlefield 4\Support" "D:\Games\Battlefield 4\"`

Or run without arguments:
Input:
```sh
Write paths to directories:
1: D:\Games\Battlefield 4\Support
2: D:\Games\Battlefield 4\Support
```
Output:
```sh
[[ Hashing ]]
1/3     size:3KB
2/3     size:9KB
3/3     size:38KB

[[ Found Dublicated Files ]]
Done in: 7ms
File size: 32554 bytes
SHA1: 515C6978EF413A1D36811FFC20EE032F1040BF79
        "D:\Games\Battlefield 4\Support\mnfst.txt"
        "D:\Games\Battlefield 4\Support\mnfst.txt"
File size: 315342 bytes
SHA1: 6A78BEAC81B034145BE5127A1875A08C71290D44
        "D:\Games\Battlefield 4\Support\eula\ru_RU_eula.rtf"
        "D:\Games\Battlefield 4\Support\eula\ru_RU_eula.rtf"
File size: 78340 bytes
SHA1: ADF5053C190DA74996B04324F86F2F89D794FAB4
        "D:\Games\Battlefield 4\Support\EA Help\Technical Support.ru_RU.rtf"
        "D:\Games\Battlefield 4\Support\EA Help\Technical Support.ru_RU.rtf"
Done in: 7ms
```
