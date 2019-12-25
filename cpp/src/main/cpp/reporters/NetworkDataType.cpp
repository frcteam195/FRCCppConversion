#include "reporters/NetworkDataType.hpp"

namespace ck {
    namespace log {
        template <typename T>
        NetworkDataType<T>::NetworkDataType(Reporter* reporter) {
            NetworkDataType<T>(reporter, "");
        }

        template <typename T>
        NetworkDataType<T>::NetworkDataType(Reporter* reporter, std::string name)
        :NetworkDataTypeBase(reporter, name) {

        }

        template <typename T>
        void NetworkDataType<T>::setName(std::string name) {
            dataName = name;
        }
    }
}