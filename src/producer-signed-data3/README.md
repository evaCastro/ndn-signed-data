producer-signed-data3 example
=============================


- This example is the same producer as producer-signed-data1 
  which filters `/example/test` interests. 
  It provides Data named `<InterestPrefix>/testApp` signed by 
  an identity. 
  The identity is a command line program argument, for instance 
  `/ndn/keys/site1/node1/app1`. In this case, data sent by this producer should
  be as following:

             +---------------------------------------------------------------+
             |Name: <InterestPrefix>/testApp/<version>                       |
             +---------------------------------------------------------------+
             |ContentType: 0 (blob)                                          |
             +---------------------------------------------------------------+
             |Freshness period: 10000 msec                                   |
             +---------------------------------------------------------------+
             |Content: <string>                                              |
             +---------------------------------------------------------------+
             |SignatureType: 1 (rsa-256)                                     |
             +---------------------------------------------------------------+
             |KeyLocator: /ndn/keys/site1/node1/KEY/app1/ksk-<number>/ID-CERT|
             +---------------------------------------------------------------+
             |SignatureValue: <signature_256_bits>                           |
             +---------------------------------------------------------------+

   Additionally this provider filters `/ndn/keys` interests to provide
   certificates which are prefix of `/ndn/keys`, if they are in the 
   keyChain. This is very useful when using no auto-signed certificates.
   In this example the certificates will use a hierarchical model, similar
   to the NDN testbed. Hierarchical certificates use the key locator:
    
           <PREFIX>/KEY/<name>/ksk-<number>/ID-CERT

- Build this example

    From `ndn-signed-data/` folder run `./waf configure`and  `./waf`. 

- Run this example

  *PROVIDER*

    We will use a hierarchical certificate model to sign data. For instance, it 
    could be used `/ndn/keys/site1/node1/app1` identity to sign data. 
    This identity has a certificate signed by `/ndn/keys/site1/node1`, which
    is signed by `/ndn/keys/site1`. The last certificate is saved in a file. 

    Then the consumer will request these certificates in order to validate data.

    Before running provider, it is required to create certificates to sign data.
    For instance, the following commands can be used from `ndn-signed-data/` folder
    in order to create these certificates:

        $ ndnsec-key-gen -n /ndn/keys/site1 
        $ ndnsec-sign-req /ndn/keys/site1 > ./config/root-site1.cert 

        $ ndnsec-key-gen -n /ndn/keys/site1/node1 > node1-unsigned.cert
        $ ndnsec-cert-install node1-unsigned.cert
        $ ndnsec-cert-gen –s /ndn/keys/site1 –N "Node 1" –r node1-unsigned.cert > node1.cert
        $ ndnsec-cert-install node1.cert

        $ ndnsec-key-gen -n /ndn/keys/site1/node1/app1 > app1-unsigned.cert
        $ ndnsec-cert-install app1-unsigned.cert
        $ ndnsec-cert-gen –s /ndn/keys/site1/node1 –N "App 1" –r app1-unsigned.cert > app1.cert
        $ ndnsec-cert-install app1.cert


    Run this example from `ndn-signed-data/` folder using the previous
    identity:

        $ ./build/bin/producer-signed-data3/producer-signed-data3 /ndn/keys/site1/node1/app1

    Whenever an interest with this prefix `/example/test` is received, 
    the producer returns a `<InterestPrefix>/testApp` signed data by 
    the identity `/ndn/keys/site1/node1/app1`. And whenever an interest 
    with prefix `/ndn/keys`
    is received, if the certificate of that identity exists in the keyChain, it 
    will be returned in a Data packet.

  *CONSUMER*

    There are 3 different ways to configure the validation at the consumer:

    a) Run the consumer from `ndn-signed-data/` folder using the
      provider-signed-data1 and the validation rules in
      `./config/validation-3a.conf`, which explicitly defines the
      chain of certificates needed to validate:

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
              name /ndn/keys/site1/node1/KEY/app1
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
            name /ndn/keys/site1/node1/KEY/app1
            relation is-prefix-of
          }
          checker
          {
            type customized
            sig-type rsa-sha256
            key-locator
            {
              type name
              name /ndn/keys/site1/KEY/node1
              relation is-prefix-of
            }
          }
        }

        rule
        {
          id "Example3 Validator"
          for data
          filter
          {
            type name
            name /ndn/keys/site1/KEY/node1
            relation is-prefix-of
          }
          checker
          {
            type customized
            sig-type rsa-sha256
            key-locator
            {
              type name
              name /ndn/keys/site1
              relation is-prefix-of
            }
          }
        }

        trust-anchor
        {
          type file
          file-name "./root-site1.cert"
        }


     Run the consumer:

        $ ./build/bin/consumer-signed-data1/consumer-signed-data1 ./config/validation-3a.conf

    b) Run the consumer from `ndn-signed-data/` folder using the provider-signed-data1 and
      the validation rules in `./config/validation-3b.conf`, which defines a 
      hierarchical model:

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
             name /ndn/keys/site1/node1/KEY/app1
             relation is-prefix-of
           }
         }
       }

       rule
       {
         id "Testbed Validation Rule"
         for data
         checker
         {
           type hierarchical
           sig-type rsa-sha256
         }
       }

       trust-anchor
       {
         type file
         file-name "./root-site1.cert"
       }


     Run the consumer:

        $ ./build/bin/consumer-signed-data1/consumer-signed-data1 ./config/validation-3b.conf

    c) Run the consumer from `ndn-signed-data/` folder using the provider-signed-data1 and
      the validation rules in `./config/validation-3cb.conf`, which defines a 
      hierarchical model by using regular expression (see 
      http://named-data.net/doc/ndn-cxx/0.3.0/tutorials/security-validator-config.html):

       rule
       {
         id "First rule: Example Validator"
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
             name /ndn/keys/site1/node1/KEY/app1
             relation is-prefix-of
           }
         }
       }

       rule
       {
         id "Second rule: Example Regex Validation Rule"
         for data
         checker
         {
           type customized
           sig-type rsa-sha256
           key-locator
           {
             type name
             hyper-relation
             {
               k-regex ^([^<KEY>]*)<KEY>(<>*)<ksk-.*><ID-CERT>
               k-expand \\1\\2
               h-relation is-prefix-of
               p-regex ^(<>*)$
               p-expand \\1
             }
           }
         }
       }

       trust-anchor
       {
         type file
         file-name "./root-site1.cert"
       }

    The "Example Regex Validation Rule" requires the packet name must be under the
    corresponding namespace of the `KeyLocator` name. Then, when a packet named with
    prefix `/example` is received:

      DATA PACKET:
        Name: /example
        KeyLocator: /ndn/keys/site1/node1/KEY/app1/ksk-<number>/ID-CERT
      
    The first rule of the configuration file is applied: the
    KeyLocator matches the rule. So, the following key is requested in
    an interest packet:
    `/ndn/keys/site1/node1/KEY/app1/ksk-<number>/ID-CERT`. When it is
    received:
      
      DATA PACKET:
        Name: /ndn/keys/site1/node1/KEY/app1/ksk-<number>/ID-CERT
        KeyLocator: /ndn/keys/site1/KEY/node1/ksk-<number>/ID-CERT

    The second rule is applied, where k-expand \\\\1\\\\2=`/ndn/keys/site1/node1` (from
    KeyLocator) is prefix of
    p-expand \\\\1= `/ndn/keys/site1/node1/KEY/app1/ksk-<number>/ID-CERT` (data
    name). So, the following key is requested in an interest packet:
    `/ndn/keys/site1/KEY/node1/ksk-<number>/ID-CERT`. When it is
    received:
      
      DATA PACKET:
        Name: /ndn/keys/site1/KEY/node1/ksk-<number>/ID-CERT
        KeyLocator: /ndn/keys/KEY/site1/ksk-<number>/ID-CERT

    The second rule is applied, where k-expand \\\\1\\\\2=`/ndn/keys/site1` (from KeyLocator) is prefix of 
    p-expand \\\\1=`/ndn/keys/site1/KEY/node1/ksk-<number>/ID-CERT` (data name).  
    And now, the key `/ndn/keys/site1/KEY/ksk-<number>/ID-CERT` is saved
    in trust anchor file.


    Run the consumer:

        $ ./build/bin/consumer-signed-data1/consumer-signed-data1 ./config/validation-3c.conf
