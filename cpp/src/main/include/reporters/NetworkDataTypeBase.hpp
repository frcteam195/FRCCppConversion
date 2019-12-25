#pragma once

#include <string>
#include "DataReporter.hpp"

namespace ck {
    namespace log {
        class DataReporter;

        class NetworkDataTypeBase {
        public:
            std::string dataName;            
            NetworkDataTypeBase(DataReporter* reporter, std::string name);
            void setName(std::string name);
            virtual std::string getReportingValue() = 0;
        };
    }
}