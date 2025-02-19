## Types
Types are a way to define the shape of data in a program. They can be used to define the shape of data that is passed between functions, or to define the shape of data that is stored in memory.

### Enums
Enums are a way to define a type that can be one of several other types.
```
type Color = 
    | Red 
    | Green 
    | Blue
```

### Unions
Unions are a way to define a type that can be one of several other types. They are similar to enums, but they can hold data.
```
type Number = 
    | Integer of i32 
    | Float of f32
```

### Objects 

```
type Person = 
    name: str
    age: i32
```

### Interfaces
Interfaces are a way to define a type that can be implemented by other types. Interfaces are defined as a type with no data, and only function headers.
```
type Polygon = 
    fn area() -> f32
    fn perimeter() -> f32
```
Implementing an interface is done by defining a type that has the same function headers as the interface. 
The `of` keyword is used to specify that a type implements an interface.
```
type Square: Polygon = 
    var side: f32
    fn area() -> f32 = side * side
    fn perimeter() -> f32 = 4.0 * side
```

### Abstract Types
Abstract types are a way to define a type that can be implemented by other types, but the implementation is hidden.
```
type 
```