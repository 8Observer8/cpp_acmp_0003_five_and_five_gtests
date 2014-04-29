#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <sstream>

class LogicError : public std::logic_error {
public:

    LogicError( int argument ) : std::logic_error( "" ), m_argument( argument ) {

    }

    virtual const char *what( ) const throw () {
        return m_message.c_str( );
    }

    virtual ~LogicError( ) throw () {

    }

protected:
    int m_argument;
    std::string m_message;
};

class InvalidArgument : public LogicError {
public:

    InvalidArgument( int argument ) : LogicError( argument ) {
        std::stringstream stream;
        stream << argument;
        m_message = "Argument " + stream.str( ) + " mush be multiple of 5";
    }
};

class OutOfRange : public LogicError {
public:

    OutOfRange( int argument, int beginOfRange, int endOfRange ) : LogicError( argument ) {
        std::string str_argument, str_beginOfRange, str_endOfRange;

        str_argument = intToString( argument );
        str_beginOfRange = intToString( beginOfRange );
        str_endOfRange = intToString( endOfRange );

        m_message = "Argument " + str_argument + " doesn't hit in the range [" +
                str_beginOfRange + ", " + str_endOfRange + "]";
    }

private:

    std::string intToString( int number ) {
        std::stringstream stream;
        stream << number;
        return stream.str( );
    }
};

double fiveAndFive( int number ) throw (InvalidArgument, OutOfRange);

TEST( test001, normalTest ) {
    int n = 5;
    double expected = 25.0;

    double actual = 0.0;
    ASSERT_NO_THROW({
                        actual = fiveAndFive( n );
                    });
    double delta = 0.001;
    ASSERT_NEAR( expected, actual, delta );
}

TEST( test002, exceptionTest ) {
    int n = 0;

    ASSERT_THROW({
                     fiveAndFive( n );
                 }, OutOfRange);
}

TEST( test003, exceptionTest ) {
    int n = 4;

    ASSERT_THROW({
                     fiveAndFive( n );
                 }, InvalidArgument);
}

TEST( test004, exceptionTest ) {
    int n = 6;

    ASSERT_THROW({
                     fiveAndFive( n );
                 }, InvalidArgument);
}

TEST( test005, normalTest ) {
    int n = 399995;
    double expected = 159996000025.0;

    double actual = 0.0;
    ASSERT_NO_THROW({
                        actual = fiveAndFive( n );
                    });
    double delta = 0.001;
    ASSERT_NEAR( expected, actual, delta );
}

TEST( test006, exceptionTest ) {
    int n = 399996;

    ASSERT_THROW({
                     fiveAndFive( n );
                 }, InvalidArgument);
}

TEST( test007, normalTest ) {
    int n = 400000;
    double expected = 160000000000.0;

    double actual = 0.0;
    ASSERT_NO_THROW({
                        actual = fiveAndFive( n );
                    });
    double delta = 0.001;
    ASSERT_NEAR( expected, actual, delta );
}

TEST( test008, exceptionTest ) {
    int n = 400001;

    ASSERT_THROW({
                     fiveAndFive( n );
                 }, InvalidArgument);
}

TEST( test009, exceptionTest ) {
    int n = 400005;

    ASSERT_THROW({
                     fiveAndFive( n );
                 }, OutOfRange);
}

int main( int argc, char *argv[] ) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
