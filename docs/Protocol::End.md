# Protocol::End

## class Protocol::End

Protoype of class Protocol::End look like this:

```cpp
class End
{
public:
    ActionStatus Status;
};
```

## ActionStatus

1. SuccesAction
2. FaildAction

### SuccesAction

Server send End with that, when command complete success

### FaildAction

Server send End with that, when command didn't complete success
