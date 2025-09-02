FROM ubuntu:22.04
LABEL authors="stefanutflorescu"

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Bucharest

RUN apt-get update && apt-get install -y \
    build-essential \
    git \
    wget \
    libopencv-dev \
    libsfml-dev \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

RUN wget https://github.com/Kitware/CMake/releases/download/v3.30.5/cmake-3.30.5-linux-x86_64.sh \
    && chmod +x cmake-3.30.5-linux-x86_64.sh \
    && ./cmake-3.30.5-linux-x86_64.sh --skip-license --prefix=/usr/local \
    && rm cmake-3.30.5-linux-x86_64.sh

RUN cmake --version

WORKDIR /app
COPY . .

RUN mkdir -p build
WORKDIR /app/build
RUN cmake .. && cmake --build .

CMD ["./OOP-main"]
