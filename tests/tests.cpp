#include "../include/cpparseopt.h"
#include <iostream>

#define STOP_ON_ERR 0

#define ASSERT_EQ(e, a) assertEquals((e), (a), STOP_ON_ERR, __FILE__, __LINE__)
#define ASSERT(v) ASSERT_EQ(true, (v))

using namespace cpparseopt;


// == begin: Utils
template<typename T>
void assertEquals(const T &expected, const T &actual, bool stopOnFailure,
                  const char *file, size_t line) {
    bool ok = (expected == actual);
    if (!ok) {
        std::cout << "Assertion failed: ['" <<
                expected << "' != '" << actual << "']" << std::endl <<
                "    on " << file << ":" << line << std::endl;
        if (stopOnFailure) {
            exit(1);
        }
    } else {
        std::cout << ".";
    }
}

template<typename T, size_t N>
inline
size_t sizeOfArray(const T(&)[N]) {
    return N;
}
// == end of: Utils

void Test__PatternBuilder__SimpleArg() {
    Pattern pattern;
    PatternBuilder(pattern).arg("arg");

    size_t pos = 0;
    const Argument &argByPos = pattern.getArg(pos);
    const Argument &argByName = pattern.getArg("arg");

    ASSERT(&argByPos == &argByName);
    ASSERT_EQ(pos, argByPos.getPos());
    ASSERT(argByPos.hasName("arg"));
    ASSERT(!argByPos.hasDefault());
}

void TestSuite__PatternBuilder() {
    std::cout << "Test Suite: PatternBuilder" << std::endl;

    Test__PatternBuilder__SimpleArg();

    std::cout << std::endl;
}


void Test__Parser__SimpleArg() {

    Pattern pattern;
    PatternBuilder(pattern).arg("arg");

    const char *argv[] = {"/path/to/bin", "param0"};
    CmdLineParams params = pattern.match(static_cast<int>(sizeOfArray(argv)),
                                         const_cast<char **>(argv));

    ASSERT_EQ(str_t("param0"), str_t(params.getArg(0)));
    ASSERT_EQ(str_t("param0"), str_t(params.getArg("arg")));
}

void TestSuite__Parser() {
    std::cout << "Test Suite: Parser" << std::endl;

    Test__Parser__SimpleArg();

    std::cout << std::endl;
}


int main(int argc, char *argv[]) {
    TestSuite__PatternBuilder();

    std::cout << std::endl;

    TestSuite__Parser();
}