## Variable
Variables are used to store data in a program. Variables can store different types of data such as integers, floats, strings, etc.

### Declaration
Variables are declared using the `var` keyword. 
```
var x = 5
var foo = true
var bar = "hello, world"
var baz = 3.14
var quz = 'a'
```
The type of the variable is inferred from the value assigned to it. However, you can also specify the type directly.
```
var x: i32 = 5
var foo: bool = true
var bar: str = "hello, world"
var baz: f32 = 3.14
var quz: char = 'a'
```

### Mutability
Variables are immutable by default. To make a variable mutable, use the `mut` keyword.
```
var x: i32 = 5
x = 10
```
The above code will throw an error because `x` is immutable.
```
mut var x: i32 = 5
x = 10
```
The above code will work because `x` is mutable.

### Access Modifiers
