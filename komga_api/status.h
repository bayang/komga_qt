#ifndef STATUS_H
#define STATUS_H

#include "komga_api_global.h"

class KOMGA_API_EXPORT Status
{
public:

    enum ApiStatus {
        ENDED,
        ONGOING,
        ABANDONED,
        HIATUS
    };

};

#endif // STATUS_H
