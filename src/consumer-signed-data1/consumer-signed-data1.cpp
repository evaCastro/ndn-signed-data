/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include <ndn-cxx/face.hpp>
#include "validator.hpp"

namespace ndn {
namespace examples {

class Consumer : noncopyable
{
public:

  Consumer(): m_validator(m_face)
  {
  }

  void
  run()
  { 
    // Request interest
    Interest interest(Name("/example/test/randomData"));
    interest.setInterestLifetime(time::milliseconds(1000));
    interest.setMustBeFresh(true);

    m_face.expressInterest(interest,
                           bind(&Consumer::onData, this,  _1, _2),
                           bind(&Consumer::onTimeout, this, _1));

    std::cout << "I >> : " << interest << std::endl;

    // processEvents will block until the requested data received or timeout occurs
    m_face.processEvents();
  }

private:
  void
  onData(const Interest& interest, const Data& data)
  {
    std::cout << "D << : " << data << std::endl;

    // Validating data
    m_validator.validate(data,
                         bind(&Consumer::onValidated, this, _1),
                         bind(&Consumer::onValidationFailed, this, _1, _2));

  }

  void
  onTimeout(const Interest& interest)
  {
    std::cout << "Timeout " << interest << std::endl;
  }

  void 
  onValidated(const shared_ptr<const Data>& data)
  {
    std::cout << "Validated data: " << data->getName() << std::endl;
  }

  void 
  onValidationFailed(const shared_ptr<const Data>& data, const std::string& failureInfo)
  {
    std::cerr << "Not validated data: " << data->getName() <<
                 ". The failure info: " << failureInfo << std::endl;
  }

private:
  Face m_face;
  examples::Validator m_validator; 
};

} // namespace examples
} // namespace ndn

int
main(int argc, char** argv)
{
  ndn::examples::Consumer consumer;
  try {
    consumer.run();
  }
  catch (const std::exception& e) {
    std::cerr << "ERROR: " << e.what() << std::endl;
  }
  return 0;
}
