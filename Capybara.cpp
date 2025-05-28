#include <bits/stdc++.h>
using namespace std;

struct Tower {
    long long pos, power, range;
    long long left, right; // coverage range
    int maxOverlap;
    
    Tower(long long p, long long pow, long long r) : pos(p), power(pow), range(r) {
        left = pos - range;
        right = pos + range;
        maxOverlap = 1;
    }
};

struct Event {
    long long coord;
    int type; // 1 for start, -1 for end
    int towerIdx;
    
    Event(long long c, int t, int idx) : coord(c), type(t), towerIdx(idx) {}
    
    bool operator<(const Event& other) const {
        if (coord != other.coord) return coord < other.coord;
        return type > other.type; // Process starts before ends at same coordinate
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<Tower> towers;
    vector<Event> events;
    
    for (int i = 0; i < n; i++) {
        long long pos, power, range;
        cin >> pos >> power >> range;
        
        towers.push_back(Tower(pos, power, range));
        
        // Add events for sweep line
        events.push_back(Event(pos - range, 1, i));  // start of range
        events.push_back(Event(pos + range + 1, -1, i)); // end of range (exclusive)
    }
    
    sort(events.begin(), events.end());
    
    // Sweep line to find maximum overlap for each tower
    set<int> activeTowers;
    int eventIdx = 0;
    
    for (int i = 0; i < n; i++) {
        int overlapCount = 1; // Count itself
        
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            
            // Check if tower j overlaps with tower i
            long long left1 = towers[i].left, right1 = towers[i].right;
            long long left2 = towers[j].left, right2 = towers[j].right;
            
            // Two ranges overlap if max(left1, left2) <= min(right1, right2)
            if (max(left1, left2) <= min(right1, right2)) {
                overlapCount++;
            }
        }
        
        towers[i].maxOverlap = overlapCount;
    }
    
    // Calculate total effective defense strength
    long long totalDefense = 0;
    
    for (int i = 0; i < n; i++) {
        long long effectivePower = towers[i].power / towers[i].maxOverlap;
        totalDefense += effectivePower;
    }
    
    cout << totalDefense << endl;
    
    return 0;
}