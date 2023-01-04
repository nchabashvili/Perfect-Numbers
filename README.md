# Find Perfect Numbers (Using Multi-Threading)

 C program called perfect that finds perfect numbers in a range for numbers. The default
number range is [1, 10000]. The program accepts the -s option to set the lower bound and the
-e option to set the higher bound. Hence, the invocation perfect -s 100 -e 1000 will search for
perfect numbers in the range [100, 1000].


## how to compile



```bash
gcc perfect.c -o perfect
./perfect 
```

## Usage
Give range (-s lower bound)(-e upper bound)
```terminal
./perfect -s 100 -e 10000
```
Use threads (-t number of threads)(-v output the process)
```terminal
./perfect -t 2 -v
```
