# TimSort C++ Header-Only Library

A C++ header-only sorting library implementing a TimSort-like algorithm, supporting input iterators for efficient and stable sorting.

## Features

- **Header-Only**: Easy integration without the need for separate compilation.
- **TimSort Algorithm**: Efficient and stable sorting inspired by Python's TimSort.
- **Iterator Support**: Compatible with various input and output iterators.
- **Customizable Comparison**: Allows custom comparison functions for sorting.

## Requirements

- C++11 compatible compiler
- [xmake](https://xmake.io/) build system for building the example.

## Installation

Since it's a header-only library, you can include the `timsort.hpp` header in your project.

### Using xmake

The project is managed with [xmake](https://xmake.io/). Follow these steps to build the example:

1. **Install xmake**

   If you haven't installed xmake yet, you can install it using the following commands:

   ```sh
   # For Linux/macOS
   curl -fsSL https://xmake.io/shget.text | bash

   # For Windows, download the installer from the [xmake website](https://xmake.io/#/guide/installation).
   ```

2. **Clone the Repository**

   Clone this repository and navigate to the project directory:

   ```sh
   git clone https://github.com/TabNahida/timsort.git
   cd https://github.com/TabNahida/timsort.git
   ```

3. **Build the Project**

   Use xmake to build the project:

   ```sh
   xmake
   ```

4. **Run the Example**

   After building, run the example binary:

   ```sh
   xmake run main
   ```

## Usage

Include the `timsort.hpp` header and use the `timsort` function from the `timsort` namespace to sort your data.

### Example

```cpp
#include <iostream>
#include "timsort.hpp"
#include <list>
#include <vector>

int main() {
    std::list<int> data = {5, 2, 9, 1, 5, 6};

    // Output iterator can be back_inserter to collect sorted results
    std::vector<int> sorted_data;
    timsort::timsort(data.begin(), data.end(), std::back_inserter(sorted_data));

    for (int num : sorted_data) {
        std::cout << num << ' ';
    }
    return 0;
}
```

### Explanation

This example demonstrates how to use the `timsort` function to sort a list of integers. The sorted result is stored in a `std::vector<int>` and printed to the console.

## Project Structure

```
.
├── include
│   └── timsort.hpp
├── src
│   └── main.cpp
├── xmake.lua
└── README.md
```

- **include/timsort.hpp**: The header-only TimSort implementation.
- **src/main.cpp**: Example usage of the TimSort library.
- **xmake.lua**: Build configuration using xmake.
- **README.md**: This file.

## Build Configuration (`xmake.lua`)

```lua
add_languages("cxx11")

target("timsort")
    set_kind("headeronly")
    set_encodings("utf-8")

    add_headerfiles("include/timsort.hpp")

target_end()

target("main")
    set_kind("binary")
    set_encodings("utf-8")

    add_files("src/main.cpp")
    add_includedirs("include")

    add_deps("timsort")
target_end()
```

### Explanation

- **add_languages("cxx11")**: Sets the C++ standard to C++11.
- **target("timsort")**: Defines the `timsort` target as a header-only library.
  - **set_kind("headeronly")**: Specifies that this target is header-only.
  - **set_encodings("utf-8")**: Sets the file encoding to UTF-8.
  - **add_headerfiles("include/timsort.hpp")**: Adds the `timsort.hpp` header file to the target.
- **target("main")**: Defines the `main` target as a binary executable.
  - **set_kind("binary")**: Specifies that this target is a binary executable.
  - **add_files("src/main.cpp")**: Adds the `main.cpp` source file to the target.
  - **add_includedirs("include")**: Adds the `include` directory to the include paths.
  - **add_deps("timsort")**: Specifies that `main` depends on the `timsort` target.

## License

This project is licensed under the MIT License.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any improvements or bug fixes.

## Acknowledgements

This library is inspired by Python's TimSort algorithm, providing efficient and stable sorting capabilities for C++ applications.