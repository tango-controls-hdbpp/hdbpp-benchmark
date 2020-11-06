# hdbpp-benchmark

[![TangoControls](https://img.shields.io/badge/-Tango--Controls-7ABB45.svg?style=flat&logo=%20data%3Aimage%2Fpng%3Bbase64%2CiVBORw0KGgoAAAANSUhEUgAAACAAAAAkCAYAAADo6zjiAAAABHNCSVQICAgIfAhkiAAAAAlwSFlzAAALEwAACxMBAJqcGAAAAsFJREFUWIXtl01IFVEYht9zU%2FvTqOxShLowlOgHykWUGEjUKqiocB1FQURB0KJaRdGiaFM7gzZRLWpTq2olhNQyCtpYCP1gNyIoUTFNnxZzRs8dzvw4Q6564XLnfOf73vedc2a%2BmZEKALgHrC3CUUR8CxZFeEoFalsdM4uLmMgFoIlZLJp3A9ZE4S2oKehhlaR1BTnyg2ocnW%2FxsxEDhbYij4EPVncaeASMAavnS%2FwA8NMaqACNQCew3f4as3KZOYh2SuqTVJeQNiFpn6QGSRVjTH9W%2FiThvcCn6H6n4BvQDvQWFT%2BSIDIFDAKfE3KOAQeBfB0XGPeQvgE67P8ZoB44DvTHmFgJdOQRv%2BUjc%2BavA9siNTWemgfA3TwGquCZ3w8szFIL1ALngIZorndvgJOR0GlP2gtJkzH%2Bd0fGFxW07NqY%2FCrx5QRXcYjbCbmxF1dkBSbi8kpACah3Yi2Sys74cVyxMWY6bk5BTwgRe%2BYlSzLmxNpU3aBeJogk4XWWpJKUeiap3RJYCpQj4QWZDQCuyIAk19Auj%2BAFYGZZjTGjksaBESB8P9iaxUBIaJzjZcCQcwHdj%2BS2Al0xPOeBYYKHk4vfmQ3Y8YkIwRUb7wQGU7j2ePrA1URx93ayd8UpD8klyPbSQfCOMIO05MbI%2BDvwBbjsMdGTwlX21AAMZzEerkaI9zFkP4AeYCPBg6gNuEb6I%2FthFgN1KSQupqzoRELOSed4DGiJala1UmOMr2U%2Bl%2FTWEy9Japa%2Fy41IWi%2FJ3d4%2FkkaAw0Bz3AocArqApwTvet3O3GbgV8qqjAM7bf4N4KMztwTodcYVyelywKSCD5V3xphNXoezuTskNSl4bgxJ6jPGVJJqbN0aSV%2Bd0M0aO7FCs19Jo2lExphXaTkxdRVgQFK7DZVDZ8%2BcpdmQh3wuILh7ut3AEyt%2B51%2BL%2F0cUfwFOX0t0StltmQAAAABJRU5ErkJggg%3D%3D)](http://www.tango-controls.org) [![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) [![](https://img.shields.io/github/release/tango-controls-hdbpp/hdbpp-mysql-project.svg)](https://github.com/tango-controls-hdbpp/hdbpp-mysql-project/releases)

- [hdbpp-benchmark](#hdbpp-benchmark)
  - [Cloning](#Cloning)
  - [Overview](#Overview)
    - [tango](#tango)
    - [docker](#docker)
    - [docker-compose](#docker-compose)
    - [conf](#conf)
  - [Building](#Building)
    - [External Components](#External-Components)
  - [Running](#Running)
      - [Test results](#Test-results)
  - [License](#License)

The hdbpp benchmark aim to ease benchmarking of HDB++, in particular it makes easier to compare different backends or different configurations of the same backend. It makes use of docker and docker-compose.

Some of the information assumes familiarity with Docker terms and technologies. Please to Docker [documentation](https://docs.docker.com/reference/) for more information.

## Cloning 

To successfully clone the project use the following git command:

```bash
git clone https://github.com/tango-controls-hdbpp/hdbpp-benchmark.git
```

## Overview

Brief overview of the modules:

### tango

Contains device servers developed for testing HDB++:
 * [evgen](tango/evgen/) is a C++ Tango device implementing attributes for all Tango data types, scalar and spectrum. Internally it has a thread, running at a configurable period, pushing events for the enabled attributes.

### docker

Contains dockers. Actually there are 4 dockers defined:
* [hdbpp-test-insertion](docker/hdbpp-test-insertion/) runs a Python script which starts an evgen device end check insertion performances of HDB++ EventSubscribers
* [tango-evgen](docker/tango-evgen/) runs the evgen Tango device
* [tango-hdbpp](docker/tango-hdbpp/) runs the HDB++ ConfigurationManager and EventSubsciber Tango devices
* [tango-hdbppconfig](docker/tango-hdbppconfig/) runs a Python script which loads in HDB++ the configuration of attributes to be archived and events threshold

### docker-compose

Contains docker-compose YAML files to define services, networks and volumes of various benchmarks. Actually there are 2 benchmarks implemented to test the maximum insertion rate of MySQL and of TimescaleDB:
* [hdbpp-mysql-innodb](docker-compose/hdbpp-mysql-innodb)
* [hdbpp-timescaledb](docker-compose/hdbpp-timescaledb)

### conf

Configuration file for dockers:
* [hdbpp_mysql_innodb.json](conf/hdbpp_mysql_innodb.json): Tango device configuration for the tango-dsconfig docker in the hdbpp-mysql-innodb test
* [hdbpp_timescaledb.json](conf/hdbpp_timescaledb.json): Tango device configuration for the tango-dsconfig docker in the hdbpp-timescaledb test
* [hdbpp_evgen.conf](conf/hdbpp_evgen.conf) HDB++ attributes configuration for first EventSubscriber using the tango-hdbppconfig docker
* [hdbpp_evgen2.conf](conf/hdbpp_evgen2.conf) HDB++ attributes configuration for second EventSubscriber using the tango-hdbppconfig docker


## Building

A Makefile is provided to build all dockers provided in this project.

### External Components

This project depends on dockers that are present in external projects and actually needs to be cloned and built manually:
* [hdbpp-timescale-project](https://github.com/tango-controls-hdbpp/hdbpp-timescale-project) for the hdbpp-timescale-docker in resources/ dir
* [hdbpp-mysql-project](https://github.com/tango-controls-hdbpp/hdbpp-mysql-project) for the hdbpp-mysql-docker in resources/ dir

## Running
To run the tests ```docker-compose up``` command must be used and several parameters should be passed:
* NETWORK_MODE
* TANGO_HOST
* HDBPP_HOST
* TANGODB_HOST
* TANGODB_PORT

Example for hdbpp-mysql-innodb (set hostname properly):
```
sudo NETWORK_MODE=bridge TANGO_HOST=hostname:10000 HDBPP_HOST=hostname:3306 TANGODB_HOST=hostname TANGODB_PORT=3307 docker-compose up
```

Example for hdbpp-timescaledb (set hostname properly):
```
sudo NETWORK_MODE=bridge TANGO_HOST=hostname:10000 HDBPP_HOST=hostname:5432 TANGODB_HOST=hostname TANGODB_PORT=3307 docker-compose up
```

### Test results

Test results are saved in the conf directory.

File are named ```<testname>_<timestamp>.txt``` and are formatted as follows:

```
<metric path> <metric value> <metric timestamp>
<metric path> <metric value> <metric timestamp>
...
```

It is easy to import to Graphite/Carbon using the PlainText protocol. More details [here](https://graphite.readthedocs.io/en/latest/feeding-carbon.html).

## License

The code is released under the LGPL3 license and a copy of this license is provided with the code. Full license [here](LICENSE.md)
