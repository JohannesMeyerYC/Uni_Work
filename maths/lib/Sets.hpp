#include <vector>
#include <algorithm>
#include <memory>
template <typename T>
class Set{
    private:
      std::vector<T> objects;
      int size;

    public:
      Set(const std::vector<T> _objects, const int _size) 
        : objects(_objects), size(_size) {}
      Set _union(Set A, Set B);
      Set _intersection(Set A, Set B);
      Set _exp(Set A);

};
