#pragma once

#include <string>
#include "NetworkDataTypeBase.hpp"

namespace ck {
    namespace log {
        template <typename T>
        class NetworkDataType : public NetworkDataTypeBase {
        public:
            T rawValue;
            
            NetworkDataType(Reporter* reporter);
            NetworkDataType(Reporter* reporter, std::string name);

            void setName(std::string name);

            //Return implicit type conversion
            operator T() const {
                return rawValue;
            } 

            //Assignment Operators
            T operator = (T const &obj) {
                return (rawValue = obj);
            }

            //Addition operators
            T operator += (T const &obj) {
                return (rawValue += obj);
            }

            //Subtraction Operators
            T operator -= (T const &obj) {
                return (rawValue -= obj);
            }

            //Multiplication Operators
            T operator *= (T const &obj) {
                return (rawValue *= obj);
            }

            //Division Operators
            T operator /= (T const &obj) {
                return (rawValue /= obj);
            }
        };
    }
}