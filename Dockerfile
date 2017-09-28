FROM quay.io/jlospinoso/cppbuild:v1.0.0
RUN apt update && apt upgrade -y

RUN mkdir forest
WORKDIR forest

COPY *.h *.hpp *.cpp CMakeLists.txt ./
RUN mkdir build
WORKDIR build
RUN cmake ..
RUN make
