producer-signed-data1 example
=============================


- This example is a producer which filters `/example/test` interest. It provides Data 
  named `<InterestPrefix>/testApp` signed with identity `/ndn/test/alice`. 

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
             |KeyLocator: /ndn/test/alice/KEY/ksk-<number>/ID-CERT    |
             +--------------------------------------------------------+
             |SignatureValue: <signature_256_bits>                    |
             +--------------------------------------------------------+

   You can test it with the consumer provided in the `src/consumer-signed-data1/` 
   folder.

- Build this example

    From `ndn-signed-data` folder run `./waf configure`and  `./waf`. 

- Run this example

    The first time the producer runs it creates the keys for identity
    `/ndn/test/alice` if it does not exist. If this identity exists, the
    producer will use it. The keys for this identity can be manually created 
    using the following command:

        $ ndnsec-key-gen -n /ndn/test/alice
 
    Check if the keys have been created by using:

        $ ndnsec-list -k /ndn/test/alice

    Run this example from `ndn-signed-data/` folder:

        $ ./build/src/producer-signed-data1/producer-signed-data1

    Whenever an interest with this prefix `/example/test` is received, 
    the producer returns a `<InterestPrefix>/testApp` signed data with 
    the identity `/ndn/test/alice`.
