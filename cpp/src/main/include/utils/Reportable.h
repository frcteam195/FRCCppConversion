#include <vector>

class Reportable {
public:
    virtual std::vector<void *> GenerateReport() = 0;
};