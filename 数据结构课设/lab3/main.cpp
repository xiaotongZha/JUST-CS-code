#include <iostream>
#include <queue>
#include <vector>
#include <map>

using namespace std;

// 哈夫曼树节点结构体
struct HuffmanNode {
    char data; // 数据
    int frequency; // 频率
    HuffmanNode* left; // 左子树指针
    HuffmanNode* right; // 右子树指针
    HuffmanNode(char d, int f) : data(d), frequency(f), left(nullptr), right(nullptr) {}
};

// 优先队列比较函数，构建小根堆
struct CompareNodes {
    bool operator()(HuffmanNode* const& node1, HuffmanNode* const& node2) {
        return node1->frequency > node2->frequency;
    }
};

// 构建哈夫曼树
HuffmanNode* buildHuffmanTree(vector<pair<char, int>>& codes) {
    vector<pair<char, int>> characters;

    if (codes.size() == 0) {
        // 如果没有提供字符和频率，从用户输入中获取
        int n;
        cout << "输入字符个数 (n): ";
        cin >> n;
        cout << "输入 " << n << " 个字符和对应的权值: ";
        for (int i = 0; i < n; i++) {
            char c;
            int f;
            cin >> c >> f;
            characters.push_back({c, f});
        }
    } else {
        characters = codes;
    }

    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> pq;

    for (const auto& pair : characters) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();

        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* internalNode = new HuffmanNode('\0', left->frequency + right->frequency);
        internalNode->left = left;
        internalNode->right = right;

        pq.push(internalNode);
    }

    return pq.top();
}

// 打印哈夫曼编码
void printHuffmanCodes(HuffmanNode* root, string code, map<char, string>& codeMap) {
    if (root == nullptr) {
        return;
    }
    if (root->data != '\0') {
        codeMap[root->data] = code;
    }
    printHuffmanCodes(root->left, code + "0", codeMap);
    printHuffmanCodes(root->right, code + "1", codeMap);
}

// 进行哈夫曼编码，输出二进制字符串
string makeHuffmanCodes(map<char, string>& codeMap) {
    cout << "请输入一段字符串: ";
    string s, code = "";
    cin >> s;
    cout << "----- 正在进行编码 -----" << endl;
    for (int i = 0; i < s.size(); i++) {
        if (codeMap[s[i]].size() == 1) {
            cout << "   " << codeMap[s[i]];
        } else if (codeMap[s[i]].size() > 4) {
            cout << " " << codeMap[s[i]];
        } else {
            cout << "  " << codeMap[s[i]];
        }
        code += codeMap[s[i]];
    }
    cout << endl;
    cout << "编码结果为：" << code << endl;

    return code;
}
// 进行哈夫曼解码
void decodeHuffmanTree(HuffmanNode* root, string encodedString) {
    cout << "----- 正在进行解码 -----" << endl;
    HuffmanNode* cur = root;
    string decodedString = "";
    for (int i = 0; i < encodedString.size(); i++) {
        if (encodedString[i] == '0') {
            cur = cur->left;
        } else if (encodedString[i] == '1') {
            cur = cur->right;
        } else {
            cout << "无效输入" << endl;
            return;
        }
        if (cur->left == nullptr && cur->right == nullptr) {
            decodedString += cur->data;
            cur = root;
        }
    }
    cout << "解码结果为：" << decodedString << endl;
}

int main() {
    HuffmanNode* root = nullptr;
    vector<pair<char, int>> codes;
    map<char, string> codeMap;
    // 构建哈夫曼树
    root = buildHuffmanTree(codes);
    // 打印哈夫曼编码
    printHuffmanCodes(root, "", codeMap);
    // 显示哈夫曼编码
    cout << "----- 哈夫曼编码 -----" << endl;
    for (const auto& entry : codeMap) {
        cout << entry.first << ": " << entry.second << endl;
    }
    // 进行哈夫曼编码
    string encodedString = makeHuffmanCodes(codeMap);
    // 进行哈夫曼解码
    decodeHuffmanTree(root, encodedString);
    system("pause");
    return 0;
}
