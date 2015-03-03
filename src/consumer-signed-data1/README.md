consumer-signed-data1 example
=============================


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
  `config/validation1.conf`. In this file
  is specified that data named `/example` should be signed by an identity which 
  its rsa-sha256 certificate is saved in a file `config/trust.cert`.
  This consumer can be tested with the provider application included in the 
  `src/provider-signed-data1/` folder. 
  The rules used by
  the validation process are written in the `validation1.conf` file:

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
                file-name ./config/trust.cert
              }
            }
          }


- Build this example

    Run `./waf configure` and `./waf` from `ndn-signed-data/` folder. 

- Run this example

    Before running this example we need to create the self-signed certificate to
    validate data (`./config/trust.cert` file). 
    If we use `provider-signed-data1` with `/ndn/keys/alice` identity, the data will
    be signed by `/ndn/keys/alice` identity, so we need to create 
    its self-signed certificate and save it in `trust.cert` file. Use
    the following commands to create them from `ndn-signed-data/` folder:

         $ ndnsec-sign-req /ndn/keys/alice > ./config/trust.cert
 
    You can check the content of the self-signed certificate by using:

         $ ndnsec-dump-certificate -p -f ./config/trust.cert

    You can run this example from `ndn-signed-data/` folder:

        ./build/bin/consumer-signed-data1/consumer-signed-data1 ./config/validation1.conf

