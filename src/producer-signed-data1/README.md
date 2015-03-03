producer-signed-data1 example
=============================


- This example is a producer which filters `/example/test` interests. 
  It provides Data named `<InterestPrefix>/testApp` signed by 
  an identity. The identity is a command line program argument, for 
  instance `/ndn/keys/alice`. In this case, data sent by this producer should
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
             |KeyLocator: /ndn/keys/alice/KEY/ksk-<number>/ID-CERT    |
             +--------------------------------------------------------+
             |SignatureValue: <signature_256_bits>                    |
             +--------------------------------------------------------+

   You can test it with the consumer provided in the `src/consumer-signed-data1/` 
   folder.

- Build this example

    From `ndn-signed-data/` folder run `./waf configure`and  `./waf`. 

- Run this example

    The producer takes an identity to sign the data as a command line argument.
    This identity should exist before running the producer.

    For instance, we can create the `/ndn/keys/alice` identity 
    using the following command:

        $ ndnsec-key-gen -n /ndn/keys/alice
 
    Check if the keys have been created:

        $ ndnsec-list -k /ndn/keys/alice

    Run this example from `ndn-signed-data/` folder using the previous
    identity:

        $ ./build/bin/producer-signed-data1/producer-signed-data1 /ndn/keys/alice

    Whenever an interest with this prefix `/example/test` is received, 
    the producer returns a `<InterestPrefix>/testApp` signed data by 
    the identity `/ndn/keys/alice`.
