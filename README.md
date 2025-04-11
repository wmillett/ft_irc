# **ft_irc**

ft_irc is a basic implementation of an IRC (Internet Relay Chat) server that allows users to communicate in real-time within channels. This project simulates the functionality of a fully-operational IRC server, enabling features such as user authentication, message broadcasting, channel management, and more.

The project follows the requirements set by [42 School](https://www.42.fr/en/) and aims to demonstrate proficiency in socket programming, network communication, and handling multithreading in C.

---

## **Table of Contents**

- [Introduction](#introduction)
- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [How It Works](#how-it-works)
- [Commands and Functionality](#commands-and-functionality)
- [Contributing](#contributing)
- [License](#license)

---

## **Introduction**

ft_irc is a C-based IRC server that implements core IRC protocols and features. It provides a basic but functional chat environment where users can connect, join channels, send private and public messages, and communicate with one another. The server supports multiple channels and users, making it a scalable solution for simple chat applications.

This project involves working with **sockets**, **multithreading**, and **network protocols** to manage multiple client connections and facilitate communication in real-time.

---

## **Features**

- **Multi-client Support:** Handle multiple users connecting and interacting simultaneously.
- **Channel Support:** Create, join, and manage channels for group communication.
- **Private Messaging:** Users can send private messages to each other.
- **Nickname Authentication:** Users can register and authenticate their nickname.
- **Server Commands:** Basic IRC commands such as `JOIN`, `PART`, `PRIVMSG`, etc.
- **Channel List:** Display the list of active channels.
- **Error Handling:** Properly handle user input errors and server issues.

---

## **Requirements**

Before you can run ft_irc, make sure you have the following installed:

- **OS:** Linux (macOS and Windows via WSL are also supported)
- **Compiler:** GCC or Clang
- **Libraries:**  
  No external libraries are required. The project uses only the C standard library and system calls.

---

## **Installation**

To set up the project on your local machine, follow these steps:

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/yourusername/ft_irc.git
   cd ft_irc
