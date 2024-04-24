# Chess AI
Basic Chess AI written in C

- Uses the Alpha-Beta Minimax algorithm to search for the best move.  
- Uses limited depth due to usage of double arrays instead of bitboards.
- Will come back to remake in C++ in the future using bitboards.

## Getting started
Clone the repository:
```
git clone git@github.com:Dirk94/ChessAI.git
```

To run the program  
```
gcc main.c engine.c board.c movegen.c && ./a.out
```

## Example Moves
Moves should have the following format:
```d2 d4``` or ```D2 D4```
