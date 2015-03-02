consumer-signed-data1 example
=============================


- This example is a consumer: it sends Interest `/example/test`. 

             +--------------------------------------------------------+
             |Name: /example/test                                     |
             +--------------------------------------------------------+
             |MustBeFresh: 1 (yes)                                    |
             +--------------------------------------------------------+
             |Nonce:                                                  |
             +--------------------------------------------------------+
             |InterestLifeTime: 1000 ms                               |
             +--------------------------------------------------------+


  When data is received it validates its signature. 

  The validation process uses the `validation.conf` file. In this file
  is specified that data named `/example` should be signed by an identity which 
  its rsa-sha256 certificate is saved in a file.
  This consumer can be tested with the provider application included in the 
  `src/provider-signed-data1/` folder. This provider signs data using 
  `/ndn/test/alice` identity, then the consumer needs the
  `/ndn/test/alice` certificate to validate signed data. This certificate must be
  saved in `./src/consumer-signed-data1/alice.cert` file. The rules used by
  the validation process are written in the `validation.conf` file:

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
              type fixed-signer
              sig-type rsa-sha256
              signer
              {
                type file
                file-name ../../src/consumer-signed-data1/alice.cert
              }
            }
          }


- Build this example

    Run `./waf configure` and `./waf` from `ndn-signed-data/` folder. 

- Run this example

    Before running this example we need to create the self-signed certificate to
    validate data. In the example `src/provider-signed-data1/` the data are
    signed by `/ndn/test/alice` identity, so we need to create 
    its self-signed certificate and save it in 
    `./src/consumer-signed-data1/alice.cert` file. Use
    the following commands to create them from `ndn-signed-data/` folder:

         $ ndnsec-sign-req /ndn/test/alice > ./src/consumer-signed-data1/alice.cert
 
    You can check the content of the self-signed certificate by using:

         $ ndnsec-dump-certificate -p -f ./src/consumer-signed-data1/alice.cert

    You can run this example from `ndn-signed-data/` folder:

        ./build/src/consumer-signed-data1/consumer-signed-data1

