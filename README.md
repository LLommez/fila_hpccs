---

# Fila Program

The `fila` program enables the execution of multiple `.pqr` files with a specific application (`hpccs`), configuring the environment to use different gases (helium and/or nitrogen) before each execution. Users can choose to process all `.pqr` files in the current folder or select specific ones, and also define the gas for each execution (helium, nitrogen, or both).

## Features

- Automatically detects `.pqr` files in the current folder.
- Allows the user to choose between processing all `.pqr` files or only selected ones.
- Provides three execution options:
  - **1**: Runs calculations with helium.
  - **2**: Runs calculations with nitrogen.
  - **3**: Runs calculations for both gases (first helium, then nitrogen).
- Automatically renames the output file to avoid overwriting, using the input file name and the gas type as a suffix.

## Requirements

For the program to work correctly, the following are required:
- The `hpccs` executable, which processes the `.pqr` files.
- The auxiliary program `ccg`, which configures the gas:
  - `./ccg 1` for helium.
  - `./ccg 2` for nitrogen.

## Usage

1. Compile the program with a C++ compiler (if necessary):
   ```bash
   g++ -o fila fila.cpp
   ```

2. Run the program:
   ```bash
   ./fila
   ```

3. Follow the terminal instructions:
   - The program will list available `.pqr` files in the current folder.
   - Choose whether to execute all files or only specific ones.
   - Choose the gas for execution:
     - `1` for helium.
     - `2` for nitrogen.
     - `3` for both gases (the program will process each file with helium first, then with nitrogen).
   
4. After execution, the output files will be renamed in the following format:
   - `<filename>_He.out` for calculations with helium.
   - `<filename>_N2.out` for calculations with nitrogen.

## Example

When you start the program, you’ll see something like this:

```
.pqr files in the current folder:
example1.pqr
example2.pqr

Would you like to execute all available .pqr files? (y/n): y
Choose the gas for execution:
1 - Helium
2 - Nitrogen
3 - Both
Option: 3
```

In this example, the program will run `hpccs` on `example1.pqr` and `example2.pqr`, first with helium (renaming to `example1_He.out` and `example2_He.out`), then with nitrogen (renaming to `example1_N2.out` and `example2_N2.out`).

## Considerations

- Make sure that `ccg` and `hpccs` are in the same directory as the program or available in the system PATH.
- `.pqr` files must be in the same folder as the program to be automatically detected.
- Each execution renames `output.out` to prevent overwriting results.

## Author

This program was developed by Lucca Lommez to streamline the execution and management of multiple `.pqr` files with different gas configurations.
