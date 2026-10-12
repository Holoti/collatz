# Collatz

This project is aimed to ponder the Collatz Conjecture, visualizing the graph, building various plots and finding interesting patterns.

This is in very early development and I am making this as a leisure and a practice of programming skills.

## Dependencies

The project uses the following libraries:
- SFML
- Dear ImGui
- ImGui-SFML

The libraries are injected via CMakeLists.txt so no installation required (I believe).

## Code coverage

Coverage reports use GCC, a matching gcov, and gcovr. Enable coverage once
in WSL from the project directory:

```bash
cmake -B build -DWITH_COVERAGE=ON
```

Then generate a report whenever needed:

```bash
cmake --build build --target coverage --parallel
```

The target builds the application and tests, resets previous execution counts,
runs all CTest tests, and writes `build/coverage.html`, `build/coverage.txt`,
and `build/coverage.json`. It stops if tests fail. Open `coverage.html` in a
browser and keep the accompanying HTML files together for source-detail links.
Only source files under `lib/` and `bin/` are included in the report.