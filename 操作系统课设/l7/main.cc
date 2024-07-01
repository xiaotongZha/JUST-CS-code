#include <bits/stdc++.h>
using namespace std;

int disk_size = 200;  // 假设磁盘大小为 200
int start = 100;      // 初始磁道位置
int request_num = 10; // 请求序列长度
int N = 3;
vector<int> requests;

// 打印调度顺序
void print_sequence(const vector<int> &sequence){
    for (int track : sequence)
        cout << track << " ";
    cout << endl;
}

void fcfs(){
    vector<int> sequence = requests;
    print_sequence(sequence);
    double len = request_num;
    double sum = 0;
    double now = start;
    for (int i = 0; i < request_num; i++){
        sum += abs(sequence[i] - now);
        now = sequence[i];
    }
    cout << "平均寻道长度: " << sum / len << endl;
}

void sstf(){
    vector<int> sequence;
    int now = start;
    vector<int> temp = requests;
    while (!temp.empty())
    {
        int min = 0x3f3f3f3f;
        int index = 0;
        for (int i = 0; i < temp.size(); i++){
            if (abs(temp[i] - now) < min){
                min = abs(temp[i] - now);
                index = i;
            }
        }
        sequence.push_back(temp[index]);
        now = temp[index];
        temp.erase(temp.begin() + index);
    }
    print_sequence(sequence);
    double len = request_num;
    double sum = 0;
    now = start;
    for (int i = 0; i < request_num; i++){
        sum += abs(sequence[i] - now);
        now = sequence[i];
    }
    cout << "平均寻道长度: " << sum / len << endl;
}

void scan(){
    vector<int> sequence;
    vector<int> left, right;
    for (int request : requests)
        if (request < start)
            left.push_back(request);
        else
            right.push_back(request);
    sort(left.begin(), left.end(), greater<int>());
    sort(right.begin(), right.end());
    sequence.push_back(start);
    for (int i = 0; i < 2; i++)
        for (int track : (i == 0 ? right : left))
            sequence.push_back(track);

    print_sequence(sequence);

    double len = request_num;
    double sum = 0;
    double now = start;
    for (int i = 0; i < request_num; i++){
        sum += abs(sequence[i] - now);
        now = sequence[i];
    }
    cout << "平均寻道长度: " << sum / len << endl;
}

void cscan(){
    vector<int> sequence;
    vector<int> left, right;
    for (int request : requests)
        if (request < start)
            left.push_back(request);
        else
            right.push_back(request);
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    sequence.push_back(start);
    for (int i = 0; i < 2; i++)
        for (int track : (i == 0 ? right : left))
            sequence.push_back(track);
    print_sequence(sequence);

    double len = request_num;
    double sum = 0;
    double now = start;
    for (int i = 0; i < request_num; i++){
        sum += abs(sequence[i] - now);
        now = sequence[i];
    }
    cout << "平均寻道长度: " << sum / len << endl;
}

int main(){
    system("chcp 65001");
    srand(time(0));
    start = rand() % disk_size;
    int num = 0;

    for (int i = 0; i < request_num; ++i){
        int temp = rand() % disk_size;
        if (temp > disk_size / 2)
            num++;
        if (num > 5)
            temp = rand() % start;
        requests.push_back(temp);
    }
    // 打印请求序列
    cout << "请求序列: " << endl;
    for (int i = 0; i < request_num; i++)
        cout << requests[i] << " ";

    cout << endl;
    cout << "初始磁头位置: " << start << endl;
    while (true){
        cout << "################\n请选择磁盘调度算法:\n"<<"1. FCFS\n"<<"2. SSTF\n"<<"3. SCAN\n"<<"4. CSCAN\n";
        cin >> N;
        if (N < 0 || N > 4){
            cout << "" << endl;
            continue;
        }
        if (N == 1) fcfs();
        if (N == 2) sstf();
        if (N == 3) scan();
        if (N == 4) cscan();
    }
    return 0;
}
