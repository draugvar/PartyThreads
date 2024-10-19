# PartyThread

PartyThread is a C++ library that provides a simple and efficient thread pool implementation. It allows you to manage a pool of threads to execute tasks concurrently, improving the performance of your applications by utilizing multiple CPU cores.

## Features

- Thread-safe task queue
- Dynamic thread management
- Simple API for adding tasks
- Graceful shutdown of threads
- Integration with Google Test for unit testing

## Requirements

- C++20 compatible compiler

## Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/PartyThread.git
    cd PartyThread
    ```

2. Create a build directory and navigate into it:
    ```sh
    mkdir build
    cd build
    ```

3. Run CMake to configure the project:
    ```sh
    cmake ..
    ```

4. Build the project:
    ```sh
    cmake --build .
    ```

## Usage

### Including PartyThread in Your Project

To use PartyThread in your project, include the `PartyThreads.h` header file:
```cpp
#include "PartyThreads.h"
```

### Example

Here is a simple example of how to use the PartyThread library:

```cpp
#include <iostream>
#include "PartyThreads.h"

PartyThreads::Pool pt;

void init()
{
    auto lambda = [] (const int i)
    {
        std::cout << "Hello, " << i << std::endl;
    };
    pt.push(lambda, 1);
}

int main()
{
    auto future = std::async(std::launch::async, init);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    pt.stop();
    return 0;
}
```

### Running Unit Tests

To run the unit tests, you can use the provided CMake target:

```sh
cmake --build . --target RunTest
```

## Project Structure

- `include/PartyThreads.h`: Header file containing the thread pool implementation.
- `examples/PartyThreadsExample.cpp`: Example usage of the PartyThread library.
- `tests/PartyThreadsTest.cpp`: Unit tests for the PartyThread library.
- `CMakeLists.txt`: CMake configuration file.
- `.github/workflows/test.yml`: GitHub Actions workflow for continuous integration.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request on GitHub.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.

## Acknowledgements

- [Google Test](https://github.com/google/googletest) for unit testing framework.
