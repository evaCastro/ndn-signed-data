producer-signed-data2 example
=============================


- This example is the same producer as producer-signed-data1 
  which filters `/example/test` interests. 
  It provides Data named `<InterestPrefix>/testApp` signed by 
  an identity. 
  The identity is a command line program argument, for instance 
  `/ndn/keys/bob`. In this case, data sent by this producer should
  be as following:

             +--------------------------------------------------------+
             |Name: <InterestPrefix>/testApp/<version>                |
             +--------------------------------------------------------+
             |ContentType: 0 (blob)                                   |
             +--------------------------------------------------------+
             |Freshness period: 10000 msec                            |
             +--------------------------------------------------------+
             |Content: <string>                                       |
             +--------------------------------------------------------+
             |SignatureType: 1 (rsa-256)                              |
             +--------------------------------------------------------+
             |KeyLocator: /ndn/keys/bob/KEY/ksk-<number>/ID-CERT      |
             +--------------------------------------------------------+
             |SignatureValue: <signature_256_bits>                    |
             +--------------------------------------------------------+

   It is not always feasible for a consumer to have a priori knowledge 
   about the signing key of all the received data packets.  In this case, 
   a consumer needs to retrieve the public key bits of a signing key 
   according to the key-locator information specified in a data packet. 
   For this reason, this producer filters `/ndn/keys` interests to provide
   certificates which are prefix of `/ndn/keys`, if they are in the 
   keyChain. This is very useful when using no auto-signed certificates.


- Build this example

    From `ndn-signed-data/` folder run `./waf configure`and  `./waf`. 

- Run this example

  **PROVIDER**

    For instance, the provider could use `/ndn/keys/bob` identity to sign data. 
    This identity could be a certificate signed by another identity, `/ndn/keys/alice`. 
    This last certificate is saved at consumer side, so the consumer will request
    the Bob's certificate in order to validate data.

    Before running provider, it is required to create certificates to sign data. 
    For instance, the following commands can be used from `ndn-signed-data/` 
    folder in order to create these certificates:

        $ ndnsec-key-gen -n /ndn/keys/bob > bob-unsigned.cert
        $ ndnsec-cert-install bob-unsigned.cert
 
    Sign this certificate by `/ndn/keys/alice` (this identity should exist
    if you have run the producer-signed-data1 before):

        $ ndnsec-cert-gen –s /ndn/keys/alice –N "Bob" –r bob-unsigned.cert > bob.cert
        $ ndnsec-cert-install bob.cert

    Check Bob certificate is signed by Alice:

        $ ndnsec-dump-certificate -p -i /ndn/keys/bob

    Run this example from `ndn-signed-data/` folder using the previous
    identity:

        $ ./build/bin/producer-signed-data2/producer-signed-data2 /ndn/keys/bob

    Whenever an interest with this prefix `/example/test` is received, 
    the producer returns a `<InterestPrefix>/testApp` signed data by 
    the identity `/ndn/keys/bob`. And whenever an interest with prefix `/ndn/keys`
    is received, if the certificate of that identity exists in the keyChain, the 
    producer returns it in a Data packet.

  **CONSUMER**

    Run the consumer from `ndn-signed-data/` folder using the provider-signed-data1 
    and the validation rules in `./config/validation2.conf`:

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



    Run this example from `ndn-signed-data/` folder:

        ./build/bin/consumer-signed-data1/consumer-signed-data1 ./config/validation2.conf

