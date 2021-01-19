#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

// Complete the countLuck function below.

int     Search(vector<string> arr, int i, int j, int sum, char b)
{
    int u = 0;
    int l = 0;
    int r = 0;
    int d = 0;

    if (arr[i][j] == '*')
        return sum;
    else {
        if (b != 'u' && i > 0 && (arr[i - 1][j] == '.' || arr[i - 1][j] == '*'))
            u = 1;
        if (b != 'd' && i < arr.size() - 1 && (arr[i + 1][j] == '.' || arr[i + 1][j] == '*'))
            d = 1;
        if (b != 'l' && j > 0 && (arr[i][j - 1] == '.' || arr[i][j - 1] == '*'))
            l = 1;
        if (b != 'r' && j < arr[i].length() - 1 && (arr[i][j + 1] == '.' || arr[i][j + 1] == '*'))
            r = 1;
        if (u + l + r + d > 1)
            sum++;
        if (u + l + r + d == 0)
            return 0;
        
        if (u)
            return Search(arr, i - 1, j, sum, 'd');
        if (d)
            return Search(arr, i + 1, j, sum, 'u');
        if (l)
            return Search(arr, i, j - 1, sum, 'r');
        if (r)
            return Search(arr, i, j + 1, sum, 'l');
        
    }
    return sum;
}

string countLuck(vector<string> matrix, int k) {
    int i = -1;
    int j;
    int sum = 0;
    static string yes = "Impressed";
    static string no = "Oops!";

    while (++i < matrix.size())
    {
        j = -1;
        while (++j < matrix[i].length())
        {
            if (matrix[i][j] == 'M')
                sum = Search(matrix, i, j, sum, 'b'); 
        }    
    }
    cout << sum;
    if (sum == k)
        return yes;
    return no;

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string nm_temp;
        getline(cin, nm_temp);

        vector<string> nm = split_string(nm_temp);

        int n = stoi(nm[0]);

        int m = stoi(nm[1]);

        vector<string> matrix(n);

        for (int i = 0; i < n; i++) {
            string matrix_item;
            getline(cin, matrix_item);

            matrix[i] = matrix_item;
        }

        int k;
        cin >> k;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string result = countLuck(matrix, k);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}

