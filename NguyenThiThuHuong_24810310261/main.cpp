#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100;
const int INF  = 1000000000;

int A[MAXN][MAXN];   // ma trận trọng số
int n;               // số đỉnh

// Câu 2: Nhập đồ thị từ file, lưu vào ma trận A
bool Nhap(const char* tenFile)
{
    ifstream f(tenFile);
    if (!f)
    {
        cout << "Khong mo duoc file " << tenFile << endl;
        return false;
    }
    f >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            f >> A[i][j];
    f.close();
    return true;
}

// Câu 3: Hiển thị đồ thị (ma trận trọng số) ra màn hình
void HienThi()
{
    cout << "So dinh: " << n << endl;
    cout << "Ma tran trong so:" << endl;
    cout << "     ";
    for (int j = 0; j < n; j++)
        cout << setw(5) << ("V" + to_string(j + 1));
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << setw(5) << ("V" + to_string(i + 1));
        for (int j = 0; j < n; j++)
            cout << setw(5) << A[i][j];
        cout << endl;
    }
}

// Câu 4: Tìm đường đi ngắn nhất từ đỉnh u đến đỉnh v (Dijkstra)
// u, v đánh số từ 1 (V1, V2, ...)
void TimDuongDi(int u, int v)
{
    u--; v--;                       // chuyển về chỉ số 0
    int  d[MAXN], truoc[MAXN];
    bool daXet[MAXN];

    for (int i = 0; i < n; i++)
    {
        d[i] = INF;
        truoc[i] = -1;
        daXet[i] = false;
    }
    d[u] = 0;

    for (int k = 0; k < n; k++)
    {
        // chọn đỉnh chưa xét có d nhỏ nhất
        int x = -1;
        for (int i = 0; i < n; i++)
            if (!daXet[i] && d[i] < INF && (x == -1 || d[i] < d[x]))
                x = i;
        if (x == -1) break;
        daXet[x] = true;
        if (x == v) break;

        // cập nhật (relax) các đỉnh kề của x
        for (int y = 0; y < n; y++)
            if (A[x][y] > 0 && !daXet[y] && d[x] + A[x][y] < d[y])
            {
                d[y] = d[x] + A[x][y];
                truoc[y] = x;
            }
    }

    if (d[v] == INF)
    {
        cout << "Khong co duong di tu V" << u + 1 << " den V" << v + 1 << endl;
        return;
    }

    // truy vết đường đi
    vector<int> path;
    for (int i = v; i != -1; i = truoc[i])
        path.push_back(i);
    reverse(path.begin(), path.end());

    cout << "Duong di ngan nhat tu V" << u + 1 << " den V" << v + 1 << ": ";
    for (size_t i = 0; i < path.size(); i++)
    {
        cout << "V" << path[i] + 1;
        if (i + 1 < path.size()) cout << " -> ";
    }
    cout << endl;
    cout << "Do dai: " << d[v] << endl;
}

// Câu 5
int main()
{
    if (!Nhap("Grap.txt"))
        return 1;
    HienThi();
    TimDuongDi(1, 6);   // từ V1 đến V6
    return 0;
}
