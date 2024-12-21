# Alegem imaginea de bază
FROM ubuntu:22.04
LABEL authors="stefanutflorescu"
# Setăm variabile de mediu
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Bucharest

# Instalăm dependențele de bază, OpenCV și SFML
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    libopencv-dev \
    libsfml-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Adăugăm sursele proiectului în container
WORKDIR /app
COPY . .

# Construim proiectul
RUN mkdir -p build && cd build && \
    cmake .. && \
    cmake --build .

# Setăm comanda implicită
CMD ["./build/your_project_executable"]

ENTRYPOINT ["top", "-b"]