#include <bits/stdc++.h>

using namespace std;

template <typename T>
T power(T a, T b) {
	T res = 1;
	while (b > 0) {
		if (b & 1) {
			res *= a;
		}
		a *= a;
		b >>= 1;
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<long long> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<int> q(m);
	for (int i = 0; i < m; i++) {
		cin >> q[i];
	}
	// sort the sequence in non-increasing order and store the values in a queue ('q1')
	sort(a.rbegin(), a.rend());
	queue<long long> q1, q2;
	for (int i = 0; i < n; i++) {
		q1.push(a[i]);
	}
	// since the 'a[i]' <= (2 ^ 63), then we need to divide it by a total
	// of 63 times, and there are (10 ^ 6) elements, so in total, 63 * (10 ^ 6)
	const int MAX = (int) 63 * power(10, 6);
	vector<long long> ans(MAX + 1, 0);
	// two queues approach
	for (int i = 1; i <= MAX; i++) {
		if (q2.empty()) {
			// if both 'q1' and 'q2' are empty, then break the loop
			// otherwise, retrieve the front element in 'q1' and store its half in 'q2'
			// also don't forget to remove the front element in 'q1'
			if (q1.empty()) {
				break;
			}
			long long x = q1.front();
			q1.pop();
			ans[i] = x;
			q2.push(x / 2);
		} else if (q1.empty()) {
			// if 'q1' is empty, then retrieve the front element in 'q2' and store its half in 'q2' as well
			// also don't forget to remove the front element in 'q2'
			long long x = q2.front();
			q2.pop();
			ans[i] = x;
			q2.push(x / 2);
		} else {
			// otherwise, choose the maximum value between the two front elements of 'q1' and 'q2'
			// and store its half in 'q2', then remove the front element from where it came from
			long long x = q1.front();
			long long y = q2.front();
			if (x > y) {
				ans[i] = x;
				q2.push(x / 2);
				q1.pop();
			} else {
				ans[i] = y;
				q2.push(y / 2);
				q2.pop();
			}
		}
	}
	// output the needed queries
	for (int i = 0; i < m; i++) {
		cout << ans[q[i]] << '\n';
	}
	return 0;
}
