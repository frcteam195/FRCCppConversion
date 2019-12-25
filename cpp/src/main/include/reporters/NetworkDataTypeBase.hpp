#pragma once

#include <string>
#include "Reporter.hpp"

namespace ck {
    namespace log {
        class Reporter;

        class NetworkDataTypeBase {
        public:
            std::string dataName;            
            NetworkDataTypeBase(Reporter* reporter, std::string name);
        };
    }
}