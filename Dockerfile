FROM quay.io/jlospinoso/cppbuild:v1.0.0

RUN mkdir forest
WORKDIR forest
COPY / ./
RUN mkdir build
WORKDIR build
RUN cmake -DFOREST_BUILD_EXAMPLES=ON -DFOREST_ENABLE_TESTING=ON -DFOREST_BUILD_DOCUMENTATION=ON ..
RUN make examples
RUN make check
RUN make doc
