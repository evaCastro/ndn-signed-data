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

   Additionally this provider filters `/ndn/keys` interests to provide
   certificates which are prefix of `/ndn/keys`, if they are in the 
   keyChain. This is very useful when using no auto-signed certificates.

   You can test it with the consumer provided in the `src/consumer-signed-data2/` 
   folder.

- Build this example

    From `ndn-signed-data/` folder run `./waf configure`and  `./waf`. 

- Run this example

    We will use `/ndn/keys/bob` identity to sign data. However, this identity has
    a certificate signed by `/ndn/keys/alice`. Then the consumer will
    request the `/ndn/keys/bob` certificate in order to validate data.

    For instance, we can create the `/ndn/keys/bob` identity 
    using the following command:

        $ ndnsec-key-gen -n /ndn/keys/bob > bob-unsigned.cert
        $ ndnsec-cert-install -f bob-unsigned.cert
 
    Sign this certificate by `/ndn/keys/alice` (this identity should exist
    if you have run the producer-signed-data1 before):

        $ ndnsec-cert-gen –s /ndn/keys/alice –N "Bob" –r bob-unsigned.cert > bob.cert
        $ ndnsec-cert-install -f bob.cert

    Check Bob certificate is signed by Alice:

        $ ndnsec-dump-cert -p -i /ndn/keys/bob

    Run this example from `ndn-signed-data/` folder using the previous
    identity:

        $ ./build/bin/producer-signed-data2/producer-signed-data2 /ndn/keys/bob

    Whenever an interest with this prefix `/example/test` is received, 
    the producer returns a `<InterestPrefix>/testApp` signed data by 
    the identity `/ndn/keys/bob`. And whenever an interest with prefix `/ndn/keys`
    is received, if the certificate of that identity exists in the keyChain, it 
    will be returned in a Data packet.
