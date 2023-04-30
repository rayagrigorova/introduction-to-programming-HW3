#include <iostream>
size_t myStrlen(char arr[]);
void encrypt(const char toEncrypt[], const size_t size, const char key, char result[]);
int main()
{
    const size_t MAX_SIZE = 1024;
    char S[MAX_SIZE + 1];
    char result[MAX_SIZE + 1];
    char C;

    std::cin >> C;
    std::cin.ignore();
    std::cin.getline(S, MAX_SIZE + 1);

    size_t sizeOfS = myStrlen(S);
    
    encrypt(S, sizeOfS, C, result);
    std::cout << result;

}

size_t myStrlen(char arr[]) {
    size_t ctr = 0;
    while (arr[ctr] != '\0') {
        ctr++;
    }
    return ctr;
}

void encrypt(const char toEncrypt[], const size_t size, const char key, char result[]) {
    for (int i = 0; i < size; i++) {
        result[i] = toEncrypt[i] ^ key;
    }
    result[size] = '\0';
}
