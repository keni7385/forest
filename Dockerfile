FROM quay.io/jlospinoso/cppbuild:v1.0.0

RUN mkdir forest
WORKDIR forest
COPY / ./
RUN mkdir build
WORKDIR build
RUN cmake -DBUILD_EXAMPLES=ON -DENABLE_TESTING=ON ..
RUN make
