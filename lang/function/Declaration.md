# Declaring a function
These functions should only be allowed to be declared in the scope of a [namespace](../namespace/Declaration.md), [class](../class/Declaration.md), or an open program body.

**Simple Example**
```xor
fn FUNCTION_NAME() -> RETURN_TYPE {
    // FUNCTION CONTENTS
};
```

**Simple with `void` return**
```xor
fn FUNCTION_NAME() {
    // FUNCTION CONTENTS
};
```

# Required Elements
- `fn` - The keyword that declares a function and tells the parser to start searching for a function.
- `<FUNCTION_NAME>` - The name of the function. This can be any valid identifier. Read the naming requirements for a function [here](Naming.md).
- `()` - The parenthesis that enclose the function's parameters. If the function has no parameters, then the parenthesis are still required. It helps the parser identify the token sector. To add parameters, read [this](Parameters.md).
- `->` - The arrow that separates the function's parameters from the function's return type. If the function has no return type, then the arrow is not expected. This can be any valid class, or returnable type. Read the return type requirements for a function [here](Return.md).
- `{}` - The curly braces that enclose the function's body. If the function has no body, then the curly braces are still required. It helps the parser identify the token sector. The code body can be any executable code, functions and anything the language supports for [codeblocks](../codeblocks/Declaration.md).
- `;` - The semicolon that ends the function declaration. This is required for the parser to identify the end of the function declaration. It acts as a final measure to help the user debug missing or mismatched grouping symbols.
