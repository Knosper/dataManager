# Start from the latest Alpine image
FROM alpine:latest

# Install C++ build environment, PostgreSQL client library, and dependencies for libpqxx
RUN apk add --no-cache \
    clang \
    make \
    postgresql-dev \
    g++ \
    cmake \
    git

# Download and build libpqxx
RUN git clone --recursive https://github.com/jtv/libpqxx.git \
    && cd libpqxx \
    && cmake -DCMAKE_INSTALL_PREFIX=/usr . \
    && make \
    && make install

# Copy your source code into the container
COPY . /usr/src/app

# Set the working directory to where you copied your source code
WORKDIR /usr/src/app

# Build your C++ application
RUN make

#CMD ["./dataManager"]

CMD ["tail", "-f", "/dev/null"]
