/*Написанная реализация решает задачи :

- Минимум/максимум на отрезке
- Сумма на отрезке
- НОД на отрезке
- НОК на отрезке
- Подсчет кол-ва нулей, единиц, других чисел
- Поиск k-го числа(решение во второй части)
*/

#include <bits/stdc++.h>

using namespace std;

//1-индексация!
struct segtree {
	//id - вершина!
	int n;
	vector<int> data;
	segtree(int _n) : n(_n), data(4 * _n){}
	segtree(const vector<int>& a) : segtree(a.size()) {
		build(1, 1, n, a);
	}
	void build(int id, int l, int r, const vector<int>& a) {
		if (l == r)
		{
			data[id] = a[l - 1];
			return;
		}
		int m = (l + r) / 2;
		build(id * 2, l, m, a);
		build(id * 2 + 1, m + 1, r, a);
//ОПЕРАЦИЯ
		data[id] = data[id * 2] + data[id * 2 + 1];
	}
	//p - position (1-индексация!)
	//x - value
	void set(int p, int x) {
		set(1, 1, n, p,x);
	}
	void set(int id, int l, int r, int p, int x) {
		if (l == r)
		{
//ОПЕРАЦИЯ
			data[id] = x;
			return;
		}
		int m = (l + r) / 2;
		if (p <= m) {
			set(id * 2, l, m, p, x);
		}
		else {
			set(id * 2 + 1, m + 1, r, p, x);
		}
//ОПЕРАЦИЯ
		data[id] = data[id * 2] + data[id * 2 + 1];
	}
	//[ql;qr] 
	//1 - индексация!
	int get(int ql, int qr) {
		return get(1, 1, n, ql, qr);
	}
	int get(int id, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) {
			return data[id];
		}
		int m = (l + r) / 2;
		if (qr <= m) {
			return get(id * 2, l, m, ql, qr);
		}
		if (ql >= m + 1) {
			return get(id * 2 + 1, m + 1, r, ql, qr);
		}
//ОПЕРАЦИЯ
		return get(id * 2, l, m, ql, qr) + 
			get(id * 2 + 1, m + 1, r, ql, qr);

	}
};
void MAINMAIN() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	segtree st(a);
	int q;
	cin >> q;
	while (q--) {
		int t;
		cin >> t;
		if (t == 1) {
			int l, r;
			cin >> l >> r;
			//1-индексация!!!
			cout << st.get(l, r) << '\n';;
		}
		else if (t == 2) {
			int p, x;
			cin >> p >> x;
			st.set(p, x);
		}
	}
}

struct pi {
	int l, r;
	int pos;
};
bool compare(pi a, pi b) {
	return a.r < b.r;
}
void coutseg(segtree seg, int n) {
	for (int i = 1; i <= n; i++) {
		cout << seg.get(i, i) << ' ';
	}
	cout << '\n';
}

void ZADACHA() {
	//задача
		//на запрос ql qr выдать кол-во различных чисел 
		int n;
	cin >> n;
	vector<int> a(n);//массив чисел;
	segtree seg(a);
	unordered_map<int, int> mem;//key = значение, value = index;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int q;
	cin >> q;
	vector<pi> qvec(q);
	for (int t = 0; t < q; t++) {
		int l, r;
		//1-индексация
		cin >> l >> r;
		qvec[t] = { l,r, t};
	}
	sort(qvec.begin(), qvec.end(), compare);
	int pointerPrefix = 0;
	vector<int> results(q);
	for (int i = 0; i < qvec.size(); i++) {
		while (pointerPrefix < qvec[i].r) {
			if (!mem.contains(a[pointerPrefix])) {
				mem[a[pointerPrefix]] = pointerPrefix;
				seg.set(pointerPrefix + 1, 1);
			}
			else {
				int pred = mem[a[pointerPrefix]];
				mem[a[pointerPrefix]] = pointerPrefix;
				seg.set(pointerPrefix + 1, 1);
				seg.set(pred + 1, 0);
			}
			pointerPrefix++;
		}
		results[qvec[i].pos] = seg.get(qvec[i].l, qvec[i].r);
	}
	for (int i = 0; i < results.size(); i++) {
		cout << results[i] << '\n';
	}
}

//Ленивое ДО
struct segtree2 {
	int n;
	vector<int> data, delay;

	segtree2(const vector<int>& v) : n(v.size()), data(4*n), delay(4*n) {
		build(1, 1, n, v);
	}
	segtree2(int _n) : n(_n), data(4 * n), delay(4 * n) {}

	void build(int id, int l, int r, const vector<int>& v) {
		if (l == r) {
			data[id] = v[l - 1];
			return;
		}
		int m = (l + r) / 2;
		build(id * 2, l, m, v);
		build(id * 2 + 1, m + 1, r, v);
		data[id] = max(data[id * 2], data[id * 2 + 1]);
	}
	void push(int id) {
		if (delay[id] == 0)
			return;
		if (id * 2 < 4 * n) {
			delay[id * 2] += delay[id];
		}
		if (id * 2 + 1 < 4 * n) {
			delay[id * 2 + 1] += delay[id];
		}
		data[id] += delay[id];
		delay[id] = 0;
	}
	void set(int p, int x) {
		set(1, 1, n, p, x);
	}
	void set(int id, int l, int r, int p, int x) {
		if (l == r) {
			data[id] = x;
			return;
		}
		push(id);
		int m = (l + r) / 2;
		if (p <= m) {
			set(id * 2, l, m, p, x);
		}
		else {
			set(id * 2 + 1, m + 1, r, p, x);
		}
		data[id] = max(data[id * 2], data[id * 2 + 1]);
	}
	int get(int l, int r) {
		return get(1, 1, n, l, r);
	}
	int get(int id, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) {
			return  data[id];
		}
		push(id);
		int m = (l + r) / 2;
		if (qr <= m) {
			return get(id * 2, l, m, ql, qr);
		}
		if (ql > m) {
			return get(id * 2 + 1, m + 1, r, ql, qr);
		}
		return max(get(id * 2, l, m, ql, qr),
			get(id * 2 + 1, m + 1, r, ql, qr));
	}
	void update(int l, int r, int x) {
		update(1, 1, n, l, r, x);
	}
	void update(int id, int l, int r, int ql, int qr, int x) {
		if (ql > r || qr < l)
			return;
		if (ql <= l && r <= qr) {
			delay[id] += x;
			push(id);
			return;
		}
		int m = (l + r) / 2;
		update(id * 2, l, m, ql, qr, x);
		update(id * 2 + 1, m + 1, r, ql, qr, x);
		data[id] = max(data[id * 2], data[id * 2 + 1]);
	}

};
struct segtree4 {
	int n;
	vector<int> data;
	segtree4(int _n) : n(_n), data(4*_n){}
	segtree4(const vector<int>& a) : segtree4(a.size()) {
		build(1, 1, n, a);
	}
	void build(int id, int l, int r, const vector<int>& a) {
		if (l == r) {
			data[id] = a[l - 1];
			return;
		}
		int m = (l + r) / 2;
		build(id * 2, l, m, a);
		build(id * 2 + 1, m + 1, r, a);
		data[id] = min(data[id * 2], data[id * 2 + 1]);
	}
	void set(int p, int x) {
		set(1, 1, n, p, x);
	}
	void set(int id, int l, int r, int p, int x) {
		if (l == r) {
			data[id] = x;
			return;
		}
		int m = (l + r) / 2;
		if (p <= m) {
			set(id * 2, l, m, p, x);
		}
		else {
			set(id * 2 + 1, m + 1, r, p, x);
		}
		data[id] = min(data[id * 2], data[id * 2 + 1]);
	}

	int get(int ql, int qr) {
		return get(1, 1, n, ql, qr);
	}
	int get(int id, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) {
			return data[id];
		}
		int m = (l + r) / 2;
		if (qr <= m) {
			return get(id * 2, l, m, ql, qr);
		}
		if (ql > m) {
			return get(id * 2 + 1, m + 1, r, ql, qr);
		}
		return min(get(id * 2, l, m, ql, qr), get(id * 2 + 1, m + 1, r, ql, qr));
	}
};


void MAIN4(){
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	segtree4 st(a);
	int q;
	cin >> q;
	while (q--) {
		int t;
		cin >> t;
		if (t == 1) {
			int l, r;
			cin >> l >> r;
			cout << st.get(l, r) << '\n';
		}
		else if (t == 2)
		{
			int p, x;
			cin >> p >> x;
			st.set(p, x);
		}
	}
}




void MAIN2() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	segtree2 st(a);
	int q;
	cin >> q;
	while (q--) {
		int t;
		cin >> t;
		if (t == 1) {
			int l, r;
			cin >> l >> r;
			cout << st.get(l, r) << endl;
		}
		else if (t == 2) {
			int p, x;
			cin >> p >> x;
			st.set(p, x);
		}
		else if (t == 3) {
			int l, r, x;
			cin >> l >> r >> x;
			st.update(l, r, x);

		}
	}
}

struct segtree3 {
	struct node {
		node* left = nullptr;
		node* right = nullptr;
		int data;
		node(int v) : data(v) {}
	};
	using ptr = node*;//pointer
	int n;
	ptr root = nullptr;
	segtree3(int _n) : n(_n) {
		root = new node(0);
	}
	int get(int l, int r) {
		return get(root, 1, n, l, r);
	}
	int get(ptr u, int l, int r, int ql, int qr) {
		if (u == nullptr) {
			return 0;
		}
		if (ql <= l and r <= qr) {
			return u->data;
		}
		int m = (l + r) / 2;
		if (qr <= m) {
			return get(u->left, l, m, ql, qr);
		}
		if (ql > m) {
			return get(u->right, m + 1, r, ql, qr);
		}
		return max(get(u->left, l, m, ql, qr),
			get(u->right, m + 1, r, ql, qr));
	}
	int get_data(ptr u) {
		if (u == nullptr) {
			return 0;
		}
		else {
			return u->data;
		}
	}
	void set(int p, int x) {
		root = set(root, 1, n, p, x);
	}
	ptr set(ptr u, int l, int r, int p, int x) {
		if (u == nullptr) {
			u = new node(0);
		}
		if (l == r) {
			u->data = x;
			return u;
		}
		int m = (l + r) / 2;
		if (p <= m) {
			u->left = set(u->left, l, m, p, x);
		}
		else {
			u->right = set(u->right, m + 1, r, p, x);
		}
		u->data = max(get_data(u->left), 
			get_data(u->right));
		return u;
	}
};
void MAIN3() {
	int n, q;
	cin >> n >> q;
	segtree3 st(n);
	while (q--) {
		int t;
		cin >> t;
		if (t == 1) {
			int l, r;
			cin >> l >> r;
			cout << st.get(l, r) << '\n';
		}
		else if (t == 2) {
			int p, x;
			cin >> p >> x;
			st.set(p, x);
		}
	}
}

struct segtree5 {
	struct node {
		node* left = nullptr;
		node* right = nullptr;
		int data;
		node(int v) : data(v) {}
	};
	using ptr = node*;//pointer
	int n;
	vector<ptr> vers;
	
	segtree5(const vector<int>& v) : n(v.size()) {
		ptr root = build(1, n, v);
		vers.push_back(root);
	}
	ptr build(int l, int r, const vector<int>& v) {
		ptr u = new node(0);
		if (l == r) {
			u->data = v[l - 1];
			return u;
		}
		int m = (l + r) / 2;
		u->left = build(l, m, v);
		u->right = build(m + 1, r, v);
		u->data = u->left->data ^ u->right->data;
		return u;
	}
	ptr copy(ptr u) {
		ptr v = new node(u->data);
		v->left = u->left;
		v->right = u->right;
		return v;
	}
	int get(int k, int l, int r) {
		return get(vers[k-1], 1, n, l, r);
	}
	int get(ptr u, int l, int r, int ql, int qr) {
		if (ql <= l and r <= qr) {
			return u->data;
		}
		int m = (l + r) / 2;
		if (qr <= m) {
			return get(u->left, l, m, ql, qr);
		}
		if (ql > m) {
			return get(u->right, m + 1, r, ql, qr);
		}
		return get(u->left, l, m, ql, qr) ^
			get(u->right, m + 1, r, ql, qr);
	}
	int get_data(ptr u) {
		if (u == nullptr) {
			return 0;
		}
		else {
			return u->data;
		}
	}
	void set(int k, int p, int x) {
		ptr newroot = set(vers[k - 1], 1, n, p, x);
		vers.push_back(newroot);
	}
	ptr set(ptr u, int l, int r, int p, int x) {
		u = copy(u);
		if (l == r) {
			u->data = x;
			return u;
		}
		int m = (l + r) / 2;
		if (p <= m) {
			u->left = set(u->left, l, m, p, x);
		}
		else {
			u->right = set(u->right, m + 1, r, p, x);
		}
		u->data = u->left->data ^
			u->right-> data;
		return u;
	}
};
void MAIN5() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	segtree5 st(a);
	int q;
	cin >> q;
	while (q--) {
		int t;
		cin >> t;
		if (t == 1) {
			int k, p;
			cin >> k >> p;
			cout << st.get(k, p, p) << '\n';
		}
		else if (t == 2) {
			int k, p, x;
			cin >> k >> p >> x;
			st.set(k, p, x);
		}
	}
}
int main() {
	MAIN5();
}

