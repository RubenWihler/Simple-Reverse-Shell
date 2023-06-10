# Simple-Reverse-Shell

Un simple reverse shell en c.

Il existe deux versions de ce reverse shell, une [version](/src/reverse_shell_args.cpp) qui prend l'adresse ip du serveur et le port en arguments et une [autre](/src/reverse_shell.cpp) qui les contient en constantes dans le code, donc si vous voulez utiliser la deuxième version, vous devez changer les constantes dans le code et recompiler le programme.

pour compiler le programme en utilisant gcc, vous devez utiliser la commande suivante:

`g++ -o reverse_shell.exe reverse_shell.cpp -lws2_32`