
# GoogleTest / GoogleMock 환경 설정
```
$ ./googletest/googlemock/scripts/fuse_gmock_files.py .
$ g++ -c gmock-gtest-all.cc -I.
$ g++ -c ./googletest/googlemock/src/gmock_main.cc -I.
$ ar rcv libgtest.a gmock-gtest-all.o gmock_main.o

$ ./build.sh source.cpp

```
