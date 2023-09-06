#include <iostream>
#include <fstream>
#include <string>

void encryptFile(const std::string &inputFilename, const std::string &outputFilename, char key)
{
    std::ifstream inputFile(inputFilename, std::ios::binary);
    if (!inputFile)
    {
        std::cerr << "Error opening input file." << std::endl;
        return;
    }

    std::ofstream outputFile(outputFilename, std::ios::binary);
    if (!outputFile)
    {
        std::cerr << "Error creating output file." << std::endl;
        return;
    }

    char ch;
    while (inputFile.get(ch))
    {
        ch = ch ^ key;
        outputFile.write(reinterpret_cast<char *>(&ch), sizeof(ch));
    }

    inputFile.close();
    outputFile.close();
}

void decryptFile(const std::string &inputFilename, const std::string &outputFilename, char key)
{
    encryptFile(inputFilename, outputFilename, key);
}

int main()
{
    std::string EServerFile = "./templates/serverBasic.bin";
    std::string serverCode;

    std::string EClientFile = "./templates/clientBasic.bin";
    std::string clientCode;

    char encryptionKey = 'Y';

    // encryptFile("server.c", "./templates/serverBasic.bin", encryptionKey);
    // encryptFile("client.c", "./templates/clientBasic.bin", encryptionKey);

    std::cout << "Enter server name: ";
    std::cin >> serverCode;

    std::cout << "Enter client name: ";
    std::cin >> clientCode;

    decryptFile(EServerFile, serverCode, encryptionKey);
    std::cout << "Generation of server was successful." << std::endl;

    decryptFile(EClientFile, clientCode, encryptionKey);
    std::cout << "Generation of client was successful." << std::endl;

    std::cout << "Press Enter to exit...";
    std::cin.ignore();
    std::cin.get();

    return 0;
}