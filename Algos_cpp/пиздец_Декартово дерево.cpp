#include <bits/stdc++.h>
#include <chrono>
#include <random>
using namespace std;
//std::mt19937
//rng(std::chrono::steady_clock::now().time_since_epoch().count());
mt19937 rng(1);
int INF = 1e9 + 7;
using ll = long long int;
struct node {
	node* left;
	node* right;
	int x;
	ll y;
	int val;
	int max_val;
	bool rev;

	node(int _val) : val(_val), max_val(_val) {
		left = nullptr;
		right = nullptr;
		x = 1;
		y = rng();
		rev = false;
	}
};
using treap = node*;

int getx(treap t) {
	return (t == nullptr ? 0 : t->x);
}
int get_max(treap t) {
	return (t == nullptr ? -INF : t->max_val);
}

void update(treap t) {
	if (t == nullptr) {
		return;
	}
	t->x = 1 + getx(t->left) + getx(t->right);
	t->max_val = t->val;
	t->max_val = max(t->max_val, get_max(t->left));
	t->max_val = max(t->max_val, get_max(t->right));
}
void reverse(treap& t) {
	if (t == nullptr) {
		return;
	}
	t->rev = t->rev ^ 1;
}
void push(treap t) {
	if (t == nullptr || t->rev == false) {
		return;
	}
	t->rev = false;
	swap(t->left, t->right);
	reverse(t->left);
	reverse(t->right);
}
void split(treap t, int x0, treap& t1, treap& t2) {
	if (t == nullptr) {
		t1 = nullptr;
		t2 = nullptr;
		return;
	}
	push(t);
	int szleft = 1 + getx(t->left);
	if (x0 >= szleft) {
		split(t->right, x0 - szleft, t->right, t2);
		t1 = t;
	}
	else {
		split(t->left, x0, t1, t->left);
		t2 = t;

	}
	update(t);
}


treap merge(treap t1, treap t2) {
	if (t1 == nullptr) {
		return t2;
	}
	if (t2 == nullptr) {
		return t1;
	}
	if (t1->y > t2->y) {
		push(t1);
		t1->right = merge(t1->right, t2);
		update(t1);

		return t1;
	}
	else {
		push(t2);
		t2->left = merge(t1, t2->left);
		update(t2);
		return t2;
	}
}
void print_t(treap t, int h) {
	if (t == nullptr) {
		return;
	}
	print_t(t->left, h + 1);
	cout << t->val << ' ';
	print_t(t->right, h + 1);
}

void print(treap t) {
	print_t(t, 0);
}
void print_c(treap t, int h) {
	if (t == nullptr) {
		return;
	}
	print_t(t->left, h + 1);
	cout << t->val << ' ';
	print_t(t->right, h + 1);
}
void printc(treap t) {
	print_c(t, 0);
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	treap t = nullptr;
	int n;
	cin >> n;
	int q;
	cin >> q;
	for (int i = 0; i < n; i++) {
		int z = 0;
		cin >> z;
		treap l, r;
		treap m = new node(z);
		split(t, i, l, r);
		t = merge(merge(l, m), r);
	}
	
	while (q--) {
		int cs;
		cin >> cs;
		if (cs == 1) {
			int l, r;
			cin >> l >> r;
			treap tl, tr, tm;
			split(t, r, tm, tr);
			split(tm, l - 1, tl, tm);
			reverse(tm);
			t = merge(merge(tl, tm), tr);

		}
		else if (cs == 2) {
			int l, r;
			cin >> l >> r;
			treap tl = nullptr, tm = nullptr, tr = nullptr;
			split(t, r, tm, tr);
			split(tm, l - 1, tl, tm);
			cout << get_max(tm) << '\n';
			t = merge(merge(tl, tm), tr);
		}
	}
}