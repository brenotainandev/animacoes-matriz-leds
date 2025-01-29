# Projeto: Animações em Matriz de LEDs 5x5 com Raspberry Pi Pico W

## 📌 Descrição

Este projeto visa criar animações visuais interativas em uma **matriz de LEDs 5x5 WS2812**, utilizando um **Raspberry Pi Pico W** e um **teclado matricial 4x4**. O sistema permite o acionamento de diferentes efeitos visuais e sonoros por meio das teclas do teclado matricial.

O desenvolvimento foi realizado no **simulador Wokwi** e na **placa BitDogLab**, como parte da **Unidade 4 - Microcontroladores**, promovendo aprendizado sobre **GPIO, periféricos, Git, GitHub e trabalho em equipe**.

## 🎯 Objetivos

✔ Controlar animações da matriz de LED's RGB e buzzer utilizando um teclado matricial.
✔ Familiarizar-se com o desenvolvimento em **C** utilizando o **Pico SDK**.
✔ Utilizar o **simulador Wokwi** para prototipagem rápida.
✔ Aprender sobre **versionamento de código** com **Git**.
✔ Aplicar **boas práticas de engenharia de software**, incluindo:
  - Criação de **branches** para funcionalidades específicas.
  - **Commits regulares** e bem documentados.
  - Uso de **pull requests** para revisão e integração de código.
  - **Colaboração eficiente** entre os membros do grupo.

## 👥 Membros do Grupo

- **Gabriel Neponuceno Batista**
- **Matheus Pereira Alves**
- **Rodrigo Damasceno Sampaio**
- **Erick Barros Ferreira Gomes**
- **João Vitor de Siqueira Santana Costa**
- **Eduarda da Silva Santos**
- **Breno Tainan Aguiar**
- **Daniel Souza Silva**

## 📺 Demonstração

- **Simulação no Wokwi:** [Assista no YouTube](https://youtu.be/2M6z68MGXbE)
- **Execução na Placa BitDogLab:** [Assista no YouTube](https://youtu.be/2M6z68MGXbE)

## 🛠 Tecnologia Utilizada

### 🔹 **Software**
- **Linguagem de Programação:** C
- **IDE:** Visual Studio Code
- **SDK:** Pico SDK
- **Simulador:** Wokwi
- **Controle de Versão:** Git
- **Plataforma de Hospedagem:** GitHub

### 🔹 **Hardware**
- **Microcontrolador:** Raspberry Pi Pico W
- **Matriz de LEDs:** WS2812 (5x5)
- **Teclado Matricial:** 4x4
- **Buzzer**

## 📂 Estrutura do Projeto

```
animacoes-matriz-leds/
│── includes/               # Cabeçalhos das funções
│   ├── animacoes.h
│   ├── buzzer.h
│   ├── matriz-led.h
│   ├── modo-gravacao.h
│   ├── teclado.h
│
│── src/                    # Implementação das funções
│   ├── animacoes.c
│   ├── buzzer.c
│   ├── matriz-led.c
│   ├── modo-gravacao.c
│   ├── teclado.c
│
│── build/                  # Arquivos compilados (gerado pelo CMake)
│── CMakeLists.txt          # Configuração do CMake
│── pico_sdk_import.cmake   # Importação do SDK do Pico
│── README.md               # Documentação do projeto
│── wokwi.toml              # Configuração do simulador Wokwi
│── diagram.json            # Arquivo de configuração do circuito
│── animacoes-matriz-leds.c # Código principal do projeto
```

## 🎮 Funcionalidades

### 📟 **Teclado Matricial 4x4**

🔹 **Teclas de Animação**

| Tecla | Animação                              | Autor  |
|-------|--------------------------------|--------|
| **1** | Rosto alternando entre feliz e triste | João  |
| **2** | Coração pulsando                   | Breno  |
| **3** | Diagramação onda senoidal          | Matheus |
| **4** | Animação oscilatória              | Rodrigo |
| **5** | Exibição do nome                  | Erick  |
| **6** | Estrela, triângulo, quadrado, círculo | Daniel  |
| **7** | Mudança de cor em gradiente         | Eduarda |
| **8** | Formação de um X                  | Gabriel |

🔹 **Teclas Especiais**

| Tecla | Função |
|-------|-----------------------------|
| **A** | Desliga todos os LEDs. |
| **B** | Acende LEDs **azuis** com 100% de brilho. |
| **C** | Acende LEDs **vermelhos** com 80% de brilho. |
| **D** | Acende LEDs **verdes** com 50% de brilho. |
| **#** | Acende LEDs **brancos** com 20% de brilho. |
| **\*** | Entra em **modo de gravação**. |

🔊 **Buzzer**
- O buzzer é acionado **toda vez** que uma tecla é pressionada.

## 📝 Como Executar o Projeto

1️⃣ **Clone o repositório:**
```sh
 git clone https://github.com/brenotainandev/animacoes-matriz-leds.git
 cd animacoes-matriz-leds
```

2️⃣ **Compile o projeto:**
```sh
 mkdir build && cd build
 cmake ..
 make
```

3️⃣ **Carregue o código no Raspberry Pi Pico W** e teste as animações pressionando as teclas do teclado matricial.

## 📜 Licença

Este projeto é de **uso educacional** e segue a licença MIT. Sinta-se à vontade para modificá-lo e contribuir!

