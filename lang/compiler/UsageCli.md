# Usage of XOR compiler

**Compile simple return code**
```xor
// File: return.xor
fn main() -> i8 {
    return 0;
}
```

Execute:
```bash
$ xorc return.xor -o return
$ ls
return.xor return
$ ./return
```

There should be no output, or error.

**Explanation:**
 - `xorc` is the XOR compiler executable
 - `return.xor` is the input file, all files before any flags are input sources.
 - `-o` is the output executable name/location.

**Compile to a library**
```xor
// File: return.xor
pub fn get0() -> i8 {
    return 0;
}
```

```bash
$ xorc return.xor -h xorHdrLib.hxor -l libXorReturn.a -n hello_xorReturn
$ ls
libXorReturn.a  xorHdrLib.h
```

**Explanation:**
 - `-h` is the output header file name/location. This automatically generated as a side effect of compiling the file. It contains resources that tell what public functions exist in the executable.
 - `-l` is the output library name/location. This is the actual library that can be linked. It requires a header which is from `-h` when used so that the parent project knows what functions exist.
 - `-n` is the name of the library. You can have a maximum of 1 underscore in the name, if an underscore is used, the word before it is the org/producer of the library, and the word after it is the name.

**Using above library in project**
```xor
// File: main.xor
import hello_xorReturn::get0;

fn main() -> i8 {
    return get0();
}
```

```bash
$ xorc main.xor -il libXorReturn.a -ih xorHdrLib.h -o main
$ ls
main.xor  libXorReturn.a  xorHdrLib.h main
$ ./main
```

**Explanation:**
 - `-il` is the input library name/location. This is the actual library that can be linked. It requires a header which is from `-ih` when used so that the parent project knows what functions exist.
 - `-ih` is the input header file name/location. This automatically generated as a side effect of compiling the file. It contains resources that tell what public functions exist in the executable.
 - `-o` is the output executable name/location.
