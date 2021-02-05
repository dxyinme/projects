# **NAME**

introduction
---
string_utils

[example](example.cpp)

if you want split string "1,2,3,4,5,5,6,3,23,3,1324," by "," you **must** use like this :

```cpp
std::string tmp = "1,2,3,4,5,5,6,3,23,3,1324,";
std::string split_c = ",";
std::vector<std::string> split_vec;
util::string_utils::split(tmp, split_c, split_vec);
```

dependencies
---
