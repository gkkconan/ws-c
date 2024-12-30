# Web Server in C
This project implements a simple and minimalist HTTP server in C. The server listens for incoming connections on a specified port (also given in input), accepts requests, and responds with a simple HTML page.

<br>

## ⚙️ Features
- Accepts and handles client connections
- Responds with a static HTML page
- Implements basic socket programming (using socket, bind, listen, accept, read, and write functions)

<br>

## 🚀 Installation and Usage
This project includes a Makefile to simplify the build process.

Use the make command to compile the program:
```bash
make
```

To run the server use:
```bash
make run
```

Or alternatively run the executable file directly and provide a port (default: 8080):
``` bash
./main [port]
```

## 🌟 Credits
This project was developed and is maintained by [gkkconan](https://github.com/gkkconan).

## 📜 License
This project is open-source and available under the [MIT License](https://github.com/gkkconan/ws-c/blob/main/LICENSE).