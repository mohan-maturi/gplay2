#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

struct lifeguard {
    int start;
    int end;
};

bool cmp (lifeguard &a, lifeguard &b) {
    if (a.start < b.start) {
        return true;
    }
    else if (a.start == b.start) {
        if (a.end < b.end) {
            return true;
        }
    }
    return false;
}

int main() {
    ifstream fin ("lifeguards.in");
    ofstream fout ("lifeguards.out");
    int n;
    fin >> n;
    lifeguard lifeguards[n];
    for (int i = 0; i < n; i++) {
        fin >> lifeguards[i].start >> lifeguards[i].end;
    }
    
    sort(lifeguards, lifeguards+n, cmp);
    
    int total_hours = 0;
    int start_hour = 0;
    for (int i = 0; i < n; i++) {
        int new_start_hour = max(lifeguards[i].start, start_hour);
        if (lifeguards[i].end > new_start_hour) {
            total_hours += lifeguards[i].end - new_start_hour;
            start_hour = lifeguards[i].end;
        }
    }
    cout << "Total hours is " << total_hours << endl;
    
    int min_loss = 2147483647;
    int start_idx = 0;
    for (int i = 0; i < n; i++) {
        cout << "** " << lifeguards[i].start << "," << lifeguards[i].end << endl;
        // bump up the starting index
        while (lifeguards[start_idx].end < lifeguards[i].start) {
            start_idx++;
        }
        int loss = 0;
        int begin = lifeguards[i].start;
        int j = start_idx;
        for (; j < n; j++) {
            if (j == i) {
                // skip comparing it with itself
                continue;
            }
            if (lifeguards[j].start > lifeguards[i].end) {
                // the jth begin is after the current end, non overlapping
                // add remaning loss
                loss += lifeguards[i].end - begin;
                break;
            }
            if (lifeguards[j].start > begin) {
                loss += lifeguards[j].start - begin;
            }
            begin = min(lifeguards[i].end, lifeguards[j].end);
            if (begin >= lifeguards[i].end) {
                // done with this lifegaurd, move to the next one
                break;
            }
        }
        if (j == n) {
            loss += lifeguards[i].end - begin;
        }
        cout << loss <<  endl;
        // reset min_loss if this is the new loss
        min_loss = min(min_loss, loss);
        // log the minimum loss as of now
        cout << min_loss << endl;
    }
    fout << (total_hours - min_loss) << endl;
    return 0;
}
