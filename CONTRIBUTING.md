# CONTRIBUTION

## Coding Conventions

#### Indentation is 2 spaces:

```
void foo(int x) {
  // code
}
```

#### Function definitions should not be separated from their arguments:

```
void foo(int a)  // preferable
void foo (int a) // not preferable
```

#### Separate arguments by a single space:

```
void foo(int a, float b) // preferable
void foo(int a,float b)  // not preferable
```

#### Space between operators:

```
if (a == b) // preferable
if (a==b)   // not preferable
```

#### Braces should be on the same line:

```
// preferable
if (a == b) {
// code
}

// not preferable
if (a == b)
{
  // code
}

```

#### Braces should not be used only if one command follows the if statement:

```
// preferable
if (a == b) c = a + b;

// not preferable
if (a == b) {
  c = a + b;
}
```

## Pull Requests

- Should not introduce merge conflicts
- Should follow the Coding Convention mentioned above
- Should pass all existing tests
- Should provide self explanatory code or sufficient comments
- Should provide tests for every new feature
