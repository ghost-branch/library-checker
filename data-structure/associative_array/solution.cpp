#include <cstdint>
#include <iostream>
#include <unordered_map>

std::int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t q; std::cin >> q;
    std::unordered_map<std::uint64_t, std::uint64_t> cache(q);

    while (q-- > 0) {
        std::uint8_t type; std::cin >> type;

        if (type == '0') {
            std::uint64_t k; std::cin >> k;
            std::uint64_t v; std::cin >> v;
            cache[k] = v;
            continue;
        }

        std::uint64_t k; std::cin >> k;
        auto it = cache.find(k);
        std::cout << (it != cache.end()? it->second : 0);
        std::cout << '\n';
    }

    return 0;
}

