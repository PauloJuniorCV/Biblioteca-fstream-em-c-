# Biblioteca fstream — C++

## O que é

A biblioteca `fstream` do C++ é utilizada para **leitura e escrita de arquivos**. Ela funciona como uma ponte entre o programa e o sistema de arquivos do computador.

Por padrão, tudo que um programa processa fica armazenado apenas na memória RAM — quando o programa é encerrado, esses dados são perdidos. Com o `fstream` é possível salvar essas informações em arquivos, tornando-as persistentes.

---

## Classes principais

- `ifstream` — leitura de arquivos
- `ofstream` — escrita em arquivos
- `fstream` — leitura e escrita ao mesmo tempo

---

## Comandos mais utilizados

- `is_open()` — verifica se o arquivo foi aberto corretamente
- `getline()` — lê o arquivo linha por linha
- `eof()` — verifica se chegou ao fim do arquivo
- `close()` — fecha o arquivo
- `seekg()` — move o cursor de leitura para uma posição específica
- `seekp()` — move o cursor de escrita para uma posição específica

---

## Exemplo de escrita

```cpp
#include 

int main() {
    std::ofstream arquivo("dados.txt");
    arquivo << "Olá, mundo!";
    arquivo.close();
    return 0;
}
```

## Exemplo de leitura

```cpp
#include 
#include 
#include 

int main() {
    std::ifstream arquivo("dados.txt");
    std::string linha;

    while (std::getline(arquivo, linha)) {
        std::cout << linha << "\n";
    }

    arquivo.close();
    return 0;
}
```

---

## Usos comuns

- Armazenamento de cadastros
- Geração de relatórios
- Leitura de arquivos de configuração
- Registro de logs