# Day 1 - How the Internet Works

## Objective

Learnt where a server fits into the Internet

## Information Gathered

The Internet - The Internet is a global network of interconnected networks that communicate using standardized protocols. These protocols define how devices exchange data, ensuring that computers built by different manufacturers and running different operating systems can communicate reliably.

Protocols - A protocol is a set of agreed-upon rules that governs communication between computers. Different protocols solve different problems. For example, HTTP defines how web applications exchange requests and responses, while TCP ensures that data is delivered reliably and in the correct order.

Role of an OS - Applications do not communicate directly with each other over the network. Instead, they interact with the operating system's networking stack. The kernel is responsible for receiving packets from the network interface, processing them, managing connections, buffering data, and finally delivering the appropriate data to the correct application.

Sockets - A socket is the interface provided by the operating system that allows an application to send and receive data over a network. It acts as the communication endpoint between a user-space program and the kernel's networking subsystem. My inference server will use sockets to listen for incoming client connections and exchange HTTP messages.

## Key Terms

- Protocol
- HTTP
- TCP
- IP
- Kernel
- Socket

## Imp Questions ( for me personally )

- How does DNS work?
- What exactly is a socket?
- How does the kernel know which process should receive data?