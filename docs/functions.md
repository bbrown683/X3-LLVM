## Functions
Functions are a way to encapsulate a block of code that can be called multiple times. Functions can take parameters and return values.

### Defining a Function
To define a function, use the `fn` keyword followed by the function name, a list of parameters, and a return type. The return type is specified after the `:` character.
```
fn calculateArea(length: i32, width: i32) : i32 =
```

### Calling a Function
To call a function, use the function name followed by a list of arguments in parentheses.
```
calculateArea(10, 20)
```

### Returning a Value
The return type of a function can be inferred by the compiler. If the return type is not specified, the compiler will try to infer it based on the final expression in the function body.
```
fn calculateArea(length: i32, width: i32) : i32 =
    length * width
```
In the above example, an i32 is returned as it is two integers being multiplied.
