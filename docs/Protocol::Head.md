# Protocol::Head

## class Protocol::Head

Protoype of class Protocol::Head look like this:

```cpp
class Protocol::Head
{
public:
    uint8_t MajorVersion;
    uint8_t MinorVersion1;
    uint8_t MinorVersion2;
    ActionType Action;
    uint32_t AdditionalData;
}
```

## ActionType's

1. NotinhToDo
2. ChekConnect
3. EndSesion
4. SendMessage

### NotinhToDo

Server will do noting, is default init value to Protocol::Head

### EndSesion

Server will send Net::Protocol::End::ActionStatus::SuccesAction,
Client should recv that.

Then server stop listening commands and close connection.

### ChekConnect

Server will send Net::Protocol::End::ActionStatus::SuccesAction,
Client shoud recv that.

### SendMessage

Server recv Head with Head::AdditionalData = message size.

Then server recving message,
client should send message.

And on end server will send Net::Protocol::End::ActionStatus::SuccesAction.
