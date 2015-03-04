ndn-signed-data: a simple example to show signed data
=================================================================================

These are some simple examples of how to program signed data.

1. Producer/consumer: consumer requests data, producer provides signed data using a 
   self-signed certificate. When consumer gets data, it checks the signature by using 
   a file that contains a self-signed certificate.

   ![alt tag](https://github.com/evaCastro/ndn-signed-data/blob/master/imgs/ndn-sign-data-01.png =650x)
   More information:
       - producer-signed-data1 [`src/producer-signed-data1/README.md`](https://github.com/evaCastro/ndn-signed-data/blob/master/src/producer-signed-data1/README.md)
       - consumer-signed-data1 [`src/consumer-signed-data1/README.md`](https://github.com/evaCastro/ndn-signed-data/blob/master/src/consumer-signed-data1/README.md).

2. Producer/consumer: consumer requests data, producer provides signed data using
   a second party signed certificate. When consumer gets data, it requests the 
   second party signed certificate to validate the data which will be also provided by
   producer.

   ![alt tag](https://github.com/evaCastro/ndn-signed-data/blob/master/imgs/ndn-sign-data-02.png =650x)
   More information information:
       - producer-signed-data2 [`src/producer-signed-data2/README.md`](https://github.com/evaCastro/ndn-signed-data/blob/master/src/producer-signed-data2/README.md)
       - consumer-signed-data2 [`src/consumer-signed-data2/README.md`](https://github.com/evaCastro/ndn-signed-data/blob/master/src/consumer-signed-data2/README.md).


Installation instructions
-------------------------

### Prerequisites

Required:

* [ndn-cxx and its dependencies](http://named-data.net/doc/ndn-cxx/)
* Boost libraries

### Build

To build `ndn-signed-data` run the following commands from 
`ndn-signed-data/` folder:

    ./waf configure
    ./waf
