# Multithreaded Circular Queue (C++)

This project implements a **thread-safe, circular buffer queue** in modern C++ using templates. It is designed to handle producer-consumer scenarios efficiently, supporting both blocking and timeout-based dequeue operations.

## Features

- ✅ Thread-safe access via `std::mutex` and `std::condition_variable`
- 🔄 Circular buffer logic to efficiently manage space
- ⏱️ Optional timeout support when popping from the queue
- ⚙️ Configurable maximum capacity
- 🧪 Unit-tested with GoogleTest
- 🧼 Clean and documented code with Doxygen support

## Class Overview

The core class is a template-based `Queue<T>` that can be used with any copyable type. It offers the following methods:

- `void Push(T element)` — Adds an element to the queue, discarding the oldest if full
- `T Pop()` — Blocks until an element is available and returns it
- `T PopWithTimeout(int milliseconds)` — Waits up to a timeout for an element, throws if none arrives
- `int Count()` — Returns the number of elements currently stored
- `int Size()` — Returns the maximum capacity

## Build Instructions

This project uses **CMake** and assumes that **GoogleTest** and **doxygen** is installed.

```bash
# Clone the repository
git clone https://github.com/DiogoFSPinheiro/Interview_Exercise
cd multithreaded-queue

# Make the script executable (only once)
chmod +x runCode.sh

# Clean previous builds, configure with CMake, and build everything
./runCode.sh remake

# Compile and run the unit tests
./runCode.sh maketest

# Delete the build directory (optional cleanup)
./runCode.sh delete

# Run Doxygen
cd docs
doxygen
```

## Working Directory
```bash
.
├── src/
│   └── Queue.tpp
│   └── Queue.hpp
├── tests/
│   └── test_queue.cpp
│   └── utils.hpp
├── docs/
│   └── Doxyfile
├── CMakeLists.txt
└── runCode.sh
└── README.md

```
