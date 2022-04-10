# 42_ft_containers
c++98までの機能を使って、STLコンテナ(vector, map, stack, set)自作

##
```bash
clang++ --version
Homebrew clang version 13.0.1
Target: x86_64-apple-darwin19.6.0
Thread model: posix
InstalledDir: /usr/local/opt/llvm/bin
```

## USAGE
```bash
$ git clone https://github.com/public-jun/42_ft_containers.git
```

`cpp`ファイルの中で `include` し、利用してください。
```cpp
#include "42_ft_containers/includes/vector.hpp"
#include "42_ft_containers/includes/map.hpp"
#include "42_ft_containers/includes/stack.hpp"
#include "42_ft_containers/includes/set.hpp"
```
もしくはコンパイル時に `-I` オプションで `include` してください。
```bash

```


### TESTS
make

make mytest
make gtest

make mybench
