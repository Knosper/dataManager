# Start from Ubuntu image
FROM ubuntu:latest

# Install C++ build environment, PostgreSQL client library, and dependencies for libpqxx
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    clang \
    make \
    g++ \
    libpq-dev \
	libpqxx-dev \
    qtbase5-dev

# Install Xfce and related components
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    x11-apps \
    xfce4 \
    xfce4-terminal \
    dbus-x11 \
    firefox \
    && apt-get clean

# Copy your source code into the container
COPY . /usr/src/app

# Set the working directory to where you copied your source code
WORKDIR /usr/src/app

# Set the default user (replace 'user' with your username)

# Start the Xfce desktop environment
CMD ["startxfce4"]