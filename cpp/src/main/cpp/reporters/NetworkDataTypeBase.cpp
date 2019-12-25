#include "reporters/NetworkDataTypeBase.hpp"

namespace ck {
    namespace log {
        NetworkDataTypeBase::NetworkDataTypeBase(DataReporter* reporter, std::string name) {
            dataName = name;
            if (reporter) {
                reporter->registerVariable(*this);
            }
        }

        void NetworkDataTypeBase::setName(std::string name) {
            dataName = name;
        }
    }
}