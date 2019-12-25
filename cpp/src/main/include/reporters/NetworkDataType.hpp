#pragma once

#include <string>
#include "NetworkDataTypeBase.hpp"

#define NetworkDouble NetworkDataType<double>
#define NetworkFloat NetworkDataType<float>
#define NetworkLong NetworkDataType<long>
#define NetworkInteger NetworkDataType<int>

#define DECLARE_REPORTED_2(ident,reporter) ident(reporter, #ident)
#define DECLARE_REPORTED(ident) DECLARE_REPORTED_2(ident,logReporter)

namespace ck {
    namespace log {
        template <typename T>
        class NetworkDataType : public NetworkDataTypeBase {
        public:
            T rawValue;
            
            NetworkDataType(DataReporter* reporter, std::string name)
            :NetworkDataTypeBase(reporter, name) {};

            NetworkDataType(DataReporter* reporter) {
                NetworkDataType(reporter, "");
            };
            
            std::string getReportingValue() override {
                if (std::is_same<T, double>::value) {
                    return dataName + ":" + std::to_string(rawValue) + ";";   //TODO: Check performance and possibly implement faster conversion
                } else {
                    return dataName + ":" + std::to_string(rawValue) + ";";
                }
            }

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