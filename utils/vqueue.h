#ifndef V_QUEUE_H_
#define V_QUEUE_H_

#include "VList.h"

namespace vcommon
{
template <typename _Ty>
class vqueue : public VList<_Ty>
{
public:
    vqueue();
    ~vqueue();

private:
};
}

#endif // V_QUEUE_H_
