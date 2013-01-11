/*
 * LibSylph Class Library
 * Copyright (C) 2013 Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must not
 *   claim that you wrote the original software. If you use this software
 *   in a product, an acknowledgment in the product documentation would be
 *   appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must not be
 *   misrepresented as being the original software.
 *
 *   3. This notice may not be removed or altered from any source
 *   distribution.
 *
 * Created on: 26 november 2008
 */

#ifndef SYLPH_CORE_STRING_H_
#define SYLPH_CORE_STRING_H_

#include "Object.h"
#include "Comparable.h"
#include "Hash.h"
#include "Primitives.h"
#include "Array.h"

// for convenience
#include "I18N.h"

#include <string>

SYLPH_BEGIN_NAMESPACE


/**
 * A integral type for storing an UTF-16 character
 */
typedef uint16_t uchar;

/**
 * This array contains the characters that are considered to be whitespace
 * characters by default. The following shows the contents of this list:
 * <ul>
 * <li> space (Unicode U+0020, character literal ' ') </li>
 * <li> newline (Unicode U+000A, character literal '\\n')</li>
 * <li> carriage return (Unicode U+000D, character literal '\\r')</li>
 * <li> form feed (Unicode U+000C, character literal '\\f')</li>
 * <li> horizontal tab (Unicode U+0009, character literal '\\t')</li>
 * <li> vertical tab (Unicode U+000B, character literal '\\v' or '\\013')</li>
 * </ul><p>
 * Certain functions, such as String::trim() and String::split() use this array
 * to determine a default set of characters to look for.
 */
static Array<uchar> spacechars = {' ', '\n', '\r', '\f', '\t', '\013'};

/**
 * The String class represents character strings. All strings used in LibSylph
 * are instances of this class. <p>
 * Strings are constant, their value can not be changed after they are created.
 * StringBuffer implements a mutable string. The copy constructor only copies
 * a pointer to the actual internal data, making Strings trivial to copy,
 * they should therefore be treated as built-in types, such as ints and floats.
 * <p>The class String includes methods for examining individual characters of
 * the sequence, for comparing strings, for searching strings, for extracting
 * substrings, and for creating a copy of a string with all characters
 * translated to uppercase or to lowercase. Case mapping relies heavily on the
 * information provided by the Unicode Consortium's Unicode 5.1 specification.
 * The specification's UnicodeData.txt and SpecialCasing.txt files are used
 * extensively to provide case mapping. For specific details, please refer
 * to the ICU library documentation.<p>
 * Strings are encoded internally in UTF-16, but only the Basic Multilinguar
 * Plane (up to U+FFFF) is supported. Future versions may add support for the
 * other planes (up to U+10FFFF). In this case, UTF-32 will be used instead.
 */
class String : public virtual Object {
    friend bool operator==(const String lhs, const String rhs);
    friend bool operator<(const String lhs, const String rhs);
    friend String operator+(const String lhs, const String rhs);
    //friend String operator%(const String lhs, const String rhs);
    friend String operator&(const String lhs, const String(*rhs)(const String));
    friend String operator&(const String(*lhs)(String), const String rhs);
    friend String operator*(const String lhs, const std::size_t len);
    friend std::ostream& operator<<(std::ostream& lhs, const String rhs);

    friend struct Hash<String>;

public:
    /**
     * Creates an empty String. An empty String has a length of 0 and does not
     * contain any internal data. All empty Strings are equal to each other.
     * <p>Since Strings are immutable, the main use of this constructor is to
     * compare against the empty string, or to supply a dummy value to a
     * function.
     */
    String();
    /**
     * Creates a String from a C-style string. The pointer passed must be a
     * pointer to a null ('\\0') terminated character array. The length
     * of the character array is deduced from the place of the null character.
     * Passing anything else than a null-terminated character array to this
     * constructor may result in undefined behaviour. <p>
     * The character array passed is expected to be encoded in UTF-8. Any other
     * encodings, or invalid UTF-8, may result in Unicode replacement
     * characters ('�', U+FFFD) to be inserted into the character sequence.<p>
     * The characters in the original string will be converted to UTF-16.
     * The original string will not be modified.<p>
     * An example:
     * <pre>String foo = "abc";
     * String bar("def");</pre>
     * @param orig A c-style null terminated string encoded in UTF-8
     */
    String(const char * orig);

    /**
     * Creates a String from an Array of uchars. The Array passed must not be
     * null ('\\0') terminated. The length of the String will be equal to the
     * length of the Array.
     * The data in the Array passed is expected to be encoded in UTF-16. The
     * data is copied into the String without any checks applied<p>
     * The original Array will not be modified. Please note that for
     * construction of a 'mutable' string, StringBuffer is prefered.
     * @param orig An Array containing the values to be copied into this string
     */
    String(const Array<uchar> orig);
    /**
     * Creates a String from a std::string. This constructor takes the same
     * effect as if you would have used <code>String(orig.c_str())</code> and is
     * supplied for your convenience. The requirements are identical of to
     * @c String::String(const char*). The original string will not be modified
     * @param orig A standard library string to convert to a String.
     */
    String(const std::string & orig);
    /**
     * Creates a String referring to the other String's data. This constructor
     * will not make a full copy of the data contained by the original string,
     * instead, it will take a copy of the pointer pointing to the actual
     * data. Afterwards, the two Strings will be both sharing the same data.<p>
     * If you do want a 1:1 copy of a String, please look at the String::copy()
     * function.
     * @param orig A string to share string data with.
     */
    String(const String& orig);
    /**
     * Creates a String from a single character. The length of the String will
     * be 1. The character is copied into the String.
     * @param c A character.
     */
    String(const uchar c);
    /**
     * Converts a bool into a String. If the specified boolean is true, then
     * this String will be equal to "true", otherwise this String will be equal
     * to "false". In other words, this constructor is equivalent to
     * <pre>String s = b ? "true" : "false"; </pre>
     * @param b A boolean.
     */
    String(const bool b);

    /**
     * Converts a 32-bit signed integer to a String. The integer will be
     * represented in base 10. If the integer is negative, an ASCII minus
     * character ('-', U+002D) will be prepended to the value. If the value is
     * not negative, no sign will be prepended. If integer is equal to 0, a
     * single ASCII 0 will be used (U+0030). The String will match the regex
     * @c (0|-?[1-9][0-9]+).
     * @param i A 32-bit signed integer.
     */
    String(const int32_t i);
    /**
     * Converts a 32-bit unsigned integer to a String. The integer will be
     * represented in base 10. If integer is equal to 0, a  single ASCII 0 will
     * be used (U+0030). The String will match the regex
     * @c (0|[1-9][0-9]+).
     * @param i A 32-bit unsigned integer.
     */
    String(const uint32_t i);
    /**
     * Converts a 64-bit signed integer to a String. The integer will be
     * represented in base 10. If the integer is negative, an ASCII minus
     * character ('-', U+002D) will be prepended to the value. If the value is
     * not negative, no sign will be prepended. If integer is equal to 0, a
     * single ASCII 0 will be used (U+0030). The String will match the regex
     * @c (0|-?[1-9][0-9]+).
     * @param l A 64-bit signed integer.
     */
    String(const int64_t l);
    /**
     * Converts a 64-bit unsigned integer to a String. The integer will be
     * represented in base 10. If integer is equal to 0, a  single ASCII 0 will
     * be used (U+0030). The String will match the regex
     * @c (0|[1-9][0-9]+).
     * @param l A 64-bit unsigned integer.
     */
    String(const uint64_t l);
    /**
     * Converts a floating point number to a String. The float will be
     * represented in base 10. The exact conversion method is mentioned below.
     * All characters are encoded in pure ASCII.
     * <ul>
     * <li>If this floating point number represents NaN (not a number) according
     * to the IEEE 754 floating point standard, in other words, if it is equal
     * to the result of the division 0.0/0.0, it will convert to the literal
     * string @c "NaN".</li>
     * <li>For all other values, a string composed of a sign character and a
     * magnitude (absolute value) will be created. For a negative value, the
     * minus sign ('-', U+002D) will be prepended. For a positive value, no
     * sign will be prepended. The magnitude is composed as following:</li>
     * <ul>
     * <li>If the magnitude is infinity, i.e. if it is the result
     * of a division of any non-zero value by zero, the literal string
     * "Infinity" will be produced. In case of a negative infinity (produced if
     * either one of the operands, but not both, are negative), as per the above
     * rule the literal string "-Infinity" will be produced.</li>
     * <li>If the magnitude is an integer, i.e. there is no decimal fraction,
     * the actual conversion will be done by the integer conversion algorithm.
     * </li>
     * <li>If the magnitude is greater than or equal to 10<sup>-4</sup>, but
     * less than 10<sup>7</sup> then it is represented as the integer part
     * in decimal form with no leading zeroes, followed by a dot ('.', U+002E),
     * followed by up to 8 digits representing the fractional part. No trailing
     * zeroes will be put in the resulting string.</li>
     * <li>If the magnitude is greater than or equal to 10<sup>7</sup>, or less
     * than 10<sup>-4</sup>, the number will be represented in scientific
     * notation. It is composed of a single significant digit, followed by an
     * optional decimal fraction and an exponent. The decimal fraction consists
     * of a dot ('.', U+002E) and up to 8 significant digits without trailing
     * zeroes. The exponent is of the form @c eN, where N is a integer,
     * optionally with a minus sign for a negative exponent.</li>
     * </ul></li></ul><p>
     * The resulting String will match the regex @c
     * -?(Infinity|[0-9]*(\.[0-9]{7}[1-9])?(e-?[0-9]*)?) .
     * @param f A floating point number to a String.
     */
    String(const float f);
    /**
     * Converts a double-width floating point number to a String. The double
     * will be represented in base 10. The exact conversion method is mentioned
     * below. All characters are encoded in pure ASCII.
     * <ul>
     * <li>If this floating point number represents NaN (not a number) according
     * to the IEEE 754 floating point standard, in other words, if it is equal
     * to the result of the division 0.0/0.0, it will convert to the literal
     * string @c "NaN".</li>
     * <li>For all other values, a string composed of a sign character and a
     * magnitude (absolute value) will be created. For a negative value, the
     * minus sign ('-', U+002D) will be prepended. For a positive value, no
     * sign will be prepended. The magnitude is composed as following:</li>
     * <ul>
     * <li>If the magnitude is infinity, i.e. if it is the result
     * of a division of any non-zero value by zero, the literal string
     * "Infinity" will be produced. In case of a negative infinity (produced if
     * either one of the operands, but not both, are negative), as per the above
     * rule the literal string "-Infinity" will be produced.</li>
     * <li>If the magnitude is an integer, i.e. there is no decimal fraction,
     * the actual conversion will be done by the integer conversion algorithm.
     * </li>
     * <li>If the magnitude is greater than or equal to 10<sup>-4</sup>, but
     * less than 10<sup>7</sup> then it is represented as the integer part
     * in decimal form with no leading zeroes, followed by a dot ('.', U+002E),
     * followed by up to 16 digits representing the fractional part. No trailing
     * zeroes will be put in the resulting string.</li>
     * <li>If the magnitude is greater than or equal to 10<sup>7</sup>, or less
     * than 10<sup>-4</sup>, the number will be represented in scientific
     * notation. It is composed of a single significant digit, followed by an
     * optional decimal fraction and an exponent. The decimal fraction consists
     * of a dot ('.', U+002E) and up to 16 significant digits without trailing
     * zeroes. The exponent is of the form @c eN, where N is a integer,
     * optionally with a minus sign for a negative exponent.</li>
     * </ul></li></ul><p>
     * The resulting String will match the regex @c
     * -?(Infinity|[0-9]*(\.[0-9]{15}[1-9])?(e-?[0-9]*)?) .
     * @param d A double-width floating point number.
     */
    String(const double d);
    /**
     * Default destructor. If this String is sharing data with any other
     * Strings, it will not release this data until no Strings refer to this
     * data anymore.
     */
    virtual ~String();

    /**
     * Returns the length of this String. The length is equal to the amount of
     * UTF-16 characters in this String. Therefore, the returned value is
     * 1-based.
     * @return The amount of characters in this String.
     */
    std::size_t length() const;

    /**
     * Checks whether this string is empty.
     *
     * This is the same as checking if the length of this string is 0.
     * 
     * @return true if the string is empty, false otherwise.
     */
    bool empty() const { return length() == 0; }

    /**
     * Returns the character at the specified index. The index is 0-based and
     * has a maximal value of length() - 1.
     * @throw ArrayException if <code>idx > length() - 1</code>.
     * @param idx the index of the character to return
     * @return the character at the specified index, in UTF-16.
     */
    uchar at(sidx_t idx) const throw(ArrayException);

    /**
     * Converts the String to ASCII. The conversion algorithm goes as follows:
     * <ul>
     * <li>For every unicode character < U+007F, which can be represented in
     * pure ASCII, the character is copied into the returned buffer</li>
     * <li>Every other character will be replaced by a question mark literal
     * ('?', U+003F) in the returned buffer.</li>
     * </ul>
     * The returned buffer is null-terminated, and does not contain excess
     * space. It is not managed by LibSylph, you need to delete it yourself.
     * Future versions may change this behaviour, and manage the buffer with
     * LibSylph's garbage collector.
     * @return A c-style string with pure ASCII characters only.
     */
    const char * ascii() const;
    /**
     * Converts the String to UTF-8. This is the default conversion algorithm
     * for implicit conversion to C string. Each UTF-16 character will be
     * represented as its UTF-8 counterpart. The length of the returned buffer
     * is in the best case (i.e. pure ASCII) <code>length() + 1</code>; in the
     * worst case (i.e CJK or other high Unicode characters) it's
     * <code>3 * length() + 1</code>.</p>
     * The returned buffer is null-terminated, and does not contain excess
     * space. It is not managed by LibSylph, you need to delete it yourself.
     * Future versions may change this behaviour, and manage the buffer with
     * LibSylph's garbage collector.
     * @return A c-style Unicode string encoded in UTF-8.
     */
    const char* utf8() const;

    /**
     * Returns an UTF-16 representation of this String. Because String uses
     * UTF-16 internally, it will simply return a copy of the internal buffer.
     * The returned value is not null-terminated. The length of the returned
     * Array is equal to the length of the String. You cannot use this Array
     * to modify the interal buffer directly, for that would make data sharing
     * impossible (as all Strings that share data would be modified). Instead,
     * use a StringBuffer or an Array<uchar>.
     * @return An Array<uchar> with the UTF-16 encoded String in it.
     */
    const Array<uchar> utf16() const;

    /**
     * Converts the String to lower case. The exact contents of the lower case
     * string are dependant on the characters and the locale used, the resulting
     * string may be shorter or longer than the original.
     * @return A lower case version of this String
     */
    String toLowerCase() const;

    /**
     * Converts the String to upper case. The exact contents of the upper case
     * string are dependant on the characters and the locale used, the resulting
     * string may be shorter or longer than the original.
     * @return An upper case version of this String
     */
    String toUpperCase() const;

    /**
     * Compares two strings ignoring differencies in case. This is the same as
     * <code>s.toLowerCase() == t.toLowerCase()</code>.
     * @param other A string to compare to
     * @return @em true if both Strings are equal ignoring case, @em false
     * otherwise.
     */
    bool equalsIgnoreCase(const String other) const;

    /**
     * Checks if the string ends with the given suffix.
     * @param other A suffix to test for.
     * @return Wheter the string ends in given suffix.
     */
    bool endsWith(const String other) const;

    /**
     * Checks if the string ends with the given prefix.
     * @param other A prefix to test for.
     * @return Wheter the string ends in given prefix.
     */
    bool startsWith(const String other) const;

    /**
     * Checks if the string contains the given substring.
     * @param other A substring to test for.
     * @return Wheter the contains the given substring.
     */
    bool contains(const String other) const;

    /**
     * Removes all whitespace characters on the front and on the end of the
     * String. Whitespace characters are defined in the array @c spacechars.
     * @return The trimmed string.
     */
    String trim() const;

    /**
     * Tokenizes a string with a given set of delimiters. This will split a
     * String into tokens, with as boundary any character given in the array.
     * Empty strings will not be included in the array.
     * @param delimiters A set of delimiters, by default equal to @c spacechars.
     * @return An array of Strings, containing each token.
     */
    Array<String> split(Array<uchar> delimiters = spacechars) const;

    /**
     * Returns a new String containing all characters from the given index to
     * the end of the String. The index is 0-based. The length of the new
     * String will be equal to <code>length() - begin - 1</code>.
     * @param begin The first index of where to cut the substring.
     * @return A string containing all characters from the given begin index.
     * @throw ArrayException if <code>begin >= length()</code>.
     */
    String substring(idx_t begin) const throw(ArrayException);

    /**
     * Returns a new String containing all characters from the given begin index
     * up to and including the given end index. The indices are 0-based. The
     * length of the new String will be equal to <code>end - begin - 1</code>.
     * @param begin The first index of where to cut the substring.
     * @param end The last index to where to cut the substring.
     * @return A string containing all characters from the given begin index to
     * the given end index.
     * @throw ArrayException if <code>begin >= length() || end >= length() ||
     * begin > end</code>.
     */
    String substring(idx_t begin, idx_t end) const
            throw(ArrayException);

    /**
     * Returns the first index from given start index in this String on which
     * the specified substring occurs. The index is 0-based.
     * @param substr The substring to search for.
     * @param start The first index to start looking for.
     * @return If the substring occurs in this String, then the index of the
     * first character of that substring is returned, else -1 is returned.
     * @throw ArrayException if <code>start >= length()</code>
     */
    sidx_t indexOf(const String substr, idx_t start = 0) const
            throw(ArrayException);

    /**
     * Returns the last index in this String on which the specified substring
     * occurs. The index is 0-based.
     * @param substr The substring to search for.
     * @return If the substring occurs in this String, then the index of the
     * first character of that substring is returned, else -1 is returned.
     */
    sidx_t lastIndexOf(const String substr) const;

    /**
     * Returns the last index in this String up to given end index
     * on which the specified substring  occurs. The index is 0-based.
     * @param substr The substring to search for.
     * @param end The last position to search on.
     * @return If the substring occurs in this String, then the index of the
     * first character of that substring is returned, else -1 is returned.
     * @throw ArrayException if <code>end >= length()</code>
     */
    sidx_t lastIndexOf(const String substr, idx_t end) const
            throw(ArrayException);

    String copy() const;
    bool merge(String other) const;

    /**
     * Creates a string from a hexadecimal number. The returned string will
     * match the regex <code>0[xX][0-9a-fA-F]+</code>.
     * @param i The integer value to create the string from.
     * @param up Whether to use uppercase alphabetic characters. This will turn
     * all alphabetic characters (@c A through @c F and @c X ) uppercase.
     * @return A string representing the given value in hex.
     */
    static String fromHex(int i, bool up);

    /**
     * Creates a string from a octal number. The returned string will match the
     * regex <code>0[0-9]+</code>.
     * @param i The integer value to create the string from.
     * @return A string representing the given value in octal.
     */
    static String fromOct(int i);

    /**
     * Creates a string from given float in scientific notation. The returned
     * string will match the regex <code>[0-9]+[eE]-?[0-9]{1,2}</code>.
     * Trailing zeroes will not be removed.
     * @param f A float to represent in scientific notation
     * @param up Whether to print the exponentional @c E in upper case.
     */
    static String fromSci(float f, bool up);

    /**
     * Creates a string from given double in scientific notation. The returned
     * string will match the regex <code>[0-9]+[eE]-?[0-9]{1,2}</code>.
     * Trailing zeroes will not be removed.
     * @param d A double to represent in scientific notation
     * @param up Whether to print the exponentional @c E in upper case.
     */
    static String fromSci(double d, bool up);

    /**
     * Interprets this string as a bool.
     * @return <i>true</i> iff this string equals ignoring case either
     * <code>"true"</code>, <code>"yes"</code>, </code>"on"</code> or
     * <code>"1</code>, false otherwise.
     */
    bool boolValue() const;

    /**
     * Interprets this string as a signed 32-bit integer. The string has to
     * match the regex <code>-?[0-9]+</code> after removing leading and trailing
     * whitespace.
     * @return The value of the integer interpreting this String in base 10. If
     * the String does not match the given regex, 0 is returned.
     */
    int32_t intValue() const;

    /**
     * Interprets this string as an unsigned 32-bit integer. The string has to
     * match the regex <code>[0-9]+</code> after removing leading and trailing
     * whitespace.
     * @return The value of the integer interpreting this String in base 10. If
     * the String does not match the given regex, 0 is returned.
     */
    uint32_t uintValue() const;

    /**
     * Interprets this string as a signed 64-bit integer. The string has to
     * match the regex <code>-?[0-9]+</code> after removing leading and trailing
     * whitespace.
     * @return The value of the integer interpreting this String in base 10. If
     * the String does not match the given regex, 0 is returned.
     */
    int64_t longValue() const;

    /**
     * Interprets this string as an unsigned 64-bit integer. The string has to
     * match the regex <code>[0-9]+</code> after removing leading and trailing
     * whitespace.
     * @return The value of the integer interpreting this String in base 10. If
     * the String does not match the given regex, 0 is returned.
     */
    uint64_t ulongValue() const;
    float floatValue() const;
    double doubleValue() const;

    inline bool toBool() const {
        return !empty();
    }

    const String & operator=(const char * orig) const;
    const String & operator=(const std::string & orig) const;
    const String & operator=(const String orig)const;

    /**
     * Appends given String to this String. The internally shared data will be
     * replaced by the new String, its reference count will be decreased by
     * one and deleted if it reaches zero.
     * @param rhs The String to append
     * @return This String, with the new part appended to it.
     */
    const String& operator+=(const String rhs) const;


    /**
     * Converts this String to a C-style array of chars. This is equivalent to
     * <code>utf8()</code>. This conversion operator allows for passing
     * Strings to functions expecting C-style strings without explicit
     * conversion.
     * @return A C-style string according to @c utf8().
     */
    operator const char *() const;

    /**
     * Converts this String to a Standard Library string. This will effectively
     * convert it to a C-style string encoded in UTF-8 and construct a
     * @c std::string from that.
     * @return A Standard Library string with the same contents as this String.
     */
    operator std::string() const;

private:
    void fromAscii(const char* ascii) const;
    void fromUtf8(const char* unicode) const;

    struct Data {

        Data(size_t len) : data(len), refcount(1) { }

        virtual ~Data() { }
        Array<uchar> data;
        mutable std::size_t refcount;
    };
    mutable Data* strdata;

};

bool operator==(const String lhs, const String rhs);

/**
 * Overridden version of Hash<T> for String.
 * @todo Explain how it works.
 */
template<>
struct Hash<String> {

    inline int32_t operator()(String s) const {
        uint32_t hash = 0;
        uint32_t x = 0;
        uint32_t i = 0;
        uchar * b = s.strdata->data.carray();

        for(i = 0; i < s.length(); b++, i++) {
            hash = (hash << 4) + (*b);
            if((x = hash & 0xF0000000L) != 0) {
                hash ^= (x >> 24);
            }
            hash &= ~x;
        }

        return hash;
    }
};

inline bool operator==(const String lhs, const char* rhs) {
    return operator==(lhs, String(rhs));
}

inline bool operator==(const char* rhs, const String lhs) {
    return operator==(String(rhs), lhs);
}
bool operator<(const String lhs, const String rhs);
inline bool operator<(const String lhs, const char* rhs) {
    return lhs < String(rhs);
}
inline bool operator<(const char* lhs, const String rhs) {
    return String(lhs) < rhs;
}
String operator+(const String lhs, const String rhs);
//String operator%(const String lhs, const String rhs);
String operator&(const String lhs, String(*rhs)(const String));
String operator&(String(*lhs)(const String), const String rhs);
String operator*(const String lhs, const std::size_t len);
std::ostream & operator<<(std::ostream& lhs, const String rhs);

String lc(const String rhs);
String uc(const String rhs);
String t(const String rhs);

S_CMP_SEQ(const String)
S_CMP_SEQ_2(const String,const char*)

SYLPH_END_NAMESPACE

#endif /* SYLPH_CORE_STRING_H_ */

// vim: ts=4:sts=4:sw=4:sta:et:tw=80:nobk
