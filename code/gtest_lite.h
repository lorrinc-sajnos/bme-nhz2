#ifndef GTEST_LITE_H
#define GTEST_LITE_H

/**
 * \file gtest_lite.h  (v3/2019)
 *
 * Google gtest keretrendszerhez hasonl� rendszer.
 * Sz.I. 2015., 2016., 2017. (_Has_X)
 * Sz.I. 2018 (template), ENDM, ENDMsg, nullptr_t
 * Sz.I. 2019 singleton
 *
 * A tesztel�s legalapvet�bb funkci�it t�mogat� f�ggv�nyek �s makr�k.
 * Nem sz�lbiztos megval�s�t�s.
 *
 *
 * Szabadon felhaszn�lhat�, b�v�thet�.
 *
 * Haszn�lati p�lda:
 *   Tesztelj�k az f(x)=2*x f�ggv�nyt:
 * int f(int x) { return 2*x; }
 *
 * int main() {
 *   TEST(TeszEsetNeve, TesztNeve)
 *     EXPECT_EQ(0, f(0));
 *     EXPECT_EQ(4, f(2)) << "A f�ggv�ny hib�s eredm�nyt adott" << std::endl;
 *     ...
 *   END
 * ...
 *
 * A m�k�d�s r�szleteinek meg�rt�se szorgalmi feladat.
 */

#include <iostream>
#include <cassert>
#include <cmath>
#include <cstring>
#include <limits>
#include <string>
#include <fstream>
#ifdef MEMTRACE
#include "memtrace.h"
#endif

// K�t makr� az egyes tesztek el� �s m�g�:
// A k�t makr� a kapcsos z�r�jelekkel egy �j blokkot hoz l�tre, amiben
// a nevek lok�lisak, �gy elker�lhet� a n�v�tk�z�s.

/// Teszt kezdete. A makr� param�terez�se hasonl�t a gtest
/// param�terez�s�hez. �gy az itt elk�sz�tett testek k�nnyen �temelhet�k
/// a gtest keretrendszerbe.
/// @param C - teszteset neve (csak a gtest kompatibilit�s miatt van k�l�n neve az eseteknek)
/// @param N - teszt neve
#define TEST(C, N) { gtest_lite::test.begin(#C"."#N);

/// Teszteset v�ge.
#define END gtest_lite::test.end(); }

/// Teszteset v�ge allok�lt blokkok sz�m�nak �sszehasonl�t�s�val
/// Ez az ellen�rz�s nem bomba biztos.
#define ENDM gtest_lite::test.end(true); }

/// Teszteset v�ge allok�lt blokkok sz�m�nak �sszehasonl�t�s�val
/// Ez az ellen�rz�s nem bomba biztos.
/// Ha hiba van ki�rja az �zenetet.
#define ENDMsg(t) gtest_lite::test.end(true) << t << std::endl; }

// Eredm�nyek vizsg�lat�t seg�t� makr�k.
// A param�terek �s a funkci�k a gtest keretrendszerrel megegyeznek.

/// Sikeres teszt makr�ja
#define SUCCEED() gtest_lite::test.expect(true, __FILE__, __LINE__, "SUCCEED()", true)

/// Sikertelen teszt makr�ja
#define FAIL() gtest_lite::test.expect(false, __FILE__, __LINE__, "FAIL()", true)

/// Azonoss�got elv�r� makr�

#define EXPECT_EQ(expected, actual) gtest_lite::EXPECT_(expected, actual, gtest_lite::eq, __FILE__, __LINE__, "EXPECT_EQ(" #expected ", " #actual ")" )

/// Elt�r�st elv�r� makr�
#define EXPECT_NE(expected, actual) gtest_lite::EXPECT_(expected, actual, gtest_lite::ne, __FILE__, __LINE__, "EXPECT_NE(" #expected ", " #actual ")", "etalon" )

/// Kisebb, vagy egyenl� rel�ci�t elv�r� makr�
#define EXPECT_LE(expected, actual) gtest_lite::EXPECT_(expected, actual, gtest_lite::le, __FILE__, __LINE__, "EXPECT_LE(" #expected ", " #actual ")", "etalon" )

/// Kisebb, mint rel�ci�t elv�r� makr�
#define EXPECT_LT(expected, actual) gtest_lite::EXPECT_(expected, actual, gtest_lite::lt, __FILE__, __LINE__, "EXPECT_LT(" #expected ", " #actual ")", "etalon" )

/// Nagyobb, vagy egyenl� rel�ci�t elv�r� makr�
#define EXPECT_GE(expected, actual) gtest_lite::EXPECT_(expected, actual, gtest_lite::ge, __FILE__, __LINE__, "EXPECT_GE(" #expected ", " #actual ")", "etalon" )

/// Nagyobb, mint rel�ci�t elv�r� makr�
#define EXPECT_GT(expected, actual) gtest_lite::EXPECT_(expected, actual, gtest_lite::gt, __FILE__, __LINE__, "EXPECT_GT(" #expected ", " #actual ")", "etalon" )

/// Igaz �rt�ket elv�r� makr�
#define EXPECT_TRUE(actual)  gtest_lite::EXPECT_(true, actual,  gtest_lite::eq, __FILE__, __LINE__, "EXPECT_TRUE(" #actual ")" )

/// Hamis �rt�ket elv�r� makr�
#define EXPECT_FALSE(actual) gtest_lite::EXPECT_(false, actual, gtest_lite::eq, __FILE__, __LINE__, "EXPECT_FALSE(" #actual ")" )

/// Val�s sz�mok azonoss�g�t elv�r� makr�
#define EXPECT_FLOAT_EQ(expected, actual)  gtest_lite::EXPECT_(expected, actual, gtest_lite::almostEQ, __FILE__, __LINE__, "EXPECT_FLOAT_EQ(" #expected ", " #actual ")" )

/// Val�s sz�mok azonoss�g�t elv�r� makr�
#define EXPECT_DOUBLE_EQ(expected, actual) gtest_lite::EXPECT_(expected, actual, gtest_lite::almostEQ, __FILE__, __LINE__, "EXPECT_DOUBLE_EQ(" #expected ", " #actual ")" )

/// C stringek (const char *) azonoss�g�t tesztel� makr�
#define EXPECT_STREQ(expected, actual) gtest_lite::EXPECTSTR(expected, actual, gtest_lite::eqstr, __FILE__, __LINE__, "EXPECT_STREQ(" #expected ", " #actual ")" )

/// C stringek (const char *) elt�r�set tesztel� makr�
#define EXPECT_STRNE(expected, actual) gtest_lite::EXPECTSTR(expected, actual, gtest_lite::nestr, __FILE__, __LINE__, "EXPECT_STRNE(" #expected ", " #actual ")", "etalon" )

/// Kiv�telt v�runk
#define EXPECT_THROW(statement, exception_type) try { gtest_lite::test.tmp = false; statement; } \
    catch (exception_type) { gtest_lite::test.tmp = true; } \
    catch (...) { } \
    EXPECTTHROW(statement, "kivetelt dob.", "nem dobott '"#exception_type"' kivetelt.")

/// Kiv�telt v�runk
#define EXPECT_ANY_THROW(statement) try { gtest_lite::test.tmp = false; statement; } \
    catch (...) { gtest_lite::test.tmp = true; } \
    EXPECTTHROW(statement, "kivetelt dob.", "nem dobott kivetelt.")

/// Nem v�runk kiv�telt
#define EXPECT_NO_THROW(statement) try { gtest_lite::test.tmp = true; statement; } \
    catch (...) { gtest_lite::test.tmp = false; }\
    EXPECTTHROW(statement, "nem dob kivetelt.", "kivetelt dobott.")

/// Nem v�runk kiv�telt gtest kompatibilit�s miatt
#define ASSERT_NO_THROW(statement) try { gtest_lite::test.tmp = true; statement; } \
    catch (...) { gtest_lite::test.tmp = false; }\
    EXPECTTHROW(statement, "nem dob kivetelt.", "kivetelt dobott.")

/// Kiv�telt v�runk �s tov�bbdobjuk -- ilyen nincs a gtest-ben
#define EXPECT_THROW_THROW(statement, exception_type) try { gtest_lite::test.tmp = false; statement; } \
    catch (exception_type) { gtest_lite::test.tmp = true; throw; } \
    EXPECTTHROW(statement, "kivetelt dob.", "nem dobott '"#exception_type"' kivetelt.")

/// Seg�dmakr� egy adattag, vagy tagf�ggv�ny l�tez�s�nek tesztel�s�re fut�si id�ben
/// �tlet:
/// https://cpptalk.wordpress.com/2009/09/12/substitution-failure-is-not-an-error-2
/// Haszn�lat:
/// CREATE_Has_(size)
/// ... if (Has_size<std::string>::member)...
#define CREATE_Has_(X) \
template<typename T> struct _Has_##X {  \
    struct Fallback { int X; };         \
    struct Derived : T, Fallback {};    \
    template<typename C, C> struct ChT; \
    template<typename D> static char (&f(ChT<int Fallback::*, &D::X>*))[1]; \
    template<typename D> static char (&f(...))[2]; \
    static bool const member = sizeof(f<Derived>(0)) == 2; \
};

/// Seg�df�ggv�ny egy publikus adattag, vagy tagf�ggv�ny l�tez�s�nek tesztel�s�re
/// ford�t�si id�ben
inline void hasMember(...) {}

/// Seg�dsablon t�puskonverzi� fut�s k�zbeni ellen�rz�sere
template <typename F, typename T>
struct _Is_Types {
    template<typename D> static char(&f(D))[1];
    template<typename D> static char(&f(...))[2];
    static bool const convertable = sizeof(f<T>(F())) == 1;
};

/// -----------------------------------
/// Bels� megval�s�t�shoz tartoz� makr�k, �s oszt�lyok.
/// Nem c�lszer� k�zvetlen�l haszn�lni, vagy m�dos�tani
/// -----------------------------------

/// EXPECTTHROW: kiv�telkezel�s
#define EXPECTTHROW(statement, exp, act) gtest_lite::test.expect(gtest_lite::test.tmp, __FILE__, __LINE__, #statement) \
    << "** Az utasitas " << (act) \
    << "\n** Azt vartuk, hogy " << (exp) << std::endl

#ifdef CPORTA
#define GTINIT(is)  \
    int magic;      \
    is >> magic;
#else
#define GTINIT(IS)
#endif // CPORTA

#ifdef CPORTA
#define GTEND(os)  \
    os << magic << (gtest_lite::test.fail() ? " NO" : " OK?") << std::endl;
#else
#define GTEND(os)
#endif // CPORTA

/// gtest_lite: a keretrendszer f�ggv�nyinek �s objektumainak n�vtere
namespace gtest_lite {

/// Tesztek �llapot�t t�rol� oszt�ly.
/// Egyetlen egy statikus p�ld�ny keletkezik, aminek a
/// destruktora a fut�s v�g�n h�v�dik meg.
    struct Test {
        int sum;            ///< tesztek sz�ml�l�ja
        int failed;         ///< hib�s tesztek
        int ablocks;        ///< allok�lt blokkok sz�ma
        bool status;        ///< �ppen fut� teszt st�tusza
        bool tmp;           ///< temp a kiv�telkezel�shez;
        std::string name;   ///< �ppen fut� teszt neve
        std::fstream null;  ///< nyel�, ha nem kell ki�rni semmit
        static Test& getTest() {
            static Test instance;///< egyed�li (singleton) p�ld�ny
            return instance;
        }
    private:    /// singleton minta miatt
        Test() :sum(0), failed(0), status(false), null("/dev/null") {}
        Test(const Test&);
        void operator=(const Test&);
    public:
        /// Teszt kezdete
        void begin(const char* n) {
            name = n; status = true;
#ifdef MEMTRACE
            ablocks = memtrace::allocated_blocks();
#endif
#ifndef CPORTA
            std::cerr << "\n---> " << name << std::endl;
#endif // CPORTA
            ++sum;
        }
        /// Teszt v�ge
        std::ostream& end(bool memchk = false) {
#ifdef MEMTRACE
            if (memchk && ablocks != memtrace::allocated_blocks()) {
                status = false;
                return std::cerr << "** Lehet, hogy nem szabaditott fel minden memoriat! **" << std::endl;
            }
#endif
#ifdef CPORTA
            if (!status)
#endif // CPORTA
                std::cerr << (status ? "     SIKERES" : "** HIBAS ****") << "\t" << name << " <---" << std::endl;
            if (!status)
                return std::cerr;
            else
                return null;
        }

        bool fail() { return failed; }

        /// Eredm�nyt adminisztr�l� tagf�ggv�ny True a j� eset.
        std::ostream& expect(bool st, const char* file, int line, const char* expr, bool pr = false) {
            if (!st) {
                ++failed;
                status = false;
            }
            if (!st || pr) {
                std::string str(file);
                size_t i = str.rfind("\\");
                if (i == std::string::npos) i = str.rfind("/");
                if (i == std::string::npos) i = 0; else i++;
                return std::cerr << "\n**** " << &file[i] << "(" << line << "): " << expr << " ****" << std::endl;
            }
            return null;
        }

        /// Destruktor
        ~Test() {
#ifdef CPORTA
            if (failed)
#endif // CPORTA
                std::cerr << "\n==== TESZT VEGE ==== HIBAS/OSSZES: " << failed << "/" << sum << std::endl;
        }
    };

    /// A statikus referencia minden ford�t�si egys�gben keletkezik, de
    /// mindegyik egyetlen p�ld�nyra fog hivatkozni a singleton minta miatt
    static Test& test = Test::getTest();

    /// �ltal�nos sablon a v�rt �rt�khez.
    template <typename T1, typename T2>
    std::ostream& EXPECT_(T1 exp, T2 act, bool (*pred)(T1, T2), const char* file, int line,
        const char* expr, const char* lhs = "elvart", const char* rhs = "aktual") {
        return test.expect(pred(exp, act), file, line, expr)
            << "** " << lhs << ": " << std::boolalpha << exp
            << "\n** " << rhs << ": " << std::boolalpha << act << std::endl;
    }

    /// pointerre specializ�lt sablon a v�rt �rt�khez.
    template <typename T1, typename T2>
    std::ostream& EXPECT_(T1* exp, T2* act, bool (*pred)(T1*, T2*), const char* file, int line,
        const char* expr, const char* lhs = "elvart", const char* rhs = "aktual") {
        return test.expect(pred(exp, act), file, line, expr)
            << "** " << lhs << ": " << (void*)exp
            << "\n** " << rhs << ": " << (void*)act << std::endl;
    }

#if __cplusplus >= 201103L
/// nullptr-re specializ�lt sablon a v�rt �rt�khez.
    template <typename T1>
    std::ostream& EXPECT_(T1* exp, std::nullptr_t act, bool (*pred)(T1*, std::nullptr_t), const char* file, int line,
        const char* expr, const char* lhs = "elvart", const char* rhs = "aktual") {
        return test.expect(pred(exp, act), file, line, expr)
            << "** " << lhs << ": " << (void*)exp
            << "\n** " << rhs << ": " << (void*)act << std::endl;
    }
#endif

/// stringek �sszehasonl�t�s�hoz.
/// az�rt nem spec. mert a sima EQ-ra m�sk�nt kell m�k�dnie.
    inline
        std::ostream& EXPECTSTR(const char* exp, const char* act, bool (*pred)(const char*, const char*), const char* file, int line,
            const char* expr, const char* lhs = "elvart", const char* rhs = "aktual") {
        return test.expect(pred(exp, act), file, line, expr)
            << "** " << lhs << ": " << (exp == NULL ? "NULL pointer" : std::string("\"") + exp + std::string("\""))
            << "\n** " << rhs << ": " << (act == NULL ? "NULL pointer" : std::string("\"") + act + std::string("\"")) << std::endl;
    }

    /// seg�d sablonok a rel�ci�khoz.
    /// az�rt nem STL (algorithm), mert csak a f�ggv�ny lehet, hogy menjen a deduckci�
    template <typename T1, typename T2>
    bool eq(T1 a, T2 b) { return a == b; }

    inline
        bool eqstr(const char* a, const char* b) {
        if (a != NULL && b != NULL)
            return strcmp(a, b) == 0;
        return false;
    }

    template <typename T1, typename T2>
    bool ne(T1 a, T2 b) { return a != b; }

    inline
        bool nestr(const char* a, const char* b) {
        if (a != NULL && b != NULL)
            return strcmp(a, b) != 0;
        return false;
    }

    template <typename T1, typename T2>
    bool le(T1 a, T2 b) { return a <= b; }

    template <typename T1, typename T2>
    bool lt(T1 a, T2 b) { return a < b; }

    template <typename T1, typename T2>
    bool ge(T1 a, T2 b) { return a >= b; }

    template <typename T1, typename T2>
    bool gt(T1 a, T2 b) { return a > b; }

    /// Seg�dsablon val�s sz�mok �sszehasonl�t�s�hoz
    /// Nem bombabiztos, de nek�nk most j� lesz
    /// Elm�leti h�t�r:
    /// http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
    template <typename T>
    bool almostEQ(T a, T  b) {
        // eps: ha a relat�v, vagy abszol�t hiba ett�l kisebb, akkor elfogadjuk
        T eps = 10 * std::numeric_limits<T>::epsilon(); // 10-szer a legkisebb �rt�k
        if (a == b) return true;
        if (fabs(a - b) < eps)
            return true;
        double aa = fabs(a);
        double ba = fabs(b);
        if (aa < ba) {
            aa = ba;
            ba = fabs(a);
        }
        return (aa - ba) < aa * eps;
    }

} // namespace gtest_lite

#endif // GTEST_LITE_H
