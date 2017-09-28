FROM quay.io/jlospinoso/cppbuild:v1.0.0

RUN mkdir forest
WORKDIR forest
COPY *.h *.hpp *.cpp CMakeLists.txt examples tests ./
RUN mkdir build
WORKDIR build
RUN cmake ..
RUN make
