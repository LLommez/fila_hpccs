#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    // Verifica se o argumento foi fornecido
    if (argc != 2) {
        std::cerr << "Uso: ./ccg <1 para hélio ou 2 para nitrogênio>" << std::endl;
        return 1;
    }

    // Verifica se o argumento é 1 ou 2
    std::string escolha = argv[1];
    if (escolha != "1" && escolha != "2") {
        std::cerr << "Erro: o argumento deve ser 1 (hélio) ou 2 (nitrogênio)." << std::endl;
        return 1;
    }

    // Caminho para o arquivo config.in
    std::string caminhoArquivo = "./config/config.in";
    
    // Abre o arquivo para leitura
    std::ifstream arquivoLeitura(caminhoArquivo);
    if (!arquivoLeitura) {
        std::cerr << "Erro ao abrir o arquivo para leitura." << std::endl;
        return 1;
    }

    // Lê o conteúdo e modifica a última coluna
    std::string linha;
    if (std::getline(arquivoLeitura, linha)) {
        linha = linha.substr(0, linha.rfind('\t') + 1) + escolha;  // Substitui o último valor
    }
    arquivoLeitura.close();

    // Abre o arquivo para escrita
    std::ofstream arquivoEscrita(caminhoArquivo);
    if (!arquivoEscrita) {
        std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
        return 1;
    }

    // Escreve a linha modificada de volta no arquivo
    arquivoEscrita << linha << std::endl;
    arquivoEscrita.close();

    
    return 0;
}
