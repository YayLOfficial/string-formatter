# String Formatter

|  | Char | What it does | Allowed arguments | Example | Output |
| - | - | - | - | - | - |
| | { | Defines the beginning of a format block |
| | } | Defines the end of a format block |
| |
| Type | b | Placeholder for "true" or "false"<br>depending on the value of the<br>argument | | "1==1 is {b}", 1==1 | 1==1 is true
| Type | c | Placeholder for a characther | char | "H{c}y", 'e' | Hey |
| Type | i | Signed integer | int | "Balance: {i}", 123 | Balance: 123 |
| Type | u | Unsigned integer | unsigned int |
| Type | x | Placeholder for 'u' in hexadecimal | unsigned int | "{u} = {x}", 123, 123 | 123 = 0x7b |
| Type | d | **NOT IMPLEMENTED YET** |
| Type | p | Placeholder for a pointer address | void * |
| Type | s | places a string | char * | "Hello, {s}", "World!" | Hello, World! |
| |
| Option | l (Lower L) | Upgrades numerical type to long | (long int)num<br>(unsigned long int) num |
| Option | L | Upgrades numerical type to long long | (long long int)<br>(unsigned long long int) |
| Option | Any number | Performs the same formatting<br>n times taking a new argument every time. | (type) var, ...n | "{2s}", "Hello, ", "World" | Hello, World! 
| Option | r | **NOT IMPLEMENTED YET** |
| Option | q | **NOT IMPLEMENTED YET** |
| Option | * | **NOT IMPLEMENTED YET** |
