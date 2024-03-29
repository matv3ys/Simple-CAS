# Simple Computer Algebra System
### Description:
This program allows you to perform arithmetic operations on polynomials and also check two polynomials for equality. Each polynomial is stored as sum of products.
The sum of products is implemented as linked list of linked lists. For convenience, the degree of each monomial is stored within each element, and a relation operation between monomials is defined.
Additionally, the program correctly handles input that is not shortest sum of products. In such cases similar terms are automatically simplified.

## Installation
```cmd
git clone https://github.com/matv3ys/Simple-CAS
cd Simple-CAS && make
```

## Usage
The program supports the following operations:
- addition (+)
- subtraction (-)
- multiplication (*)
- Equality test (=)

Each input polynomial must be represented as a sum of products. Variable names are single letter and case sensitive.

Running:
```cmd
./psf
```

### Example 1:
**Input:**
```cmd
+
x + 2 * x * y - 3
y + x*x
```
**Output:**
```cmd
x*x + 2*x*y + x + y - 3
```
### Example 2:
**Input:**
```cmd
-
-x*y*z + 2*x*y - z
-x*y*z - 2*z + 5
```
**Output:**
```cmd
2*x*y + z - 5
```
### Example 3:
**Input:**
```cmd
*
a - b
a * a + a * b + b * b
```
*Output:*
```cmd
a*a*a - b*b*b
```
### Example 4:
**Input:**
```cmd
=
-1*x*x*y + 5*y * y + 1 * z * z  - 3 * x - 1*y
-y + 5*y*y + z * z -3 * x - x*x*y
```
**Output:**
```cmd
equal
```
### Example 5:
**Input:**
```cmd
=
-x*y*y + 5 * x + y
-x*y*y + 4 * x + y
```
**Output:**
```cmd
not equal
```
## Additional info:
The programs were tested using manually written tests and tests with large input data generated using the SymPy library by **gen.py**.
The **./tests** directory contains testing data, **./testing.sh** and **./profiling.sh** scripts. You can find a detailed **description.txt** in the same directory.