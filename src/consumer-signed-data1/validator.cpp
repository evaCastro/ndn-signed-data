/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "validator.hpp"

#include <ndn-cxx/data.hpp>
#include <ndn-cxx/security/validator-config.hpp>


namespace ndn {
namespace examples {

std::string Validator::VALIDATOR_CONF_FILE = "./src/consumer-signed-data1/validator.conf";

Validator::Validator(Face& face, const std::string &confFile /* = VALIDATOR_CONF_FILE */)
  : ValidatorConfig(face)
{
  try {
    this->load(confFile);
  }
  catch (const std::exception& ) {
    std::cout << "Loading embeded config" << std::endl;
    std::string config =
      "rule                                                                       \n"
      "{                                                                          \n"
      "  id \"Example Validator\"                                                 \n"
      "  for data                                                                 \n"
      "  filter                                                                   \n"
      "  {                                                                        \n"
      "    type name                                                              \n"
      "    name /example                                                          \n"
      "    relation is-prefix-of                                                  \n"
      "  }                                                                        \n"
      "  checker                                                                  \n"
      "  {                                                                        \n"
      "    type fixed-signer                                                      \n"
      "    sig-type rsa-sha256                                                    \n"
      "    signer                                                                 \n"
      "    {                                                                      \n"
      "      type file                                                            \n"
      "      file-name ./src/consumer-signed-data1/alice.cert                     \n"
      "    }                                                                      \n"
      "  }                                                                        \n"
      "}                                                                          \n"
      ;
    this->load(config, "embededConf");
  }
}


void
Validator::validate(const Data& data,
                    const OnDataValidated& onValidated,
                    const OnDataValidationFailed& onValidationFailed)
{
  ValidatorConfig::validate(data,
                            [this, onValidated] (const shared_ptr<const Data>& data) {
                              this->onDataValidated(data);
                              onValidated(data);
                            },
                            [this, onValidationFailed] (const shared_ptr<const Data>& data,
                                                        const std::string& str) {
                              this->onDataValidationFailed(data, str);
                              onValidationFailed(data, str);
                            }
                            );
}

void
Validator::onDataValidated(const shared_ptr<const Data>& data)
{
  std::cout << "Validated. KeyLocator: " <<
                data->getSignature().getKeyLocator().getName() << std::endl;

}

void
Validator::onDataValidationFailed(const shared_ptr<const Data>& data, const std::string& str)
{
  std::cerr << "Validated FAILED " << data->getName() << ". due to: " << str <<
                ". KeyLocator: " << data->getSignature().getKeyLocator().getName() << 
               std::endl;
}

} // namespace examples
} // namespace ndn
