FROM ubuntu:22.04
LABEL authors="stefanutflorescu"

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Bucharest

RUN apt-get update && apt-get install -y \
    build-essential \
    wget \
    git \
    cmake \
    libopencv-dev \
    libsfml-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN mkdir -p build && cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release && \
    cmake --build . --config Release

WORKDIR /app/build
CMD ["./OOP-main"]
