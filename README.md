# safe-compare
A C++11 header-only template library for safely comparing two arithmetic values.

# Usage
The library currently consists of a single header file, [safe_compare.h](src/safe_compare.h), which can be dropped in and included in your project.

## Comparison Operators ( >, <, >=, <= )

| operator | functor | function |
| -- | ----------------------------- | -------------------------------- |
| >  | `safe_compare::greater`       | `safe_compare::is_greater`       |
| <  | `safe_compare::less`          | `safe_compare::is_less`          |
| >= | `safe_compare::greater_equal` | `safe_compare::is_greater_equal` |
| <= | `safe_compare::less_equal`    | `safe_compare::is_less_equal`    |

### Functors
```C++
safe_compare::greater safe_greater< int, unsigned int >;
bool gt = safe_greater( -1, 1U );
safe_compare::less safe_less< int, unsigned int >;
bool lt = safe_less( -1, 1U );
safe_compare::greater_equal safe_greater_equal< int, unsigned int >;
bool gte = safe_greater_equal( -1, 1U );
safe_compare::less_equal safe_less_equal< int, unsigned int >;
bool lte = safe_less_equal( -1, 1U );
```

### Functions
```C++
bool gt = safe_compare::is_greater( -1, 1U );
bool lt = safe_compare::is_less( -1, 1U );
bool gte = safe_compare::is_greater_equal( -1, 1U );
bool lte = safe_compare::is_less_equal( -1, 1U );
```
# Build
There is currently a simple test application that can be built with CMake. <br />
It provides a bare-bones use case. <br />
Unit tests may be added in the future if time permits.

## Linux
```
mkdir <build-dir>
cd <build-dir>
cmake .. -DCMAKE_INSTALL_PREFIX=<install-dir>
make
make install
```

## Windows
```
mkdir <build-dir>
cd <build-dir>
cmake .. -G "Visual Studio 15 2017 Win64" -DCMAKE_INSTALL_PREFIX=<install-dir>
open safe-compare.sln or use msbuild or use devenv.com
```
