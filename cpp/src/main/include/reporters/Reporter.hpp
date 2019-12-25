#pragma once

#include <vector>

#include "NetworkDataTypeBase.hpp"

namespace ck {
    namespace log {
        class NetworkDataTypeBase;

        class Reporter {
        public:
            std::vector<NetworkDataTypeBase*> reportingSet;

            virtual void registerVariable(NetworkDataTypeBase& logVar) = 0;
        };
    }
}