#include "reporters/NetworkDataTypeBase.hpp"

namespace ck {
    namespace log {
        NetworkDataTypeBase::NetworkDataTypeBase(Reporter* reporter, std::string name) {
            dataName = name;
            reporter->registerVariable(*this);
        }
    }
}