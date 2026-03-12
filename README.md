# net++

net++ is a class-based C++ encapsulation over POSIX sockets providing a simple, readable interface, asynchronous support, and RAII management for persistent objects like connections.

The project is still under construction. As of right now there is a mechanism to resolve addresses that a client wants to connect to:

```cpp
conn_resolver::Resolver res{ "www.google.com", "8080" };
```

You can view the full documentation [here.](http://jpagcal.github.io/net-plus-plus)
