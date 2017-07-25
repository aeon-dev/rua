#pragma once

#include <aeon/streams/file_stream.h>
#include <string>
#include <cstdint>
#include <vector>

namespace rua
{

struct control_signal
{
    std::string mnemonic;
    std::string description;
    std::uint64_t bit_value;
};

class control_signals_parser
{
public:
    control_signals_parser(const std::string &signals_path);
    ~control_signals_parser() = default;

    auto get_control_signals() const -> std::vector<control_signal>;
    auto get_control_signal(const std::string &mnemonic) const -> control_signal;

private:
    void parse_control_lines();
    void parse_line(const std::string &line, const unsigned int line_number);

    auto parse_signal_name(const std::vector<std::string> &line, const unsigned int line_number) const -> std::string;
    auto parse_signal_bitval(const std::vector<std::string> &line, const unsigned int line_number) const
        -> std::uint64_t;
    auto parse_signal_description(const std::vector<std::string> &line, const unsigned int line_number) const
        -> std::string;

    auto from_hex_string(const std::string &str) const -> std::uint64_t;
    aeon::streams::file_stream file_;
    std::vector<control_signal> control_signals_;
};

} // namespace rua
