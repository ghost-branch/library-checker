#include <vector>
#include <cstdint>
#include <iostream>
#include <optional>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>

template<typename T>
using ordered_set = __gnu_pbds::tree <
    T,
    __gnu_pbds::null_type,
    std::less<T>,
    __gnu_pbds::rb_tree_tag,
    __gnu_pbds::tree_order_statistics_node_update
>;

template<typename T>
class OrderedSet {
private:
    ordered_set<T> s;
public:
    using Elements = std::vector<std::int32_t>;
    explicit OrderedSet(const Elements& elements) {
        for (auto& x : elements) {
            s.insert(x);
        }
    }

    void insert(T x) {
        s.insert(x);
    }

    void remove(T x) {
        s.erase(x);
    }

    std::int32_t kth(std::size_t k) const {
        if (s.size() < k) {
            return -1;
        }

        auto it = s.find_by_order(k - 1);
        return *it;
    }

    std::size_t count_leq(T x) const {
        return s.order_of_key(x + 1);
    }

    std::optional<T> successor(T x) const {
        auto it = s.lower_bound(x);

        if (it == s.end()) {
            return std::nullopt;
        }

        return *it;
    }

    std::optional<T> predecessor(T x) const {
        auto it = s.upper_bound(x);

        if (it == s.begin()) {
            return std::nullopt;
        }

        return *std::prev(it);
    }
};

std::int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n; std::cin >> n;
    std::size_t q; std::cin >> q;

    std::vector<std::int32_t> elements(n);
    for (auto& x : elements) {
        std::cin >> x;
    }

    OrderedSet<std::int32_t> oset(elements);
    while (q-- > 0) {
        char task; std::cin >> task;
        std::int32_t x; std::cin >> x;
        switch (task) {
            case '0': {
                oset.insert(x);
                break;
            }

            case '1': {
                oset.remove(x);
                break;
            }

            case '2': {
                std::cout << oset.kth(x) << '\n';
                break;
            }

            case '3': {
                std::cout << oset.count_leq(x) << '\n';
                break;
            }

            case '4': {
                auto it = oset.predecessor(x);
                std::cout << it.value_or(-1) << '\n';
                break;
            }

            case '5': {
                auto it = oset.successor(x);
                std::cout << it.value_or(-1) << '\n';
                break;
            }
        }
    }

    return 0;
}
