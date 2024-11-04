#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <cstdlib>

namespace fs = std::filesystem;

int main() {
    std::vector<std::string> files;
    std::string filename;
    char choice;

    // Lista apenas arquivos .pqr na pasta atual
    std::cout << "Arquivos .pqr na pasta atual:\n";
    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        if (entry.is_regular_file() && entry.path().extension() == ".pqr") {
            std::cout << entry.path().filename().string() << std::endl;
        }
    }

    // Pergunta se o usuário deseja executar todos os arquivos .pqr
    std::cout << "\nDeseja executar todos os arquivos .pqr disponíveis? (s/n): ";
    std::cin >> choice;

    if (choice == 's' || choice == 'S') {
        // Adiciona todos os arquivos .pqr à fila
        for (const auto& entry : fs::directory_iterator(fs::current_path())) {
            if (entry.is_regular_file() && entry.path().extension() == ".pqr") {
                files.push_back(entry.path().filename().string());
            }
        }
    } else {
        // Lê todos os nomes de arquivos escolhidos e adiciona à fila
        std::cout << "\nDigite os nomes dos arquivos que deseja adicionar à fila, separados por espaço:\n";
        std::cout << "(Pressione Enter ao finalizar)\n";

        while (std::cin >> filename) {
            files.push_back(filename);
            if (std::cin.peek() == '\n') break;
        }
    }

    // Executa o comando ./hpccs para cada arquivo na fila e renomeia o output
    for (const auto& file : files) {
        std::string command = "./hpccs " + file;
        std::cout << "Executando: " << command << std::endl;
        system(command.c_str());  // Executa o comando no terminal

        // Renomeia output.out para o formato nomedoarquivo.out
        std::string outputFilename = fs::path(file).stem().string() + ".out";
        fs::rename("output.out", outputFilename);

        std::cout << "Arquivo output.out renomeado para " << outputFilename << std::endl;
    }

    std::cout << "Todos os arquivos foram processados.\n";
    return 0;
}

