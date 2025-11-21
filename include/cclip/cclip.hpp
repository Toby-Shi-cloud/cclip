#ifndef CCLIP_CCLIP_H_
#define CCLIP_CCLIP_H_

#include <algorithm>
#include <array>
#include <charconv>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <format>
#include <numeric>
#include <ranges>
#include <source_location>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

// copied from https://github.com/qlibs/reflect/blob/main/reflect
namespace {
struct REFLECT_STRUCT {
  void *MEMBER;
  enum class ENUM { VALUE };
};
}  // namespace
namespace cclip::details::reflect {
// clang-format off
namespace {
template<bool Cond> struct REFLECT_FWD_LIKE { template<class T> using type = std::remove_reference_t<T>&&; };
template<> struct REFLECT_FWD_LIKE<true> { template<class T> using type = std::remove_reference_t<T>&; };
} // to speed up compilation times

template<class T> extern const T ext{};
template<class T> struct ref { T& ref_; };
template<class T> ref(T&) -> ref<T>;

#define REFLECT_FWD(...) static_cast<decltype(__VA_ARGS__)&&>(__VA_ARGS__)
#define REFLECT_FWD_LIKE(T, ...) static_cast<typename ::cclip::details::reflect::REFLECT_FWD_LIKE<::std::is_lvalue_reference_v<T>>::template type<decltype(__VA_ARGS__)>>(__VA_ARGS__)

template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&&,   std::integral_constant<std::size_t, 0>) { return REFLECT_FWD(fn)(); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 1>) { auto&& [_1] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 2>) { auto&& [_1, _2] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 3>) { auto&& [_1, _2, _3] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 4>) { auto&& [_1, _2, _3, _4] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 5>) { auto&& [_1, _2, _3, _4, _5] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 6>) { auto&& [_1, _2, _3, _4, _5, _6] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 7>) { auto&& [_1, _2, _3, _4, _5, _6, _7] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 8>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 9>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 10>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 11>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 12>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 13>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 14>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 15>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 16>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 17>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 18>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 19>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 20>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 21>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 22>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 23>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 24>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 25>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 26>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 27>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 28>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 29>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 30>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 31>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 32>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 33>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 34>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 35>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 36>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 37>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 38>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 39>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 40>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 41>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 42>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 43>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 44>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43), REFLECT_FWD_LIKE(T, _44)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 45>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43), REFLECT_FWD_LIKE(T, _44), REFLECT_FWD_LIKE(T, _45)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 46>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43), REFLECT_FWD_LIKE(T, _44), REFLECT_FWD_LIKE(T, _45), REFLECT_FWD_LIKE(T, _46)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 47>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43), REFLECT_FWD_LIKE(T, _44), REFLECT_FWD_LIKE(T, _45), REFLECT_FWD_LIKE(T, _46), REFLECT_FWD_LIKE(T, _47)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 48>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43), REFLECT_FWD_LIKE(T, _44), REFLECT_FWD_LIKE(T, _45), REFLECT_FWD_LIKE(T, _46), REFLECT_FWD_LIKE(T, _47), REFLECT_FWD_LIKE(T, _48)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 49>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43), REFLECT_FWD_LIKE(T, _44), REFLECT_FWD_LIKE(T, _45), REFLECT_FWD_LIKE(T, _46), REFLECT_FWD_LIKE(T, _47), REFLECT_FWD_LIKE(T, _48), REFLECT_FWD_LIKE(T, _49)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 50>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43), REFLECT_FWD_LIKE(T, _44), REFLECT_FWD_LIKE(T, _45), REFLECT_FWD_LIKE(T, _46), REFLECT_FWD_LIKE(T, _47), REFLECT_FWD_LIKE(T, _48), REFLECT_FWD_LIKE(T, _49), REFLECT_FWD_LIKE(T, _50)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 51>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43), REFLECT_FWD_LIKE(T, _44), REFLECT_FWD_LIKE(T, _45), REFLECT_FWD_LIKE(T, _46), REFLECT_FWD_LIKE(T, _47), REFLECT_FWD_LIKE(T, _48), REFLECT_FWD_LIKE(T, _49), REFLECT_FWD_LIKE(T, _50), REFLECT_FWD_LIKE(T, _51)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 52>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43), REFLECT_FWD_LIKE(T, _44), REFLECT_FWD_LIKE(T, _45), REFLECT_FWD_LIKE(T, _46), REFLECT_FWD_LIKE(T, _47), REFLECT_FWD_LIKE(T, _48), REFLECT_FWD_LIKE(T, _49), REFLECT_FWD_LIKE(T, _50), REFLECT_FWD_LIKE(T, _51), REFLECT_FWD_LIKE(T, _52)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 53>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43), REFLECT_FWD_LIKE(T, _44), REFLECT_FWD_LIKE(T, _45), REFLECT_FWD_LIKE(T, _46), REFLECT_FWD_LIKE(T, _47), REFLECT_FWD_LIKE(T, _48), REFLECT_FWD_LIKE(T, _49), REFLECT_FWD_LIKE(T, _50), REFLECT_FWD_LIKE(T, _51), REFLECT_FWD_LIKE(T, _52), REFLECT_FWD_LIKE(T, _53)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 54>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43), REFLECT_FWD_LIKE(T, _44), REFLECT_FWD_LIKE(T, _45), REFLECT_FWD_LIKE(T, _46), REFLECT_FWD_LIKE(T, _47), REFLECT_FWD_LIKE(T, _48), REFLECT_FWD_LIKE(T, _49), REFLECT_FWD_LIKE(T, _50), REFLECT_FWD_LIKE(T, _51), REFLECT_FWD_LIKE(T, _52), REFLECT_FWD_LIKE(T, _53), REFLECT_FWD_LIKE(T, _54)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 55>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43), REFLECT_FWD_LIKE(T, _44), REFLECT_FWD_LIKE(T, _45), REFLECT_FWD_LIKE(T, _46), REFLECT_FWD_LIKE(T, _47), REFLECT_FWD_LIKE(T, _48), REFLECT_FWD_LIKE(T, _49), REFLECT_FWD_LIKE(T, _50), REFLECT_FWD_LIKE(T, _51), REFLECT_FWD_LIKE(T, _52), REFLECT_FWD_LIKE(T, _53), REFLECT_FWD_LIKE(T, _54), REFLECT_FWD_LIKE(T, _55)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 56>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43), REFLECT_FWD_LIKE(T, _44), REFLECT_FWD_LIKE(T, _45), REFLECT_FWD_LIKE(T, _46), REFLECT_FWD_LIKE(T, _47), REFLECT_FWD_LIKE(T, _48), REFLECT_FWD_LIKE(T, _49), REFLECT_FWD_LIKE(T, _50), REFLECT_FWD_LIKE(T, _51), REFLECT_FWD_LIKE(T, _52), REFLECT_FWD_LIKE(T, _53), REFLECT_FWD_LIKE(T, _54), REFLECT_FWD_LIKE(T, _55), REFLECT_FWD_LIKE(T, _56)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 57>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43), REFLECT_FWD_LIKE(T, _44), REFLECT_FWD_LIKE(T, _45), REFLECT_FWD_LIKE(T, _46), REFLECT_FWD_LIKE(T, _47), REFLECT_FWD_LIKE(T, _48), REFLECT_FWD_LIKE(T, _49), REFLECT_FWD_LIKE(T, _50), REFLECT_FWD_LIKE(T, _51), REFLECT_FWD_LIKE(T, _52), REFLECT_FWD_LIKE(T, _53), REFLECT_FWD_LIKE(T, _54), REFLECT_FWD_LIKE(T, _55), REFLECT_FWD_LIKE(T, _56), REFLECT_FWD_LIKE(T, _57)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 58>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43), REFLECT_FWD_LIKE(T, _44), REFLECT_FWD_LIKE(T, _45), REFLECT_FWD_LIKE(T, _46), REFLECT_FWD_LIKE(T, _47), REFLECT_FWD_LIKE(T, _48), REFLECT_FWD_LIKE(T, _49), REFLECT_FWD_LIKE(T, _50), REFLECT_FWD_LIKE(T, _51), REFLECT_FWD_LIKE(T, _52), REFLECT_FWD_LIKE(T, _53), REFLECT_FWD_LIKE(T, _54), REFLECT_FWD_LIKE(T, _55), REFLECT_FWD_LIKE(T, _56), REFLECT_FWD_LIKE(T, _57), REFLECT_FWD_LIKE(T, _58)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 59>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43), REFLECT_FWD_LIKE(T, _44), REFLECT_FWD_LIKE(T, _45), REFLECT_FWD_LIKE(T, _46), REFLECT_FWD_LIKE(T, _47), REFLECT_FWD_LIKE(T, _48), REFLECT_FWD_LIKE(T, _49), REFLECT_FWD_LIKE(T, _50), REFLECT_FWD_LIKE(T, _51), REFLECT_FWD_LIKE(T, _52), REFLECT_FWD_LIKE(T, _53), REFLECT_FWD_LIKE(T, _54), REFLECT_FWD_LIKE(T, _55), REFLECT_FWD_LIKE(T, _56), REFLECT_FWD_LIKE(T, _57), REFLECT_FWD_LIKE(T, _58), REFLECT_FWD_LIKE(T, _59)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 60>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43), REFLECT_FWD_LIKE(T, _44), REFLECT_FWD_LIKE(T, _45), REFLECT_FWD_LIKE(T, _46), REFLECT_FWD_LIKE(T, _47), REFLECT_FWD_LIKE(T, _48), REFLECT_FWD_LIKE(T, _49), REFLECT_FWD_LIKE(T, _50), REFLECT_FWD_LIKE(T, _51), REFLECT_FWD_LIKE(T, _52), REFLECT_FWD_LIKE(T, _53), REFLECT_FWD_LIKE(T, _54), REFLECT_FWD_LIKE(T, _55), REFLECT_FWD_LIKE(T, _56), REFLECT_FWD_LIKE(T, _57), REFLECT_FWD_LIKE(T, _58), REFLECT_FWD_LIKE(T, _59), REFLECT_FWD_LIKE(T, _60)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 61>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43), REFLECT_FWD_LIKE(T, _44), REFLECT_FWD_LIKE(T, _45), REFLECT_FWD_LIKE(T, _46), REFLECT_FWD_LIKE(T, _47), REFLECT_FWD_LIKE(T, _48), REFLECT_FWD_LIKE(T, _49), REFLECT_FWD_LIKE(T, _50), REFLECT_FWD_LIKE(T, _51), REFLECT_FWD_LIKE(T, _52), REFLECT_FWD_LIKE(T, _53), REFLECT_FWD_LIKE(T, _54), REFLECT_FWD_LIKE(T, _55), REFLECT_FWD_LIKE(T, _56), REFLECT_FWD_LIKE(T, _57), REFLECT_FWD_LIKE(T, _58), REFLECT_FWD_LIKE(T, _59), REFLECT_FWD_LIKE(T, _60), REFLECT_FWD_LIKE(T, _61)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 62>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43), REFLECT_FWD_LIKE(T, _44), REFLECT_FWD_LIKE(T, _45), REFLECT_FWD_LIKE(T, _46), REFLECT_FWD_LIKE(T, _47), REFLECT_FWD_LIKE(T, _48), REFLECT_FWD_LIKE(T, _49), REFLECT_FWD_LIKE(T, _50), REFLECT_FWD_LIKE(T, _51), REFLECT_FWD_LIKE(T, _52), REFLECT_FWD_LIKE(T, _53), REFLECT_FWD_LIKE(T, _54), REFLECT_FWD_LIKE(T, _55), REFLECT_FWD_LIKE(T, _56), REFLECT_FWD_LIKE(T, _57), REFLECT_FWD_LIKE(T, _58), REFLECT_FWD_LIKE(T, _59), REFLECT_FWD_LIKE(T, _60), REFLECT_FWD_LIKE(T, _61), REFLECT_FWD_LIKE(T, _62)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 63>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43), REFLECT_FWD_LIKE(T, _44), REFLECT_FWD_LIKE(T, _45), REFLECT_FWD_LIKE(T, _46), REFLECT_FWD_LIKE(T, _47), REFLECT_FWD_LIKE(T, _48), REFLECT_FWD_LIKE(T, _49), REFLECT_FWD_LIKE(T, _50), REFLECT_FWD_LIKE(T, _51), REFLECT_FWD_LIKE(T, _52), REFLECT_FWD_LIKE(T, _53), REFLECT_FWD_LIKE(T, _54), REFLECT_FWD_LIKE(T, _55), REFLECT_FWD_LIKE(T, _56), REFLECT_FWD_LIKE(T, _57), REFLECT_FWD_LIKE(T, _58), REFLECT_FWD_LIKE(T, _59), REFLECT_FWD_LIKE(T, _60), REFLECT_FWD_LIKE(T, _61), REFLECT_FWD_LIKE(T, _62), REFLECT_FWD_LIKE(T, _63)); }
template<class Fn, class T> [[nodiscard]] constexpr decltype(auto) visit(Fn&& fn, T&& t, std::integral_constant<std::size_t, 64>) { auto&& [_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64] = REFLECT_FWD(t); return REFLECT_FWD(fn)(REFLECT_FWD_LIKE(T, _1), REFLECT_FWD_LIKE(T, _2), REFLECT_FWD_LIKE(T, _3), REFLECT_FWD_LIKE(T, _4), REFLECT_FWD_LIKE(T, _5), REFLECT_FWD_LIKE(T, _6), REFLECT_FWD_LIKE(T, _7), REFLECT_FWD_LIKE(T, _8), REFLECT_FWD_LIKE(T, _9), REFLECT_FWD_LIKE(T, _10), REFLECT_FWD_LIKE(T, _11), REFLECT_FWD_LIKE(T, _12), REFLECT_FWD_LIKE(T, _13), REFLECT_FWD_LIKE(T, _14), REFLECT_FWD_LIKE(T, _15), REFLECT_FWD_LIKE(T, _16), REFLECT_FWD_LIKE(T, _17), REFLECT_FWD_LIKE(T, _18), REFLECT_FWD_LIKE(T, _19), REFLECT_FWD_LIKE(T, _20), REFLECT_FWD_LIKE(T, _21), REFLECT_FWD_LIKE(T, _22), REFLECT_FWD_LIKE(T, _23), REFLECT_FWD_LIKE(T, _24), REFLECT_FWD_LIKE(T, _25), REFLECT_FWD_LIKE(T, _26), REFLECT_FWD_LIKE(T, _27), REFLECT_FWD_LIKE(T, _28), REFLECT_FWD_LIKE(T, _29), REFLECT_FWD_LIKE(T, _30), REFLECT_FWD_LIKE(T, _31), REFLECT_FWD_LIKE(T, _32), REFLECT_FWD_LIKE(T, _33), REFLECT_FWD_LIKE(T, _34), REFLECT_FWD_LIKE(T, _35), REFLECT_FWD_LIKE(T, _36), REFLECT_FWD_LIKE(T, _37), REFLECT_FWD_LIKE(T, _38), REFLECT_FWD_LIKE(T, _39), REFLECT_FWD_LIKE(T, _40), REFLECT_FWD_LIKE(T, _41), REFLECT_FWD_LIKE(T, _42), REFLECT_FWD_LIKE(T, _43), REFLECT_FWD_LIKE(T, _44), REFLECT_FWD_LIKE(T, _45), REFLECT_FWD_LIKE(T, _46), REFLECT_FWD_LIKE(T, _47), REFLECT_FWD_LIKE(T, _48), REFLECT_FWD_LIKE(T, _49), REFLECT_FWD_LIKE(T, _50), REFLECT_FWD_LIKE(T, _51), REFLECT_FWD_LIKE(T, _52), REFLECT_FWD_LIKE(T, _53), REFLECT_FWD_LIKE(T, _54), REFLECT_FWD_LIKE(T, _55), REFLECT_FWD_LIKE(T, _56), REFLECT_FWD_LIKE(T, _57), REFLECT_FWD_LIKE(T, _58), REFLECT_FWD_LIKE(T, _59), REFLECT_FWD_LIKE(T, _60), REFLECT_FWD_LIKE(T, _61), REFLECT_FWD_LIKE(T, _62), REFLECT_FWD_LIKE(T, _63), REFLECT_FWD_LIKE(T, _64)); }

#undef REFLECT_FWD
#undef REFLECT_FWD_LIKE

template<auto...  Vs> [[nodiscard]] constexpr auto function_name() noexcept -> std::string_view { return std::source_location::current().function_name(); }
template<class... Ts> [[nodiscard]] constexpr auto function_name() noexcept -> std::string_view { return std::source_location::current().function_name(); }
// clang-format on
}  // namespace cclip::details::reflect

namespace cclip {
namespace details {
template <size_t N>
struct fixed_string {
  consteval fixed_string() noexcept {}
  consteval fixed_string(const char (&str)[N + 1]) noexcept {
    for (size_t i = 0; i <= N; ++i) data[i] = str[i];
  }
  consteval fixed_string(std::string_view sv) noexcept {
    for (size_t i = 0; i < N; ++i) data[i] = sv[i];
    data[N] = '\0';
  }
  constexpr operator const char *() const noexcept { return data; }
  constexpr operator std::string_view() const noexcept { return {data, N}; }
  constexpr size_t size() const noexcept { return N; }
  constexpr auto operator<=>(const fixed_string &) const noexcept = default;

  char data[N + 1];
};
template <size_t N>
fixed_string(const char (&)[N]) -> fixed_string<N - 1>;

struct to_any_type {
  template <typename T>
  constexpr operator T() const noexcept;
};

template <auto>
struct from_any_type {
  constexpr from_any_type(const auto &...) noexcept {}
};

template <typename T, size_t... Is>
  requires requires {
    { T{((void)Is, to_any_type{})...} } -> std::same_as<T>;
  }
consteval T construct_by(std::index_sequence<Is...>);

template <typename T, size_t N>
concept member_size_at_least = requires {
  { construct_by<T>(std::make_index_sequence<N>()) } -> std::same_as<T>;
};

template <std::default_initializable T, size_t N = 0>
consteval size_t member_size_impl() {
  static_assert(N <= 64, "struct with more than 64 members are currently not support!");
  if constexpr (member_size_at_least<T, N + 1>) {
    return member_size_impl<T, N + 1>();
  } else {
    return N;
  }
}

template <typename T>
inline constexpr size_t member_size = member_size_impl<std::remove_cvref_t<T>>();

template <class Fn, class T>
[[nodiscard]] constexpr decltype(auto) visit(Fn &&fn, T &&t) {
  return reflect::visit(std::forward<Fn>(fn), std::forward<T>(t), std::integral_constant<size_t, member_size<T>>());
}

template <typename T>
constexpr auto unpacked_as_tuple(T &&t) noexcept {
  if constexpr (std::is_rvalue_reference_v<decltype(t)>) {
    return visit([](auto &&...vs) { return std::make_tuple(std::forward<decltype(vs)>(vs)...); }, std::forward<T>(t));
  } else {
    return visit([](auto &&...vs) { return std::forward_as_tuple(std::forward<decltype(vs)>(vs)...); },
                 std::forward<T>(t));
  }
}

template <std::size_t I>
inline constexpr auto nth_pack_element = []<auto... Is>(std::index_sequence<Is...>) noexcept {
  return [](const from_any_type<Is> &..., auto &&nth, const auto &...) noexcept -> decltype(auto) {
    return std::forward<decltype(nth)>(nth);
  };
}(std::make_index_sequence<I>{});

template <size_t I, typename T>
constexpr decltype(auto) get(T &&t) noexcept {
  return visit(nth_pack_element<I>, std::forward<T>(t));
}

template <size_t I, typename T>
using member_type = std::tuple_element_t<I, decltype(unpacked_as_tuple(std::declval<T>()))>;

struct member_name_info {
  static constexpr auto name = reflect::function_name<reflect::ref{reflect::ext<::REFLECT_STRUCT>.MEMBER}>();
  static constexpr auto begin = name[name.find("MEMBER") - 1];
  static constexpr auto end = name.substr(name.find("MEMBER") + std::size(std::string_view{"MEMBER"}));
};

template <size_t I, typename T>
inline constexpr auto member_name_stored = [] {
  constexpr auto function_name =
      reflect::function_name<reflect::ref{visit(nth_pack_element<I>, reflect::ext<std::remove_cvref_t<T>>)}>();
  constexpr auto tmp_name = function_name.substr(0, function_name.find(member_name_info::end));
  constexpr auto name = tmp_name.substr(tmp_name.find_last_of(member_name_info::begin) + 1);
  return fixed_string<name.size()>(name);
}();

template <size_t I, typename T>
inline constexpr std::string_view member_name = member_name_stored<I, T>;
static_assert(member_name<0, ::REFLECT_STRUCT> == "MEMBER");

template <class T>
struct type_name_info {
  static constexpr auto name = reflect::function_name<int>();
  static constexpr auto begin = name.find("int");
  static constexpr auto end = name.substr(begin + std::size(std::string_view{"int"}));
};

template <class T>
  requires std::is_class_v<T>
struct type_name_info<T> {
  static constexpr auto name = reflect::function_name<::REFLECT_STRUCT>();
  static constexpr auto begin = name.find("REFLECT_STRUCT");
  static constexpr auto end = name.substr(begin + std::size(std::string_view{"REFLECT_STRUCT"}));
};

template <class T>
  requires std::is_enum_v<T>
struct type_name_info<T> {
  static constexpr auto name = reflect::function_name<::REFLECT_STRUCT::ENUM>();
  static constexpr auto begin = name.find("REFLECT_STRUCT::ENUM");
  static constexpr auto end = name.substr(begin + std::size(std::string_view{"REFLECT_STRUCT::ENUM"}));
};

template <typename T>
inline constexpr auto type_name_stored = [] {
  constexpr auto function_name = reflect::function_name<T>();
  constexpr auto suffix = function_name.substr(type_name_info<T>::begin);
  constexpr auto name = suffix.substr(0, suffix.size() - type_name_info<T>::end.size());
  return fixed_string<name.size()>(name);
}();

template <typename T>
inline constexpr std::string_view type_name = type_name_stored<T>;
static_assert(type_name<::REFLECT_STRUCT> == "REFLECT_STRUCT");

template <typename T, typename Fn>
constexpr void for_each(T &&t, Fn &&fn) {
  return visit(
      [&]<size_t... Is>(std::index_sequence<Is...>) {
        return [&](auto &&...vs) { (fn(std::integral_constant<size_t, Is>(), std::forward<decltype(vs)>(vs)), ...); };
      }(std::make_index_sequence<member_size<T>>()),
      std::forward<T>(t));
}

template <typename T, typename Fn>
constexpr void for_each(Fn &&fn) {
  [&]<size_t... Is>(std::index_sequence<Is...>) {
    (fn(std::integral_constant<size_t, Is>()), ...);
  }(std::make_index_sequence<member_size<T>>());
}
}  // namespace details

class build_exception : public std::runtime_error {
  using std::runtime_error::runtime_error;
};

class parse_exception : public std::runtime_error {
  using std::runtime_error::runtime_error;
};

namespace details {

template <typename T>
concept parsable = std::is_aggregate_v<T>;

inline std::string replace(std::string_view src, char from, const std::string &to) {
  std::string result;
  for (char ch : src) {
    if (ch == from)
      result += to;
    else
      result += ch;
  }
  return result;
}

template <typename... Ts>
using parse_action_t = bool (*)(std::string_view, Ts &...);

// action for all support types.
template <typename T>
struct parse_info {
  static_assert(sizeof(T) < 1, "unsupport type");
  static constexpr parse_action_t<T> action = nullptr;
  static constexpr size_t at_least = 0;
  static constexpr size_t at_most = 0;
  static constexpr bool has_value = false;
};

template <std::integral T>
struct parse_info<T> {
  static constexpr parse_action_t<T> action = [](std::string_view sv, T &value) {
    if constexpr (std::same_as<T, bool>) {
      value = true;
      return false;
    } else {
      auto [ptr, ec] = std::from_chars(sv.begin(), sv.end(), value);
      if (ec != std::errc() || ptr != sv.end())
        throw parse_exception(std::format("cannot parse {} to type {}", sv, type_name<T>));
      return true;
    }
  };
  static constexpr size_t at_least = 0;
  static constexpr size_t at_most = 1;
  static constexpr bool has_value = !std::same_as<T, bool>;
};

template <std::floating_point T>
struct parse_info<T> {
  static constexpr parse_action_t<T> action = [](std::string_view sv, T &value) {
    if constexpr (requires { std::from_chars(sv.begin(), sv.end(), value); }) {
      // note: std::from_chars for floating_point is not fully support!
      auto [ptr, ec] = std::from_chars(sv.begin(), sv.end(), value);
      if (ec != std::errc() || ptr != sv.end())
        throw parse_exception(std::format("cannot parse {} to type {}", sv, type_name<T>));
    } else {
      try {
        size_t endptr = 0;
        T tmp_value;
        if constexpr (std::same_as<T, float>)
          tmp_value = std::stof(std::string(sv), &endptr);
        else if constexpr (std::same_as<T, double>)
          tmp_value = std::stod(std::string(sv), &endptr);
        else if constexpr (std::same_as<T, long double>)
          tmp_value = std::stold(std::string(sv), &endptr);
        else
          static_assert(sizeof(T) < 1, "unsupport floating point T");
        if (endptr != sv.size()) throw std::exception();
        value = tmp_value;
      } catch (std::exception const &) {
        throw parse_exception(std::format("cannot parse {} to type {}", sv, type_name<T>));
      }
    }
    return true;
  };
  static constexpr size_t at_least = 0;
  static constexpr size_t at_most = 1;
  static constexpr bool has_value = true;
};

template <typename Ac>
// we only support std::string_view which element type is char
struct parse_info<std::basic_string<char, std::char_traits<char>, Ac>> {
  static constexpr parse_action_t<std::basic_string<char, std::char_traits<char>, Ac>> action =
      [](std::string_view sv, std::basic_string<char, std::char_traits<char>, Ac> &value) {
        value = static_cast<std::basic_string<char, std::char_traits<char>, Ac>>(sv);
        return true;
      };
  static constexpr size_t at_least = 0;
  static constexpr size_t at_most = 1;
  static constexpr bool has_value = true;
};

template <>
// we only support std::string_view which element type is char
struct parse_info<std::string_view> {
  static constexpr parse_action_t<std::string_view> action = [](std::string_view sv, std::string_view &value) {
    value = sv;
    return true;
  };
  static constexpr size_t at_least = 0;
  static constexpr size_t at_most = 1;
  static constexpr bool has_value = true;
};

template <std::ranges::range T>
  requires requires(T &t, std::ranges::range_value_t<T> v) { t.push_back(std::move(v)); }
// vector-like containers
struct parse_info<T> {
  static_assert(parse_info<std::ranges::range_value_t<T>>::action != nullptr, "The element of T cannot be parsed");
  static constexpr parse_action_t<T> action = [](std::string_view sv, T &cont) {
    std::ranges::range_value_t<T> value;
    auto acc = parse_info<std::ranges::range_value_t<T>>::action(sv, value);
    cont.push_back(std::move(value));
    return acc;
  };
  static constexpr size_t at_least = 0;
  static constexpr size_t at_most = static_cast<size_t>(-1);
  static constexpr bool has_value = true;
};

template <std::ranges::range T>
  requires requires(T &t, std::ranges::range_value_t<T> v) { t.insert(std::move(v)); }
// set-like containers
struct parse_info<T> {
  static_assert(parse_info<std::ranges::range_value_t<T>>::action != nullptr, "The element of T cannot be parsed");
  static constexpr parse_action_t<T> action = [](std::string_view sv, T &cont) {
    std::ranges::range_value_t<T> value;
    auto acc = parse_info<std::ranges::range_value_t<T>>::action(sv, value);
    cont.insert(std::move(value));
    return acc;
  };
  static constexpr size_t at_least = 0;
  static constexpr size_t at_most = static_cast<size_t>(-1);
  static constexpr bool has_value = true;
};

template <std::ranges::range T>
  requires requires(T &t, std::ranges::range_value_t<T> v) { t.push(std::move(v)); }
// stack-like containers
struct parse_info<T> {
  static_assert(parse_info<std::ranges::range_value_t<T>>::action != nullptr, "The element of T cannot be parsed");
  static constexpr parse_action_t<T> action = [](std::string_view sv, T &cont) {
    std::ranges::range_value_t<T> value;
    auto acc = parse_info<std::ranges::range_value_t<T>>::action(sv, value);
    cont.push(std::move(value));
    return acc;
  };
  static constexpr size_t at_least = 0;
  static constexpr size_t at_most = static_cast<size_t>(-1);
  static constexpr bool has_value = true;
};

template <typename T>
struct is_wrapped_option : std::false_type {};
}  // namespace details

template <details::parsable... Ts>
class Parser {
  Parser() = default;
  using parse_action_t = details::parse_action_t<Ts...>;

  template <auto raw_action, size_t OutI, size_t InI>
  inline static bool wrapped_action(std::string_view sv, Ts &...vs) {
    auto &nth = details::nth_pack_element<OutI>(vs...);
    auto &value = details::visit(details::nth_pack_element<InI>, nth);
    return raw_action(sv, value);
  }

 public:
  inline static Parser build(std::string underline_replace = "-")
    requires(sizeof...(Ts) > 0)
  {
    Parser parser;
    const auto build_impl = [&]<size_t OutI>(std::integral_constant<size_t, OutI>) {
      using T = std::tuple_element_t<OutI, std::tuple<Ts...>>;
      details::for_each<T>([&]<size_t InI>(std::integral_constant<size_t, InI>) {
        using InnerType = details::member_type<InI, T>;
        size_t cur_idx = parser.action_table_.size();
        std::string arg_name = details::replace(details::member_name<InI, T>, '_', underline_replace);
        parser.arg_names_.push_back(arg_name);
        parser.help_messages_.emplace_back();
        if constexpr (details::is_wrapped_option<InnerType>::value) {
          if constexpr (InnerType::is_positional) {
            parser.position_arg_map_.push_back(cur_idx);
          }
          if constexpr (InnerType::has_long_fmt) {
            if constexpr (InnerType::longf_builder_size == 0) {
              auto succ = parser.long_arg_map_.try_emplace(arg_name, cur_idx).second;
              if (!succ) throw build_exception(std::format("conflict long name: {}", arg_name));
            } else {
              for (std::string_view fmt : InnerType::get_long_fmt()) {
                auto succ = parser.long_arg_map_.try_emplace(std::string(fmt), cur_idx).second;
                if (!succ) throw build_exception(std::format("conflict long option: {} at {}", fmt, arg_name));
              }
            }
          }
          if constexpr (InnerType::has_short_fmt) {
            if constexpr (InnerType::shortf_builder_size == 0) {
              auto succ = parser.short_arg_map_.try_emplace(arg_name[0], cur_idx).second;
              if (!succ) throw build_exception(std::format("conflict short option: {} at {}", arg_name[0], arg_name));
            } else {
              for (char fmt : InnerType::get_short_fmt()) {
                auto succ = parser.short_arg_map_.try_emplace(fmt, cur_idx).second;
                if (!succ) throw build_exception(std::format("conflict short option: {} at {}", fmt, arg_name));
              }
            }
          }
          if constexpr (InnerType::help_builder_size != 0) {
            parser.help_messages_[cur_idx] = std::string(InnerType::help_string);
          }
        } else {
          auto succ = parser.long_arg_map_.try_emplace(std::move(arg_name), cur_idx).second;
          if (!succ) throw build_exception(std::format("conflict name: {}", details::member_name<InI, T>));
        }
        using parse_info = details::parse_info<InnerType>;
        parser.action_table_.push_back(&Parser::wrapped_action<parse_info::action, OutI, InI>);
        static_assert(parse_info::at_most > 0 && parse_info::at_most >= parse_info::at_least);
        parser.at_least_repeat_times_.push_back(parse_info::at_least);
        parser.at_most_repeat_times_.push_back(parse_info::at_most);
        parser.has_value_.push_back(parse_info::has_value);
      });
    };
    [&]<size_t... Is>(std::index_sequence<Is...>) {
      (build_impl(std::integral_constant<size_t, Is>()), ...);
    }(std::make_index_sequence<sizeof...(Ts)>());
    return parser;
  }

  Parser &set_long_arg_prefix(std::string fmt) {
    long_arg_prefix_ = std::move(fmt);
    return *this;
  }

  Parser &set_short_arg_prefix(std::string fmt) {
    short_arg_prefix_ = std::move(fmt);
    return *this;
  }

  Parser &require(const std::string &opt, size_t n = 1) {
    if (auto found = long_arg_map_.find(opt); found != long_arg_map_.end())
      at_least_repeat_times_[found->second] = n;
    else
      throw build_exception(std::format("option \"{}\" not found", opt));
    return *this;
  }

  Parser &require(char opt, size_t n = 1) {
    if (auto found = short_arg_map_.find(opt); found != short_arg_map_.end())
      at_least_repeat_times_[found->second] = n;
    else
      throw build_exception(std::format("option \"{}\" not found", opt));
    return *this;
  }

  Parser &set_alias(const std::string &opt, std::string alias) {
    if (auto found = long_arg_map_.find(opt); found != long_arg_map_.end()) {
      if (!long_arg_map_.emplace(std::move(alias), found->second).second)
        throw build_exception(std::format("set alias: {} already exists", alias));
    } else
      throw build_exception(std::format("option \"{}\" not found", opt));
    return *this;
  }

  Parser &set_alias(const std::string &opt, char alias) {
    if (auto found = long_arg_map_.find(opt); found != long_arg_map_.end()) {
      if (!short_arg_map_.emplace(alias, found->second).second)
        throw build_exception(std::format("set alias: {} already exists", alias));
    } else
      throw build_exception(std::format("option \"{}\" not found", opt));
    return *this;
  }

  Parser &set_alias(char opt, std::string alias) {
    if (auto found = short_arg_map_.find(opt); found != short_arg_map_.end()) {
      if (!long_arg_map_.emplace(std::move(alias), found->second).second)
        throw build_exception(std::format("set alias: {} already exists", alias));
    } else
      throw build_exception(std::format("option '{}' not found", opt));
    return *this;
  }

  Parser &set_alias(char opt, char alias) {
    if (auto found = short_arg_map_.find(opt); found != short_arg_map_.end()) {
      if (!short_arg_map_.emplace(alias, found->second).second)
        throw build_exception(std::format("set alias: {} already exists", alias));
    } else
      throw build_exception(std::format("option '{}' not found", opt));
    return *this;
  }

  Parser &set_help_msg(const std::string &opt, std::string msg) {
    if (auto found = long_arg_map_.find(opt); found != long_arg_map_.end()) {
      if (!help_messages_[found->second].empty())
        throw build_exception(std::format("help message for {} already exists", opt));
      help_messages_[found->second] = std::move(msg);
    } else
      throw build_exception(std::format("option \"{}\" not found", opt));
    return *this;
  }

  Parser &set_help_msg(char opt, std::string msg) {
    if (auto found = short_arg_map_.find(opt); found != short_arg_map_.end()) {
      if (!help_messages_[found->second].empty())
        throw build_exception(std::format("help message for {} already exists", opt));
      help_messages_[found->second] = std::move(msg);
    } else
      throw build_exception(std::format("option \"{}\" not found", opt));
    return *this;
  }

  template <std::input_iterator Iter, std::sentinel_for<Iter> Sent>
    requires std::convertible_to<std::iter_reference_t<Iter>, std::string_view>
  void parse(Iter it, Sent se, Ts &...vs) const {
    std::vector<size_t> occured_time(at_least_repeat_times_.size(), 0);
    size_t position_arg_index = 0;
    size_t active_arg = static_cast<size_t>(-1);
    std::string active_opt_name;
    bool allow_failed = true;
    bool in_short_opt = false;
    for (std::string_view sv; !sv.empty() || it != se;) {
      if (sv.empty()) {
        sv = static_cast<std::string_view>(*it++);
        in_short_opt = false;
      }
      if (active_arg == static_cast<size_t>(-1)) {
        // find next argument
        if (position_arg_index < position_arg_map_.size() &&
            occured_time[position_arg_map_[position_arg_index]] ==
                at_most_repeat_times_[position_arg_map_[position_arg_index]])
          ++position_arg_index;
        if (position_arg_index < position_arg_map_.size()) active_arg = position_arg_map_[position_arg_index];
        if (sv.substr(0, long_arg_prefix_.size()) == long_arg_prefix_) {
          auto lookup_string_view = sv.substr(long_arg_prefix_.size());
          if (auto idx = lookup_string_view.find('='); idx != sv.npos)
            lookup_string_view = lookup_string_view.substr(0, idx);
          std::string lookup_string{lookup_string_view};
          if (auto found = long_arg_map_.find(lookup_string); found != long_arg_map_.end()) {
            if (found->second < active_arg) {
              active_arg = found->second;
              allow_failed = false;
              active_opt_name = long_arg_prefix_ + lookup_string;
              sv = sv.substr(long_arg_prefix_.size() + lookup_string_view.size());
              if (sv.substr(0, 1) == "=") sv = sv.substr(1);
            }
          }
        } else if (in_short_opt || sv.substr(0, short_arg_prefix_.size()) == short_arg_prefix_) {
          auto lookup_string_view = in_short_opt ? sv : sv.substr(short_arg_prefix_.size());
          if (lookup_string_view.empty()) {
            if (active_arg == static_cast<size_t>(-1)) {
              throw parse_exception(std::format("unknown option: {}", sv));
            }
            continue;
          }
          char lookup_char = lookup_string_view[0];
          if (auto found = short_arg_map_.find(lookup_char); found != short_arg_map_.end()) {
            if (found->second < active_arg) {
              active_arg = found->second;
              allow_failed = false;
              active_opt_name = short_arg_prefix_ + lookup_char;
              sv = sv.substr(short_arg_prefix_.size() + (in_short_opt ? 0 : 1));
              in_short_opt = true;
            }
          }
        }
        if (active_arg == static_cast<size_t>(-1)) {
          throw parse_exception(std::format("unknown option: {}", in_short_opt ? sv.substr(0, 1) : sv));
        }
      } else {
        // parse currently active argument
        try {
          parse_action_t action = action_table_[active_arg];
          auto acc = action(sv, vs...);
          if (acc) sv = "";
          if (++occured_time[active_arg] == at_most_repeat_times_[active_arg]) active_arg = static_cast<size_t>(-1);
          allow_failed = true;
        } catch (parse_exception const &e) {
          if (allow_failed)
            active_arg = static_cast<size_t>(-1);
          else
            throw;
        }
      }
    }
    if (active_arg != static_cast<size_t>(-1)) {
      // parse again with empty string-view
      try {
        std::string_view sv = "";
        parse_action_t action = action_table_[active_arg];
        action(sv, vs...);
        ++occured_time[active_arg];
      } catch (parse_exception const &e) {
        if (!allow_failed) throw parse_exception(std::format("no argument provided for option {}", active_opt_name));
      }
    }
    for (size_t i = 0; i < occured_time.size(); ++i) {
      if (occured_time[i] < at_least_repeat_times_[i]) {
        if (occured_time[i] == 0)
          throw parse_exception(std::format("missing required argument: {}", arg_names_[i]));
        else
          throw parse_exception(std::format("argument `{}` expected to repeat at least {} times, but found {} times",
                                            arg_names_[i], at_least_repeat_times_[i], occured_time[i]));
      } else if (occured_time[i] > at_most_repeat_times_[i]) {
        if (at_most_repeat_times_[i] == 1)
          throw parse_exception(std::format("duplicate argument: {}", arg_names_[i]));
        else
          throw parse_exception(std::format("argument `{}` expected to repeat at most {} times, but found {} times",
                                            arg_names_[i], at_most_repeat_times_[i], occured_time[i]));
      }
    }
  }

  void parse(std::ranges::input_range auto &&r, Ts &...vs) const {
    return parse(std::ranges::begin(r), std::ranges::end(r), vs...);
  }
  void parse(int argc, char *argv[], Ts &...vs) const { return parse(argv + 1, argv + argc, vs...); }

  std::string help(const std::string &program) const {
    std::vector<std::pair<bool, std::vector<std::string>>> arg_opts(arg_names_.size());
    for (auto &idx : position_arg_map_) arg_opts[idx].first = true;
    for (auto &[s, idx] : long_arg_map_) arg_opts[idx].second.push_back(long_arg_prefix_ + s);
    for (auto &[c, idx] : short_arg_map_) arg_opts[idx].second.push_back(short_arg_prefix_ + c);

    std::stringstream ss;
    ss << "Usage: " << program;
    for (size_t idx = 0; idx < arg_names_.size(); ++idx) {
      if (arg_opts[idx].second.empty()) continue;
      ss << ' ';
      bool required = at_least_repeat_times_[idx] > 0;
      bool repeated = at_most_repeat_times_[idx] > 1;
      std::string str = arg_opts[idx].second.front();
      str += has_value_[idx] ? " VAR" : "";
      if (required && repeated)
        ss << "(" << str << "...)";
      else if (required)
        ss << str;
      else if (repeated)
        ss << "[" << str << "...]";
      else
        ss << "[" << str << "]";
    }
    for (auto &idx : position_arg_map_) {
      ss << ' ';
      bool required = at_least_repeat_times_[idx] > 0;
      bool repeated = at_most_repeat_times_[idx] > 1;
      const auto &str = arg_names_[idx];
      if (required && repeated)
        ss << "(" << str << "...)";
      else if (required)
        ss << str;
      else if (repeated)
        ss << "[" << str << "...]";
      else
        ss << "[" << str << "]";
    }
    ss << "\n\n";

    if (!position_arg_map_.empty()) {
      ss << "Positional arguments:\n";
      size_t longest_name = std::ranges::max(position_arg_map_ |
                                             std::views::transform([&](size_t idx) { return arg_names_[idx].size(); }));
      for (auto &idx : position_arg_map_) {
        ss << "  " << arg_names_[idx];
        size_t spaces = longest_name - arg_names_[idx].size();
        while (spaces--) ss << ' ';
        ss << "  " << help_messages_[idx];
        if (at_least_repeat_times_[idx] == 0 && at_most_repeat_times_[idx] == 1)
          ;
        else if (at_least_repeat_times_[idx] == 1 && at_most_repeat_times_[idx] == 1)
          ss << " [required]";
        else if (at_least_repeat_times_[idx] == at_most_repeat_times_[idx])
          ss << " [nargs=" << at_least_repeat_times_[idx] << "]";
        else if (at_most_repeat_times_[idx] == static_cast<size_t>(-1))
          ss << " [nargs=" << at_least_repeat_times_[idx] << "..]";
        else
          ss << " [nargs=" << at_least_repeat_times_[idx] << ".." << at_most_repeat_times_[idx] << "]";
        ss << '\n';
      }
    }

    if (!position_arg_map_.empty() && (!short_arg_map_.empty() || !long_arg_map_.empty())) ss << '\n';
    if (!short_arg_map_.empty() || !long_arg_map_.empty()) {
      ss << "Optional arguments:\n";
      size_t longest_opt =
          std::ranges::max(arg_opts | std::views::transform([&](auto &&pair) -> size_t {
                             if (pair.second.empty()) return 0;
                             return std::accumulate(pair.second.begin(), pair.second.end(), size_t{0},
                                                    [&](size_t acc, auto &&str) { return acc + str.size(); }) +
                                    (pair.second.size() - 1) * 2;
                           }));
      for (size_t idx = 0; idx < arg_names_.size(); ++idx) {
        if (arg_opts[idx].second.empty()) continue;
        size_t bytes = arg_opts[idx].second.front().size();
        ss << "  " << arg_opts[idx].second.front();
        for (auto &&str : arg_opts[idx].second | std::views::drop(1)) ss << ", " << str, bytes += 2 + str.size();
        size_t spaces = longest_opt - bytes;
        while (spaces--) ss << ' ';
        ss << "  " << help_messages_[idx];
        if (at_least_repeat_times_[idx] == 0 && at_most_repeat_times_[idx] == 1)
          ;
        else if (at_least_repeat_times_[idx] == 1 && at_most_repeat_times_[idx] == 1)
          ss << " [required]";
        else if (at_least_repeat_times_[idx] == at_most_repeat_times_[idx])
          ss << " [nargs=" << at_least_repeat_times_[idx] << "]";
        else if (at_most_repeat_times_[idx] == static_cast<size_t>(-1))
          ss << " [nargs=" << at_least_repeat_times_[idx] << "..]";
        else
          ss << " [nargs=" << at_least_repeat_times_[idx] << ".." << at_most_repeat_times_[idx] << "]";
        ss << '\n';
      }
    }

    return std::move(ss).str();
  }

 private:
  std::vector<size_t> position_arg_map_;
  std::unordered_map<char, size_t> short_arg_map_;
  std::unordered_map<std::string, size_t> long_arg_map_;
  std::vector<parse_action_t> action_table_;
  std::vector<std::string> arg_names_;
  std::vector<std::string> help_messages_;
  std::vector<bool> has_value_;
  std::vector<size_t> at_least_repeat_times_, at_most_repeat_times_;
  std::string long_arg_prefix_ = "--", short_arg_prefix_ = "-";
};

inline namespace option_builder {
enum OptionType : uint8_t {
  LONG = 0x1,
  SHORT = 0x2,
  POSITIONAL = 0x4,
};
inline consteval OptionType operator|(OptionType x, OptionType y) {
  return static_cast<OptionType>(static_cast<uint8_t>(x) | static_cast<uint8_t>(y));
}

struct at_least {
  size_t data;
  consteval at_least(size_t t) : data(t) {}
};
inline constexpr at_least required{1};

struct at_most {
  size_t data;
  consteval at_most(size_t t) : data(t) {}
};

template <size_t N>
struct help {
  details::fixed_string<N> data;
  consteval help(const details::fixed_string<N> &msg) : data(msg) {}
};
template <size_t N>
help(const char (&)[N]) -> help<N - 1>;

template <size_t N>
struct longf {
  details::fixed_string<N> data;
  consteval longf(const details::fixed_string<N> &s) : data(s) {}
};
template <size_t N>
longf(const char (&)[N]) -> longf<N - 1>;

struct shortf {
  char data;
  consteval shortf(char c) : data(c) {}
};
}  // namespace option_builder

namespace details {
template <typename T>
struct is_option_builder_help : std::false_type {};
template <size_t N>
struct is_option_builder_help<option_builder::help<N>> : std::true_type {};

template <typename T>
struct is_option_builder_longf : std::false_type {};
template <size_t N>
struct is_option_builder_longf<option_builder::longf<N>> : std::true_type {};

template <typename T>
concept is_option_builder = std::same_as<T, at_least> || std::same_as<T, at_most> || std::same_as<T, shortf> ||
                            is_option_builder_help<T>::value || is_option_builder_longf<T>::value;
}  // namespace details

inline namespace option_builder {
template <std::default_initializable T, OptionType flags = LONG, details::is_option_builder auto... args>
class Option {
  template <details::parsable... Ts>
  friend class ::cclip::Parser;
  friend ::cclip::details::parse_info<Option>;

  static constexpr bool is_positional = static_cast<bool>(flags & POSITIONAL);
  static constexpr bool has_long_fmt = static_cast<bool>(flags & LONG);
  static constexpr bool has_short_fmt = static_cast<bool>(flags & SHORT);

  static_assert(is_positional || has_long_fmt || has_short_fmt,
                "Option flag should contain one of LONG, SHORT and POSITIONAL");

  static constexpr size_t at_least_builder_size =
      (static_cast<size_t>(std::same_as<std::remove_cvref_t<decltype(args)>, option_builder::at_least>) + ... + 0);
  static constexpr size_t at_most_builder_size =
      (static_cast<size_t>(std::same_as<std::remove_cvref_t<decltype(args)>, option_builder::at_most>) + ... + 0);
  static constexpr size_t shortf_builder_size =
      (static_cast<size_t>(std::same_as<std::remove_cvref_t<decltype(args)>, option_builder::shortf>) + ... + 0);
  static constexpr size_t longf_builder_size =
      (static_cast<size_t>(details::is_option_builder_longf<std::remove_cvref_t<decltype(args)>>::value) + ... + 0);
  static constexpr size_t help_builder_size =
      (static_cast<size_t>(details::is_option_builder_help<std::remove_cvref_t<decltype(args)>>::value) + ... + 0);

  static_assert(at_least_builder_size <= 1, "Option should not have at_least builder more than 1");
  static_assert(at_most_builder_size <= 1, "Option should not have at_most builder more than 1");
  static_assert(help_builder_size <= 1, "Option should not have help builder more than 1");

  template <size_t I>
  static consteval size_t get_at_least() {
    if constexpr (I == sizeof...(args))
      return 0;
    else if constexpr (std::same_as<std::remove_cvref_t<decltype(details::nth_pack_element<I>(args...))>,
                                    option_builder::at_least>)
      return details::nth_pack_element<I>(args...).data;
    else
      return get_at_least<I + 1>();
  }
  template <size_t I>
  static consteval size_t get_at_most() {
    if constexpr (I == sizeof...(args))
      return 0;
    else if constexpr (std::same_as<std::remove_cvref_t<decltype(details::nth_pack_element<I>(args...))>,
                                    option_builder::at_most>)
      return details::nth_pack_element<I>(args...).data;
    else
      return get_at_most<I + 1>();
  }
  template <size_t I>
  static consteval auto get_help_string() {
    if constexpr (I == sizeof...(args))
      return details::fixed_string("");
    else if constexpr (details::is_option_builder_help<
                           std::remove_cvref_t<decltype(details::nth_pack_element<I>(args...))>>::value)
      return details::nth_pack_element<I>(args...).data;
    else
      return get_help_string<I + 1>();
  }
  template <size_t I>
  static consteval char get_short_fmt_impl() {
    if constexpr (std::same_as<std::remove_cvref_t<decltype(details::nth_pack_element<I>(args...))>,
                               option_builder::shortf>)
      return details::nth_pack_element<I>(args...).data;
    else
      return 0;
  }
  template <size_t I>
  static constexpr std::string_view get_long_fmt_impl() {
    if constexpr (details::is_option_builder_longf<
                      std::remove_cvref_t<decltype(details::nth_pack_element<I>(args...))>>::value)
      return details::nth_pack_element<I>(args...).data;
    else
      return "";
  }
  static constexpr std::vector<char> get_short_fmt() {
    std::vector<char> result;
    result.reserve(shortf_builder_size);
    [&]<size_t... Is>(std::index_sequence<Is...>) {
      ((get_short_fmt_impl<Is>() ? result.push_back(get_short_fmt_impl<Is>()) : (void)0), ...);
    }(std::make_index_sequence<sizeof...(args)>());
    return result;
  }
  static constexpr std::vector<std::string_view> get_long_fmt() {
    std::vector<std::string_view> result;
    result.reserve(longf_builder_size);
    [&]<size_t... Is>(std::index_sequence<Is...>) {
      ((!get_long_fmt_impl<Is>().empty() ? result.push_back(get_long_fmt_impl<Is>()) : (void)0), ...);
    }(std::make_index_sequence<sizeof...(args)>());
    return result;
  }

  static constexpr size_t at_least = get_at_least<0>();
  static constexpr size_t at_most = get_at_most<0>();
  static constexpr auto help_string = get_help_string<0>();

 public:
  constexpr Option() : data() {}
  constexpr Option(T init) : data(std::move(init)) {}
  constexpr Option &operator=(T init) { return data = std::move(init), *this; }
  constexpr operator const T &() const & { return data; }
  constexpr operator T &() & { return data; }
  constexpr operator T() && { return std::move(data); }
  constexpr const T &get() const & { return data; }
  constexpr T &get() & { return data; }
  constexpr T get() && { return std::move(data); }

 private:
  T data;
};
}  // namespace option_builder

namespace details {
template <std::default_initializable T, OptionType flags, details::is_option_builder auto... args>
struct is_wrapped_option<Option<T, flags, args...>> : std::true_type {};

template <std::default_initializable T, OptionType flags, details::is_option_builder auto... args>
  requires(parse_info<T>::action != nullptr)
struct parse_info<Option<T, flags, args...>> {
  using MyOption = Option<T, flags, args...>;
  static constexpr parse_action_t<MyOption> action = [](std::string_view sv, MyOption &value) {
    return parse_info<T>::action(sv, static_cast<T &>(value));
  };
  static constexpr size_t at_least = MyOption::at_least ? MyOption::at_least : parse_info<T>::at_least;
  static constexpr size_t at_most = MyOption::at_most ? MyOption::at_most : parse_info<T>::at_most;
  static constexpr bool has_value = parse_info<T>::has_value;
};
}  // namespace details
}  // namespace cclip

#endif /* CCLIP_CCLIP_H_ */