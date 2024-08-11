#include "protocol.h"

namespace Net
{
    Protocol::Head::Head(ActionType actoin, uint32_t addData)
    :
    Action(actoin),
    AdditionalData(addData)
    {}
    Protocol::Head::Head(ActionType actoin)
    :
    Action(actoin)
    {}
    Protocol::Head::Head() = default;

    Protocol::Middle::Middle() = default;

    Protocol::End::End(ActionStatus action)
    :
    Status(action)
    {}
    Protocol::End::End() = default;

} // namespace Net
