#pragma once
#include <concepts>
#include <memory>
#include <vector>
#include <iostream>

template <typename T>
concept Equatable = requires(T& a, T& b)
{
	{a == b}->std::equality_comparable;
	{a != b}->std::equality_comparable;
};

template <typename T>
concept Copiable = std::copy_constructible<T> || std::copyable<T>;

template<typename T>
concept Printable = requires(std::ostream& os, T & a)
{
	{os << a}->std::convertible_to<decltype(os)>;
};

template<typename T>
concept Addable = requires (T& a, T & b)
{
	{ a + b } -> std::convertible_to<T>;
};

template<typename T>
concept Subtractable = requires (T& a, T & b)
{
	{ a - b } -> std::convertible_to<T>;
};

template<typename T>
concept Multiplyable = requires (T& a, T & b)
{
	{ a * b } -> std::convertible_to<T>;
};

template<typename T>
concept Scalable = requires (T& a, double b)
{
	{ a * b } -> std::convertible_to<T>;
	{ a + b } -> std::convertible_to<T>;
	{ a - b } -> std::convertible_to<T>;
};

template<typename T>
concept Negatable = requires (T& a)
{
	{ -a } -> std::convertible_to<T>;
};

template<typename T>
concept Tensorable = Negatable<T> && Scalable<T> && Multiplyable<T> && Subtractable<T> && Addable<T>;
