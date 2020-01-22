/*!
 * @author yaishenka
 * @date 2020-01-22
 */
#pragma once
#include <set>
#include "Grammar.hpp"

namespace parsers {

/*!
 * \brief Abstract interface for parser
 */
class AbstractParser {
 public:
  ~AbstractParser() = default;

  /*!
   * Check if @word in @grammar
   * @param grammar should contain as first rule U->S where U is unique non terminal
   * @param word
   * @return true if grammar contains word
   */
  virtual bool IsBelongToGrammar(const Grammar& grammar,
                                 const std::string& word) = 0;
};

class EarlyAlgorithm : public AbstractParser {
 public:
  EarlyAlgorithm() = default;

  /*!
   * Check if @word in @grammar
   * @param grammar should contain as first rule U->S where U is unique non terminal
   * @param word
   * @return true if grammar contains word
   */
  bool IsBelongToGrammar(const Grammar& grammar,
                         const std::string& word) override;

 private:
  struct Situation;

  void BuildSets(const Grammar& grammar, const std::string& word);

  void Predict(size_t situation_set_number, const Grammar& grammar);

  void Scan(size_t situation_set_number, char symbol);

  void Complete(size_t situation_set_number);

  std::vector<std::set<Situation>> situations_sets_;
};

/*!
 * Contain situation for Early algorithm
 */
struct EarlyAlgorithm::Situation {
 public:
  Situation(Rule rule, size_t point_position, size_t begin_position)
      : rule(std::move(rule)),
        point_position(point_position),
        begin_position(begin_position) {}

  bool IsCompleted() const {
    return point_position == rule.GetFinishState().size();
  }

  char GetCurrentSymbol() const {
    return rule.GetFinishState()[point_position];
  }

  bool operator<(const Situation& other) const {
    if (rule == other.rule) {
      if (point_position == other.point_position) {
        return begin_position < other.begin_position;
      }

      return point_position < other.point_position;
    }

    return rule < other.rule;
  }

  Rule rule;
  size_t point_position;
  size_t begin_position;
};

}  // namespace parsers
