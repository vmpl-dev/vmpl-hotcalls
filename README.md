# vmpl-hotcalls

## Build instructions
```bash
$ mkdir m4
$ aclocal
$ autoconf
$ automake --add-missing
$ autoreconf --install
$ ./configure
$ make all -j$(nproc)
$ make install
```

## Usage
```bash
$ ./hot_calls_test
```
Then, you will see the following output:
```bash
enter main...
setup finish 
enter hotcalls_call
hello world
call finish 
```