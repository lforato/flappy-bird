# Flappy Bird em C++ e OpenGL

Repositório da série do YouTube onde implementamos o Flappy Bird do zero usando **C++** e **OpenGL**.

🎬 [Acesse o canal no YouTube](https://www.youtube.com/channel/UCSMgWnbazFU8JXuA7hHSgqQ/posts?pvf=CAI%253D)
🎬 [Acesse os diagramas do vídeo](https://drive.google.com/drive/folders/1nmXEinAaj76q8SjYBJJh-0v0uzR20hUh?usp=sharing)

---

## Sobre a série

Cada vídeo tem uma branch correspondente no formato `video-xxx`, onde `xxx` é o número do vídeo. Para acompanhar um episódio específico, basta fazer checkout na branch desejada:

```bash
git checkout video-001
```

## Tecnologias

- **C++**
- **OpenGL 3.3 Core**
- **GLFW** — janela e input
- **GLAD** — carregamento das funções OpenGL
- **stb_image** — carregamento de texturas

## Como compilar

### Pré-requisitos

- CMake 3.10+
- Compilador C++ (GCC, Clang ou MSVC)

### Build

```bash
cmake -B build
cmake --build build
```

O executável será gerado em `build/flappy-bird`.
