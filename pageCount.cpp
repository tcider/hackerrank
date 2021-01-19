#include <bits/stdc++.h>

using namespace std;

/*
 * Complete the pageCount function below.
 */
int pageCount(int n, int p) {
    /*
     * Write your code here.
     */
    vector <int> pages;
    int page;

    for (int i = 0; i <= n; i += 2)
        pages.push_back(i);

    for (int i = 0; i < pages.size(); i++)
        if (pages.at(i) == p || pages.at(i) + 1 == p)
        {
            page = i;
            break;
        }

    if (page < pages.size() - 1 - page)
        return page;
    else
        return pages.size() - page - 1;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int p;
    cin >> p;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int result = pageCount(n, p);

    fout << result << "\n";

    fout.close();

    return 0;
}

