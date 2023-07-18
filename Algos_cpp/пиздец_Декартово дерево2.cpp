#include <bits/stdc++.h>
#include <chrono>
#include <random>
using namespace std;
//std::mt19937
//rng(std::chrono::steady_clock::now().time_since_epoch().count());
mt19937 rng(1);

using ll = long long int;
struct node {
	node* left;
	node* right;
	int x;
	ll y;
	int val;


	node(int _val) : val(_val) {
		left = nullptr;
		right = nullptr;
		x = 1;
		y = rng();
	}
};
using treap = node*;

int getx(treap t) {
	return (t == nullptr ? 0 : t->x);
}


void update(treap t) {
	if (t == nullptr) {
		return;
	}
	t->x = 1 + getx(t->left) + getx(t->right);
}

void split(treap t, int x0, treap& t1, treap& t2) {
	if (t == nullptr) {
		t1 = nullptr;
		t2 = nullptr;
		return;
	}
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
		t1->right = merge(t1->right, t2);
		update(t1);

		return t1;
	}
	else {
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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	treap t = nullptr;
	int q;
	cin >> q;
	while (q--) {
		int p, x;
		cin >> x >> p;
		treap l, r;
		split(t, p, l, r);
		treap m = new node(x);
		t = merge(merge(l, m), r);
	}
	print(t);
	//treap t = nullptr;
	//int n;
	//cin >> n;
	//for (int i = 0; i < n; i++) {
	//	int a;
	//	cin >> a;
	//	treap m = new node(a);
	//	t = merge(t, m);
	//}
	//ДОПИСАТЬ
	//int q;
	//cin >> q;
	//while (q--) {
	//	int l, r;
	//	cin >> l >> r;
	//	treap tl, tm, tr;
	//	split(t, r, tm, tr);
	//	split(tm, l - 1, tl, tm);
	//	merge(merge(tm, tl), tr);
	//	print(t);
	//}

}