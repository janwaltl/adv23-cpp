#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>

const std::string c_file = "data/adv01.txt";
constexpr std::string_view c_digits = "0123456789";
constexpr std::array<std::string_view, 9> c_words{
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
};

static auto
find_digits(const std::string_view str) {
    auto first = str.find_first_of(c_digits);
    auto last = str.find_last_of(c_digits);
    return std::pair{first, last};
}

static auto
find_words(const std::string_view str) {
    std::size_t first = str.npos;
    std::size_t first_i = 0;
    std::size_t last = str.npos;
    std::size_t last_i = 0;
    for (std::size_t i = 0; i < c_words.size(); ++i) {
        auto pos = str.find(c_words[i]);
        if (pos != str.npos && pos < first) {
            first = pos;
            first_i = i;
        }
        pos = str.rfind(c_words[i]);
        if (pos != str.npos && (last == str.npos || pos > last)) {
            last = pos;
            last_i = i;
        }
    }
    return std::tuple{first, last, first_i + 1, last_i + 1};
}
static void
part1() {
    std::ifstream infile{c_file};

    std::size_t sum = 0;
    std::string line;
    while (std::getline(infile, line)) {
        auto [first, last] = find_digits(line);

        if (first != line.npos)
            sum += static_cast<std::size_t>(line[first] - '0') * 10;

        if (last != line.npos)
            sum += static_cast<std::size_t>(line[last] - '0');
    }

    std::cout << "Sum is " << sum << '\n';
}

static void
part2() {
    std::ifstream infile{c_file};

    std::size_t sum = 0;
    std::string line;
    while (std::getline(infile, line)) {
        auto [dfirst, dlast] = find_digits(line);
        auto [wfirst, wlast, ifirst, ilast] = find_words(line);
        auto first = std::min(dfirst, wfirst);

        if (first != line.npos)
            sum += 10 * (wfirst == first
                             ? ifirst
                             : static_cast<std::size_t>(line[first] - '0'));

        auto last = std::max(dlast, wlast);
        if (last == line.npos)
            last = std::min(dlast, wlast);

        if (last != line.npos)
            sum += wlast == last ? ilast
                                 : static_cast<std::size_t>(line[last] - '0');
        std::cout << "LINE" << line[first] << line[last] << ' ' << dlast << ' '
                  << wlast << '\n';
    }

    std::cout << "Sum is " << sum << '\n';
}

int
main() {
    part1();
    part2();
    return 0;
}
