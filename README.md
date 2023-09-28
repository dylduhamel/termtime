# TermTime

TermTime is a CLI utility that displays an ASCII art digital clock, showing the current system time. It provides a visually appealing way to quickly check the time directly from your terminal.

## Features

- Displays the current time in an ASCII art digital format.
- Non-blocking keyboard input to interact with the utility.
- Compatible with Linux and macOS.

## Setup

### Compilation

1. Ensure you have a C++ compiler installed. On most Linux distributions, you can use `g++`.
2. Navigate to the directory containing `termtime.cpp`.
3. Compile the program:
   ```bash
   g++ termtime.cpp -o termtime
   ```

### Adding to PATH

To make TermTime accessible from anywhere in your terminal:

1. Move the compiled executable to a directory in your PATH, such as `/usr/local/bin`:
   ```bash
   sudo mv termtime /usr/local/bin/
   ```

2. Ensure the program is executable:
   ```bash
   sudo chmod +x /usr/local/bin/termtime
   ```

Now, you can run TermTime by simply typing `termtime` in your terminal.

## Usage

After setting up, simply type:

```bash
termtime
```

This will display the current time in an ASCII art digital format.