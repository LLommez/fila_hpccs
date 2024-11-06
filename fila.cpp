#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <cstdlib>

namespace fs = std::filesystem;

int main() {
    std::vector<std::string> files;
    std::string filename;
    char choice, gasChoice;

    // Escolha do gás
    std::cout << "Escolha o gás para a execução:\n";
    std::cout << "1 - Hélio\n2 - Nitrogênio\n3 - Ambos\n";
    std::cout << "Opção: ";
    std::cin >> gasChoice;

    if (gasChoice == '1') {
        std::system("./ccg 1");  // Configura para hélio
        std::cout << "Configurado para Hélio.\n";
    } else if (gasChoice == '2') {
        std::system("./ccg 2");  // Configura para nitrogênio
        std::cout << "Configurado para Nitrogênio.\n";
    } else if (gasChoice == '3') {
        std::system("./ccg 1");  // Garante que comece com hélio ao escolher ambos
        std::cout << "Executando para ambos Hélio e Nitrogênio.\n";
    } else {
        std::cerr << "Opção inválida.\n";
        return 1;
    }

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
        for (const auto& entry : fs::directory_iterator(fs::current_path())) {
            if (entry.is_regular_file() && entry.path().extension() == ".pqr") {
                files.push_back(entry.path().filename().string());
            }
        }
    } else {
        std::cout << "\nDigite os nomes dos arquivos que deseja adicionar à fila, separados por espaço:\n";
        std::cout << "(Pressione Enter ao finalizar)\n";

        while (std::cin >> filename) {
            files.push_back(filename);
            if (std::cin.peek() == '\n') break;
        }
    }

    // Executa o comando ./hpccs para cada arquivo na fila e renomeia o output
    for (const auto& file : files) {
        if (gasChoice == '1' || gasChoice == '3') {
            std::string command = "./hpccs " + file;
            std::cout << "Executando com Hélio: " << command << std::endl;
            system(command.c_str());
            std::string outputFilename = fs::path(file).stem().string() + "_He.out";
            fs::rename("output.out", outputFilename);
            std::cout << "Arquivo output.out renomeado para " << outputFilename << std::endl;
        }

        if (gasChoice == '2' || gasChoice == '3') {
            std::system("./ccg 2");  // Alterna para Nitrogênio, se necessário
            std::string command = "./hpccs " + file;
            std::cout << "Executando com Nitrogênio: " << command << std::endl;
            system(command.c_str());
            std::string outputFilename = fs::path(file).stem().string() + "_N2.out";
            fs::rename("output.out", outputFilename);
            std::cout << "Arquivo output.out renomeado para " << outputFilename << std::endl;
            
            if (gasChoice == '3') {
                std::system("./ccg 1");  // Alterna de volta para Hélio para o próximo arquivo
            }
        }
    }

    std::cout << "Todos os arquivos foram processados.\n";
    return 0;
}


