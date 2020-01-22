#include "ParsersLibrary/EarlyAlgorithm.cpp"

using namespace parsers;

class Solver {
 public:
  bool operator()() {
    std::vector<char> alphabet;

    ReadVector(alphabet);

    Grammar grammar;

    std::cin >> grammar;

    std::string word;

    std::cin >> word;

    EarlyAlgorithm parser;

    return parser.IsBelongToGrammar(grammar, word);
  }

 private:
  template <typename T>
  void ReadVector(std::vector<T>& vector) {
    size_t count;

    std::cin >> count;

    vector.resize(count);

    for (int i = 0; i < count; ++i) {
      std::cin >> vector[i];
    }
  }
};

int main() {
  Solver solver;

  std::cout << (solver() ? "YES" : "NO");
}