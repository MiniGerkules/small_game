#pragma once
#include <string>

class HeroDied : public std::exception
{
public:
	std::string message;

	HeroDied(std::string message_)
		: std::exception(), message(std::move(message_))
	{
	}

	const char* what() const noexcept override {
		return message.c_str();
	}
};

class AnotherMove : public std::exception
{
public:
	std::string message;

	AnotherMove(std::string message_)
		: std::exception(), message(std::move(message_))
	{
	}

	const char* what() const noexcept override {
		return message.c_str();
	}
};