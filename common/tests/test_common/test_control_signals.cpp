#include <gtest/gtest.h>
#include <control_signals.cpp>

static void check_from_str(const std::string &value, const std::uint32_t expected)
{
    EXPECT_EQ(expected, cs::from_multi_string(value));
}

static void check_conversion(const std::uint32_t value)
{
    auto str = cs::to_multi_string(value);
    auto new_val = cs::from_multi_string(str);
    EXPECT_EQ(value, new_val);
}

TEST(test_control_signals, test_from_multi_string)
{
    check_from_str("ai bo", cs::ai | cs::bo);
    check_from_str("ao bi", cs::ao | cs::bi);
    check_from_str("mo spi pcp", cs::mo | cs::spi | cs::pcp);
    check_from_str("alm0 alm1 alm2 alm3", cs::alm0 | cs::alm1 | cs::alm2 | cs::alm3);
}

TEST(test_control_signals, test_conversion)
{
    check_conversion(cs::ai);
    check_conversion(cs::bi);
    check_conversion(cs::xi);
    check_conversion(cs::yi);

    check_conversion(cs::ai | cs::bo | cs::alm0);
    check_conversion(cs::alm0 | cs::pcp | cs::hlt);
}
