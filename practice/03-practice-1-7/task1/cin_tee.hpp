// cin_tee.hpp
#pragma once

#include <iostream>
#include <streambuf>

class TeeStreambuf : public std::streambuf {
private:
    std::streambuf* in_buf;  // Исходный буфер cin
    std::streambuf* out_buf; // Буфер для дублирования (cout)
    char ch;                 // Временный односимвольный буфер

public:
    TeeStreambuf(std::streambuf* in, std::streambuf* out)
        : in_buf(in), out_buf(out) {}

protected:
    int_type underflow() override {
        int_type c = in_buf->sbumpc();
        if (c != traits_type::eof()) {
            ch = traits_type::to_char_type(c);
            out_buf->sputc(ch);
            
            // Сбрасываем буфер при переводе строки для точной имитации ручного ввода
            if (ch == '\n') {
                out_buf->pubsync();
            }
            
            setg(&ch, &ch, &ch + 1);
        }
        return c;
    }
};

namespace detail {
    struct CinEchoGuard {
        std::streambuf* orig_cin;
        TeeStreambuf tee_buf;

        CinEchoGuard()
            : orig_cin(std::cin.rdbuf()),
              tee_buf(orig_cin, std::cout.rdbuf()) {
            // Гарантируем, что cin и cout уже инициализированы до main()
            static std::ios_base::Init init;
            std::cin.rdbuf(&tee_buf);
        }

        ~CinEchoGuard() {
            // Возвращаем исходный буфер перед уничтожением tee_buf
            std::cin.rdbuf(orig_cin);
        }
    };

    // inline-переменная (C++17+) создает ровно один экземпляр на всю программу
    inline CinEchoGuard cin_echo_guard;
}
