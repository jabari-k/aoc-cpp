#include <stdexcept>
#include <vector>

class SkipIterator {
public:
  SkipIterator(const std::vector<int>& vec, size_t pos, size_t skip_pos = 0) : vec{vec}, pos{pos}, skip_pos{skip_pos} {
    if (pos == skip_pos) {
      throw std::invalid_argument("SkipIterator: cannot initialize iterator position to skipped position");
    }
  }

  bool operator==(const SkipIterator& other) {
    return pos == other.pos; // && skip_pos == other.skip_pos; ...?
  }

  bool operator!=(const SkipIterator& other) {
    return !(*this == other);
  }
  
  int operator*() const {
    return vec[pos];
  }

  SkipIterator& operator++() {
    if (pos + 1 == skip_pos) {
      pos += 2;
    }
    else {
      pos += 1;
    }
    return *this;
  }
  
private:
  std::vector<int> vec;
  size_t pos;
  size_t skip_pos;
};
    
