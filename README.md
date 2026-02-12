# INF404 Project: Language Processor (Calculator & Interpreter)

This project, developed as part of the INF404 curriculum, consists of two main C programs: a **Calculator** for arithmetic evaluation and an **Interpreter** for a custom procedural language. The system processes source code through a full pipeline: lexical analysis, recursive descent parsing, and Abstract Syntax Tree (AST) execution.

## Project Structure & Components

The implementation is highly modular, with each component handling a specific stage of the language processing:

### 1. Core Logic & Entry Points
* **calculette.c**: The entry point for the arithmetic calculator. It reads an expression, builds an AST, and prints the result of the calculation.
* **interpreteur.c**: The entry point for the language interpreter. It executes programs containing assignments, I/O, and control loops.

### 2. Lexical Analysis (`analyse_lexicale.c / .h`)
* Implements a **Finite State Automaton** to recognize tokens (lexemes) such as identifiers, integers, decimals, and keywords.
* Handles keywords like `lire`, `ecrire`, `si`, `alors`, `sinon`, `fsi`, `tantque`, `faire`, and `fait`.
* Tracks line and column numbers for precise error reporting.

### 3. Syntactic Analysis (`analyse_syntaxique.c / .h`)
* Uses **Recursive Descent Parsing** to validate the grammar of the input.
* Functions like `Rec_eag()`, `Rec_terme()`, and `Rec_facteur()` handle expression hierarchy.
* Constructs the AST by calling construction functions during the parsing process.

### 4. AST Management (`ast_construction.c` & `ast_parcours.c`)
* **Construction**: Defines functions to create nodes for operations (`creer_operation`), assignments (`creer_aff`), and control structures (`creer_si`, `creer_tantque`).
* **Traversal**: Contains the logic to evaluate arithmetic trees (`evaluer`) and execute the program instructions (`interpreter`).

### 5. Symbol Table (`table_symbole.c / .h`)
* Manages the storage and retrieval of variables (identifiers) during interpretation.
* Ensures that variables are declared before use and maintains their values across instructions.

## Supported Features

* **Floating-Point Arithmetic**: The calculator supports decimals, though the interpreter currently treats variables as integers.
* **I/O Operations**: Use `lire(x)` to take user input and `ecrire(expression)` to output results to the terminal.
* **Boolean Logic**: Supports comparison operators (`==`, `!=`, `<`, `>`, `<=`, `>=`) and logical operators (`et`, `ou`, `non`).
* **Control Flow**: Fully supports conditional `si-alors-sinon-fsi` blocks and iterative `tantque-faire-fait` loops.

## How to Run

1.  **Compile**: Run `make` to build both executables.
2.  **Calculator**: `./calculette entree.txt`
3.  **Interpreter**: `./interpreteur source.txt`

## Author
* **Arhan UNAY**
