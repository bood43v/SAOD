#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    setlocale(LC_ALL, "ru");
    std::ifstream inputFile("input.txt"); // Путь к текстовому файлу в формате "0 1\n2 3\n..."
    std::ofstream outputFile("output.graphml"); // Путь к выходному файлу в формате GraphML

    if (!inputFile) {
        std::cerr << "Не удалось открыть входной файл." << std::endl;
        return 1;
    }

    if (!outputFile) {
        std::cerr << "Не удалось создать выходной файл." << std::endl;
        return 1;
    }

    // Записываем заголовок GraphML
    outputFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    outputFile << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\"\n";
    outputFile << "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n";
    outputFile << "xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns\n";
    outputFile << "http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n";
    outputFile << "<graph id=\"G\" edgedefault=\"undirected\">\n";

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        int source, target;
        if (!(iss >> source >> target)) {
            std::cerr << "Ошибка чтения строки: " << line << std::endl;
            return 1;
        }

        // Записываем ребро в формате GraphML
        outputFile << "<edge source=\"" << source << "\" target=\"" << target << "\"/>\n";
    }

    // Записываем завершающие теги GraphML
    outputFile << "</graph>\n";
    outputFile << "</graphml>\n";

    // Закрываем файлы
    inputFile.close();
    outputFile.close();

    std::cout << "Экспорт успешно выполнен. Результат сохранен в output.graphml" << std::endl;

    return 0;
}