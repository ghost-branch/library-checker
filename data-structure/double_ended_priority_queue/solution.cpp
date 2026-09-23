#include <set>
#include <vector>
#include <cstdint>
#include <iostream>

std::int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n; std::cin >> n;
    std::size_t q; std::cin >> q;

    std::vector<std::int32_t> v(n);
    for (auto& x : v) {
        std::cin >> x;
    }

    std::multiset<std::int32_t> s(v.begin(), v.end());
    while (q-- > 0) {
        char task; std::cin >> task;

        if (task == '0') {
            std::int32_t x; std::cin >> x;
            s.emplace(x);
            continue;
        }

        if (task == '1') {
            auto it = s.begin();
            std::cout << *it << '\n';
            s.erase(it);
            continue;
        }

        if (task == '2') {
            auto it = std::prev(s.end());
            std::cout << *it << '\n';
            s.erase(it);
        }
    }


    return 0;
}
