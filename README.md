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

コンパイル時に `-I` オプションで `include` し、`cpp`ファイルで `include` してください。
```bash
$ clang++ main.cpp -I./42_ft_containers/includes/containers -I./42_ft_containers/includes/utils
```
`main.cpp`
```
#include <vector.hpp>
#include <map.hpp>
#include <stack.hpp>
#include <set.hpp>
```


## TESTS
### Unit TEST
---
google test(c++11) で行う
```
$ make gtest
```

自作テスト(c++98)で行う
```
$ make mytest
$ ./mytest_exe
```
### Benchmark TEST
---
```bash
$ make mybench
$ ./mybench_exe
```

### Clean up
```bash
$ make clean (except Execution binary)
or
$ make fclean 
```

### 自分の関連記事
[c++98で自作コンテナ](https://public-jun.github.io/series/c++98%E3%81%A7%E8%87%AA%E4%BD%9C%E3%82%B3%E3%83%B3%E3%83%86%E3%83%8A/)
