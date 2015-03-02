/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include <ndn-cxx/data.hpp>
#include <ndn-cxx/security/validator-config.hpp>


namespace ndn {
namespace examples {

/**
 * @brief validator, which validates Data with fixed-signer way. 
 * ./examples/consumer-signed-data1/alice.cert file contents the certification
 * which validates the data.
 */
class Validator : public ValidatorConfig
{

public:
  static std::string VALIDATOR_CONF_FILE;

  /**
   * @brief the callback function which is called after validation finishes
   * @param[in] callback The function is called after validation finishes, no matter validation
   * succeeds or fails
   */
  explicit
  Validator(Face& face, const std::string& confFile = VALIDATOR_CONF_FILE);

  /**
   * @brief validate the Data
   */
  virtual void
  validate(const Data& data,
           const OnDataValidated& onValidated,
           const OnDataValidationFailed& onValidationFailed);

private:
  /**
   * @brief the default callback function on data validated
   */
  void
  onDataValidated(const shared_ptr<const Data>& data);

  /**
   * @brief the default callback function on data validation failed
   */
  void
  onDataValidationFailed(const shared_ptr<const Data>& data, const std::string& str);

};


} // namespace examples
} // namespace ndn

