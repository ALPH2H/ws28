# ws28
C++14 WebSocket server library

## Do you use this in production?

Yes.

## Should I use this in production?

Maybe.

## Is it spec compliant?

Mostly. Text messages are handled exactly as binary ones and handed directly to the application, this means no UTF-8 validation. Everything else should be spec compliant.

## How do I use this?

1. Copy the source files into your project, I don't like making libraries.

2. Create a server:

```c++
ws28::Server server{uv_default_loop(), SSL_CTX* or nullptr};
```

Note: if you have a secure server, it'll actually listen for both secure and insecure connections on that same port
by sniffing the first byte. This allows you to run insecure websocket servers on port 443 and not deal with the swarm
of broken proxies out there.

3. Set up some callbacks

    See `src/Server.h`. But basically, you need some or all of these methods from `ws28::Server`: `SetClientConnectedCallback`, `SetClientDisconnectedCallback`, `SetClientDataCallback`, `SetCheckConnectionCallback` and `SetHTTPCallback`.

4. Listen

```c++
server.Listen(port);
```

## What's the license?

Most files are MIT. The base64 and sha1 code are BSD, feel free to pull request some MIT licensed code to replace those.


## More FAQ

### Can I store pointers to `ws28::Client`?

Only between the ClientConnected and ClientDisconnected callbacks. The client will be deleted at the next event loop iteration after ClientDisconnected, or later.

### When is ClientDisconnected called?

As soon as you call Destroy on a connected client. Just make sure to clean up everything there, the client object will still be valid for at least this event loop iteration. Any writes you try to make to the client will be safely ignored.