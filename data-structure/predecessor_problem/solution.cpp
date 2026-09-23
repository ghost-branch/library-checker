#include <vector>
#include <cstdint>
#include <optional>
#include <iostream>

template<typename T>
class Fenwick {
private:
    std::size_t n_;
    std::size_t top_bit_;
    std::vector<T> bit_;

    static std::size_t lsb(std::size_t pos) {
        return pos & -pos;
    }

    void init_top_bit() {
        while ((top_bit_ << 1) <= n_) {
            top_bit_ <<= 1;
        }
    }

public:
    explicit Fenwick(std::string_view s)
        : n_{s.size()}, top_bit_{1}, bit_(n_ + 1) {

        init_top_bit();

        for (std::size_t i = 1; i <= n_; ++i) {
            bit_[i] += static_cast<T>(s[i - 1] - '0');

            const std::size_t parent = i + lsb(i);

            if (parent <= n_) {
                bit_[parent] += bit_[i];
            }
        }
    }

    void add(std::size_t pos, std::int32_t delta) {
        for (++pos; pos <= n_; pos += lsb(pos)) {
            bit_[pos] += delta;
        }
    }

    T query(std::size_t pos) const {
        T res{};
        for (++pos; pos > 0; pos -= lsb(pos)) {
            res += bit_[pos];
        }
        return res;
    }

    T query(std::size_t left, std::size_t right) {
        return query(right) - (left? query(left - 1) : T{});
    }

    std::size_t kth(std::size_t k) const {
        std::size_t pos{};

        for (std::size_t step = top_bit_; step; step >>= 1) {
            std::size_t next = pos + step;
            if (next <= n_ && bit_[next] < k) {
                pos = next;
                k -= bit_[next];
            }
        }

        return pos;
    }
};

class PredecessorSet {
private:
    std::size_t size_;
    Fenwick<std::size_t> fen_;
    std::vector<bool> present_;

public:
    PredecessorSet(std::string_view s)
        : size_{}, fen_{s}, present_(s.size()) {

        for (std::size_t i = 0; i < s.size(); ++i) {
            present_[i] = (s[i] == '1');
            size_ += present_[i];
        }
    };

    void insert(std::size_t pos) {
        if (!present_[pos]) {
            ++size_;
            present_[pos] = true;
            fen_.add(pos, 1);
        }
    }

    void erase(std::size_t pos) {
        if (present_[pos]) {
            --size_;
            present_[pos] = false;
            fen_.add(pos, -1);
        }
    }

    bool contains(std::size_t pos) const {
        return present_[pos];
    }

    std::optional<std::size_t> successor(std::size_t pos) const {
        if (present_[pos]) {
            return pos;
        }

        const std::size_t before = pos? fen_.query(pos - 1) : 0;

        if (before == size_) {
            return std::nullopt;
        }

        return fen_.kth(before + 1);
    }

    std::optional<std::size_t> predecessor(std::size_t pos) const {
        if (present_[pos]) {
            return pos;
        }

        const std::size_t count = fen_.query(pos);

        if (count == 0) {
            return std::nullopt;
        }

        return fen_.kth(count);
    }

};

std::int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::size_t n; std::cin >> n;
    std::size_t q; std::cin >> q;
    std::string s; std::cin >> s;


    PredecessorSet set(s);

    while (q-- > 0) {
        std::uint8_t task; std::cin >> task;
        std::size_t k; std::cin >> k;

        switch (task) {
            case '0': {
                set.insert(k);
                break;
            }

            case '1': {
                set.erase(k);
                break;
            }

            case '2': {
                std::cout << set.contains(k) << '\n';
                break;
            }

            case '3': {
                auto res = set.successor(k);
                std::cout << (res? static_cast<std::int32_t>(*res) : -1) << '\n';
                break;
            }

            case '4': {
                auto res = set.predecessor(k);
                std::cout << (res? static_cast<std::int32_t>(*res) : -1) << '\n';
                break;
            }
        }
    }

    return 0;
}

