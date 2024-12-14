# Cmod Library

The Cmod library provides various utilities, including matrix operations, string manipulation, HTTP requests (with `libcurl`), and a custom printf function. This README will guide you through the process of installing and using the Cmod library.

## Table of Contents

1. [Installation](#installation)
2. [Usage](#usage)
3. [API](#api)
4. [Contributing](#contributing)
5. [License](#license)

## Installation

### Prerequisites

Before installing Cmod, ensure you have the following:

- A C compiler (e.g., `gcc`).
- The `make` build tool.
- `libcurl` development libraries (if you're using the HTTP API).

On Ubuntu, you can install the dependencies using:

```bash
sudo apt update
sudo apt install build-essential libcurl4-openssl-dev
```

### Building and Installing Cmod

1. Clone the repository or download the source files:

    ```bash
    git clone <repository_url>
    cd cmod
    ```

2. Build the library and executable:

    ```bash
    make
    ```

3. To install the library and its headers system-wide, run:

    ```bash
    sudo make install
    ```

This will copy the library and headers to appropriate system directories (e.g., `/usr/local/lib` and `/usr/local/include`) for easy use in your projects.

### Uninstalling Cmod

If you want to uninstall the library, you can run:

```bash
sudo make uninstall
```

## Usage

Once the Cmod library is installed, you can use it in your projects by including the header file and linking against the library.

### Example Code:

Here is an example of how to use the matrix API from Cmod:

```c
#include <stdio.h>
#include "cmod.h"

int main() {
    Matrix *m1 = matrix_create(3, 3);
    Matrix *m2 = matrix_create(3, 3);
    
    // Fill m1 and m2 with some data, perform operations...

    Matrix *result = matrix_add(m1, m2);
    
    // Work with the result...

    matrix_destroy(m1);
    matrix_destroy(m2);
    matrix_destroy(result);
    
    return 0;
}
```

To compile your program, link against the `libcmod` library:

```bash
gcc -o my_program my_program.c -lcmod
```

### Available Commands

- `make`: Build the library and executable.
- `make install`: Install the library and header files system-wide.
- `make uninstall`: Uninstall the library from system directories.
- `make clean`: Clean up build artifacts (object files, executables, etc.).

## API

### Matrix API

The matrix API provides functions for creating, manipulating, and destroying matrices.

- **matrix_create(size_t rows, size_t cols)**: Creates a new matrix with the specified number of rows and columns.
- **matrix_destroy(Matrix *m)**: Destroys a matrix, freeing its allocated memory.
- **matrix_add(const Matrix *a, const Matrix *b)**: Adds two matrices.
- **matrix_sub(const Matrix *a, const Matrix *b)**: Subtracts two matrices.
- **matrix_mul(const Matrix *a, const Matrix *b)**: Multiplies two matrices.
- **matrix_div(const Matrix *a, const Matrix *b)**: Divides two matrices element-wise.

### String API

The string API provides functions for creating and manipulating strings.

- **string_create(const char *initial_data)**: Creates a new string initialized with the given data.
- **string_destroy(String *s)**: Destroys a string, freeing its allocated memory.
- **string_replace(String *s, const char *find, const char *replace)**: Replaces occurrences of `find` with `replace` in the string.

### HTTP API

The HTTP API provides functions for making HTTP requests using `libcurl`.

- **http_request(RequestType type, String *url, String *headers, String *body)**: Performs an HTTP request (GET, POST, PUT, DELETE) with the specified URL, headers, and body.

### Custom printf

- **pprintf(const char *format, ...)**: A custom printf function that supports printing `String` objects.

## Contributing

Contributions are welcome! If you'd like to contribute to the Cmod library, please fork the repository, make your changes, and submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.


### Key Points in the `README.md`:

1. **Installation Instructions**:
   - Includes the required dependencies (`libcurl` development libraries).
   - Steps to clone the repository and build the project.
   - Instructions for installing the library system-wide using `sudo make install`.

2. **Usage**:
   - Shows an example program using the Cmod library (matrix operations).
   - Explains how to compile a program that uses the library.

3. **API Overview**:
   - Provides descriptions for the matrix, string, HTTP, and custom `printf` APIs, with a summary of available functions.

4. **Contributing**:
   - Mentions how to contribute via forking the repository and submitting pull requests.

5. **License**:
   - Specifies that the project is licensed under the MIT License (you can change this as per your project's license).

This should provide a clear and complete guide for users to install, use, and contribute to the Cmod library. Let me know if you'd like further modifications!
