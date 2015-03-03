consumer-signed-data2 example (same code as consumer-signed-data1)
==================================================================


- This example is a consumer. It sends interests requesting `/example/test`. 

             +--------------------------------------------------------+
             |Name: /example/test                                     |
             +--------------------------------------------------------+
             |MustBeFresh: 1 (yes)                                    |
             +--------------------------------------------------------+
             |Nonce:                                                  |
             +--------------------------------------------------------+
             |InterestLifeTime: 1000 ms                               |
             +--------------------------------------------------------+


  When data is received it validates its signature by using a configuration
  file which contains the validation rules. This configuration file is
  a command line program argument. 

  We provide an example of the configuration file in the `config/` folder: 
  `config/validation2.conf`. In this file
  is specified that data named `/example` should be signed by an identity which 
  is prefix of `/ndn/keys/bob`. The certificate of the identity `/ndn/keys/bob`
  should be signed by an identity which is prefix of `/ndn/keys/alice`. The 
  self-signed certificate of the `/ndn/keys/alice` is is saved in a 
  file `config/trust.cert`.

  This consumer can be tested with the provider application included in the 
  `src/provider-signed-data2/` folder. 

  The rules used by the validation process are written in the `validation2.conf` 
  file:


      rule
      {
        id "Example Validator"
        for data
        filter
        {
          type name
          name /example
          relation is-prefix-of
        }
        checker
        {
          type customized
          sig-type rsa-sha256
          key-locator
          {
            type name
            name /ndn/keys/bob
            relation is-prefix-of
          }
        }
      }

      rule
      {
        id "Example2 Validator"
        for data
        filter
        {
          type name
          name /ndn/keys/bob
          relation is-prefix-of
        }
        checker
        {
          type customized
          sig-type rsa-sha256
          key-locator
          {
            type name
            name /ndn/keys/alice
            relation is-prefix-of
          }
        }
      }

      trust-anchor
      {
        type file
        file-name "./config/trust.cert"
      }



- Build this example

    Run `./waf configure` and `./waf` from `ndn-signed-data/` folder. 

- Run this example

    Before running this example we need to create the self-signed certificate to
    validate data (`./config/trust.cert` file). If we have run the `consumer-signed-data1`
    before, we have already had this file.

    You can run this example from `ndn-signed-data/` folder:

        ./build/bin/consumer-signed-data2/consumer-signed-data2 ./config/validation2.conf

